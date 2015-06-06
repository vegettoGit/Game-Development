#include "matrix.h"
#include <utility>
#include <cmath>

Matrix::Matrix()
   : m_m0(0.0f),
     m_m1(0.0f),
     m_m2(0.0f),
     m_m3(0.0f),
     m_m4(0.0f),
     m_m5(0.0f),
     m_m6(0.0f),
     m_m7(0.0f),
     m_m8(0.0f),
     m_m9(0.0f),
     m_m10(0.0f),
     m_m11(0.0f),
     m_m12(0.0f),
     m_m13(0.0f),
     m_m14(0.0f),
     m_m15(0.0f)
{
}

Matrix::Matrix(const Vector4& v0, const Vector4& v1, const Vector4& v2, const Vector4& v3)
   : m_v0(v0),
     m_v1(v1),
     m_v2(v2),
     m_v3(v3)
{
}

Matrix::Matrix(RotationType rotationType, float angle)
{
   float cos = cosf(angle);
   float sin = sinf(angle);

   switch (rotationType)
   {
      case RotationType::X:
      {
         m_v0.set(1.0f, 0.0f, 0.0f, 0.0f);

         m_m4 = 0.0f;
         m_m5 = cos;
         m_m6 = sin;
         m_m7 = 0.0f;

         m_m8 = 0.0f;
         m_m9 = -sin;
         m_m10 = cos;
         m_m11 = 0.0f;

         m_v3.set(0.0f, 0.0f, 0.0f, 1.0f);

         break;
      }
      case RotationType::Y:
      {
         m_m0 = cos;
         m_m1 = 0.0f;
         m_m2 = -sin;
         m_m3 = 0.0f;

         m_v1.set(0.0f, 1.0f, 0.0f, 0.0f);

         m_m8 = sin;
         m_m9 = 0.0f;
         m_m10 = cos;
         m_m11 = 0.0f;

         m_v3.set(0.0f, 0.0f, 0.0f, 1.0f);
         
         break;
      }
      case RotationType::Z:
      {
         m_m0 = cos;
         m_m1 = sin;
         m_m2 = 0.0f;
         m_m3 = 0.0f;

         m_m4 = -sin;
         m_m5 = cos;
         m_m6 = 0.0f;
         m_m7 = 0.0f;

         m_v2.set(0.0f, 0.0f, 1.0f, 0.0f);
         m_v3.set(0.0f, 0.0f, 0.0f, 1.0f);
      }

      break;
   }
}

void Matrix::set(const Vector4& v0, const Vector4& v1, const Vector4& v2, const Vector4& v3)
{
   m_v0 = v0;
   m_v1 = v1;
   m_v2 = v2;
   m_v3 = v3;
}

Matrix Matrix::operator + (const Matrix &m) const
{
   return Matrix(
      Vector4(m_m0 + m.m_m0,   m_m1 + m.m_m1,   m_m2 + m.m_m2,   m_m3 + m.m_m3),
      Vector4(m_m4 + m.m_m4,   m_m5 + m.m_m5,   m_m6 + m.m_m6,   m_m7 + m.m_m7),
      Vector4(m_m8 + m.m_m8,   m_m9 + m.m_m9,   m_m10 + m.m_m10, m_m11 + m.m_m11),
      Vector4(m_m12 + m.m_m12, m_m13 + m.m_m13, m_m14 + m.m_m14, m_m15 + m.m_m15)
    );
}

Matrix& Matrix::operator += (const Matrix &m)
{
   m_v0.set(m_m0 + m.m_m0,   m_m1 + m.m_m1,   m_m2 + m.m_m2,   m_m3 + m.m_m3);
   m_v1.set(m_m4 + m.m_m4,   m_m5 + m.m_m5,   m_m6 + m.m_m6,   m_m7 + m.m_m7);
   m_v2.set(m_m8 + m.m_m8,   m_m9 + m.m_m9,   m_m10 + m.m_m10, m_m11 + m.m_m11);
   m_v3.set(m_m12 + m.m_m12, m_m13 + m.m_m13, m_m14 + m.m_m14, m_m15 + m.m_m15);

   return *this;
}

Matrix Matrix::operator - (const Matrix &m) const
{
   return Matrix(
      Vector4(m_m0 - m.m_m0,   m_m1 - m.m_m1,   m_m2 - m.m_m2,   m_m3 - m.m_m3),
      Vector4(m_m4 - m.m_m4,   m_m5 - m.m_m5,   m_m6 - m.m_m6,   m_m7 - m.m_m7),
      Vector4(m_m8 - m.m_m8,   m_m9 - m.m_m9,   m_m10 - m.m_m10, m_m11 - m.m_m11),
      Vector4(m_m12 - m.m_m12, m_m13 - m.m_m13, m_m14 - m.m_m14, m_m15 - m.m_m15)
   );
}
Matrix& Matrix::operator -= (const Matrix &m)
{
   m_v0.set(m_m0 - m.m_m0,   m_m1 - m.m_m1,   m_m2 - m.m_m2,   m_m3 - m.m_m3);
   m_v1.set(m_m4 - m.m_m4,   m_m5 - m.m_m5,   m_m6 - m.m_m6,   m_m7 - m.m_m7);
   m_v2.set(m_m8 - m.m_m8,   m_m9 - m.m_m9,   m_m10 - m.m_m10, m_m11 - m.m_m11);
   m_v3.set(m_m12 - m.m_m12, m_m13 - m.m_m13, m_m14 - m.m_m14, m_m15 - m.m_m15);

   return *this;
}

