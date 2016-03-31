
#include "simplePeer.h"
#include "networkProperties.h"

const char* NetworkProperties::s_defaultPort   = "27015";
const char* NetworkProperties::s_serverAddress = "127.0.0.1";


const char* ISimplePeer::getErrorText() const
{
   return m_errorText;
}

void ISimplePeer::setError(const char* text, int error)
{
   std::string errorString = text + std::string(" %d");
   sprintf_s(m_errorText, errorString.c_str(), error);
}

const char* ISimplePeer::getLastSentText() const
{
   const char* returnString = nullptr;
   if (m_lastSentText.size() > 0)
   {
      returnString = m_lastSentText.c_str();
   }
   return returnString;
}

const char* ISimplePeer::getLastReceivedText() const
{
   const char* returnString = nullptr;
   if (m_lastReceivedText.size() > 0)
   {
      returnString = m_lastReceivedText.c_str();
   }
   return returnString;
}

void ISimplePeer::setLastSentText(const char* text, int size)
{
   m_lastSentText.append(text, size);
}

void ISimplePeer::setLastReceivedText(const char* text, int size)
{
   m_lastReceivedText.append(text, size);
}