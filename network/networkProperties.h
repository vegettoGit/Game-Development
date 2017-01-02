/* 
   Various network properties to be used by our sample network tests
*/

#include "network.h"

struct NetworkProperties
{

   static const Network::NetworkAddressType s_networkAddressType        = Network::NetworkAddressType::IPv4;
   static const int                         s_defaultSocketBufferLength = 512;

   static const char*                       s_localHost;
   static const char*                       s_serverAddress;
   static const unsigned int                s_defaultPort;
};


