#include "vector3.h"
#include "matrix.h"
#include <utility>
#include <cmath>
#include "math.h"


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

float Vector3::operator * (const Vector3& v) const
{
   return (m_x * v.m_x + m_y * v.m_y + m_z * v.m_z);
}

Vector3 Vector3::operator * (float scalar) const
{
   return Vector3(
      m_x * scalar,
      m_y * scalar,
      m_z * scalar
   );
}

Vector3 Vector3::operator + (const Vector3& v) const
{
   return Vector3(
      m_x + v.m_x,
      m_y + v.m_y,
      m_z + v.m_z
   );
}

Vector3 Vector3::operator - (const Vector3& v) const
{
   return Vector3(
      m_x - v.m_x,
      m_y - v.m_y,
      m_z - v.m_z
   );
}

Vector3& Vector3::operator += (const Vector3& v)
{
   m_x += v.m_x;
   m_y += v.m_y;
   m_z += v.m_z;

   return *this;
}

Vector3& Vector3::operator /= (float scalar)
{
   m_x /= scalar;
   m_y /= scalar;
   m_z /= scalar;

   return *this;
}

Vector3& Vector3::operator *= (Matrix &m)
{
   Vector4 v4(m_x, m_y, m_z);
   v4 *= m;
   set(v4.m_x, v4.m_y, v4.m_z);

   return *this;
}

Vector3 Vector3::cross(const Vector3& v) const
{
   return Vector3(
      m_y * v.m_z - m_z * v.m_y,
      m_z * v.m_x - m_x * v.m_z,
      m_x * v.m_y - m_y * v.m_x
   );
}

bool Vector3::isPerpendicular(const Vector3& v) const
{
   return Math::equal(0.0f, *this * v);
}

float Vector3::getAngle(const Vector3& v) const
{
   float cos = 0.0f;
   cos = (*this * v) / ((*this).length() * v.length());
   return acos(cos);
}

float Vector3::length() const
{
   return sqrt(squaredLength());
}

float Vector3::squaredLength() const
{
   return (*this) * (*this);
}

void Vector3::normalize()
{
   *this /= length();
}

void Vector3::set(float x, float y, float z)
{
   m_x = x;
   m_y = y;
   m_z = z;
}

void Vector3::reset()
{
   m_x = 0.0f;
   m_y = 0.0f;
   m_z = 0.0f;
}
