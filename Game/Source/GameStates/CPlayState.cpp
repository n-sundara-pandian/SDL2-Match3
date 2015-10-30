

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
  //if (e.type == SDL_KEYDOWN)
  switch (e.type)
  {
  case SDL_KEYDOWN:
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
      /*case SDLK_0:
      {
        for (int i = 0; i < m_gameBoard.size(); i++)
        {
          m_gameBoard[i].SetTexture(m_game->GetRenderer(), "data/Red.png");
        }
        break;
      }
      case SDLK_1:
      {
        for (int i = 0; i < m_gameBoard.size(); i++)
        {
          m_gameBoard[i].SetTexture(m_game->GetRenderer(), "data/Blue.png");
        }
        break;
      }
      case SDLK_2:
      {
        for (int i = 0; i < m_gameBoard.size(); i++)
        {
          m_gameBoard[i].SetTexture(m_game->GetRenderer(), "data/Green.png");
        }
        break;
      }
      case SDLK_3:
      {
        for (int i = 0; i < m_gameBoard.size(); i++)
        {
          m_gameBoard[i].SetTexture(m_game->GetRenderer(), "data/Purple.png");
        }
        break;
      }
      case SDLK_4:
      {
        for (int i = 0; i < m_gameBoard.size(); i++)
        {
          m_gameBoard[i].SetTexture(m_game->GetRenderer(), "data/Yellow.png");
        }
        break;
      }*/
    }
    break;
  case SDL_MOUSEBUTTONDOWN:
    if (e.button.button == SDL_BUTTON_LEFT)
    {
      //Get the mouse offsets
      cout <<  e.button.x + " " +  e.button.y;
    }
  default:
    break;
  }
}

void CPlayState::Update(float dt)
{
  
}

void CPlayState::Draw()
{
  CRenderer *renderer = m_game->GetRenderer();
  renderer->clear();
  renderer->renderTexture(m_bg);
  m_board.Draw();
  renderer->flip();
}

