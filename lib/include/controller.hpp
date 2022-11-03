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
  Model::Control calcControl(const Model::State &currState);

  /// set new goal state
  void setGoal(Model::State newGoal);

private:
  Model::State m_goal;
  NetOper m_netOper;
  const float Eps = 0.1; // [m]
};
