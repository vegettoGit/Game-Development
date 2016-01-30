/* 
   Various network properties to be used by our sample network tests
*/

struct NetworkProperties
{
   static const Network::NetworkAddressType s_networkAddressType        = Network::NetworkAddressType::IPv4;
   static const int                         s_defaultSocketBufferLength = 512;

   // To be defined by application user
   static const char*                       s_defaultPort;
   static const char*                       s_serverAddress;
};


