
#include <GameStates/BaseState/GameManager.h>
#include <GameStates/CIntroState.h>
#include "SDL_events.h"
#include "SDL_timer.h"

int main ( int argc, char *argv[] )
{
	CGameManager game;

	game.Init( "King Match3 Test" );
  game.ChangeState( CIntroState::Instance() );
  SDL_Event input_event;
  int this_time = SDL_GetTicks();
  int last_time = this_time + 1;
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
	game.Cleanup();

	return 0;
}
