#include <memory>

/*
   Simple graphics engine, which might evolve later on :)
*/

struct IGraphicsGame;
struct Vector3;
struct Color;


class Graphics
{

   Graphics();
   ~Graphics();

   static void            updateGame            ();

   static std::unique_ptr<IGraphicsGame>  s_graphicsGame;

public:

   enum class GraphicsResult
   {
      OK,
      EXTENSION_ERROR,
      ERROR
   };

   Graphics                                     (const Graphics& graphics) = delete;
   Graphics&              operator =            (const Graphics& graphics) = delete;

   Graphics                                     (Graphics&& graphics)      = delete;
   Graphics&              operator =            (Graphics&& graphics)      = delete;

   static Graphics&       getInstance           ();
   static GraphicsResult  init                  (int argc, char* argv[], const char* name, std::unique_ptr<IGraphicsGame> graphicsGame);
   static void            update                ();

   static void            drawPoint             (const Vector3& point, const Color& color);
   static void            drawVector3           (const Vector3& start, const Vector3& end, const Color& color);
   static void            drawVector3FromOrigin (const Vector3& end, const Color& color);
   static void            drawAxis              (float length, const Color& color);
   static void            drawAxis              (float length);
   static void            drawText              (float x, float y, const Color& color, const char* text);

};

