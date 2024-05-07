#include "chrono/physics/ChBody.h"
#include "chrono/physics/ChSystemNSC.h"
#include "chrono_irrlicht/ChVisualSystemIrrlicht.h"
#include "chrono/assets/ChVisualMaterial.h"
#include "chrono/assets/ChColor.h"
#include "chrono/core/ChCoordsys.h"
#include "chrono/core/ChTypes.h"
#include "chrono/geometry/ChSphere.h"
#include "chrono/core/ChRotation.h"

int main()
{

    double rot_angle = 50.0 * chrono::CH_DEG_TO_RAD;
    auto the_body = std::make_shared<chrono::ChBody>();
    the_body->SetMass(1);

    chrono::ChCoordsys pos_coodinates(chrono::ChVector3d(0, 0, 0), chrono::ChQuaterniond(1, 0, 0, 0));

    chrono::ChFramed box_frame(pos_coodinates);
    // the_body->SetLinVel(chrono::ChVector3d(1, 0, 0));
    the_body->SetLinAcc(chrono::ChVector3d(1, 0, 0));
    std::cout << "Initial acceleration set to " << the_body->GetLinAcc() << std::endl;

    chrono::ChSystemNSC sys;
    std::cout << "After making system, acceleration set to " << the_body->GetLinAcc() << std::endl;

    sys.SetGravitationalAcceleration(chrono::ChVector3d(0, 0, 0));
    std::cout << "After setting Gravity, acceleration set to " << the_body->GetLinAcc() << std::endl;

    sys.AddBody(the_body);
    std::cout << "After Adding Body, acceleration set to " << the_body->GetLinAcc() << std::endl;

    double frame_time_interval = 0.1;

    for (double frame_time = 0.0; frame_time < 5.0; frame_time += frame_time_interval)
    {
        std::cout << "Pos: " << the_body->GetPos()
                  << " ___ Vel: " << the_body->GetLinVel() << " ___ Acc: " << the_body->GetLinAcc() << std::endl;
        sys.DoStepDynamics(frame_time_interval);
    }
    std::cout << "The end, acceleration set to " << the_body->GetLinAcc() << std::endl;
    return 0;
}