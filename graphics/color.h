/* 
   Each member is normalized
*/
struct Color
{
   Color              ();
   Color              (float red, float green, float blue);

   // We don't really need our own move/copy constructor and assignment operators here, note that this is just intended to be an example of how to implement our own :)
   Color              (const Color&);
   Color& operator =  (const Color&);

   Color              (Color&&);
   Color& operator =  (Color&&);

   ~Color             ();

   float  m_red;
   float  m_green;
   float  m_blue;
};
