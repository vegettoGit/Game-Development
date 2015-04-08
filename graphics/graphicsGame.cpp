#include "graphicsGame.h"
#include <utility>

const Vector3 GraphicsGameProperties::s_defaultEye               = Vector3(-3000.0f, -3000.0f, -3000.0f);
const Vector3 GraphicsGameProperties::s_defaultCenter            = Vector3(0.0f, 0.0f, 0.0f);
const Vector3 GraphicsGameProperties::s_defaultUp                = Vector3(0.0f, 1.0f, 0.0f);
const int     GraphicsGameProperties::s_defaultWindowWidth       = 1024;
const int     GraphicsGameProperties::s_defaultWindowHeight      = 768;
const float   GraphicsGameProperties::s_defaultFieldOfViewAngle  = 1.0f;
const float   GraphicsGameProperties::s_defaultAspectRatio       = 1.33f;
const float   GraphicsGameProperties::s_defaultNearClippingPlane = 1.0f;
const float   GraphicsGameProperties::s_defaultFarClippingPlane  = 10000.0f;


GraphicsGameProperties::GraphicsGameProperties()
   :  m_windowWidth (s_defaultWindowWidth),
      m_windowHeight(s_defaultWindowHeight),
      m_fieldOfViewAngle(s_defaultFieldOfViewAngle),
      m_aspectRatio(s_defaultAspectRatio),
      m_nearClippingPlane(s_defaultNearClippingPlane),
      m_farClippingPlane(s_defaultFarClippingPlane),
      m_eye(s_defaultEye),
      m_center(s_defaultCenter),
      m_up(s_defaultUp)
{
}

GraphicsGameProperties::GraphicsGameProperties(int windowWidth, int windowHeight)
   :  m_windowWidth(windowWidth),
      m_windowHeight(windowHeight),
      m_fieldOfViewAngle(s_defaultFieldOfViewAngle),
      m_aspectRatio(s_defaultAspectRatio),
      m_nearClippingPlane(s_defaultNearClippingPlane),
      m_farClippingPlane(s_defaultFarClippingPlane),
      m_eye(s_defaultEye),
      m_center(s_defaultCenter),
      m_up(s_defaultUp)
{
}

GraphicsGameProperties::GraphicsGameProperties(int windowWidth, int windowHeight, float FOVAngle, float aspectRatio, float zNear, float zFar, const Vector3& eye, const Vector3& center, const Vector3& up)
   :  m_windowWidth(windowWidth),
      m_windowHeight(windowHeight),
      m_fieldOfViewAngle(FOVAngle),
      m_aspectRatio(aspectRatio),
      m_nearClippingPlane(zNear),
      m_farClippingPlane(zFar),
      m_eye(eye),
      m_center(center),
      m_up(up)
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


