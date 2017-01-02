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
      ERROR_CONNECT,
      ERROR_LISTEN,
      ERROR_ACCEPT,
      ERROR_RECEIVE,
      ERROR_SEND,
      ERROR_SEND_DATAGRAM,
      ERROR_SHUTDOWN,
      ERROR_CLOSE,
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

   enum class SocketCreationType
   {
      ACCEPT_INCOMING_CONNECTIONS,
      CONNECT,
      CONNECTIONLESS
   };

   enum class SocketState
   {
      UNINITIALIZED,
      BINDED,
      LISTENING,
      CONNECTED,
      SHUTDOWN
   };

   enum class SocketOperation
   {
      NONE,
      SEND,
      RECEIVE,
      SEND_AND_RECEIVE
   };

   Socket             ();

   Socket             (const Socket&)  = delete;
   Socket& operator = (const Socket&)  = delete;

   Socket             (Socket&&)       = delete;
   Socket& operator = (Socket&&)       = delete;

   ~Socket            ();
   
   SocketResult listenIncomingConnection ();
   SocketResult acceptIncomingConnection ();

   // Connection based
   SocketResult receiveBytes(char* buffer, int bufferLength, int& outNumberReceivedBytes);
   SocketResult sendBytes   (const char* buffer, int bufferLength, int& outNumberSentBytes);

   // Connectionless
   SocketResult sendDatagram(const char* buffer, int bufferLength, unsigned short port, const char* address, int& outNumberSentBytes);

   SocketResult shutdownOperation(SocketOperation operation);
   SocketResult close            ();

   SOCKET       m_socket;
   SocketState  m_socketState;


private:

   friend class Network;
   static SocketResult createSocket(SocketCreationType socketCreationType, struct addrinfo* addressInfo, Socket& outSocket);
   static SocketResult createSocket(struct addrinfo& addressInfo, Socket& outSocket);
};

#endif
