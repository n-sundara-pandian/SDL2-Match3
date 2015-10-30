
#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include <GameStates/CGameState.h>
//#include "SDL_render.h"
#include "Utils/Sprite.h"
class CGameManager;
class Renderer;
class Item
{
public:
  enum class Color
  {
    Red,
    Blue,
    Green,
    Yellow,
    Purple
  };
  enum class Status
  {
    Moving,
    Active,
    InActive
  };
public:
  Item() 
    : m_color(Color::Red) 
    , m_status(Status::Active)
  {}
  
private:
  Vector<int> m_position;
  Vector<float> m_actualPosition;
  Vector<float> m_targetPosition;
  Color m_color;
  Status m_status;
};

class Board
{
public:
  Board(){}
  Board(Renderer* renderer);
  void GenerateBoard();
  void Draw();

private:
  std::vector<Item> m_itemList;
  std::vector<Sprite> m_spriteList;
  Renderer *m_renderer;
  int m_boardSize;
  int m_currentItem;
};
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
  Board m_board;
};

#endif
