#include "vector3.h"
#include <utility>
#include <math.h>


Vector3::Vector3()
   : m_x(0.0f),
     m_y(0.0f),
     m_z(0.0f)
{
}

Vector3::Vector3(float x, float y, float z)
   : m_x(x),
     m_y(y),
     m_z(z)
{
}

Vector3::Vector3(const Vector3& v)
{
   *this = v;
}

Vector3& Vector3::operator = (const Vector3& v)
{
   m_x = v.m_x;
   m_y = v.m_y;
   m_z = v.m_z;

   return *this;
}

Vector3::Vector3(Vector3&& v)
{
   *this = std::move(v);
}

Vector3& Vector3::operator = (Vector3&& v)
{
   m_x = v.m_x;
   m_y = v.m_y;
   m_z = v.m_z;

   v.m_x = 0.0f;
   v.m_y = 0.0f;
   v.m_z = 0.0f;

   return *this;
}

Vector3::~Vector3()
{
}

float Vector3::operator * (const Vector3& v)
{
   return (m_x * v.m_x + m_y * v.m_y + m_z * v.m_z);
}

Vector3& Vector3::operator /= (float scalar)
{
   m_x /= scalar;
   m_y /= scalar;
   m_z /= scalar;
   return *this;
}

float Vector3::length()
{
   return sqrt((*this) * (*this));
}

void Vector3::normalize()
{
   *this /= length();
}