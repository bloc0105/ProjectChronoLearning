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
    // Make a red Sphere and a Green Box
    auto the_body = std::make_shared<chrono::ChBody>();

    chrono::ChFramed box_frame(chrono::ChVector3d(3.0, 2.3, 1.778), 0);

    // Set the physical properties of the box.
    the_body->SetCoordsys(chrono::ChCoordsys(box_frame.GetCoordsys()));
    the_body->SetAngVelLocal(chrono::ChVector3d(rot_angle, 0, 0));
    the_body->SetRotDt2(chrono::QuatFromAngleX(0));

    std::cout << "Rotation angle should be " << rot_angle << std::endl;
    std::cout << "Prior angular Velocity is " << the_body->GetAngVelLocal() << std::endl;
    std::cout << "The Ratio is " << rot_angle / (the_body->GetAngVelLocal()[0]) << std::endl;

    return 0;
}