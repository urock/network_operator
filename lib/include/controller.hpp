#pragma once

#include "model.hpp"
#include "nop.hpp"

#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

class Controller 
{
public:
  Controller(const Model::State &goalState, NetOper &netOper);
  /// RP from pascal version
  virtual Model::Control calcControl(const Model::State &currState);
  /// set new goal state
  void setGoal(Model::State newGoal);
  
  NetOper& netOper();

  void setUMax(float newUMax);
  void setEps(float newEps);

protected:
  Model::State m_goal;
  NetOper m_netOper;
  float Eps = 0.1; // [m]
  float Umax = 10.f;
};
