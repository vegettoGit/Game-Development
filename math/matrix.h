#ifndef MATRIX
#define MATRIX

#include "vector4.h"

/*
   Matrix
*/
struct Matrix
{
   enum class RotationType
   {
      X,
      Y,
      Z
   };

   Matrix                  ();
   Matrix                  (const Vector4& v0, const Vector4& v1, const Vector4& v2, const Vector4& v3);
   Matrix                  (RotationType rotationType, float angle);

   Matrix                  (const Matrix& m)     = default;
   Matrix& operator =      (const Matrix& m)     = default;

   Matrix                  (Matrix&& m)          = default;
   Matrix& operator =      (Matrix&& m)          = default;
   
   ~Matrix                 ()                    = default;

   void    set             (const Vector4& v0, const Vector4& v1, const Vector4& v2, const Vector4& v3);

   Matrix  operator +      (const Matrix &m) const;
   Matrix& operator +=     (const Matrix &m);
   Matrix  operator -      (const Matrix &m) const;
   Matrix& operator -=     (const Matrix &m);
   Matrix  operator *      (const Matrix &m) const;
   Matrix& operator *=     (const Matrix &m);
   Matrix  operator *      (float s) const;
   Matrix& operator *=     (float s);

   union
   {
      struct
      {
         Vector4 m_v0;
         Vector4 m_v1;
         Vector4 m_v2;
         Vector4 m_v3;
      };

      struct
      {
         float m_m0;
         float m_m1;
         float m_m2;
         float m_m3;
         float m_m4;
         float m_m5;
         float m_m6;
         float m_m7;
         float m_m8;
         float m_m9;
         float m_m10;
         float m_m11;
         float m_m12;
         float m_m13;
         float m_m14;
         float m_m15;
      };
   };

};

#endif

