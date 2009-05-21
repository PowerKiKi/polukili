#include <Constants.h>
#include <Game.h>

#include <Logger.h>

int main( int argc, char **argv )
{
   Polukili::Game game;
   Polukili::Logger::log("Game constructed");
   game.run(Polukili::Constants::basePath + "level_0.xml");
   
   return 0;
}
