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

public:

   enum class JointSolution
   { 
      FOUND, 
      NOT_FOUND,
      ERROR_NEGATIVE_LENGTH,
      ERROR 
   };

   LinkConfiguration                     (const LinkConfiguration& linkConfiguration) = delete;
   LinkConfiguration&       operator =   (const LinkConfiguration& linkConfiguration) = delete;

   LinkConfiguration                     (LinkConfiguration&& linkConfiguration)      = delete;
   LinkConfiguration&       operator =   (LinkConfiguration&& linkConfiguration)      = delete;

   static LinkConfiguration& getInstance ();

   JointSolution             solve       (const Vector3& link1StartPoint, const Vector3& link2EndPoint, float link1Length, float link2Length, Vector3& solution);

};

