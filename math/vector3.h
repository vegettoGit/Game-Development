/*
   Simple vector using 3 axis

   - Even though we could just rely on the compiler's copy/move,
     some practice with them doesn't hurt :)
*/
struct Vector3
{
   Vector3              ();
   Vector3              (float x, float y, float z);

   Vector3              (const Vector3& v);
   Vector3& operator =  (const Vector3& v);

   Vector3              (Vector3&& v);
   Vector3& operator =  (Vector3&& v);
   
   ~Vector3             ();

   // Dot product
   float    operator *  (const Vector3& v) const;
   
   Vector3  operator +  (const Vector3& v) const;
   Vector3  operator -  (const Vector3& v) const;

   Vector3  operator *  (float) const;

   Vector3& operator += (const Vector3& v);

   Vector3& operator /= (float scalar);

   float    length      () const;
   void     normalize   ();

   float    m_x;
   float    m_y;
   float    m_z;
};
