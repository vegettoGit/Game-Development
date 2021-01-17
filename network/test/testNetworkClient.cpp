#include "test.h"

#ifdef TEST_NETWORK_CLIENT

#include "graphics.h"
#include "graphicsGame.h"
#include "simpleClient.h"
#include "testNetworkDisplay.h"
#include "input.h"

struct TestNetworkClient : IGraphicsGame
{
   TestNetworkClient(int width, int height)
      : IGraphicsGame(GraphicsGameProperties(width, height)),
        m_numberMessage(0)
   {
   }

   void updateInput()
   {
      unsigned char key = '0';

      if (Input::extractKey(key))
      {
         std::string textToSend;

         if (key == s_endKey)
         {
            textToSend = m_simpleClient.s_connectionEndText;
         }
         else
         {
            textToSend = "Another text " + std::to_string(++ m_numberMessage);
         }

         m_simpleClient.setTextToSend(textToSend);
      }
   }

   void gameUpdate(int millisecondsSinceGameStart) override
   {
      displayClientFeedBack(millisecondsSinceGameStart);

      updateInput();
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
   int m_numberMessage;

   static const unsigned char s_endKey;
};

const unsigned char TestNetworkClient::s_endKey = 101;

int main(int argc, char* argv[])
{
   std::unique_ptr<IGraphicsGame> testNetworkClient = std::make_unique<TestNetworkClient>(400, 300);
   Graphics::getInstance().init(argc, argv, "Test Network Client", std::move(testNetworkClient));

   return 0;
}

#endif
