#ifndef VECTOR3
#define VECTOR3

struct Matrix;

/*
   Simple vector using 3 axis

   - Even though we could just rely on the compiler's copy/move,
     some practice with them doesn't hurt :)
*/
struct Vector3
{
   Vector3                  ();
   Vector3                  (float x, float y, float z);

   Vector3                  (const Vector3& v)            = default;
   Vector3& operator =      (const Vector3& v)            = default;

   Vector3                  (Vector3&& v)                 = default;
   Vector3& operator =      (Vector3&& v)                 = default;
   
   ~Vector3                 ()                            = default;

   // Dot product
   float    operator *      (const Vector3& v) const;
   
   Vector3  operator +      (const Vector3& v) const;
   Vector3  operator -      (const Vector3& v) const;

   Vector3& operator +=     (const Vector3& v);

   Vector3& operator *=     (Matrix &m);

   Vector3  operator *      (float) const;
   Vector3& operator /=     (float scalar);

   Vector3  cross           (const Vector3& v) const;
   bool     isPerpendicular (const Vector3& v) const;

   // Returns the angle in radians between this vector and v
   float    getAngle        (const Vector3& v) const;

   float    length          () const;
   float    squaredLength   () const;
   void     normalize       ();
   void     set             (float x, float y, float z);
   void     reset           ();

   float    m_x;
   float    m_y;
   float    m_z;
};

#endif

