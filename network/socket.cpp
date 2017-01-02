#include "socket.h"

Socket::Socket()
   : m_socket(NULL),
     m_socketState(SocketState::UNINITIALIZED)
{
}

Socket::~Socket()
{
}

Socket::SocketResult Socket::createSocket(struct addrinfo& addressInfo, Socket& outSocket)
{
   SocketResult socketResult;
   outSocket.m_socket = socket(addressInfo.ai_family, addressInfo.ai_socktype, addressInfo.ai_protocol);
   if (outSocket.m_socket == INVALID_SOCKET)
   {
      socketResult.m_error = SocketError::ERROR_CREATE;
      socketResult.m_internalError = WSAGetLastError();
   }
   return socketResult;
}

Socket::SocketResult Socket::createSocket(SocketCreationType socketCreationType, struct addrinfo* addressInfo, Socket& outSocket)
{
   SocketResult socketResult;
   switch (socketCreationType)
   {
      case SocketCreationType::ACCEPT_INCOMING_CONNECTIONS:
      {
         socketResult = createSocket(*addressInfo, outSocket);
         if (outSocket.m_socket != INVALID_SOCKET)
         {
            int bindResult = bind(outSocket.m_socket, addressInfo->ai_addr, addressInfo->ai_addrlen);
            if (bindResult == SOCKET_ERROR)
            {
               socketResult.m_error = SocketError::ERROR_BIND;
               socketResult.m_internalError = WSAGetLastError();
               closesocket(outSocket.m_socket);
            }

            outSocket.m_socketState = Socket::SocketState::BINDED;
         }

         break;
      }
      case SocketCreationType::CONNECT:
      {
         struct addrinfo *currentAddressInfo = nullptr;

         // Attempt to connect to an address until one succeeds
         for (currentAddressInfo = addressInfo; currentAddressInfo != nullptr; currentAddressInfo = currentAddressInfo->ai_next)
         {
            // Create a SOCKET for connecting
            socketResult = createSocket(*currentAddressInfo, outSocket);
            if (outSocket.m_socket != INVALID_SOCKET)
            {
               int connectResult = connect(outSocket.m_socket, currentAddressInfo->ai_addr, (int)currentAddressInfo->ai_addrlen);
               if (connectResult == SOCKET_ERROR)
               {
                  socketResult.m_error = SocketError::ERROR_CONNECT;
                  socketResult.m_internalError = WSAGetLastError();
                  closesocket(outSocket.m_socket);
                  continue;
               }
               outSocket.m_socketState = Socket::SocketState::CONNECTED;
            }
            break;
         }

         break;
      }
      case SocketCreationType::CONNECTIONLESS:
      default:
      {
         socketResult = createSocket(*addressInfo, outSocket);
         break;
      }
   }

   
   return socketResult;
}

Socket::SocketResult Socket::listenIncomingConnection()
{
   SocketResult socketResult;

   int result = listen(m_socket, SOMAXCONN);
   if (result == SOCKET_ERROR)
   {
      socketResult.m_error         = SocketError::ERROR_LISTEN;
      socketResult.m_internalError = WSAGetLastError();
      close();
   }
   else
   {
      m_socketState = SocketState::LISTENING;
   }

   return socketResult;
}

Socket::SocketResult Socket::acceptIncomingConnection()
{
   SocketResult socketResult;
   SOCKET previousInternalSocket = m_socket;

   SOCKET clientsocket = accept(m_socket, nullptr, nullptr);
   if (clientsocket == INVALID_SOCKET)
   {
      socketResult.m_error         = SocketError::ERROR_LISTEN;
      socketResult.m_internalError = WSAGetLastError();
      m_socket = NULL;
      m_socketState = SocketState::UNINITIALIZED;
   }
   else
   {
      m_socket      = clientsocket;
      m_socketState = SocketState::CONNECTED;
   }

   if (previousInternalSocket)
   {
      closesocket(previousInternalSocket);
   }

   return socketResult;
}

