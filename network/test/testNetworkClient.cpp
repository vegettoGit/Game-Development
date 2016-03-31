#include "test.h"

#ifdef TEST_NETWORK_CLIENT

#include "graphics.h"
#include "graphicsGame.h"
#include "simpleClient.h"
#include "testNetworkDisplay.h"

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
      m_simpleClient.createWork();
   }

private:

   void displayClientFeedBack(int millisecondsSinceGameStart)
   {
      std::string stateText;

      bool bError = false;

      switch (m_simpleClient.getClientState())
      {
      case SimpleClient::ClientState::CREATE:
         stateText = "Creating socket for connection";
         break;
      case SimpleClient::ClientState::SEND:
         stateText = "Sending bytes";
         break;
      case SimpleClient::ClientState::SHUT_DOWN:
         stateText = "Shutting down socket sending operation";
         break;
      case SimpleClient::ClientState::CLOSE:
         stateText = "Closing connection";
         break;
      case SimpleClient::ClientState::CLIENT_ERROR:
         stateText = m_simpleClient.getErrorText();
         bError = true;
         break;
      }

      m_testNetworkDisplay.displayNetworkText(millisecondsSinceGameStart, stateText.c_str(), m_simpleClient.getLastSentText(), m_simpleClient.getLastReceivedText(), bError);
   }

   SimpleClient m_simpleClient;
   TestNetworkDisplay m_testNetworkDisplay;
};

int main(int argc, char* argv[])
{
   std::unique_ptr<IGraphicsGame> testNetworkClient = std::make_unique<TestNetworkClient>(400, 300);
   Graphics::getInstance().init(argc, argv, "Test Network Client", std::move(testNetworkClient));

   return 0;
}

#endif
