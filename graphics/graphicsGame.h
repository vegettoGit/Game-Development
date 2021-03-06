#ifndef GRAPHICS_GAME
#define GRAPHICS_GAME

#include "vector3.h"

struct Camera
{
   enum class CameraMode
   {
      NONE,
      DEFAULT_ROTATION_Y
   };

   Camera                 ();
   Camera                 (const Camera& camera) = default;
   Camera&    operator  = (const Camera& camera) = default;
   Camera                 (Camera&&      camera) = default;
   Camera&    operator  = (Camera&&      camera) = default;
   ~Camera                ()                     = default;

   CameraMode m_cameraMode;
};

struct GraphicsGameProperties
{
   enum class BufferMode
   {
      SINGLE,
      DOUBLE
   };

   GraphicsGameProperties();
   GraphicsGameProperties(int windowWidth, int windowHeight);
   GraphicsGameProperties(const Vector3& eye, const Vector3& center, const Vector3& up, int windowWidth, int windowHeight, float FOVAngle, float aspectRatio, float zNear, float zFar, BufferMode bufferMode);
   
   GraphicsGameProperties             (const GraphicsGameProperties& graphicsGameProperties)  = default;
   GraphicsGameProperties& operator = (const GraphicsGameProperties& graphicsGameProperties)  = default;
   GraphicsGameProperties             (GraphicsGameProperties&& graphicsGameProperties)       = default;
   GraphicsGameProperties& operator = (GraphicsGameProperties&& graphicsGameProperties)       = default;
   ~GraphicsGameProperties            ()                                                      = default;

   Vector3              m_eye;

   // Reference point (center of the scene)
   Vector3              m_center;

   Vector3              m_up;

   int                  m_windowWidth;
   int                  m_windowHeight;

   // FOV in degrees in the y direction
   float                m_fieldOfViewAngle;

   // FOV in the x direction (ratio of x width to y height)
   float                m_aspectRatio;

   // Distance from the viewer to the near clipping plane (z)
   float                m_nearClippingPlane;

   // Distance from the viewer to the far clipping plane (z)
   float                m_farClippingPlane;

   BufferMode           m_bufferMode;


   static const Vector3 s_defaultEye;
   static const Vector3 s_defaultCenter;
   static const Vector3 s_defaultUp;
   static const int     s_defaultWindowWidth;
   static const int     s_defaultWindowHeight;
   static const float   s_defaultFieldOfViewAngle;
   static const float   s_defaultAspectRatio;
   static const float   s_defaultNearClippingPlane;
   static const float   s_defaultFarClippingPlane;

};

/*
   Interface to be implemented by a class in charge of the game loop render frame
*/
struct IGraphicsGame
{
   explicit IGraphicsGame(const GraphicsGameProperties&);
   virtual ~IGraphicsGame();

   IGraphicsGame             (const IGraphicsGame&)   = delete;
   IGraphicsGame             (IGraphicsGame&&)        = delete;

   IGraphicsGame& operator = (const IGraphicsGame& v) = delete;
   IGraphicsGame& operator = (IGraphicsGame&& v)      = delete;

   virtual void   initialize()                               = 0;
   virtual void   gameUpdate(int millisecondsSinceGameStart) = 0;

   void           update(int millisecondsSinceGameStart);
   void           setCameraMode(Camera::CameraMode cameraMode);

   GraphicsGameProperties m_properties;
   Camera                 m_camera;

   static const float     s_defaultRotationY;
};

#endif


