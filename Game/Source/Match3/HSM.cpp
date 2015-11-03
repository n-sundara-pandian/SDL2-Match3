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
  m_transitionMap[std::make_pair(CBoard::State::Idle, CBoard::State::OneItemSelected)] = &CBoard::ToOneItemSelected;
  m_transitionMap[std::make_pair(CBoard::State::OneItemSelected, CBoard::State::BothItemSelected)] = &CBoard::ToBothItemSelected;
  m_transitionMap[std::make_pair(CBoard::State::OneItemSelected, CBoard::State::Idle)] = &CBoard::ToIdle;

  // validate
  m_transitionMap[std::make_pair(CBoard::State::BothItemSelected, CBoard::State::SwapItem)] = &CBoard::ToTestSwapItem;
  m_transitionMap[std::make_pair(CBoard::State::SwapItem, CBoard::State::ValidateMove)] = &CBoard::ToValidateMove;

  // invalid
  m_transitionMap[std::make_pair(CBoard::State::ValidateMove, CBoard::State::NonMatchingMove)] = &CBoard::ToInvalidMove;
  m_transitionMap[std::make_pair(CBoard::State::NonMatchingMove, CBoard::State::Idle)] = &CBoard::ToIdle;

  m_transitionMap[std::make_pair(CBoard::State::ValidateMove, CBoard::State::MatchingMove)] = &CBoard::ToActualSwap;
  m_transitionMap[std::make_pair(CBoard::State::MatchingMove, CBoard::State::ValidateBoard)] = &CBoard::ToValidateBoard;
  m_transitionMap[std::make_pair(CBoard::State::ValidateBoard, CBoard::State::Idle)] = &CBoard::ToIdle;
  //m_transitionMap[std::make_pair(CBoard::State::ValidMove, CBoard::State::ValidateBoard)] = &CBoard::ToValidateBoard;
  //m_transitionMap[std::make_pair(CBoard::State::ValidateBoard, CBoard::State::Idle)] = &CBoard::ToIdle;
  //m_transitionMap[std::make_pair(CBoard::State::GenerateBoard, CBoard::State::ValidateBoard)] = &CBoard::ToValidateBoard;
  //m_transitionMap[std::make_pair(CBoard::State::GenerateBoard, CBoard::State::Idle)] = &CBoard::ToIdle;
}
void HSM::Go(CBoard::State nextState, float delay) {
  m_targetDelay = delay;
  m_elapsedTime = 0.0f;
  m_nextState = nextState;
  if (m_targetDelay == 0.0f)
    DoTransition();
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
    DoTransition();
    m_targetDelay = m_elapsedTime = 0;
  }
}

void HSM::DoTransition()
{
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
  SDL_Log(" transferring from %s to %s . . .", Utils::ToString(m_currentState).c_str(), Utils::ToString(m_nextState).c_str());
  m_currentState = m_nextState;
  (m_board->*m_transitionMap[transition])();
}