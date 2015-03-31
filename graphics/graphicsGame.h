
/*
   Interface to be implemented by a class in charge of the game loop render frame
*/

struct GraphicsGameProperties
{
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

};


