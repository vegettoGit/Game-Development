#include "matrix.h"
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

void Vector4::set(float x, float y, float z, float w)
{
   m_x = x;
   m_y = y;
   m_z = z;
   m_w = w;
}

void Vector4::reset()
{
   m_x = 0.0f;
   m_y = 0.0f;
   m_z = 0.0f;
   m_w = 1.0f;
}

Vector4 Vector4::operator * (Matrix &m) const
{
   return Vector4(m_x * m.m_m0 + m_y * m.m_m4 + m_z * m.m_m8  + m_w * m.m_m12,
                  m_x * m.m_m1 + m_y * m.m_m5 + m_z * m.m_m9  + m_w * m.m_m13,
                  m_x * m.m_m2 + m_y * m.m_m6 + m_z * m.m_m10 + m_w * m.m_m14,
                  m_x * m.m_m3 + m_y * m.m_m7 + m_z * m.m_m11 + m_w * m.m_m15);
}

Vector4& Vector4::operator *= (Matrix &m)
{
   set(m_x * m.m_m0 + m_y * m.m_m4 + m_z * m.m_m8  + m_w * m.m_m12,
       m_x * m.m_m1 + m_y * m.m_m5 + m_z * m.m_m9  + m_w * m.m_m13,
       m_x * m.m_m2 + m_y * m.m_m6 + m_z * m.m_m10 + m_w * m.m_m14,
       m_x * m.m_m3 + m_y * m.m_m7 + m_z * m.m_m11 + m_w * m.m_m15);

   return *this;
}

