
#include "chrono/physics/ChSystemNSC.h"
#include "chrono/assets/ChVisualMaterial.h"
#include "chrono/assets/ChColor.h"
#include "chrono/core/ChCoordsys.h"
#include "chrono/core/ChTypes.h"
#include "chrono/geometry/ChSphere.h"
#include "chrono/core/ChRotation.h"
#include "chrono/physics/ChBody.h"

int main()
{

    double rot_angle = 50.0 * chrono::CH_DEG_TO_RAD;
    auto the_body = std::make_shared<chrono::ChBody>();
    the_body->SetMass(1);

    chrono::ChCoordsys pos_coodinates(chrono::ChVector3d(0, 0, 0), chrono::ChQuaterniond(1, 0, 0, 0));

    // the_body->SetLinVel(chrono::ChVector3d(1, 0, 0));

    the_body->SetPos(pos_coodinates.pos);
    std::cout << "Initial acceleration set to " << the_body->GetLinAcc() << std::endl;

    chrono::ChVector3d initial_acc(1, 0, 0);
    chrono::ChVector3d initial_force = the_body->GetMass() * initial_acc;
    the_body->AccumulateForce(initial_force, pos_coodinates.pos, false);

    chrono::ChSystemNSC sys;
    std::cout << "After making system, acceleration set to " << the_body->GetLinAcc() << std::endl;

    sys.SetGravitationalAcceleration(chrono::ChVector3d(0, 0, -1));
    std::cout << "After setting Gravity, acceleration set to " << the_body->GetLinAcc() << std::endl;

    sys.AddBody(the_body);
    std::cout << "After Adding Body, acceleration set to " << the_body->GetLinAcc() << std::endl;

    double frame_time_interval = 0.1;

    for (double frame_time = 0.0; frame_time < 5.0; frame_time += frame_time_interval)
    {
        std::cout << "Pos: " << the_body->GetPos()
                  << "     Vel: " << the_body->GetLinVel() << "     Acc: " << the_body->GetLinAcc() << std::endl;
        sys.DoStepDynamics(frame_time_interval);
    }
    std::cout << "The end, acceleration set to " << the_body->GetLinAcc() << std::endl;
    return 0;
}