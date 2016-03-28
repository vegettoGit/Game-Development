/* 
   Each member is normalized
*/
struct Color
{
   Color              ();
   Color              (float red, float green, float blue);

   Color              (const Color&);
   Color& operator =  (const Color&);

   Color              (Color&&);
   Color& operator =  (Color&&);

   ~Color             ();

   float  m_red;
   float  m_green;
   float  m_blue;
};
