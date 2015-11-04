#ifndef HSM_H
#define HSM_H
#include <Match3/CBoard.h>
class HSM {

public:
  typedef std::map<std::pair<CBoard::State, CBoard::State>, CBoard::DoAction > TransitionMap;
  HSM();
  void Init(CBoard *board);
  void Go(CBoard::State nextState, float delay = 0);
  bool CanTransit(CBoard::State nextState);
  bool CanAcceptInput() { return m_currentState == CBoard::State::Idle || m_currentState == CBoard::State::OneItemSelected; }
  CBoard::State GetState();
  void AddTransit(std::pair<CBoard::State, CBoard::State> state_pair, CBoard::DoAction transition);
  void Update(float dt);
private:
  TransitionMap m_transitionMap;
  CBoard *m_board;
  CBoard::State m_currentState;
  CBoard::State m_nextState;
  float m_elapsedTime;
  float m_targetDelay;

private:
  void DoTransition();

};

#endif /*HSM_H*/