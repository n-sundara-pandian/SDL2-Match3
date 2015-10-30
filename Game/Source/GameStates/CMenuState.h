
#ifndef MENUSTATE_H
#define MENUSTATE_H

#include <GameStates/CGameState.h>

class CGameManager;
class CMenuState : public CGameState
{
public:
  void Init(CGameManager* game) override;
	void Cleanup() override;

	void Pause() override;
	void Resume() override;

  void HandleEvents(const SDL_Event &e) override;
	void Update(float dt) override;
	void Draw() override;

	static CMenuState* Instance() {
		return &m_MenuState;
	}

protected:
	CMenuState() { }

private:
	static CMenuState m_MenuState;
  CGameManager* m_game;
};

#endif