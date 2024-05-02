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

    chrono::ChCoordsys pos_coodinates(chrono::ChVector3d(0, 0, 0), chrono::ChQuaterniond(1, 0, 0, 0));

    chrono::ChCoordsys vel_coodinates(chrono::ChVector3d(1,.22222,0.3),chrono::ChQuaterniond(1,0,0,0));
    chrono::ChCoordsys acc_coodinates(chrono::ChVector3d(0,0.25,0),chrono::ChQuaterniond(1,0,0,0));

    chrono::ChFramed box_frame(pos_coodinates);
    the_body->SetCoordsys(box_frame.GetCoordsys());
    // the_body->SetLinVel(chrono::ChVector3d(0, 0, 0));
    // the_body->SetLinAcc(chrono::ChVector3d(0, 0.25, 0));
    the_body->SetCoordsysDt(vel_coodinates);
    the_body->SetCoordsysDt2(acc_coodinates);

    chrono::ChSystemNSC sys;

    sys.SetGravitationalAcceleration(0.0);

    sys.AddBody(the_body);

    double frame_time_interval = 0.1;

    for (double frame_time = 0.0; frame_time < 5.0; frame_time += frame_time_interval)
    {
        std::cout << "Position of the Box is " << the_body->GetPos() << std::endl;
        sys.DoStepDynamics(frame_time_interval);
    }

    return 0;
}