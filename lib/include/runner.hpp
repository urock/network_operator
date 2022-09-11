#include "model.hpp"
#include "controller.hpp"

class Runner {

    public:
        Runner(Model& model_, Controller & controller_);
        void setGoal(const Model::State &);
        void init(const Model::State &);

        Model::State makeStep(); 

    private:
        Model &mModel;
        Controller &mController;  

        void Euler2(void);

};
