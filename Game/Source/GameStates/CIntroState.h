
#ifndef INTROSTATE_H
#define INTROSTATE_H

#include <GameStates/CGameState.h>

struct SDL_Texture;
class CGameManager;

class CIntroState : public CGameState
{
public:
  void Init(CGameManager* game) override; 
	void Cleanup() override;

	void Pause() override;
	void Resume() override;

  void HandleEvents(const SDL_Event &e) override;
	void Update( float dt) override;
	void Draw() override;

	static CIntroState* Instance() {
		return &m_IntroState;
	}

protected:
	CIntroState() { }

private:
	static CIntroState m_IntroState;
  float m_elapsed_time;
  float m_timeout;
  CGameManager* m_game;
  SDL_Texture *m_splash;
  bool m_active;
};

#endif