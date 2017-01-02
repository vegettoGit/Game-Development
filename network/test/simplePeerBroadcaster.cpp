
#include "SimplePeerBroadcaster.h"

SimplePeerBroadcaster::SimplePeerBroadcaster()
   : m_state(PeerBroadcasterState::NONE)
{
}

SimplePeerBroadcaster::~SimplePeerBroadcaster()
{
}

void SimplePeerBroadcaster::createWork()
{
   m_state = PeerBroadcasterState::INITIALIZE;

   m_initializeTask = async([&]
   { 
      Network::NetworkResult networkResult = Network::getInstance().initialize();
      if (networkResult.m_error != Network::NetworkError::NONE)
      {
         setError("Initialization of Network Layer failed with error", networkResult.m_internalError);
      }
      else
      {
         m_state = PeerBroadcasterState::CREATE;

         networkResult = Network::getInstance().createSocket(NetworkProperties::s_networkAddressType, 
                                                             Network::NetworkProtocol::UDP, 
                                                             Socket::SocketCreationType::CONNECTIONLESS, 
                                                             m_socket);

         if (networkResult.m_error != Network::NetworkError::NONE)
         {
            setError("Error creating connectionless socket", networkResult.m_internalError);
         }
      }

      return networkResult;
   });
      
   m_sendTask = m_initializeTask.then([&](const Network::NetworkResult networkResult)
   {
      Socket::SocketResult socketResult;
      if (networkResult.m_error == Network::NetworkError::NONE)
      {
         m_textToSend.append("This is a test");

         m_state = PeerBroadcasterState::SEND;
         int numberSentBytes = 0;
               
         socketResult = m_socket.sendDatagram(m_textToSend.c_str(), m_textToSend.size(), NetworkProperties::s_defaultPort, NetworkProperties::s_localHost, numberSentBytes);
         if (numberSentBytes == 0)
         {
            setError("Error sending datagram to peer", socketResult.m_internalError);
         }
         else
         {
            setLastSentText(m_textToSend.c_str(), numberSentBytes);

            m_state = PeerBroadcasterState::CLOSE;
            socketResult = m_socket.close();
            if (socketResult.m_error != Socket::SocketError::NONE)
            {
                setError("Error closing socket", socketResult.m_internalError);
            }
         }
      }

      return socketResult;
   });
}

void SimplePeerBroadcaster::setError(const char* text, int error)
{
   ISimplePeer::setError(text, error);

   m_state = PeerBroadcasterState::CLIENT_ERROR;
}

SimplePeerBroadcaster::PeerBroadcasterState SimplePeerBroadcaster::getState() const
{
   return m_state;
}

