struct Vector3;

/*

   Link Configuration solver

   - Provided two links Link1 and Link2, with lengths L1 and L2 respectively, 
     knowing Link1 starting point (P1) and Link2 ending point (P2), how many
     configurations can you find for the joint point between the two links?

*/
class LinkConfiguration
{
   LinkConfiguration                     ();
   ~LinkConfiguration                    ();

   LinkConfiguration                     (const LinkConfiguration& v)   = delete;
   LinkConfiguration&       operator =   (const LinkConfiguration& v)   = delete;

   LinkConfiguration                     (LinkConfiguration&& v)        = delete;
   LinkConfiguration&       operator =   (LinkConfiguration&& v)        = delete;

public:

   enum class JointSolution
   { 
      FOUND, 
      NOT_FOUND,
      ERROR_NEGATIVE_LENGTH,
      ERROR 
   };

   static LinkConfiguration& GetInstance ();

   JointSolution             Solve(const Vector3& link1StartPoint, const Vector3& link2EndPoint, float link1Length, float link2Length, Vector3& solution);

};

