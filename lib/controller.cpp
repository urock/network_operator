#include <iostream>
#include <cmath>

#include "controller.hpp"

Controller::Controller(const Model::State &goal_, NetOper &netOper):mGoal(goal_)
	,m_netOper(netOper)
{
}

Model::Control Controller::calcControl(const Model::State& currState)
{	
	Model::State d = mGoal - currState; 


	std::vector<float> u(2, 0);

	m_netOper.calcResult({d.x, d.y, d.yaw}, u);

    constexpr float Umax = 10.0f;
  	u[0] = std::min(std::max(u[0], -Umax), Umax);
  	u[1] = std::min(std::max(u[1], -Umax), Umax);


	return Model::Control{u[0], u[1]};
}

void Controller::setGoal(Model::State newGoal)
{
	mGoal = newGoal;
}

// NetOper& Controller::netOper()
// {
// 	return m_netOper;
// }
