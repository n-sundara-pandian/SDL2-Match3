
#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include <GameStates/CGameState.h>
#include <Utils/CSprite.h>
#include <Match3/CBoard.h>
#include <Match3/HSM.h>
#include <GUI/GameHud.h>

class CGameManager;
class CRenderer;

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

  void GameOver();

	static CPlayState* Instance() {
		return &m_PlayState;
	}

protected:
	CPlayState() { }

private:
	static CPlayState m_PlayState;

  CBoard m_board;
  HSM m_stateMachine;
  CGameManager* m_game;
  GameHUD *m_gameHud;
  SDL_Texture *m_bg;
  
};

#endif
