#ifndef GRAPHICS_GAME
#define GRAPHICS_GAME

/*
   Interface to be implemented by a class in charge of the game loop render frame
*/

struct GraphicsGameProperties
{
   static const int s_defaultWindowWidth = 1024;
   static const int s_defaultWindowHeight = 768;

   GraphicsGameProperties()
      : m_windowWidth (s_defaultWindowWidth),
        m_windowHeight(s_defaultWindowHeight)
   {
   }

   GraphicsGameProperties(int windowWidth, int windowHeight)
      : m_windowWidth(windowWidth),
        m_windowHeight(windowHeight)
   {
   }

   GraphicsGameProperties(const GraphicsGameProperties& graphicsGameProperties)
   {
      *this = graphicsGameProperties;
   }

   GraphicsGameProperties& operator = (const GraphicsGameProperties& graphicsGameProperties)
   {
      m_windowWidth  = graphicsGameProperties.m_windowWidth;
      m_windowHeight = graphicsGameProperties.m_windowHeight;

      return *this;
   }

   GraphicsGameProperties(GraphicsGameProperties&& graphicsGameProperties)
   {
      *this = std::move(graphicsGameProperties);
   }

   GraphicsGameProperties& operator = (GraphicsGameProperties&& graphicsGameProperties)
   {
      m_windowWidth  = graphicsGameProperties.m_windowWidth;
      m_windowHeight = graphicsGameProperties.m_windowHeight;

      graphicsGameProperties.m_windowWidth  = 0;
      graphicsGameProperties.m_windowHeight = 0;

      return *this;
   }

   int m_windowWidth;
   int m_windowHeight;
};

struct IGraphicsGame
{

   virtual void render() const = 0;

   GraphicsGameProperties m_properties;

};

#endif


