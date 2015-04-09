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

   Graphics                               (const Graphics& v) = delete;
   Graphics&            operator =        (const Graphics& v) = delete;

   Graphics                               (Graphics&& v) = delete;
   Graphics&            operator =        (Graphics&& v) = delete;

   static void          renderScene       ();

   static std::unique_ptr<IGraphicsGame>  s_graphicsGame;

public:

   static Graphics&     getInstance       ();
   static void          init              (int argc, char* argv[], const char* name, std::unique_ptr<IGraphicsGame> graphicsGame);

   static void          drawPoint         (const Vector3& point, const Color& color);
   static void          drawVector3       (const Vector3& start, const Vector3& end, const Color& color);
   static void          drawAxis          (float length, const Color& color);
   static void          drawAxis          (float length);
};

