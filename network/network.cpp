#include "network.h"

Network::Network()
{
}

Network::~Network()
{
}

Network& Network::getInstance()
{
   static Network networkInstance;
   return networkInstance;
}

Network::NetworkResult Network::initialize()
{
   NetworkResult result;

   // Initialize Winsock
   int socketsResult = WSAStartup(MAKEWORD(2, 2), &m_wsaData);

   if (socketsResult != 0)
   {
      result.m_error         = NetworkError::ERROR_INITIALIZATION_SOCKETS;
      result.m_internalError = socketsResult;
   }

   return result;
}

