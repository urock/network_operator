#include "nop.hpp"
#include "model.hpp"
#include "controller.hpp"
#include "runner.hpp"

#include <boost/program_options.hpp>
#include <string>

#include <iostream>
namespace po = boost::program_options;

int main(int argc, char* argv[])
{

    std::string output;
    bool stopInGoal = true;
    float start_x = 0.;
    float start_y = 0.;
    float start_yaw = 0.;
    float maxTime = 10.0;
    // Configure options here
    po::options_description desc ("Allowed options");
    desc.add_options ()
        ("help,h", "print usage message")
        ("start_x,x", po::value(&start_x), "start x")
        ("start_y,y", po::value(&start_y), "start y")
        ("start_yaw,yaw", po::value(&start_yaw), "start yaw")
        ("stopInGoal,s", po::value(&stopInGoal), "stop when Goal(0., 0., 0.) is reached")
        ("maxTime,t", po::value(&maxTime), "max time")
        ("output,o", po::value(&output), "Output files and graphs");


    // Parse command line arguments
    po::variables_map vm;
    po::store (po::command_line_parser (argc, argv).options (desc).run (), vm);
    po::notify (vm);

    //////////////
    constexpr float dt = 0.01;      
    constexpr float delta = 0.1;
    
    Model::State currState = {start_x, start_y, start_yaw}; 
    const Model::State Goal = {0., 0., 0.};

    std::cout<<"START\n";
    std::cout<<"Initial state = "<<currState.x<<" "<<currState.y<<" "<<currState.yaw<<"\n";
    std::cout<<"Goal state = "<<Goal.x<<" "<<Goal.y<<" "<<Goal.yaw<<"\n";
    
    // create network operator and set prarams
    NetOper nop = NetOper();
    nop.setNodesForVars({0, 1, 2});      // Pnum
    nop.setNodesForParams({3, 4, 5});    // Rnum
    nop.setNodesForOutput({22, 23});     // Dnum
    nop.setCs(qc);                       // set Cs
    nop.setPsi(NopPsiN);                 // set matrix

    Model model(currState, dt);

    Controller controller(Goal, nop);

    Runner runner(model, controller); 
    runner.setGoal(Goal);

    double time = 0.;                     
    while (maxTime > time) 
    {
        currState = runner.makeStep();
        // currState.print();
        time += dt;
        if (stopInGoal && currState.dist(Goal) < delta)
            break; 
    }
    std::cout<<"State ";
    currState.print();
    std::cout<<"spend time: " << time <<" (s)\n";
    std::cout<<"END\n";

    return 0;
}


