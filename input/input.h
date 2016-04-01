/* 
   Input class receiving and reacting to all kinds of player input
*/

class Input
{   

   Input();
   ~Input();

public:

   Input                          (const Input& input) = delete;
   Input&          operator =     (const Input& input) = delete;

   Input                          (Input&& input)      = delete;
   Input&          operator =     (Input&& input)      = delete;

   static Input&   getInstance();

   static void     onKeyPressed   (unsigned char charASCII, int mouseX, int mouseY);

   static bool     extractKey     (unsigned char& charASCII);

private:

   static bool          m_availableKey;
   static unsigned char m_key;

};
