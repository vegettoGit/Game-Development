#include "test.h"

#ifdef TEST_NETWORK_CLIENT

#include "graphics.h"
#include "graphicsGame.h"
#include "color.h"
#include "simpleClient.h"


struct TestNetworkClient : IGraphicsGame
{
   enum class TextType
   {
      NONE,
      TEXT_ERROR
   };

   TestNetworkClient(int width, int height)
      : IGraphicsGame(GraphicsGameProperties(width, height))
   {
   }

   void displayText(const char* text, TextType textType = TextType::NONE)
   {
      Color color = textType == TextType::TEXT_ERROR ? Color(1.0f, 0.0f, 0.0f) : Color(1.0f, 1.0f, 1.0f);
      Graphics::getInstance().drawText(15.0f, 30.0f, color, text);
   }

   void displayClientFeedBack()
   {
      switch (m_simpleClient.getClientState())
      {
      case SimpleClient::ClientState::CREATE:
         displayText("Creating socket for connection");
         break;
      case SimpleClient::ClientState::SEND:
         displayText("Sending bytes");
         break;
      case SimpleClient::ClientState::SHUT_DOWN:
         displayText("Shutting down socket sending operation");
         break;
      case SimpleClient::ClientState::CLOSE:
         displayText("Closing connection");
         break;
      case SimpleClient::ClientState::CLIENT_ERROR:
         displayText(m_simpleClient.getErrorText(), TextType::TEXT_ERROR);
         break;
      }
   }

   void gameUpdate() override
   {
      if (m_simpleClient.getClientState() == SimpleClient::ClientState::NONE)
      {
         m_simpleClient.createClientWork();
      }

      displayClientFeedBack();

      Graphics::getInstance().update();
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
