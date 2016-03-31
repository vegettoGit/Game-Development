#include "testNetworkDisplay.h"
#include "debugUIHelpers.h"
#include "color.h"

const float TestNetworkDisplay::s_StatusPositionX = 15.0f;
const float TestNetworkDisplay::s_StatusPositionY = 30.0f;
const float TestNetworkDisplay::s_LastSentPositionX = 15.0f;
const float TestNetworkDisplay::s_LastSentPositionY = 60.0f;
const float TestNetworkDisplay::s_LastReceivedPositionX = 15.0f;
const float TestNetworkDisplay::s_LastReceivedPositionY = 90.0f;

void TestNetworkDisplay::displayNetworkText(int millisecondsSinceGameStart, const char* stateText, const char* sentText, const char* receivedText, bool bError) const
{
   if (stateText != nullptr)
   {
      std::string networkStateText = stateText + DebugUIHelpers::getUIDotsFromTime(millisecondsSinceGameStart);
      DebugUIHelpers::displayText(networkStateText.c_str(), s_StatusPositionX, s_StatusPositionY, bError ? DebugUIHelpers::TextType::TEXT_ERROR : DebugUIHelpers::TextType::NORMAL);
   }

   std::string lastSent     = (sentText != nullptr)     ? "Last Sent: "     + std::string(sentText)     : "Last Sent: None";
   std::string lastReceived = (receivedText != nullptr) ? "Last Received: " + std::string(receivedText) : "Last Received: None";

   DebugUIHelpers::displayText(lastSent.c_str(),     Color(0.0f, 1.0f, 0.0f), s_LastSentPositionX,     s_LastSentPositionY);
   DebugUIHelpers::displayText(lastReceived.c_str(), Color(0.0f, 1.0f, 1.0f), s_LastReceivedPositionX, s_LastReceivedPositionY);
}