#include "chrono/core/ChCoordsys.h"
#include <numbers>
#include <math.h>

#include "chrono/core/ChQuaternion.h"
#include "chrono/core/ChRotation.h"

int main()
{

    chrono::ChVector3d somevector(1.3, 35.44, 56.8);

    std::cout << "x = " << somevector[0] << "\n";
    std::cout << "y = " << somevector[1] << "\n";
    std::cout << "z = " << somevector[2] << "\n";

    chrono::ChQuaterniond rotator = chrono::QuatFromAngleY(30 * chrono::CH_DEG_TO_RAD);

    chrono::ChVector3d rot = rotator.Rotate(somevector);

    std::cout << "_________________________________________________________________\n\n";

    std::cout << "x = " << rot[0] << "\n";
    std::cout << "y = " << rot[1] << "\n";
    std::cout << "z = " << rot[2] << "\n";

    return 0;
}
