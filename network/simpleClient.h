
#include "task.h"
#include "network.h"

/*

   An example of a very simple client which does the following tasks asynchronously, one after the other:

   - Initializes our network and creates a socket for connecting to the server.
   - Sends all the data to the server, when it finishes then we shut down the network.

*/
class SimpleClient
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

   SimpleClient();
   ~SimpleClient();

   SimpleClient             (const SimpleClient& server) = delete;
   SimpleClient& operator = (const SimpleClient& server) = delete;

   SimpleClient             (SimpleClient&& server)      = delete;
   SimpleClient& operator = (SimpleClient&& server)      = delete;

   void        createClientWork();
   ClientState getClientState  () const;
   const char* getErrorText    () const;

private:

   void setErrorState       (const char* text, int error);

   Future<Network::NetworkResult> m_initializeTask;
   Future<Socket::SocketResult>   m_sendTask;

   Socket      m_socket;
   ClientState m_clientState;
   char        m_errorText[64];

};

