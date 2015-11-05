#include <Match3/HSM.h>
#include <Match3/CBoard.h>
#include "Utils/Common.h"

HSM::HSM() 
  : m_currentState(CBoard::State::Idle)
  , m_board(nullptr)
  , m_elapsedTime(0)
  , m_targetDelay(0)
{
}

void HSM::Init(CBoard *board)
{
  m_board = board;
  // selection states
  m_transitionMap[std::make_pair(CBoard::State::Idle, CBoard::State::OneItemSelected)] = &CBoard::OnOneSelected;
  m_transitionMap[std::make_pair(CBoard::State::Idle, CBoard::State::Hint)] = &CBoard::ToHint;
  m_transitionMap[std::make_pair(CBoard::State::Hint, CBoard::State::OneItemSelected)] = &CBoard::OnOneSelected;
  m_transitionMap[std::make_pair(CBoard::State::OneItemSelected, CBoard::State::BothItemSelected)] = &CBoard::OnBothItemSelected;
  m_transitionMap[std::make_pair(CBoard::State::OneItemSelected, CBoard::State::Idle)] = &CBoard::ToIdle;
  m_transitionMap[std::make_pair(CBoard::State::Idle, CBoard::State::BothItemSelected)] = &CBoard::OnBothItemSelected;

  m_transitionMap[std::make_pair(CBoard::State::Idle, CBoard::State::ValidateBoard)] = &CBoard::ToValidateBoard;

  // validate
  m_transitionMap[std::make_pair(CBoard::State::BothItemSelected, CBoard::State::SwapItem)] = &CBoard::OnMakeMove;
  m_transitionMap[std::make_pair(CBoard::State::SwapItem, CBoard::State::ValidateMove)] = &CBoard::ToValidateMove;

  // invalid
  m_transitionMap[std::make_pair(CBoard::State::ValidateMove, CBoard::State::NonMatchingMove)] = &CBoard::ToInvalidMove;
  m_transitionMap[std::make_pair(CBoard::State::NonMatchingMove, CBoard::State::Idle)] = &CBoard::ToIdle;

  m_transitionMap[std::make_pair(CBoard::State::ValidateMove, CBoard::State::MatchingMove)] = &CBoard::ToActualSwap;
  m_transitionMap[std::make_pair(CBoard::State::MatchingMove, CBoard::State::ValidateBoard)] = &CBoard::ToValidateBoard;
  m_transitionMap[std::make_pair(CBoard::State::ValidateBoard, CBoard::State::FallDown)] = &CBoard::ToFallDown;
  m_transitionMap[std::make_pair(CBoard::State::FallDown, CBoard::State::GenerateBoard)] = &CBoard::ToGenerateBoard;
  m_transitionMap[std::make_pair(CBoard::State::GenerateBoard, CBoard::State::SyncBoard)] = &CBoard::ToSyncBoard;
  m_transitionMap[std::make_pair(CBoard::State::SyncBoard, CBoard::State::ValidateBoard)] = &CBoard::ToValidateBoard;
  m_transitionMap[std::make_pair(CBoard::State::ValidateBoard, CBoard::State::Idle)] = &CBoard::ToIdle;
}
void HSM::Go(CBoard::State nextState, float delay) {
  if (!m_board->IsBoardReady())
  {
    m_nextState = nextState;
    DoTransition();
    return;
  }
  m_elapsedTime = 0.0f;
  m_nextState = nextState;
  if (delay == 0)
    DoTransition();
  else
    m_targetDelay = delay;
}

bool HSM::CanTransit(CBoard::State nextState) {
  std::pair<CBoard::State, CBoard::State> transition = std::make_pair(m_currentState, nextState);
  return !(m_transitionMap.find(transition) == m_transitionMap.end());
}

CBoard::State HSM::GetState() {
  return m_currentState;
}

void HSM::AddTransit(std::pair<CBoard::State, CBoard::State> state_pair, CBoard::DoAction transition)
{
  m_transitionMap[state_pair] = transition;
}

void HSM::Update(float dt)
{
  if (m_targetDelay > 0)
    m_elapsedTime += dt;
  if (m_targetDelay < m_elapsedTime)
  {
    m_targetDelay = 0;
    DoTransition();
  }
}

void HSM::DoTransition()
{
  if (m_currentState == m_nextState)
  {
    //SDL_Log(" Transfer to itself : can be dangerous %s ", Utils::ToString(m_currentState).c_str());
    return; 
  }
  std::pair<CBoard::State, CBoard::State> transition = std::make_pair(m_currentState, m_nextState);
  if (m_transitionMap.find(transition) == m_transitionMap.end()) {
    if (m_nextState == CBoard::State::Idle)
    {
      m_transitionMap[transition] = &CBoard::ToIdle;
    }
    else
    {
      SDL_Log(" Failed to transfer state . . . %s to %s ", Utils::ToString(m_currentState).c_str(), Utils::ToString(m_nextState).c_str());
      return;
    }
  }
  m_currentState = m_nextState;
  (m_board->*m_transitionMap[transition])();
}