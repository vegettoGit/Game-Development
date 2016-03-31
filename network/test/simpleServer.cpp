
#include "simpleServer.h"
#include "networkProperties.h"

SimpleServer::SimpleServer()
   : m_serverState(ServerState::NONE)
{
}

SimpleServer::~SimpleServer()
{
}

void SimpleServer::createWork()
{
   m_serverState = ServerState::INITIALIZE;

   // Initialize the network and create a socket
   m_initializeTask = async([&]
   { 
      Network::NetworkResult networkResult = Network::getInstance().initialize();
      if (networkResult.m_error != Network::NetworkError::NONE)
      {
         setError("Initialization of Network Layer failed with error", networkResult.m_internalError);
      }
      else
      {
         m_serverState = ServerState::CREATE;
         networkResult = Network::getInstance().createSocket(NULL, 
                                                             NetworkProperties::s_defaultPort, 
                                                             NetworkProperties::s_networkAddressType, 
                                                             Network::NetworkProtocol::TCP, 
                                                             Socket::SocketCreationType::ACCEPT_INCOMING_CONNECTIONS, 
                                                             m_socket);

         if (networkResult.m_error != Network::NetworkError::NONE)
         {
            setError("Error creating or binding socket", networkResult.m_internalError);
         }
      }

      return networkResult;
   });

   // Listen until we accept an incoming connection
   m_listenTask = m_initializeTask.then([&](const Network::NetworkResult networkResult)
   {
      Socket::SocketResult socketResult;

      if (networkResult.m_error == Network::NetworkError::NONE)
      {
         m_serverState = ServerState::LISTEN;
         socketResult = m_socket.listenIncomingConnection();
         if (socketResult.m_error != Socket::SocketError::NONE)
         {
            setError("Listen failed with error", socketResult.m_internalError);
         }
         else
         {
            m_serverState = ServerState::ACCEPT;
            socketResult = m_socket.acceptIncomingConnection();

            if (socketResult.m_error != Socket::SocketError::NONE)
            {
               setError("Accept failed with error", socketResult.m_internalError);
            }
         }
      }

      return socketResult;
   });
      
   // Receive bytes until the client shuts down the connection
   m_receiveTask = m_listenTask.then([&](const Socket::SocketResult result)
   {
      Socket::SocketResult socketResult;

      if (socketResult.m_error == Socket::SocketError::NONE)
      {
         char recvbuf[NetworkProperties::s_defaultSocketBufferLength];
         int  recvbuflen = NetworkProperties::s_defaultSocketBufferLength;
         
         m_serverState = ServerState::RECEIVE;

         int numberReceivedBytes = 0;
         do
         {
            socketResult = m_socket.receiveBytes(recvbuf, recvbuflen, numberReceivedBytes);
            if (numberReceivedBytes > 0)
            {
               setLastReceivedText(recvbuf, numberReceivedBytes);
               
               // Echo the buffer back to the sender
               int numberSentBytes = 0;
               socketResult = m_socket.sendBytes(recvbuf, recvbuflen, numberSentBytes);
               if (numberSentBytes == 0)
               {
                  setError("Send echo failed with error", socketResult.m_internalError);
                  return socketResult;
               }
               else
               {
                  setLastSentText(recvbuf, numberReceivedBytes);
               }
            }
            else if (numberReceivedBytes == 0)
            {
               m_serverState = ServerState::CLOSE;
            }
            else
            {
               setError("Receive failed with error", socketResult.m_internalError);
               return socketResult;
            }
         } while (numberReceivedBytes > 0);

         m_serverState = ServerState::SHUT_DOWN;
         socketResult = m_socket.shutdownOperation(Socket::SocketOperation::SEND);

         if (socketResult.m_error != Socket::SocketError::NONE)
         {
            setError("Shutdown failed with error", socketResult.m_internalError);
         }
         else
         {
            socketResult = m_socket.close();
            if (socketResult.m_error != Socket::SocketError::NONE)
            {
               setError("Error closing socket", socketResult.m_internalError);
            }
         }
      }

      return socketResult;
   });
}

SimpleServer::ServerState SimpleServer::getServerState() const
{
   return m_serverState;
}

void SimpleServer::setError(const char* text, int error)
{
   ISimplePeer::setError(text, error);

   m_serverState = ServerState::SERVER_ERROR;
}
