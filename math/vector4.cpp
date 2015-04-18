#include "vector4.h"
#include <utility>


Vector4::Vector4()
   : m_x(0.0f),
     m_y(0.0f),
     m_z(0.0f),
     m_w(1.0f)
{
}

Vector4::Vector4(float x, float y, float z)
   : m_x(x),
     m_y(y),
     m_z(z),
     m_w(1.0f)
{
}

Vector4::Vector4(float x, float y, float z, float w)
   : m_x(x),
     m_y(y),
     m_z(z),
     m_w(w)
{
}

Vector4::Vector4(const Vector4& v)
{
   *this = v;
}

Vector4& Vector4::operator = (const Vector4& v)
{
   m_x = v.m_x;
   m_y = v.m_y;
   m_z = v.m_z;
   m_w = v.m_w;

   return *this;
}

Vector4::Vector4(Vector4&& v)
{
   *this = std::move(v);
}

Vector4& Vector4::operator = (Vector4&& v)
{
   m_x = v.m_x;
   m_y = v.m_y;
   m_z = v.m_z;
   m_w = v.m_w;

   v.m_x = 0.0f;
   v.m_y = 0.0f;
   v.m_z = 0.0f;
   v.m_w = 1.0f;

   return *this;
}

Vector4::~Vector4()
{
}

