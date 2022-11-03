#pragma once
#include <iostream>
#include <vector>
#include <cmath>

class Model {

public:
  Model(const State &state, float dt);
  void setState(const State &state);
  const State& getState();
  // State getNextState(const Control &u);
  State calcVelocity(const Control &u) ;
  State calcState(State &Vs) ;
  State calcState(const Control &u);

public:

struct Control 
{
  explicit Control();

  float left;
  float right;

  Control operator+(const Control &ctrl) const;   
  Control operator-(const Control &ctrl) const;
  Control operator*(float val) const;

};

struct State 
{
  explicit State();

  float x;
  float y;
  float yaw;

  State operator+(const State &state);
  State operator-(const State &state) ;
  State operator*(float val);
  float dist(const State &state);
  void print();

};


private:
  float k = 0.5f;
  State m_currentState;
  float m_dt; 

};
