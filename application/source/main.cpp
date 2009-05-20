#include <Constants.h>
#include <Game.h>

int main( int argc, char **argv )
{
   Polukili::Game game;
   Logger::log("Game constructed");
   game.run(Polukili::Constants::basePath + "level_0.xml");
   
   return 0;
}
