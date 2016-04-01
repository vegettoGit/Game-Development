
#include "simpleClient.h"
#include "networkProperties.h"

SimpleClient::SimpleClient()
   : m_clientState(ClientState::NONE)
{
}

SimpleClient::~SimpleClient()
{
}

void SimpleClient::createWork()
{
   m_clientState = ClientState::INITIALIZE;

   // Initialize the network and create a socket for connecting to the server
   m_initializeTask = async([&]
   { 
      Network::NetworkResult networkResult = Network::getInstance().initialize();
      if (networkResult.m_error != Network::NetworkError::NONE)
      {
         setError("Initialization of Network Layer failed with error", networkResult.m_internalError);
      }
      else
      {
         m_clientState = ClientState::CREATE;

         networkResult = Network::getInstance().createSocket(NetworkProperties::s_serverAddress, 
                                                             NetworkProperties::s_defaultPort,
                                                             NetworkProperties::s_networkAddressType, 
                                                             Network::NetworkProtocol::TCP, 
                                                             Socket::SocketCreationType::CONNECT, 
                                                             m_socket);

         if (networkResult.m_error != Network::NetworkError::NONE)
         {
            setError("Error creating or binding socket for connecting to server", networkResult.m_internalError);
         }
      }

      return networkResult;
   });
      
   // Send bytes, receive echo bytes, then close the connection
   m_sendTask = m_initializeTask.then([&](const Network::NetworkResult networkResult)
   {
      Socket::SocketResult socketResult;
      if (networkResult.m_error == Network::NetworkError::NONE)
      {
         m_textToSend.append("This is a test");

         m_clientState = ClientState::SEND;

         while (m_clientState == ClientState::SEND)
         {
            if (m_textToSend.size() > 0)
            {
               int numberSentBytes = 0;
               socketResult = m_socket.sendBytes(m_textToSend.c_str(), m_textToSend.size(), numberSentBytes);
               if (numberSentBytes == 0)
               {
                  setError("Error sending bytes to the server", socketResult.m_internalError);
                  break;
               }
               else
               {
                  setLastSentText(m_textToSend.c_str(), numberSentBytes);
                  
                  char recvbuf[NetworkProperties::s_defaultSocketBufferLength];
                  int  recvbuflen = NetworkProperties::s_defaultSocketBufferLength;

                  int numberReceivedBytes = 0;

                  socketResult = m_socket.receiveBytes(recvbuf, recvbuflen, numberReceivedBytes);
                  
                  if (numberReceivedBytes < 0)
                  {
                     setError("Error receiving echo bytes from the server", socketResult.m_internalError);
                     break;
                  }
                  else
                  {
                     setLastReceivedText(recvbuf, numberReceivedBytes);
                  }
               }

               if (m_textToSend == s_connectionEndText)
               {
                  break;
               }

               m_textToSend.clear();
            }
         }

         m_clientState = ClientState::SHUT_DOWN;
         socketResult = m_socket.shutdownOperation(Socket::SocketOperation::SEND);
         if (socketResult.m_error != Socket::SocketError::NONE)
         {
            setError("Error shutting down sending operation", socketResult.m_internalError);
         }
         else
         { 
            m_clientState = ClientState::CLOSE;
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

void SimpleClient::setError(const char* text, int error)
{
   ISimplePeer::setError(text, error);

   m_clientState = ClientState::CLIENT_ERROR;
}

SimpleClient::ClientState SimpleClient::getClientState() const
{
   return m_clientState;
}

void SimpleClient::setTextToSend(std::string& sendText)
{
   m_textToSend = sendText;
}

