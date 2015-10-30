
#include <GameStates/BaseState/GameManager.h>
#include <GameStates/CIntroState.h>
#include "SDL_events.h"
#include "SDL_timer.h"

int main ( int argc, char *argv[] )
{
	CGameManager game;
  const int FPS = 60;
  const int TICK = 1000 / FPS;
  const int max_frame_skip = 10;

	// initialize the engine
	game.Init( "Engine Test v1.0" );

	// load the intro
	game.ChangeState( CIntroState::Instance() );
  SDL_Event input_event;
  int this_time = SDL_GetTicks();
  int last_time = this_time + 1;
	// main loop
	while ( game.Running() )
	{
    this_time = SDL_GetTicks();
    while (SDL_PollEvent(&input_event))
    {
      game.HandleEvents(input_event);
    }		
    game.Update((float)(this_time - last_time) / 1000);
		game.Draw();
    last_time = this_time;
	}

	// cleanup the engine
	game.Cleanup();

	return 0;
}
