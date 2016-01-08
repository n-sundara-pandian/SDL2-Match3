

#include <iostream>
#include <GameStates/CGameState.h>
#include <GameStates/BaseState/GameManager.h>
#include <GameStates/CPlayState.h>
#include <GameStates/CMenuState.h>
#include "SDL_image.h"
#include <Utils/CRenderer.h>
#include <Utils/Common.h>
#include <Utils/CAudio.h>

CPlayState CPlayState::m_PlayState;
using namespace std;


void CPlayState::Init(CGameManager* game)
{
  m_game = game;
  SDL_assert(m_game != nullptr);
  m_renderer = m_game->GetRenderer();
  SDL_assert(m_renderer != nullptr);
  m_bg = m_game->GetRenderer()->LoadImage("data/BackGround.png");
  SDL_assert(m_bg != nullptr);
  m_gameHud = make_shared<GameHUD>(game);
  m_board = CBoard(m_game->GetRenderer(), m_gameHud);
  m_stateMachine.Init(&m_board);
  m_board.Init(&m_stateMachine);
}

void CPlayState::Cleanup()
{
}

void CPlayState::Pause()
{
  m_gameHud->Pause();
}

void CPlayState::Resume()
{
  m_gameHud->Resume();
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
        break;
      }
      case SDLK_SPACE:
      {
        break;
      }
    }
  }
  else if (e.type == SDL_MOUSEMOTION && e.button.button == SDL_BUTTON(SDL_BUTTON_LEFT))
  {    
    int move_threshold = 3;
    int x_rel = e.motion.xrel;
    int x_diff = abs(x_rel);
    int y_rel = e.motion.yrel;
    int y_diff = abs(y_rel);
    if (x_diff > move_threshold || y_diff > move_threshold)
    {
      ResetHint();
      if ((m_stateMachine.GetState() == CBoard::State::OneItemSelected) || (m_stateMachine.GetState() == CBoard::State::Hint))
        m_stateMachine.Go(CBoard::State::Idle);
      m_board.RespondToSwipe(Vector2i(e.motion.x, e.motion.y), Vector2i(x_rel, y_rel), Vector2i(x_diff, y_diff));
    }
  }
  else if (e.type == SDL_MOUSEBUTTONDOWN)
  {
    if (e.button.button == SDL_BUTTON_LEFT)
    {
      int selected_item = Utils::GetTileFromScreenPosition(e.button.x, e.button.y);
      if (selected_item != -1 && m_stateMachine.CanAcceptInput())
      {
        CBoard::State state = m_stateMachine.GetState();
        switch (state)
        {
        case CBoard::State::Hint:
        case CBoard::State::Idle:
        {
            m_board.AddSelectedItem(selected_item);
            m_board.CalculateNextValidTiles(selected_item);
            m_stateMachine.Go(CBoard::State::OneItemSelected);
            ResetHint();
            CAudio::Player.Play("Select");
            break;
        }
        case CBoard::State::OneItemSelected:
        {
          if (m_board.IsValidSelection(selected_item))
          {
            m_board.AddSelectedItem(selected_item);
            m_stateMachine.Go(CBoard::State::BothItemSelected);
            ResetHint();
            CAudio::Player.Play("Select");
          }
          else
          {
            m_board.ClearSeleceteditemList();
            m_stateMachine.Go(CBoard::State::Idle);
            ResetHint();
          }
          break;
        }
        }
      }
    }
  }
}

void CPlayState::Update(float dt)
{
  if (m_board.IsBoardReady())
    m_gameHud->Resume();
  m_board.Update(dt);
  m_stateMachine.Update(dt);
  m_gameHud->Update(dt);
  m_HintTimer += dt;
  if (m_HintTimer > Utils::gHintTime)
  {
    HandleHintState();
    ResetHint();
  }

  if (m_gameHud->IsGameOver() && ((m_stateMachine.GetState() == CBoard::State::Idle) || (m_stateMachine.GetState() == CBoard::State::Hint)))
  {
    m_game->ChangeState(CMenuState::Instance());
  }
}

void CPlayState::Draw()
{
  m_renderer->Clear();
  m_renderer->Render(m_bg);
  m_board.Draw();
  m_gameHud->Draw();
  m_renderer->Flip();
}

void CPlayState::HandleHintState()
{
  CBoard::State state = m_stateMachine.GetState();
  if (state == CBoard::State::Idle)
  {
    m_stateMachine.Go(CBoard::State::Hint);
  }
}