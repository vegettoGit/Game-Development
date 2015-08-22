#include "network.h"
#include <ws2tcpip.h>

Network::Network()
{
}

Network::~Network()
{
   if (m_networkLayerState == NetworkLayerState::INITIALIZED)
   {
      WSACleanup();
   }
}

Network& Network::getInstance()
{
   static Network networkInstance;
   return networkInstance;
}

Network::NetworkResult Network::initialize()
{
   NetworkResult result;

   if (m_networkLayerState == NetworkLayerState::NONE)
   {
      int socketsResult = WSAStartup(MAKEWORD(2, 2), &m_wsaData);

      if (socketsResult != 0)
      {
         result.m_error = NetworkError::ERROR_INITIALIZATION_SOCKETS;
         result.m_internalError = socketsResult;
      }
      else
      {
         m_networkLayerState = NetworkLayerState::INITIALIZED;
      }
   }
   else
   {
      result.m_error = NetworkError::ERROR_NETWORK_ALREADY_INITIALIZED;
   }

   return result;
}

Network::NetworkResult Network::getAddressInfo(const char* hostName, const char* serviceName, NetworkAddressType addressType, NetworkProtocol protocol, Socket::SocketCreationType socketCreationType, struct addrinfo*& outAddressInfo)
{
   NetworkResult result;
   
   struct addrinfo hints;

   result.m_error = buildAddressInfo(addressType, protocol, socketCreationType, hints);

   if (result.m_error == NetworkError::NONE)
   {
      // Resolve the server address and port
      result.m_internalError = getaddrinfo(hostName, serviceName, &hints, &outAddressInfo);
      if (result.m_internalError != 0)
      {
         result.m_error = NetworkError::ERROR_GET_ADDRESS_INFO;
      }
   }

   return result;
}


Network::NetworkError Network::buildAddressInfo(NetworkAddressType addressType, NetworkProtocol protocol, Socket::SocketCreationType socketCreationType, struct addrinfo& outAddressInfo)
{
   NetworkError result = NetworkError::NONE;

   ZeroMemory(&outAddressInfo, sizeof(outAddressInfo));

   switch (addressType)
   {
      case NetworkAddressType::IPv4:
      {
         outAddressInfo.ai_family = AF_INET;
         break;
      }
      case NetworkAddressType::IPv6:
      {
         outAddressInfo.ai_family = AF_INET6;
         break;
      }
      default:
      {
         result = NetworkError::ERROR_WRONG_GET_ADDRESS_INFO_INPUT;
         break;
      }
   }

   if (result == NetworkError::NONE)
   {
      switch (protocol)
      {
         case NetworkProtocol::TCP:
         {
            outAddressInfo.ai_socktype = SOCK_STREAM;
            outAddressInfo.ai_protocol = IPPROTO_TCP;
            break;
         }
         case NetworkProtocol::UDP:
         {
            outAddressInfo.ai_socktype = SOCK_DGRAM;
            outAddressInfo.ai_protocol = IPPROTO_UDP;
            break;
         }
         default:
         {
            result = NetworkError::ERROR_WRONG_GET_ADDRESS_INFO_INPUT;
            break;
         }
      }
   }

   if (result == NetworkError::NONE)
   {
      switch (socketCreationType)
      {
         case Socket::SocketCreationType::ACCEPT_INCOMING_CONNECTIONS:
         {
            outAddressInfo.ai_flags = AI_PASSIVE;
            break;
         }
         case Socket::SocketCreationType::CONNECT:
         {
            break;
         }
         default:
         {
            result = NetworkError::ERROR_WRONG_GET_ADDRESS_INFO_INPUT;
            break;
         }
      }
   }

   return result;
}

Network::NetworkResult Network::createSocket(const char* hostName, const char* serviceName, NetworkAddressType addressType, NetworkProtocol protocol, Socket::SocketCreationType socketCreationType, Socket& outSocket)
{
   NetworkResult result;

   if (m_networkLayerState != NetworkLayerState::INITIALIZED)
   {
      result.m_error = NetworkError::ERROR_NETWORK_UNINITIALIZED;
      return result;
   }

   // Resolve the host address and port
   struct addrinfo* addressInfo = nullptr;
   result = Network::getInstance().getAddressInfo(hostName, serviceName, addressType, protocol, socketCreationType, addressInfo);

   if (result.m_error == NetworkError::NONE)
   {
      Socket::SocketResult socketResult = Socket::createSocket(socketCreationType, addressInfo, outSocket);
      if (socketResult.m_error != Socket::SocketError::NONE)
      {
         result.m_error = NetworkError::ERROR_SOCKET_CREATION;

         switch (socketResult.m_error)
         {
            case Socket::SocketError::ERROR_BIND:
            {
               result.m_error = NetworkError::ERROR_SOCKET_BINDING;
               break;
            }
            case Socket::SocketError::ERROR_CONNECT:
            {
               result.m_error = NetworkError::ERROR_SOCKET_CONNECTING;
               break;
            }
         }

         result.m_internalError = socketResult.m_internalError;
      }
      
      freeaddrinfo(addressInfo);
   }

   return result;
}

