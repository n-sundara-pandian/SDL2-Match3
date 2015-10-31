

#include <iostream>


#include <GameStates/CGameState.h>
#include <GameStates/BaseState/GameManager.h>
#include <GameStates/CPlayState.h>
#include <GameStates/CMenuState.h>
#include "SDL_image.h"
#include "Utils/CRenderer.h"
#include "Utils/Common.h"

CPlayState CPlayState::m_PlayState;
using namespace std;


void CPlayState::Init(CGameManager* game)
{
  m_game = game;
  m_bg = m_game->GetRenderer()->loadImage("data/BackGround.jpg");  
  if (m_bg == nullptr)
  {
    SDL_assert(m_bg != nullptr);
    return;
  }
  m_board = CBoard(m_game->GetRenderer());
}

void CPlayState::Cleanup()
{
  
}

void CPlayState::Pause()
{
}

void CPlayState::Resume()
{
}

void CPlayState::HandleEvents(const SDL_Event &e)
{
  if (e.type == SDL_KEYDOWN)
  {
    switch (e.key.keysym.sym)
    {
      case SDLK_ESCAPE:
      {
        m_game->Quit();
        break;
      }
      case SDLK_m:
      {
        m_game->PushState(CMenuState::Instance());
        break;
      }
      case SDLK_SPACE:
      {
        m_board.RemoveMatches();
        //m_board.AnalyseBoard();
        break;
      }
    }
  }
  else if (e.type == SDL_MOUSEMOTION && e.button.button == SDL_BUTTON(SDL_BUTTON_RIGHT))
  {
  }
  else if (e.type == SDL_MOUSEBUTTONDOWN)
  {
    if (e.button.button == SDL_BUTTON_LEFT)
    {
      //Get the mouse offsets
      SDL_Log(" Grid Point %d ", Utils::GetTile(e.button.x, e.button.y));
      int selected_item = Utils::GetTile(e.button.x, e.button.y);
      if (selected_item != -1)
        m_board.SetItemVisible(selected_item, CItem::State::InActive);
      m_board.AnalyseBoard();
    }
    if (e.button.button == SDL_BUTTON_RIGHT)
    {
      int selected_item = Utils::GetTile(e.button.x, e.button.y);
      if (selected_item != -1)
      {
        SDL_Log("color at %d is %s", selected_item, Utils::GetFileName(m_board.GetColorAt(selected_item)).c_str());
      }
    }
  }
}

void CPlayState::Update(float dt)
{
  m_board.Update(dt);
}

void CPlayState::Draw()
{
  CRenderer *renderer = m_game->GetRenderer();
  renderer->clear();
  renderer->renderTexture(m_bg);
  m_board.Draw();
  renderer->flip();
}

