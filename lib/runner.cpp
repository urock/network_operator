#include "runner.hpp"


Runner::Runner(Model & model_, Controller & controller_, float dt_):
                mModel(model_), mController(controller_), dt(dt_)
{ 
}



void Runner::setGoal(const Model::State &goal_) {
    mGoal = goal_;
    mController.setGoal(mGoal);
}

void Runner::init(const Model::State &state_) {
    mCurrentState = state_;
}

void Runner::Euler2() {

    auto u1 = mController.calcControl(mCurrentState);
    // u1.print();

    auto v1 = mModel.calcVelocity(u1);
    auto s1 = mModel.calcState(v1);

    auto u2 = mController.calcControl(s1);
    // u2.print();

    auto v2 = mModel.calcVelocity(u2);

    mCurrentState = mCurrentState + (v1 + v2)*0.5*dt;

    mModel.setState(mCurrentState);

    mCurrentTime += dt; 
}

Model::State Runner::makeStep() {

    Euler2();

    return mCurrentState; 
}




