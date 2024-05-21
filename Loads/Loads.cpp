#include "chrono/physics/ChSystemNSC.h"
#include "chrono/physics/ChBody.h"
#include "chrono/physics/ChLoadsBody.h"

int main()
{
    // Create a physical system
    chrono::ChSystemNSC my_system;

    // Create two bodies
    auto the_body = chrono_types::make_shared<chrono::ChBody>();
    the_body->SetMass(2.0);
    my_system.AddBody(the_body);
    my_system.SetGravitationalAcceleration(0);
    
    

    auto the_force = chrono_types::make_shared<chrono::ChForce>();

    the_body->AddForce(the_force);
    the_force->SetMforce(1.0);
    while (my_system.GetChTime() < 2)
    {
        my_system.DoStepDynamics(0.01);
        std::cout << "Time: " << my_system.GetChTime() << " Acceleration: " << the_body->GetLinAcc() << " Velocity: " << the_body->GetLinVel() << " Position: " << the_body->GetPos() << std::endl;
    }

    return 0;
}
