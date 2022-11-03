#include "runner.hpp"


Runner::Runner(Model& model, Controller& controller): 
    m_model(model),
    m_controller(controller) 
    { }

void Runner::setGoal(const Model::State &goal)
{
    m_controller.setGoal(goal);
}

void Runner::init(const Model::State& state)
{
    m_model.setState(state);
}

void Runner::Euler2() 
{
    Model::State initialState = m_model.getState();

    Model::Control u1 = m_controller.calcControl(initialState);
    Model::State v1 = m_model.calcVelocity(u1); // fa
    Model::State s1 = m_model.calcState(v1); // moved state

    Model::Control u2 = m_controller.calcControl(s1);
    m_model.setState(s1);
    Model::State v2 = m_model.calcVelocity(u2); // fb
    m_model.setState(initialState);
    Model::State ctrl = (v1 + v2) * 0.5;
    Model::State movedState = m_model.calcState(ctrl);

    m_model.setState(movedState);
}

Model::State Runner::makeStep() 
{
    Euler2();
    return m_model.getState(); 
}
