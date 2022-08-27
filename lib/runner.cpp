#include "runner.hpp"

Runner::Runner(Model &model_, Controller &controller_, float &dt_)
    : mController(controller_), mModel(model_), dt(dt_) {}

void Runner::Euler2() {
  auto u1 = mController.calcControl(mModel.getState());
  auto s1 = mModel.calcState(u1);
  auto u2 = mController.calcControl(s1);
  mModel.setState((u1 + u2) * 0.5);
  mCurrentTime += dt;
}

Model::State Runner::makeStep() {

  Euler2();
  return mModel.getState();
}