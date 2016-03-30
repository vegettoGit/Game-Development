#include "test.h"

#ifdef TEST_NETWORK_SERVER

#include "graphics.h"
#include "color.h"
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
      displayServerFeedBack(millisecondsSinceGameStart);

      Graphics::getInstance().update();
   }

   void initialize() override
   {
      m_simpleServer.createServerWork();
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
         DebugUIHelpers::displayText(m_simpleServer.getErrorText(), s_StatusPositionX, s_StatusPositionY, DebugUIHelpers::TextType::TEXT_ERROR);
         break;
      }

      if (displayMessageText.size() > 0)
      {
         displayMessageText += DebugUIHelpers::getUIDotsFromTime(millisecondsSinceGameStart);
         DebugUIHelpers::displayText(displayMessageText.c_str(), s_StatusPositionX, s_StatusPositionY);
      }

      const char* lastSentText = m_simpleServer.getLastSentText();
      const char* lastReceivedText = m_simpleServer.getLastReceivedText();
      std::string lastSent = (lastSentText != nullptr) ? "Last Sent: " + std::string(lastSentText) : "Last Sent: None";
      std::string receivedText = (lastReceivedText != nullptr) ? "Last Received: " + std::string(lastReceivedText) : "Last Received: None";

      DebugUIHelpers::displayText(lastSent.c_str(),     Color(0.0f, 1.0f, 0.0f), s_LastSentPositionX,     s_LastSentPositionY);
      DebugUIHelpers::displayText(receivedText.c_str(), Color(0.0f, 1.0f, 1.0f), s_LastReceivedPositionX, s_LastReceivedPositionY);
   }

   SimpleServer m_simpleServer;

   static const float s_StatusPositionX;
   static const float s_StatusPositionY;
   static const float s_LastSentPositionX;
   static const float s_LastSentPositionY;
   static const float s_LastReceivedPositionX;
   static const float s_LastReceivedPositionY;

};

const float TestNetworkServer::s_StatusPositionX       = 15.0f;
const float TestNetworkServer::s_StatusPositionY       = 30.0f;
const float TestNetworkServer::s_LastSentPositionX     = 15.0f;
const float TestNetworkServer::s_LastSentPositionY     = 60.0f;
const float TestNetworkServer::s_LastReceivedPositionX = 15.0f;
const float TestNetworkServer::s_LastReceivedPositionY = 90.0f;

int main(int argc, char* argv[])
{
   std::unique_ptr<IGraphicsGame> testNetworkServer = std::make_unique<TestNetworkServer>(400, 300);
   Graphics::getInstance().init(argc, argv, "Test Network Server", std::move(testNetworkServer));

   return 0;
}

#endif
