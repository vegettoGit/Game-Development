#include "graphics.h"
#include "graphicsGame.h"
#include "color.h"

// OpenGL Extension Wrangler
#include "glew.h"

// We are using freeglut as our OpenGL Utility Toolkit: http://freeglut.sourceforge.net/
#include "freeglut.h"


std::unique_ptr<IGraphicsGame> Graphics::s_graphicsGame = nullptr;

Graphics::Graphics()
{
}

Graphics::~Graphics()
{
}

Graphics& Graphics::getInstance()
{
   static Graphics s_instance;
   return s_instance;
}

void Graphics::drawPoint(const Vector3& point, const Color& color)
{
   glBegin(GL_POINTS);

   glColor3f(color.m_red, color.m_green, color.m_blue);
   glVertex3f(point.m_x, point.m_y, point.m_z);

   glEnd();
}

void Graphics::drawVector3(const Vector3& start, const Vector3& end, const Color& color)
{
   glBegin(GL_LINES);

   glColor3f(color.m_red, color.m_green, color.m_blue);
   glVertex3f(start.m_x, start.m_y, start.m_z);
   glVertex3f(end.m_x, end.m_y, end.m_z);
   
   glEnd();
}

void Graphics::drawVector3FromOrigin(const Vector3& end, const Color& color)
{
   drawVector3(Vector3(0.0f, 0.0f, 0.0f), end, color);
}

void Graphics::drawAxis(float length)
{
   Vector3 origin(0.0f, 0.0f, 0.0f);
   drawVector3(origin, Vector3(length, 0.0f, 0.0f), Color(1.0f, 0.0f, 0.0f));
   drawVector3(origin, Vector3(0.0f, length, 0.0f), Color(0.0f, 1.0f, 0.0f));
   drawVector3(origin, Vector3(0.0f, 0.0f, length), Color(0.0f, 0.0f, 1.0f));
}

void Graphics::drawAxis(float length, const Color& color)
{
   Vector3 origin(0.0f, 0.0f, 0.0f);
   drawVector3(origin, Vector3(length, 0.0f, 0.0f), color);
   drawVector3(origin, Vector3(0.0f, length, 0.0f), color);
   drawVector3(origin, Vector3(0.0f, 0.0f, length), color);
}

void Graphics::updateGame()
{
   glClear(GL_COLOR_BUFFER_BIT);
   
   // Camera setup
   const GraphicsGameProperties& properties = (*s_graphicsGame).m_properties;

   glLoadIdentity();
   
   gluPerspective(properties.m_fieldOfViewAngle, properties.m_aspectRatio, properties.m_nearClippingPlane, properties.m_farClippingPlane);

   gluLookAt(properties.m_eye.m_x, properties.m_eye.m_y, properties.m_eye.m_z, 
             properties.m_center.m_x, properties.m_center.m_y, properties.m_center.m_z, 
             properties.m_up.m_x, properties.m_up.m_y, properties.m_up.m_z);

   (*s_graphicsGame).update();

   switch (properties.m_bufferMode)
   {
      case GraphicsGameProperties::BufferMode::DOUBLE:
      {
         glutSwapBuffers();
         break;
      }
      case GraphicsGameProperties::BufferMode::SINGLE:
      {
         glFlush();
         break;
      }
   }
   
}

Graphics::GraphicsResult Graphics::init(int argc, char* argv[], const char* name, std::unique_ptr<IGraphicsGame> graphicsGame)
{
   GraphicsResult result = GraphicsResult::OK;

   s_graphicsGame = std::move(graphicsGame);

   const GraphicsGameProperties& properties = (*s_graphicsGame).m_properties;
   glutInit(&argc, argv);
   
   switch (properties.m_bufferMode)
   {
      case GraphicsGameProperties::BufferMode::DOUBLE:
      {
         glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
         break;
      }
      case GraphicsGameProperties::BufferMode::SINGLE:
      {
         glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
         break;
      }
   }
   
   glutInitWindowSize(properties.m_windowWidth, properties.m_windowHeight);
   glutCreateWindow(name);

   // Extension Wrangler
   GLenum glew_status = glewInit();

   if (glew_status == GLEW_OK)
   {
      glutDisplayFunc(updateGame);
      glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
      glutMainLoop();
   }
   else
   {
      result = GraphicsResult::EXTENSION_ERROR;
   }

   return result;
}

void Graphics::update()
{
   glutPostRedisplay();
}