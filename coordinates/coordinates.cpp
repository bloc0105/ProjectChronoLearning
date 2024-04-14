#include "chrono/core/ChCoordsys.h"
#include <numbers>
#include <math.h>


int main()
{

    chrono::ChVector3d somevector(1.3, 35.44, 56.8);

    std::cout << "x = " << somevector[0] << "\n";
    std::cout << "y = " << somevector[1] << "\n";
    std::cout << "z = " << somevector[2] << "\n";

    return 0;
}