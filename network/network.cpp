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

Network::NetworkResult Network::getAddressInfo(const char* hostName, const char* serviceName, NetworkAddressType addressType, NetworkProtocol protocol, struct addrinfo*& outAddressInfo)
{
   NetworkResult result;
   
   struct addrinfo hints;

   result.m_error = buildAddressInfo(addressType, protocol, hints);

   if (result.m_error == NetworkError::NONE)
   {
      hints.ai_flags = AI_PASSIVE;

      // Resolve the server address and port
      result.m_internalError = getaddrinfo(NULL, serviceName, &hints, &outAddressInfo);
      if (result.m_internalError != 0)
      {
         result.m_error = NetworkError::ERROR_GET_ADDRESS_INFO;
      }
   }

   return result;
}

Network::NetworkError Network::buildAddressInfo(NetworkAddressType addressType, NetworkProtocol protocol, struct addrinfo& outAddressInfo)
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

   return result;
}

Network::NetworkResult Network::createSocket(const char* hostName, const char* serviceName, NetworkAddressType addressType, NetworkProtocol protocol, Socket& outSocket)
{
   NetworkResult result;

   if (m_networkLayerState != NetworkLayerState::INITIALIZED)
   {
      result.m_error = NetworkError::ERROR_NETWORK_UNINITIALIZED;
      return result;
   }

   // Resolve the server address and port
   struct addrinfo* addressInfo = nullptr;
   result = Network::getInstance().getAddressInfo(hostName, serviceName, addressType, protocol, addressInfo);

   if (result.m_error == Network::NetworkError::NONE)
   {
      outSocket.m_socket = socket(addressInfo->ai_family, addressInfo->ai_socktype, addressInfo->ai_protocol);
      if (outSocket.m_socket == INVALID_SOCKET)
      {
         result.m_error         = NetworkError::ERROR_CREATE_SOCKET;
         result.m_internalError = WSAGetLastError();
      }
      else
      {
         int bindResult = bind(outSocket.m_socket, addressInfo->ai_addr, addressInfo->ai_addrlen);
         if (bindResult == SOCKET_ERROR)
         {
            result.m_error         = NetworkError::ERROR_BIND_SOCKET;
            result.m_internalError = WSAGetLastError();
            closesocket(outSocket.m_socket);
         }
      }
         
      freeaddrinfo(addressInfo);
   }

   return result;
}