Matrix Matrix::operator * (const Matrix &m) const
{
   return Matrix(

      Vector4(m_m0 * m.m_m0 + m_m1 * m.m_m4 + m_m2 * m.m_m8  + m_m3 * m.m_m12,
              m_m0 * m.m_m1 + m_m1 * m.m_m5 + m_m2 * m.m_m9  + m_m3 * m.m_m13,
              m_m0 * m.m_m2 + m_m1 * m.m_m6 + m_m2 * m.m_m10 + m_m3 * m.m_m14,
              m_m0 * m.m_m3 + m_m1 * m.m_m7 + m_m2 * m.m_m11 + m_m3 * m.m_m15),

      Vector4(m_m4 * m.m_m0 + m_m5 * m.m_m4 + m_m6 * m.m_m8  + m_m7 * m.m_m12,
              m_m4 * m.m_m1 + m_m5 * m.m_m5 + m_m6 * m.m_m9  + m_m7 * m.m_m13,
              m_m4 * m.m_m2 + m_m5 * m.m_m6 + m_m6 * m.m_m10 + m_m7 * m.m_m14,
              m_m4 * m.m_m3 + m_m5 * m.m_m7 + m_m6 * m.m_m11 + m_m7 * m.m_m15),

      Vector4(m_m8 * m.m_m0 + m_m9 * m.m_m4 + m_m10 * m.m_m8  + m_m11 * m.m_m12,
              m_m8 * m.m_m1 + m_m9 * m.m_m5 + m_m10 * m.m_m9  + m_m11 * m.m_m13,
              m_m8 * m.m_m2 + m_m9 * m.m_m6 + m_m10 * m.m_m10 + m_m11 * m.m_m14,
              m_m8 * m.m_m3 + m_m9 * m.m_m7 + m_m10 * m.m_m11 + m_m11 * m.m_m15),

      Vector4(m_m12 * m.m_m0 + m_m13 * m.m_m4 + m_m14 * m.m_m8  + m_m15 * m.m_m12,
              m_m12 * m.m_m1 + m_m13 * m.m_m5 + m_m14 * m.m_m9  + m_m15 * m.m_m13,
              m_m12 * m.m_m2 + m_m13 * m.m_m6 + m_m14 * m.m_m10 + m_m15 * m.m_m14,
              m_m12 * m.m_m3 + m_m13 * m.m_m7 + m_m14 * m.m_m11 + m_m15 * m.m_m15)
   );
}

Matrix& Matrix::operator *= (const Matrix &m)
{
   m_v0.set(m_m0 * m.m_m0 + m_m1 * m.m_m4 + m_m2 * m.m_m8  + m_m3 * m.m_m12,
            m_m0 * m.m_m1 + m_m1 * m.m_m5 + m_m2 * m.m_m9  + m_m3 * m.m_m13,
            m_m0 * m.m_m2 + m_m1 * m.m_m6 + m_m2 * m.m_m10 + m_m3 * m.m_m14,
            m_m0 * m.m_m3 + m_m1 * m.m_m7 + m_m2 * m.m_m11 + m_m3 * m.m_m15);

   m_v1.set(m_m4 * m.m_m0 + m_m5 * m.m_m4 + m_m6 * m.m_m8  + m_m7 * m.m_m12,
            m_m4 * m.m_m1 + m_m5 * m.m_m5 + m_m6 * m.m_m9  + m_m7 * m.m_m13,
            m_m4 * m.m_m2 + m_m5 * m.m_m6 + m_m6 * m.m_m10 + m_m7 * m.m_m14,
            m_m4 * m.m_m3 + m_m5 * m.m_m7 + m_m6 * m.m_m11 + m_m7 * m.m_m15);

   m_v2.set(m_m8 * m.m_m0 + m_m9 * m.m_m4 + m_m10 * m.m_m8  + m_m11 * m.m_m12,
            m_m8 * m.m_m1 + m_m9 * m.m_m5 + m_m10 * m.m_m9  + m_m11 * m.m_m13,
            m_m8 * m.m_m2 + m_m9 * m.m_m6 + m_m10 * m.m_m10 + m_m11 * m.m_m14,
            m_m8 * m.m_m3 + m_m9 * m.m_m7 + m_m10 * m.m_m11 + m_m11 * m.m_m15);

   m_v3.set(m_m12 * m.m_m0 + m_m13 * m.m_m4 + m_m14 * m.m_m8  + m_m15 * m.m_m12,
            m_m12 * m.m_m1 + m_m13 * m.m_m5 + m_m14 * m.m_m9  + m_m15 * m.m_m13,
            m_m12 * m.m_m2 + m_m13 * m.m_m6 + m_m14 * m.m_m10 + m_m15 * m.m_m14,
            m_m12 * m.m_m3 + m_m13 * m.m_m7 + m_m14 * m.m_m11 + m_m15 * m.m_m15);

   return *this;
}

Matrix Matrix::operator * (float s) const
{
   return Matrix(
      Vector4(s * m_m0, s * m_m1, s * m_m2, s * m_m3),
      Vector4(s * m_m4, s * m_m5, s * m_m6, s * m_m7),
      Vector4(s * m_m8, s * m_m9, s * m_m10, s * m_m11),
      Vector4(s * m_m12, s * m_m13, s * m_m14, s * m_m15)
   );
}

Matrix& Matrix::operator *= (float s)
{
   m_v0.set(s * m_m0,  s * m_m1,  s * m_m2,  s * m_m3);
   m_v1.set(s * m_m4,  s * m_m5,  s * m_m6,  s * m_m7);
   m_v2.set(s * m_m8,  s * m_m9,  s * m_m10, s * m_m11);
   m_v3.set(s * m_m12, s * m_m13, s * m_m14, s * m_m15);

   return *this;
}




