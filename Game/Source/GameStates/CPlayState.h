
#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include <GameStates/CGameState.h>
#include "SDL_render.h"
class CGameManager;
class CPlayState : public CGameState
{
public:
  void Init(CGameManager* game) override;
	void Cleanup() override;

	void Pause() override;
	void Resume() override;

  void HandleEvents(const SDL_Event &e) override;
	void Update(float dt) override;
	void Draw() override;

	static CPlayState* Instance() {
		return &m_PlayState;
	}

protected:
	CPlayState() { }

private:
	static CPlayState m_PlayState;
  CGameManager* m_game;
  SDL_Texture *m_bg;
};

#endif
