#include "test.h"

#ifdef TEST_NETWORK_SERVER

#include "graphics.h"
#include "graphicsGame.h"
#include "simpleServer.h"
#include "debugUIHelpers.h"

struct TestNetworkServer : IGraphicsGame
{
   TestNetworkServer(int width, int height)
      : IGraphicsGame(GraphicsGameProperties(width, height))
   {
   }

   void gameUpdate(int millisecondsSinceGameStart) override
   {
      if (m_simpleServer.getServerState() == SimpleServer::ServerState::NONE)
      {
         m_simpleServer.createServerWork();
      }

      displayServerFeedBack(millisecondsSinceGameStart);

      Graphics::getInstance().update();
   }

private:

   void displayServerFeedBack(int millisecondsSinceGameStart) const
   {
      std::string displayMessageText;

      switch (m_simpleServer.getServerState())
      {
      case SimpleServer::ServerState::CREATE:
         displayMessageText = "Creating listen socket";
         break;
      case SimpleServer::ServerState::LISTEN:
         displayMessageText = "Listening";
         break;
      case SimpleServer::ServerState::ACCEPT:
         displayMessageText = "Accepting";
         break;
      case SimpleServer::ServerState::RECEIVE:
         displayMessageText = "Receiving and echoing bytes";
         break;
      case SimpleServer::ServerState::CLOSE:
         displayMessageText = "Connection closing";
         break;
      case SimpleServer::ServerState::SHUT_DOWN:
         displayMessageText = "Shutting down";
         break;
      case SimpleServer::ServerState::SERVER_ERROR:
         DebugUIHelpers::displayText(m_simpleServer.getErrorText(), DebugUIHelpers::TextType::TEXT_ERROR);
         break;
      }

      if (displayMessageText.size() > 0)
      {
         displayMessageText += DebugUIHelpers::getUIDotsFromTime(millisecondsSinceGameStart);
         DebugUIHelpers::displayText(displayMessageText.c_str());
      }
      
   }

   SimpleServer m_simpleServer;

};

int main(int argc, char* argv[])
{
   std::unique_ptr<IGraphicsGame> testNetworkServer = std::make_unique<TestNetworkServer>(400, 300);
   Graphics::getInstance().init(argc, argv, "Test Network Server", std::move(testNetworkServer));

   return 0;
}

#endif
