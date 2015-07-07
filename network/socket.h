#ifndef NETWORK_SOCKET
#define NETWORK_SOCKET

#include <winsock2.h>

/* 
   Implementation of a Network Socket built on top of Windows Sockets

   - As many of the following functions are blocking, it is recommended to consider their usage in an
     asynchronous manner.
*/
struct Socket
{
   enum class SocketError
   {
      NONE,
      ERROR_CREATE,
      ERROR_BIND,
      ERROR_LISTEN,
      ERROR_ACCEPT,
      UNKNOWN_ERROR
   };

   struct SocketResult
   {
      SocketResult()
         : m_error(SocketError::NONE),
           m_internalError(0)
      {
      }

      SocketError m_error;
      int         m_internalError;
   };

   enum class SocketState
   {
      UNINITIALIZED,
      BINDED,
      LISTENING,
      CONNECTED
   };

   Socket             ();

   Socket             (const Socket& )  = delete;
   Socket& operator = (const Socket& v) = delete;

   Socket             (Socket&& )       = delete;
   Socket& operator = (Socket&& v)      = delete;

   ~Socket            ();
   
   SocketResult listenIncomingConnection ();
   SocketResult acceptIncomingConnection ();

   SOCKET       m_socket;
   SocketState  m_socketState;


private:

   friend class Network;
   static SocketResult createSocket(struct addrinfo& addressInfo, Socket& outSocket);
};

#endif
