
#ifndef GAMEENGINE_H
#define GAMEENGINE_H


#include <vector>
#include <map>
#include "SDL_events.h"


class CGameState;
struct SDL_Window;
class CRenderer;

extern "C" { typedef struct _TTF_Font TTF_Font; }
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
  TTF_Font *GetFont(std::string font_name){ return m_fontList[font_name]; }
  CRenderer *GetRenderer() { return m_renderer; }
private:
	// the stack of states
	std::vector<CGameState*> states;
  std::map<std::string, TTF_Font*> m_fontList;
  SDL_Window *m_window;
  CRenderer *m_renderer;

	bool m_running;
	bool m_fullscreen;
};

#endif
