
#include "task.h"
#include "simplePeer.h"

/*

   An example of a very simple client which does the following tasks asynchronously, one after the other:

   - Initializes our network and creates a socket for connecting to the server.
   - Sends all the data to the server, when it finishes then we shut down the network.

*/
class SimpleClient : public ISimplePeer
{

public:

   enum class ClientState
   {
      NONE,
      INITIALIZE,
      CREATE,
      SEND,
      CLOSE,
      SHUT_DOWN,
      CLIENT_ERROR
   };

   SimpleClient              ();
   ~SimpleClient             ();

   void        createWork    ()                          override;
   ClientState getClientState()                          const;
   void        setTextToSend (std::string&);

private:

   void setError           (const char* text, int error) override;

   Future<Network::NetworkResult> m_initializeTask;
   Future<Socket::SocketResult>   m_sendTask;
   std::string                    m_textToSend;
   ClientState m_clientState;

};

