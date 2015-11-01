#include <Match3/HSM.h>
#include <Match3/CBoard.h>

HSM::HSM() 
  : m_currentState(CBoard::State::Idle)
  , m_board(nullptr)
{
}

void HSM::Init(CBoard *board)
{
  m_board = board;
  m_transitionMap[std::make_pair(CBoard::State::Idle, CBoard::State::OneItemSelected)] = &CBoard::ToOneItemSelected;
  m_transitionMap[std::make_pair(CBoard::State::OneItemSelected, CBoard::State::BothItemSelected)] = &CBoard::ToBothItemSelected;
  m_transitionMap[std::make_pair(CBoard::State::BothItemSelected, CBoard::State::SwapItem)] = &CBoard::ToTestSwapItem;
  m_transitionMap[std::make_pair(CBoard::State::SwapItem, CBoard::State::ValidateMove)] = &CBoard::ToValidateMove;
  m_transitionMap[std::make_pair(CBoard::State::ValidateMove, CBoard::State::InvalidMove)] = &CBoard::ToInvalidMove;
  m_transitionMap[std::make_pair(CBoard::State::InvalidMove, CBoard::State::Idle)] = &CBoard::ToIdle;
  m_transitionMap[std::make_pair(CBoard::State::ValidateMove, CBoard::State::ValidMove)] = &CBoard::ToActualSwap;
  m_transitionMap[std::make_pair(CBoard::State::ValidMove, CBoard::State::ValidateBoard)] = &CBoard::ToValidateBoard;
  m_transitionMap[std::make_pair(CBoard::State::ValidateBoard, CBoard::State::GenerateBoard)] = &CBoard::ToGenerateBoard;
  m_transitionMap[std::make_pair(CBoard::State::GenerateBoard, CBoard::State::ValidateBoard)] = &CBoard::ToValidateBoard;
  m_transitionMap[std::make_pair(CBoard::State::ValidateBoard, CBoard::State::Idle)] = &CBoard::ToIdle;
}
void HSM::Go(CBoard::State nextState) {
  std::pair<CBoard::State, CBoard::State> transition = std::make_pair(m_currentState, nextState);
  if (m_transitionMap.find(transition) == m_transitionMap.end()) {
    SDL_Log(" Failed to transfer state . . .");
    return;
  }
  m_currentState = nextState;
  (m_board->*m_transitionMap[transition])();
}

bool HSM::CanTransit(CBoard::State nextState) {
  std::pair<CBoard::State, CBoard::State> transition = std::make_pair(m_currentState, nextState);
  return !(m_transitionMap.find(transition) == m_transitionMap.end());
}

CBoard::State HSM::GetState() {
  return m_currentState;
}

void HSM::AddTransit(std::pair<CBoard::State, CBoard::State> state_pair, HSM::DoAction transition)
{
  //m_transitionMap[state_pair] = transition;
}