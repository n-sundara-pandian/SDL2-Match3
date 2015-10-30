
#ifndef GAMEENGINE_H
#define GAMEENGINE_H


#include <vector>
#include "SDL_events.h"

using namespace std;
class CGameState;
struct SDL_Window;
class CRenderer;

class CGameManager
{
public:

	void Init(const char* title, int width=640, int height=480, 
		      int bpp=0);
	void Cleanup();

	void ChangeState(CGameState* state);
	void PushState(CGameState* state);
	void PopState();

	void HandleEvents(const SDL_Event &e);
	void Update(float dt);
	void Draw();

	bool Running() { return m_running; }
	void Quit() { m_running = false; }

  CRenderer *GetRenderer() { return m_renderer; }
private:
	// the stack of states
	vector<CGameState*> states;
  SDL_Window *m_window;
  CRenderer *m_renderer;

	bool m_running;
	bool m_fullscreen;
};

#endif
