#include "task.h"
#include "simplePeer.h"

/*

   An example of a very simple server which does the following tasks asynchronously, one after the other:

   - Initializes our network and creates a socket.
   - Waits for an incoming connection and accepts it.
   - Receives all the data from the client, when the client finishes then we shut down the network.

*/
class SimpleServer : public ISimplePeer
{

public:

   enum class ServerState
   {
      NONE,
      INITIALIZE,
      CREATE,
      LISTEN,
      ACCEPT,
      RECEIVE,
      CLOSE,
      SHUT_DOWN,
      SERVER_ERROR
   };

   SimpleServer();
   ~SimpleServer();

   void          createWork    ()                            override;
   ServerState   getServerState()                            const;

private:

   void          setError      (const char* text, int error) override;

   Future<Network::NetworkResult> m_initializeTask;
   Future<Socket::SocketResult>   m_listenTask;
   Future<Socket::SocketResult>   m_receiveTask;

   ServerState m_serverState;
};

