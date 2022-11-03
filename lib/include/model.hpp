#pragma once
#include <iostream>
#include <vector>
#include <cmath>

class Model {

public:

struct Control 
{
  float left;
  float right;

  Control operator+(const Control &ctrl);   
  Control operator-(const Control &ctrl);
  Control operator*(float val);
};

struct State 
{
  float x;
  float y;
  float yaw;

  bool operator==(const State &state);
  State operator+(const State &state);
  State operator-(const State &state);
  State operator*(float val);
  float dist(const State &state);
  float distXY(const State &state);
  void print();
};

public:
  Model(const State &state, float dt);
  void setState(const State &state);
  const State& getState();
  State velocityFromControl(const Control &u) ;
  State nextStateFromVelocity(State &vel) ;
  State nextStateFromControl(const Control &u);

private:

  float k = 0.5f;
  State m_currentState;
  float m_dt; 

};
