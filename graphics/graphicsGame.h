#ifndef GRAPHICS_GAME
#define GRAPHICS_GAME

struct GraphicsGameProperties
{
   GraphicsGameProperties();
   GraphicsGameProperties(int windowWidth, int windowHeight);
   GraphicsGameProperties(int windowWidth, int windowHeight, float FOVAngle, float aspectRatio, float zNear, float zFar);
   GraphicsGameProperties(const GraphicsGameProperties& graphicsGameProperties);
   GraphicsGameProperties& operator = (const GraphicsGameProperties& graphicsGameProperties);
   GraphicsGameProperties(GraphicsGameProperties&& graphicsGameProperties);
   GraphicsGameProperties& operator = (GraphicsGameProperties&& graphicsGameProperties);

   int                m_windowWidth;
   int                m_windowHeight;

   // FOV in degrees in the y direction
   float              m_fieldOfViewAngle;

   // FOV in the x direction (ratio of x width to y height)
   float              m_aspectRatio;

   // Distance from the viewer to the near clipping plane (z)
   float              m_nearClippingPlane;

   // Distance from the viewer to the far clipping plane (z)
   float              m_farClippingPlane;

   static const int   s_defaultWindowWidth;
   static const int   s_defaultWindowHeight;
   static const float s_defaultFieldOfViewAngle;
   static const float s_defaultAspectRatio;
   static const float s_defaultNearClippingPlane;
   static const float s_defaultFarClippingPlane;
};

/*
   Interface to be implemented by a class in charge of the game loop render frame
*/
struct IGraphicsGame
{

   virtual void render() const = 0;

   GraphicsGameProperties m_properties;

};

#endif


