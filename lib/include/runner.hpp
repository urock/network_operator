#include "model.hpp"
#include "controller.hpp"

class Runner {

    public:
        Runner(Model &, Controller &, float);
        void setGoal(const Model::State &);
        void init(const Model::State &);

        Model::State makeStep(); 

    private:
        Model &mModel;
        Controller &mController;  
        
        Model::State mCurrentState;
        Model::State mGoal;
        
        float dt;
        float mCurrentTime; 

        void Euler2(void);

};
