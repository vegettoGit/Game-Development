
#include "task.h"
#include "network.h"

/*

   An example of a very simple server which does the following tasks asynchronously, one after the other:

   - Initializes our network and creates a socket.
   - Waits for an incoming connection and accepts it.
   - Receives all the data from the client, when the client finishes then we shut down the network.

*/
class SimpleServer
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

   SimpleServer             (const SimpleServer& server) = delete;
   SimpleServer& operator = (const SimpleServer& server) = delete;

   SimpleServer             (SimpleServer&& server)      = delete;
   SimpleServer& operator = (SimpleServer&& server)      = delete;

   void        createServerWork();
   ServerState getServerState  () const;
   const char* getErrorText    () const;

private:

   void setErrorState       (const char* text, int error);

   Future<Network::NetworkResult> m_initializeTask;
   Future<Socket::SocketResult>   m_listenTask;
   Future<Socket::SocketResult>   m_receiveTask;

   Socket      m_socket;
   ServerState m_serverState;
   char        m_errorText[64];

};

