#include "model.hpp"
#include <cmath>

Model::Model(const State &state_, float dt_): 
  mCurrentState(state_),
  dt(dt_) 
  {

  }

void Model::setState(const State &state_) 
{ 
  mCurrentState = state_; 
}

const Model::State &Model::getState() 
{ 
  return mCurrentState; 
}

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
