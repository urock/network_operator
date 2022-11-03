#include "model.hpp"

// Model::Control

Model::Control operator+(const Control &ctrl) const 
{
  return Control{this->left + ctrl.left, this->right + ctrl.right};
}

Model::Control operator-(const Control &ctrl) const 
{
  return Control{this->left - ctrl.left, this->right - ctrl.right};
}

Model::Control operator*(float val) const 
{
  return Control{this->left * val, this->right * val};
}

// Model::State

Model::State operator+(const State &state) 
{
  return State{this->x + state.x, this->y + state.y, this->yaw + state.yaw};
}

Model::State operator-(const State &state) 
{
  return State{this->x - state.x, this->y - state.y, this->yaw - state.yaw};
}

Model::State operator*(float val) 
{
  return State{this->x * val, this->y * val, this->yaw * val};
}

float dist(const State &state) 
{
  float dx = fabs(this->x - state.x);
  float dy = fabs(this->y - state.y);
  float dyaw = fabs(this->yaw - state.yaw);

  return std::sqrt(dx * dx + dy * dy + dyaw * dyaw);
}

void print() 
{
  std::cout << x << " " << y << " " << yaw << "\n";
}

// Model::Model

Model::Model(const State &state, float dt): 
  m_currentState(state),
  m_dt(dt) 
  {}

void Model::setState(const State &state) 
{ 
  mCurrentState = state; 
}

const Model::State &Model::getState() 
{ 
  return mCurrentState; 
}

// State getNextState(const Control &u)
// {
//   State deltaState = m_dt * State{k * (u.left + u.right) * cosf(mCurrentState.yaw),
//                                   k * (u.left + u.right) * sinf(mCurrentState.yaw),
//                                   k * (u.left - u.right)};

//   return mCurrentState + deltaState;
// }

Model::State Model::calcVelocity(const Control &u) 
{
  return  State{k * (u.left + u.right) * cosf(mCurrentState.yaw),
                k * (u.left + u.right) * sinf(mCurrentState.yaw),
                k * (u.left - u.right)};
}

Model::State Model::calcState(State &Vs) 
{
  return mCurrentState + Vs * dt;
}

Model::State Model::calcState(const Control &u) 
{
  auto Vs = calcVelocity(u);
  return calcState(Vs);
}

