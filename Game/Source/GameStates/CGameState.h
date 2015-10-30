
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <GameStates/BaseState/GameManager.h>
#include "SDL_events.h"
#include "SDL_Assert.h"


class CGameManager;
class CGameState
{
public:
  virtual void Init(CGameManager* game) = 0;
	virtual void Cleanup() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

  virtual void HandleEvents(const SDL_Event &e) = 0;
	virtual void Update(float dt) = 0;
	virtual void Draw() = 0;

	void ChangeState(CGameManager* game, CGameState* state) {
		m_game->ChangeState(state);
	}

protected:
	CGameState() { }
  CGameManager* m_game;
};

#endif