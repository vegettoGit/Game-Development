
#include "task.h"
#include "simplePeer.h"

/*

   An example of a very simple peer which does the following tasks asynchronously, one after the other:

   - Initializes our network and creates a connectionless UDP datagram socket.
   - Broadcasts a sample datagram to a given IP address and port

*/
class SimplePeerBroadcaster : public ISimplePeer
{

public:

   enum class PeerBroadcasterMode
   {
      SEND,
      RECEIVE
   };

   enum class PeerBroadcasterState
   {
      NONE,
      INITIALIZE,
      CREATE,
      SEND,
      RECEIVE,
      CLOSE,
      CLIENT_ERROR
   };

   SimplePeerBroadcaster        ();
   ~SimplePeerBroadcaster       ();

   void        createWork        () override;
   void        setBroadcasterMode(PeerBroadcasterMode);

   PeerBroadcasterState getState() const;

private:

   void setError                (const char* text, int error) override;

   Future<Network::NetworkResult> m_initializeTask;
   Future<Socket::SocketResult>   m_sendTask;
   Future<Socket::SocketResult>   m_receiveTask;
   std::string                    m_textToSend;
   PeerBroadcasterState           m_state;
   PeerBroadcasterMode            m_broadcasterMode;

};

