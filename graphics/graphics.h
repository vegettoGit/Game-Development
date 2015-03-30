#include <memory>

/*
   Simple graphics engine, which might evolve later on :)
*/

struct IGraphicsGame;
struct Vector3;

/* 
   Each member is normalized
*/
struct Color
{
   Color              ();
   Color              (float red, float green, float blue);

   Color              (const Color& );
   Color& operator =  (const Color& v);

   Color              (Color&& );
   Color& operator =  (Color&& v);

   ~Color             ();

   float  m_red;
   float  m_green;
   float  m_blue;
};

class Graphics
{
   Graphics();
   ~Graphics();

   Graphics                               (const Graphics& v) = delete;
   Graphics&            operator =        (const Graphics& v) = delete;

   Graphics                               (Graphics&& v) = delete;
   Graphics&            operator =        (Graphics&& v) = delete;

   static void          renderScene       (const IGraphicsGame&);
   static void          renderScene       ();

   static const int     s_window_width;
   static const int     s_window_height;

   static std::unique_ptr<IGraphicsGame> s_graphicsGame;

public:

   static Graphics&     getInstance       ();
   void                 init              (int argc, char* argv[], const char* name, std::unique_ptr<IGraphicsGame> graphicsGame);

   static void          drawVector3       (const Vector3& start, const Vector3& end, const Color& color);
   static void          drawAxis          (float length, const Color& color);
};

