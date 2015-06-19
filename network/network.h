/* 
   Generic Network class in charge of the configuration of a Network layer built on the Windows OS

   - As many of the following functions are blocking, it is recommended to consider their usage in an
     asynchronous manner.
*/

#include <winsock2.h>

class Network
{

public:

   enum class NetworkError
   {
      NONE,
      ERROR_INITIALIZATION_SOCKETS,
      UNKNOWN_ERROR
   };

   struct NetworkResult
   {
      NetworkResult()
         : m_error        (NetworkError::NONE),
           m_internalError(0)
      {
      }

      NetworkError m_error;
      int          m_internalError;
   };

   static Network& getInstance ();
   NetworkResult   initialize  ();

private:

   Network                     ()                         ;

   Network                     (const Network& )  = delete;
   Network&        operator =  (const Network& v) = delete;

   Network                     (Network&& )       = delete;
   Network&        operator =  (Network&& v)      = delete;

   ~Network                    ();

   WSADATA         m_wsaData;

};
