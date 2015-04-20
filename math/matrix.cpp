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

