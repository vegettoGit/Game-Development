#include "socket.h"

Socket::Socket()
   : m_socketState(SocketState::UNINITIALIZED)
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
      socketResult.m_error = SocketError::ERROR_LISTEN;
      socketResult.m_internalError = WSAGetLastError();
      closesocket(m_socket);
   }

   return socketResult;
}
