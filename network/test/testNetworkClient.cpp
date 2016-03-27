#include "test.h"

#ifdef TEST_NETWORK_CLIENT

#include "graphics.h"
#include "graphicsGame.h"
#include "simpleClient.h"
#include "debugUIHelpers.h"

struct TestNetworkClient : IGraphicsGame
{
   TestNetworkClient(int width, int height)
      : IGraphicsGame(GraphicsGameProperties(width, height))
   {
   }

   void gameUpdate(int millisecondsSinceGameStart) override
   {
      displayClientFeedBack(millisecondsSinceGameStart);

      Graphics::getInstance().update();
   }

   void initialize() override
   {
      m_simpleClient.createClientWork();
   }

private:

   void displayClientFeedBack(int millisecondsSinceGameStart)
   {
      std::string displayMessageText;

      switch (m_simpleClient.getClientState())
      {
      case SimpleClient::ClientState::CREATE:
         displayMessageText = "Creating socket for connection";
         break;
      case SimpleClient::ClientState::SEND:
         displayMessageText = "Sending bytes";
         break;
      case SimpleClient::ClientState::SHUT_DOWN:
         displayMessageText = "Shutting down socket sending operation";
         break;
      case SimpleClient::ClientState::CLOSE:
         displayMessageText = "Closing connection";
         break;
      case SimpleClient::ClientState::CLIENT_ERROR:
         DebugUIHelpers::displayText(m_simpleClient.getErrorText(), DebugUIHelpers::TextType::TEXT_ERROR);
         break;
      }

      if (displayMessageText.size() > 0)
      {
         displayMessageText += DebugUIHelpers::getUIDotsFromTime(millisecondsSinceGameStart);
         DebugUIHelpers::displayText(displayMessageText.c_str());
      }
   }

   SimpleClient m_simpleClient;
};

int main(int argc, char* argv[])
{
   std::unique_ptr<IGraphicsGame> testNetworkClient = std::make_unique<TestNetworkClient>(400, 300);
   Graphics::getInstance().init(argc, argv, "Test Network Client", std::move(testNetworkClient));

   return 0;
}

#endif