Socket::SocketResult Socket::receiveBytes(char* buffer, int bufferLength, int& outNumberReceivedBytes)
{
   SocketResult socketResult;
   outNumberReceivedBytes = 0;

   int recvResult = recv(m_socket, buffer, bufferLength, 0);

   if (recvResult == SOCKET_ERROR)
   {
      socketResult.m_error         = SocketError::ERROR_RECEIVE;
      socketResult.m_internalError = WSAGetLastError();
      close();
   }
   else
   {
      outNumberReceivedBytes = recvResult;
   }

   return socketResult;
}

Socket::SocketResult Socket::sendBytes(const char* buffer, int bufferLength, int& outNumberSentBytes)
{
   SocketResult socketResult;
   outNumberSentBytes = 0;

   int sendResult = send(m_socket, buffer, bufferLength, 0);

   if (sendResult == SOCKET_ERROR)
   {
      socketResult.m_error         = SocketError::ERROR_SEND;
      socketResult.m_internalError = WSAGetLastError();
      close();
   }
   else
   {
      outNumberSentBytes = sendResult;
   }

   return socketResult;
}

Socket::SocketResult Socket::getAddressFamily(int& outputAddressFamily)
{
    SocketResult socketResult;

    char optval[1024];
    int optlen = sizeof(optval);

    int getSocketOptionResult = getsockopt(m_socket, (int)SOL_SOCKET, (int)SO_PROTOCOL_INFO, optval, &optlen);
    if (getSocketOptionResult == SOCKET_ERROR)
    {
        socketResult.m_error = SocketError::ERROR_GET_SOCKET_OPTION;
        socketResult.m_internalError = WSAGetLastError();
        close();
    }
    else
    {
        LPWSAPROTOCOL_INFO addressInfo = (LPWSAPROTOCOL_INFO)optval;
        outputAddressFamily = addressInfo->iAddressFamily;
    }

    return socketResult;
}

Socket::SocketResult Socket::sendDatagram(const char* buffer, int bufferLength, unsigned short port, const char* address, int& outNumberSentBytes)
{
    SocketResult socketResult;
    outNumberSentBytes = 0;

    int addressFamily = 0;
    socketResult = getAddressFamily(addressFamily);

    if (socketResult.m_error == SocketError::NONE)
    {
        sockaddr_in receivingAddress;
        receivingAddress.sin_family = addressFamily;
        receivingAddress.sin_port = htons(port);
        receivingAddress.sin_addr.s_addr = inet_addr(address);

        int sendResult = sendto(m_socket, buffer, bufferLength, 0, (SOCKADDR *)& receivingAddress, sizeof(receivingAddress));
        if (sendResult == SOCKET_ERROR)
        {
            socketResult.m_error = SocketError::ERROR_SEND_DATAGRAM;
            socketResult.m_internalError = WSAGetLastError();
            close();
        }
        else
        {
            outNumberSentBytes = sendResult;
        }
    }

    return socketResult;
}

Socket::SocketResult Socket::shutdownOperation(SocketOperation socketOperation)
{
   SocketResult socketResult;

   int operation = SD_RECEIVE;

   switch (socketOperation)
   {
      case SocketOperation::SEND:
      {
         operation = SD_SEND;
         break;
      }
      case SocketOperation::SEND_AND_RECEIVE:
      {
         operation = SD_BOTH;
         break;
      }
   }

   int shutdownResult = shutdown(m_socket, operation);

   if (shutdownResult == SOCKET_ERROR)
   {
      socketResult.m_error         = SocketError::ERROR_SHUTDOWN;
      socketResult.m_internalError = WSAGetLastError();
      close();
   }
   else
   {
      m_socketState = SocketState::SHUTDOWN;
   }

   return socketResult;
}

Socket::SocketResult Socket::close()
{
   SocketResult socketResult;

   int closeResult = closesocket(m_socket);

   if (closeResult == SOCKET_ERROR)
   {
      socketResult.m_error         = SocketError::ERROR_CLOSE;
      socketResult.m_internalError = WSAGetLastError();
   }

   m_socket = NULL;
   m_socketState = SocketState::UNINITIALIZED;

   return socketResult;
}
