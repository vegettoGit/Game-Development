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
   Socket             ();

   Socket             (const Socket& )  = delete;
   Socket& operator = (const Socket& v) = delete;

   Socket             (Socket&& )       = delete;
   Socket& operator = (Socket&& v)      = delete;

   ~Socket            ();

   SOCKET  m_socket;
};

#endif
