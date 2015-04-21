#include "matrix.h"
#include <utility>


Matrix::Matrix()
{
}

Matrix::Matrix(const Vector4& v0, const Vector4& v1, const Vector4& v2, const Vector4& v3)
   : m_v0(v0),
     m_v1(v1),
     m_v2(v2),
     m_v3(v3)
{
}

Matrix::Matrix(const Matrix& m)
{
   *this = m;
}

Matrix& Matrix::operator = (const Matrix& m)
{
   m_v0 = m.m_v0;
   m_v1 = m.m_v1;
   m_v2 = m.m_v2;
   m_v3 = m.m_v3;

   return *this;
}

Matrix::Matrix(Matrix&& m)
{
   *this = std::move(m);
}

Matrix& Matrix::operator = (Matrix&& m)
{
   m_v0 = std::move(m.m_v0);
   m_v1 = std::move(m.m_v1);
   m_v2 = std::move(m.m_v2);
   m_v3 = std::move(m.m_v3);

   m.m_v0.reset();
   m.m_v1.reset();
   m.m_v2.reset();
   m.m_v3.reset();

   return *this;
}

Matrix::~Matrix()
{
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

void Matrix::operator += (const Matrix &m)
{
   m_v0.set(m_m0 + m.m_m0,   m_m1 + m.m_m1,   m_m2 + m.m_m2,   m_m3 + m.m_m3);
   m_v1.set(m_m4 + m.m_m4,   m_m5 + m.m_m5,   m_m6 + m.m_m6,   m_m7 + m.m_m7);
   m_v2.set(m_m8 + m.m_m8,   m_m9 + m.m_m9,   m_m10 + m.m_m10, m_m11 + m.m_m11);
   m_v3.set(m_m12 + m.m_m12, m_m13 + m.m_m13, m_m14 + m.m_m14, m_m15 + m.m_m15);
}


