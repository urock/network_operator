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

    Control operator+(const Control &ctrl) const 
    {
      return Control{this->left + ctrl.left, this->right + ctrl.right};
    }
    
    Control operator-(const Control &ctrl) const 
    {
      return Control{this->left - ctrl.left, this->right - ctrl.right};
    }
    
    Control operator*(float val) const 
    {
      return Control{this->left * val, this->right * val};
    }

  };

  struct State {
    float x;
    float y;
    float yaw;

    State operator+(const State &state) {
      return State{this->x + state.x, this->y + state.y, this->yaw + state.yaw};
    }
    State operator-(const State &state) {
      return State{this->x - state.x, this->y - state.y, this->yaw - state.yaw};
    }
    State operator*(float val) {
      return State{this->x * val, this->y * val, this->yaw * val};
    }

    float dist(const State &state) {
      float dx = fabs(this->x - state.x);
      float dy = fabs(this->y - state.y);
      float dyaw = fabs(this->yaw - state.yaw);

      return std::sqrt(dx * dx + dy * dy + dyaw * dyaw);
    }

    void print() {
      std::cout << x << " " << y << " " << yaw << "\n";
    }

  };


  Model(const State &state, float dt_);
  void setState(const State &);
  const State &getState();
  
  State calcVelocity(const Control &) ;

  State calcState(const Control &u);
  State calcState(State &Vs) ;


private:
  float k = 0.5f;
  State mCurrentState;
  float dt; 
};
