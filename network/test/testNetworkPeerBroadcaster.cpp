#include "test.h"

#ifdef TEST_NETWORK_PEER_BROADCASTER

#include "graphics.h"
#include "graphicsGame.h"
#include "simplePeerBroadcaster.h"
#include "testNetworkDisplay.h"
#include "input.h"

struct TestNetworkPeerBroadcaster : IGraphicsGame
{
   TestNetworkPeerBroadcaster(int width, int height)
      : IGraphicsGame(GraphicsGameProperties(width, height)),
        m_numberMessage(0)
   {
   }

   void gameUpdate(int millisecondsSinceGameStart) override
   {
      displayClientFeedBack(millisecondsSinceGameStart);

      Graphics::getInstance().update();
   }

   void initialize() override
   {
      m_simplePeerBroadcaster.createWork();
   }

private:

   void displayClientFeedBack(int millisecondsSinceGameStart)
   {
      std::string stateText;

      bool bError = false;

      switch (m_simplePeerBroadcaster.getState())
      {
      case SimplePeerBroadcaster::PeerBroadcasterState::CREATE:
         stateText = "Creating connectionless socket";
         break;
      case SimplePeerBroadcaster::PeerBroadcasterState::SEND:
         stateText = "Sending datagram";
         break;
      case SimplePeerBroadcaster::PeerBroadcasterState::CLOSE:
         stateText = "Closing socket";
         break;
      case SimplePeerBroadcaster::PeerBroadcasterState::CLIENT_ERROR:
         stateText = m_simplePeerBroadcaster.getErrorText();
         bError = true;
         break;
      }

      m_testNetworkDisplay.displayNetworkText(millisecondsSinceGameStart, stateText.c_str(), m_simplePeerBroadcaster.getLastSentText(), m_simplePeerBroadcaster.getLastReceivedText(), bError);
   }

   SimplePeerBroadcaster m_simplePeerBroadcaster;
   TestNetworkDisplay m_testNetworkDisplay;
   int m_numberMessage;

   static const unsigned char s_endKey;
};

int main(int argc, char* argv[])
{
   std::unique_ptr<IGraphicsGame> testNetworkPeerBroadcaster = std::make_unique<TestNetworkPeerBroadcaster>(400, 300);
   Graphics::getInstance().init(argc, argv, "Test Network Client", std::move(testNetworkPeerBroadcaster));

   return 0;
}

#endif
