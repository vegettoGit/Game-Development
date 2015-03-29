
/*
   Simple graphics engine, which might evolve later on :)
*/

struct Vector3;

class Graphics
{
   Graphics();
   ~Graphics();

   Graphics                           (const Graphics& v) = delete;
   Graphics&        operator =        (const Graphics& v) = delete;

   Graphics                           (Graphics&& v) = delete;
   Graphics&        operator =        (Graphics&& v) = delete;

   static void      renderScene       ();
   static void      drawAxis          ();
   static void      drawVector3       (const Vector3& start, const Vector3& end);

   static const int s_window_width;
   static const int s_window_height;

public:

   static Graphics& GetInstance       ();
   void init                          (int argc, char* argv[]);
};

