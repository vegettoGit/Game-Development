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

Network::NetworkResult Network::getSocketInfo(const char* hostName, const char* serviceName, NetworkAddressType addressType, NetworkProtocol protocol, Socket::SocketCreationType socketCreationType, struct addrinfo*& outAddressInfo)
{
   NetworkResult result;
   
   if (socketCreationType == Socket::SocketCreationType::CONNECTIONLESS_SEND)
   {
        result.m_error = buildSocketInfo(addressType, protocol, socketCreationType, *outAddressInfo);
   }
   else
   {
        struct addrinfo hints;
        result.m_error = buildSocketInfo(addressType, protocol, socketCreationType, hints);

        // Resolve the server address and port
        result.m_internalError = getaddrinfo(hostName, serviceName, &hints, &outAddressInfo);
        if (result.m_internalError != 0)
        {
            result.m_error = NetworkError::ERROR_GET_ADDRESS_INFO;
        }
   }

   return result;
}

Network::NetworkError Network::buildSocketInfo(NetworkAddressType addressType, NetworkProtocol protocol, Socket::SocketCreationType socketCreationType, struct addrinfo& outAddressInfo)
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
         case Socket::SocketCreationType::CONNECTIONLESS_RECEIVE:
         {
            outAddressInfo.ai_flags = AI_PASSIVE;
            break;
         }
         case Socket::SocketCreationType::CONNECT:
         case Socket::SocketCreationType::CONNECTIONLESS_SEND:
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
   struct addrinfo addressInfo;
   struct addrinfo* addressInfoToBeFilled = nullptr;
   if (socketCreationType == Socket::SocketCreationType::CONNECTIONLESS_SEND)
   {
       addressInfoToBeFilled = &addressInfo;
   }
   result = Network::getInstance().getSocketInfo(hostName, serviceName, addressType, protocol, socketCreationType, addressInfoToBeFilled);

   if (result.m_error == NetworkError::NONE)
   {
      Socket::SocketResult socketResult = Socket::createSocket(socketCreationType, addressInfoToBeFilled, outSocket);
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
      
      if (socketCreationType != Socket::SocketCreationType::CONNECTIONLESS_SEND)
      {
          freeaddrinfo(addressInfoToBeFilled);
      }
   }

   return result;
}

