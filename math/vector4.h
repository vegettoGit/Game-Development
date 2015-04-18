#ifndef VECTOR4
#define VECTOR4

/*
   Vector4: Vector using homogeneous coordinates
*/
struct Vector4
{
   Vector4                  ();
   Vector4                  (float x, float y, float z);
   Vector4                  (float x, float y, float z, float w);

   Vector4                  (const Vector4& v);
   Vector4& operator =      (const Vector4& v);

   Vector4                  (Vector4&& v);
   Vector4& operator =      (Vector4&& v);
   
   ~Vector4                 ();

   float    m_x;
   float    m_y;
   float    m_z;
   float    m_w;
};

#endif

