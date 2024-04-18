#include "chrono/physics/ChBody.h"

int main()
{
    auto my_body_A = chrono_types::make_shared<chrono::ChBody>();

    my_body_A->SetRot(chrono::QuatFromAngleY(30 * chrono::CH_DEG_TO_RAD));

    std::cout << "Rotation is " << my_body_A->GetRotAngle() << std::endl;

    return 0;
}