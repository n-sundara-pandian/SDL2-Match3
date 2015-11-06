
#ifndef MENUSTATE_H
#define MENUSTATE_H

#include <GameStates/CGameState.h>
#include <memory>

class CGameManager;
class CTextRenderer;
struct SDL_Texture;

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
  SDL_Texture *m_splash;
  std::unique_ptr<CTextRenderer> m_gameOverText;
  std::string m_msg;
  std::string m_msg1;
  int m_highScore;
  int m_lastScore;
};

#endif