#include <fat.h>

#include <Constants.h>
#include <Game.h>


/*************************************************/
int main(int argc, char **argv) 
{
   fatInitDefault();

   Polukili::Game game;
   game.run(Polukili::Constants::basePath + "level_0.xml");

   return 0;
}
