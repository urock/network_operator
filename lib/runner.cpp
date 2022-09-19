#include "runner.hpp"


Runner::Runner(Model& model_, Controller& controller_): mModel(model_)
  ,mController(controller_) {}



void Runner::setGoal(const Model::State &goal_)
{
    mController.setGoal(goal_);
}

void Runner::init(const Model::State &state_)
{
    mModel.setState(state_);
}

void Runner::Euler2() 
{

    Model::State initialState = mModel.getState();

    Model::Control u1 = mController.calcControl(initialState);
    Model::State v1 = mModel.calcVelocity(u1); // fa
    Model::State s1 = mModel.calcState(v1); // moved state

    Model::Control u2 = mController.calcControl(s1);
    mModel.setState(s1);
    Model::State v2 = mModel.calcVelocity(u2); // fb

    mModel.setState(initialState);
    Model::State ctrl = (v1 + v2) * 0.5;
    Model::State movedState = mModel.calcState(ctrl);

    mModel.setState(movedState);
}

Model::State Runner::makeStep() 
{
    Euler2();
    return mModel.getState(); 
}
