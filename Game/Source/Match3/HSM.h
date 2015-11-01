#ifndef HSM_H
#define HSM_H
#include <Match3/CBoard.h>
class HSM {
  typedef void (HSM::*DoAction)(void);
public:
  typedef std::map<std::pair<CBoard::State, CBoard::State>, CBoard::DoAction > TransitionMap;
  HSM();
  void Init(CBoard *board);
  void Go(CBoard::State nextState);
  bool CanTransit(CBoard::State nextState);
  bool CanAcceptInput() { return m_currentState == CBoard::State::Idle || m_currentState == CBoard::State::OneItemSelected; }
  CBoard::State GetState();
  void AddTransit(std::pair<CBoard::State, CBoard::State> state_pair, HSM::DoAction transition);

private:
  TransitionMap m_transitionMap;
  CBoard *m_board;
  CBoard::State m_currentState;
};

#endif /*HSM_H*/