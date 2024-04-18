#include "chrono/core/ChCoordsys.h"
#include <numbers>
#include <math.h>

#include "chrono/core/ChQuaternion.h"
#include "chrono/core/ChRotation.h"
#include "chrono/core/ChFrameMoving.h"

int main()
{

    chrono::ChVector3d somevector(1.3, 35.44, 56.8);

    std::cout << "x = " << somevector[0] << "\n";
    std::cout << "y = " << somevector[1] << "\n";
    std::cout << "z = " << somevector[2] << "\n";

    chrono::ChQuaterniond rotatorY = chrono::QuatFromAngleY(30 * chrono::CH_DEG_TO_RAD);
    chrono::ChQuaterniond rotatorX = chrono::QuatFromAngleX(22 * chrono::CH_DEG_TO_RAD);
    chrono::ChQuaterniond rotatorZ = chrono::QuatFromAngleZ(33 * chrono::CH_DEG_TO_RAD);

    chrono::ChVector3d rot = rotatorY.Rotate(somevector);

    std::cout << "_________________________________________________________________\n\n";

    std::cout << "x = " << rot[0] << "\n";
    std::cout << "y = " << rot[1] << "\n";
    std::cout << "z = " << rot[2] << "\n";

    chrono::ChMatrix33d rot_matrix = chrono::ChMatrix33d(rotatorY) * chrono::ChMatrix33d(rotatorX) * chrono::ChMatrix33d(rotatorZ);

    chrono:: ChVector3d rotated_magic = rot_matrix * somevector;

    std::cout << "--------------------------------------------------------------------" << std::endl;

    std::cout << "x = " << rotated_magic[0] << std::endl;
    std::cout << "y = " << rotated_magic[1] << std::endl;
    std::cout << "z = " << rotated_magic[2] << std::endl;

    chrono::ChCoordsysd some_referenceFrame(rotated_magic,rotatorY);
    chrono::ChCoordsysd another_referenceFrame(rotated_magic,rotatorZ);

    chrono::ChCoordsysd other_sys = some_referenceFrame >> another_referenceFrame;

    chrono::ChVector3d derp = somevector >> other_sys;

    std::cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;

    std::cout << "x = " << derp[0] << std::endl;
    std::cout << "y = " << derp[1] << std::endl;
    std::cout << "z = " << derp[2] << std::endl;

    chrono::ChFrameMoving<> aMovingFrame;
    aMovingFrame.SetPos(chrono::ChVector3d(1,4,2));
    aMovingFrame.SetRot(rotatorX);
    aMovingFrame.SetPosDt(chrono::ChVector3d(7,0,0));
    chrono::ChFrameMoving q = aMovingFrame.GetInverse();


    return 0;
}
