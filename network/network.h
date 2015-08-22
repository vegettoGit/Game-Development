/* 
   Generic Network class in charge of the configuration of a Network layer built on the Windows OS

   - As many of the following functions are blocking, it is recommended to consider their usage in an
     asynchronous manner.
*/

#include "socket.h"

class Network
{

public:

   enum class NetworkAddressType
   {
      IPv4,
      IPv6
   };

   enum class NetworkProtocol
   {
      TCP,
      UDP
   };

   enum class NetworkError
   {
      NONE,
      ERROR_NETWORK_UNINITIALIZED,
      ERROR_NETWORK_ALREADY_INITIALIZED,
      ERROR_INITIALIZATION_SOCKETS,
      ERROR_WRONG_GET_ADDRESS_INFO_INPUT,
      ERROR_GET_ADDRESS_INFO,
      ERROR_SOCKET_CREATION,
      ERROR_SOCKET_BINDING,
      ERROR_SOCKET_CONNECTING,
      UNKNOWN_ERROR
   };

   enum class NetworkLayerState
   {
      NONE,
      INITIALIZED
   };

   struct NetworkResult
   {
      NetworkResult()
         : m_error        (NetworkError::NONE),
           m_internalError(0)
      {
      }

      NetworkError m_error;
      int          m_internalError;
   };

   static Network&   getInstance          ();
   NetworkResult     initialize           ();
   NetworkResult     createSocket         (const char* hostName, const char* serviceName, NetworkAddressType addressType, NetworkProtocol protocol, Socket::SocketCreationType socketCreationType, Socket& outSocket);

private:

   Network                                ()                         ;

   Network                                (const Network& )  = delete;
   Network&          operator =           (const Network& v) = delete;

   Network                                (Network&& )       = delete;
   Network&          operator =           (Network&& v)      = delete;

   ~Network                               ();
   
   NetworkResult     getAddressInfo       (const char* hostName, const char* serviceName, NetworkAddressType addressType, NetworkProtocol protocol, Socket::SocketCreationType socketCreationType, struct addrinfo*& outAddressInfo);
   NetworkError      buildAddressInfo     (NetworkAddressType addressType, NetworkProtocol protocol, Socket::SocketCreationType socketCreationType, struct addrinfo& outAddressInfo);

   WSADATA           m_wsaData;
   NetworkLayerState m_networkLayerState;

};
