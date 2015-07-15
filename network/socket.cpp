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
   else
   {
      int bindResult = bind(outSocket.m_socket, addressInfo.ai_addr, addressInfo.ai_addrlen);
      if (bindResult == SOCKET_ERROR)
      {
         socketResult.m_error = SocketError::ERROR_BIND;
         socketResult.m_internalError = WSAGetLastError();
         closesocket(outSocket.m_socket);
      }

      outSocket.m_socketState = Socket::SocketState::BINDED;
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
      closesocket(m_socket);
      m_socket      = NULL;
      m_socketState = SocketState::UNINITIALIZED;
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

   socketResult.m_internalError = recv(m_socket, buffer, bufferLength, 0);

   if (socketResult.m_internalError == SOCKET_ERROR)
   {
      socketResult.m_error         = SocketError::ERROR_RECEIVE;
      socketResult.m_internalError = WSAGetLastError();
      closesocket(m_socket);
      m_socket      = NULL;
      m_socketState = SocketState::UNINITIALIZED;
   }
   else
   {
      outNumberReceivedBytes = socketResult.m_internalError;
   }

   return socketResult;
}

Socket::SocketResult Socket::sendBytes(char* buffer, int bufferLength, int& outNumberSentBytes)
{
   SocketResult socketResult;
   outNumberSentBytes = 0;

   socketResult.m_internalError = send(m_socket, buffer, bufferLength, 0);

   if (socketResult.m_internalError == SOCKET_ERROR)
   {
      socketResult.m_error         = SocketError::ERROR_SEND;
      socketResult.m_internalError = WSAGetLastError();
      closesocket(m_socket);
      m_socket = NULL;
      m_socketState = SocketState::UNINITIALIZED;
   }
   else
   {
      outNumberSentBytes = socketResult.m_internalError;
   }

   return socketResult;
}
