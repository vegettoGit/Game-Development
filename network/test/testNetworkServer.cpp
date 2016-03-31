#include "test.h"

#ifdef TEST_NETWORK_SERVER

#include "graphics.h"
#include "color.h"
#include "graphicsGame.h"
#include "simpleServer.h"
#include "testNetworkDisplay.h"

struct TestNetworkServer : IGraphicsGame
{
   TestNetworkServer(int width, int height)
      : IGraphicsGame(GraphicsGameProperties(width, height))
   {
   }

   void gameUpdate(int millisecondsSinceGameStart) override
   {
      displayServerFeedBack(millisecondsSinceGameStart);

      Graphics::getInstance().update();
   }

   void initialize() override
   {
      m_simpleServer.createWork();
   }

private:

   void displayServerFeedBack(int millisecondsSinceGameStart) const
   {
      std::string stateText;

      bool bError = false;

      switch (m_simpleServer.getServerState())
      {
      case SimpleServer::ServerState::CREATE:
         stateText = "Creating listen socket";
         break;
      case SimpleServer::ServerState::LISTEN:
         stateText = "Listening";
         break;
      case SimpleServer::ServerState::ACCEPT:
         stateText = "Accepting";
         break;
      case SimpleServer::ServerState::RECEIVE:
         stateText = "Receiving and echoing bytes";
         break;
      case SimpleServer::ServerState::CLOSE:
         stateText = "Connection closing";
         break;
      case SimpleServer::ServerState::SHUT_DOWN:
         stateText = "Shutting down";
         break;
      case SimpleServer::ServerState::SERVER_ERROR:
         stateText = m_simpleServer.getErrorText();
         bError = true;
         break;
      }

      m_testNetworkDisplay.displayNetworkText(millisecondsSinceGameStart, stateText.c_str(), m_simpleServer.getLastSentText(), m_simpleServer.getLastReceivedText(), bError);
   }

   SimpleServer       m_simpleServer;
   TestNetworkDisplay m_testNetworkDisplay;
};

int main(int argc, char* argv[])
{
   std::unique_ptr<IGraphicsGame> testNetworkServer = std::make_unique<TestNetworkServer>(400, 300);
   Graphics::getInstance().init(argc, argv, "Test Network Server", std::move(testNetworkServer));

   return 0;
}

#endif
