#include "chrono/physics/ChSystemNSC.h"
#include "chrono/physics/ChBody.h"
#include "chrono/physics/ChLoadsBody.h"
#include "chrono/physics/ChContactMaterialNSC.h"
#include "chrono/collision/ChCollisionShapeBox.h"
#include "chrono/collision/ChCollisionSystem.h"

int main()
{
    // Create a physical system
    chrono::ChSystemNSC my_system;

    // Create two bodies
    auto the_ground = chrono_types::make_shared<chrono::ChBody>();
    the_ground->SetPos(chrono::ChVector3d(0, 0, 0));
    the_ground->SetFixed(true);
    auto ground_collision = the_ground->GetCollisionModel();

    auto coll_material = chrono_types::make_shared<chrono::ChContactMaterialNSC>();
    auto coll_shape = chrono_types::make_shared<chrono::ChCollisionShapeBox>(coll_material,0.1,0.2,0.3);

    ground_collision->Clear();
    ground_collision->AddShape(coll_shape);
    the_ground->EnableCollision(true);
    my_system.AddBody(the_ground);

    auto the_body = chrono_types::make_shared<chrono::ChBody>();

    auto the_force = chrono_types::make_shared<chrono::ChForce>();

    the_body->AddForce(the_force);
    the_force->SetMforce(1.0);
    my_system.SetCollisionSystemType(chrono::ChCollisionSystem::Type::BULLET);
    while (my_system.GetChTime() < 2)
    {
        my_system.DoStepDynamics(0.01);
        std::cout << "Time: " << my_system.GetChTime() << " Acceleration: " << the_body->GetLinAcc() << " Velocity: " << the_body->GetLinVel() << " Position: " << the_body->GetPos() << std::endl;
    }

    return 0;
}
