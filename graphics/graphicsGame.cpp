#include "graphicsGame.h"
#include <utility>

const int   GraphicsGameProperties::s_defaultWindowWidth       = 1024;
const int   GraphicsGameProperties::s_defaultWindowHeight      = 768;
const float GraphicsGameProperties::s_defaultFieldOfViewAngle  = 1.0f;
const float GraphicsGameProperties::s_defaultAspectRatio       = 1.33f;
const float GraphicsGameProperties::s_defaultNearClippingPlane = 1.0f;
const float GraphicsGameProperties::s_defaultFarClippingPlane  = 10000.0f;


GraphicsGameProperties::GraphicsGameProperties()
   :  m_windowWidth (s_defaultWindowWidth),
      m_windowHeight(s_defaultWindowHeight),
      m_fieldOfViewAngle(s_defaultFieldOfViewAngle),
      m_aspectRatio(s_defaultAspectRatio),
      m_nearClippingPlane(s_defaultNearClippingPlane),
      m_farClippingPlane(s_defaultFarClippingPlane)
{
}

GraphicsGameProperties::GraphicsGameProperties(int windowWidth, int windowHeight)
   :  m_windowWidth(windowWidth),
      m_windowHeight(windowHeight),
      m_fieldOfViewAngle(s_defaultFieldOfViewAngle),
      m_aspectRatio(s_defaultAspectRatio),
      m_nearClippingPlane(s_defaultNearClippingPlane),
      m_farClippingPlane(s_defaultFarClippingPlane)
{
}

GraphicsGameProperties::GraphicsGameProperties(int windowWidth, int windowHeight, float FOVAngle, float aspectRatio, float zNear, float zFar)
   :  m_windowWidth(windowWidth),
      m_windowHeight(windowHeight),
      m_fieldOfViewAngle(FOVAngle),
      m_aspectRatio(aspectRatio),
      m_nearClippingPlane(zNear),
      m_farClippingPlane(zFar)
{
}

GraphicsGameProperties::GraphicsGameProperties(const GraphicsGameProperties& graphicsGameProperties)
{
   *this = graphicsGameProperties;
}

GraphicsGameProperties& GraphicsGameProperties::operator = (const GraphicsGameProperties& graphicsGameProperties)
{
   m_windowWidth  = graphicsGameProperties.m_windowWidth;
   m_windowHeight = graphicsGameProperties.m_windowHeight;

   return *this;
}

GraphicsGameProperties::GraphicsGameProperties(GraphicsGameProperties&& graphicsGameProperties)
{
   *this = std::move(graphicsGameProperties);
}

GraphicsGameProperties& GraphicsGameProperties::operator = (GraphicsGameProperties&& graphicsGameProperties)
{
   m_windowWidth  = graphicsGameProperties.m_windowWidth;
   m_windowHeight = graphicsGameProperties.m_windowHeight;

   graphicsGameProperties.m_windowWidth  = 0;
   graphicsGameProperties.m_windowHeight = 0;

   return *this;
}


