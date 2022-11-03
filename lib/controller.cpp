#include "controller.hpp"

Controller::Controller(const Model::State &goalState, NetOper &netOper):
	mGoal(goalState),
	m_netOper(netOper)
{ }

Model::Control Controller::calcControl(const Model::State& currState)
{	
	Model::State delta = mGoal - currState; 

	std::vector<float> u(2, 0);

	m_netOper.calcResult({delta.x, delta.y, delta.yaw}, u);

    constexpr float Umax = 10.0f;
  	u[0] = std::min(std::max(u[0], -Umax), Umax);
  	u[1] = std::min(std::max(u[1], -Umax), Umax);


	return Model::Control{u[0], u[1]};
}

void Controller::setGoal(Model::State newGoal)
{
	mGoal = newGoal;
}
