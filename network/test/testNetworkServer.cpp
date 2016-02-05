#include "test.h"

#ifdef TEST_NETWORK_SERVER

#include "graphics.h"
#include "graphicsGame.h"
#include "color.h"
#include "simpleServer.h"

struct TestNetworkServer : IGraphicsGame
{

   enum class TextType
   {
      NONE,
      TEXT_ERROR
   };

   TestNetworkServer(int width, int height)
      :  IGraphicsGame(GraphicsGameProperties(width, height))
   {
   }

   void displayText(const char* text, TextType textType = TextType::NONE)
   {
      Color color = (textType == TextType::TEXT_ERROR) ? Color(1.0f, 0.0f, 0.0f) : Color(1.0f, 1.0f, 1.0f) ;
      Graphics::getInstance().drawText(15.0f, 30.0f, color, text);
   }

   void displayServerFeedBack()
   {
      switch (m_simpleServer.getServerState())
      {
      case SimpleServer::ServerState::CREATE:
         displayText("Creating listen socket");
         break;
      case SimpleServer::ServerState::LISTEN:
         displayText("Listening");
         break;
      case SimpleServer::ServerState::ACCEPT:
         displayText("Accepting");
         break;
      case SimpleServer::ServerState::RECEIVE:
         displayText("Receiving and echoing bytes");
         break;
      case SimpleServer::ServerState::CLOSE:
         displayText("Connection closing");
         break;
      case SimpleServer::ServerState::SHUT_DOWN:
         displayText("Shutting down");
         break;
      case SimpleServer::ServerState::SERVER_ERROR:
         displayText(m_simpleServer.getErrorText(), TextType::TEXT_ERROR);
         break;
      }
   }

   void gameUpdate() override
   {
      if (m_simpleServer.getServerState() == SimpleServer::ServerState::NONE)
      {
         m_simpleServer.createServerWork();
      }

      displayServerFeedBack();

      Graphics::getInstance().update();
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
