#ifndef polukili_Players_Player_h_08f5452b_7458_424a_adf0_33de30429ebb
#define polukili_Players_Player_h_08f5452b_7458_424a_adf0_33de30429ebb


namespace Polukili 
{
   class Actor;
   
   namespace Players 
   {

      /** 
      *  Represents a player.
      */
      class Player : public Actor
      {

         // Associations
      public:
      
      /**
      * Constructor.
      */
      Player(Level* level);
      

      /**
      * Initialize physic data
      */
      virtual void initPhysic();
      
      virtual void loadGraphics();


         //end of class Player
      };

   } /* End of namespace Polukili::Players */
} /* End of namespace Polukili */

#endif // polukili_Players_Player_h_08f5452b_7458_424a_adf0_33de30429ebb

