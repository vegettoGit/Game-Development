
#include <string>

struct TestNetworkDisplay
{
   TestNetworkDisplay()  = default;
   ~TestNetworkDisplay() = default;

   void displayNetworkText(int millisecondsSinceGameStart, const char* stateText, const char* sentText, const char* receivedText, bool bError) const;

private:

   static const float s_StatusPositionX;
   static const float s_StatusPositionY;
   static const float s_LastSentPositionX;
   static const float s_LastSentPositionY;
   static const float s_LastReceivedPositionX;
   static const float s_LastReceivedPositionY;
};

