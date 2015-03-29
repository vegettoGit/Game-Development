#include "graphics.h"
#include "vector3.h"

// We are using freeglut as our OpenGL Utility Toolkit: http://freeglut.sourceforge.net/
#include "freeglut.h"


// TODO: These are default window size constants, but we should have it configurable
const int Graphics::s_window_width  = 500;
const int Graphics::s_window_height = 500;

Graphics::Graphics()
{
}

Graphics::~Graphics()
{
}

Graphics& Graphics::GetInstance()
{
   static Graphics s_instance;
   return s_instance;
}

void Graphics::drawVector3(const Vector3& start, const Vector3& end)
{
   glBegin(GL_LINES);

   // TODO: Color should be configurable
   glColor3f(0.0f, 1.0f, 0.0f);
   glVertex3f(start.m_x, start.m_y, start.m_z);
   glVertex3f(end.m_x, end.m_y, end.m_z);
   
   glEnd();
}

void Graphics::drawAxis()
{
   // TODO: Axis length should be configurable
   drawVector3(Vector3(0.0f, 0.0f, 0.0f), Vector3(50.0f, 0.0f, 0.0f));
   drawVector3(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 50.0f, 0.0f));
   drawVector3(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 50.0f));
}

void Graphics::renderScene()
{
   glClear(GL_COLOR_BUFFER_BIT);

   // Camera setup
   // TODO: The following parameters should be configurable
   glLoadIdentity();
   gluPerspective(1.0f, 1.0f, 1.0f, 10000.0f);
   gluLookAt(-3000.0f, -3000.0f, -3000.0f, 0, 0, 0, 0.0f, 1.0f, 0.0f);

   drawAxis();

   glFlush();
}

void Graphics::init(int argc, char* argv[])
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
   glutInitWindowSize(s_window_width, s_window_height);
   glutCreateWindow("Example Graphics");
   glutDisplayFunc(renderScene);
   glutMainLoop();
}