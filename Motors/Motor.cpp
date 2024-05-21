#include "chrono/physics/ChSystemNSC.h"
#include "chrono/physics/ChBody.h"
#include "chrono/physics/ChLinkMotorRotationAngle.h"

int main()
{
    // Create a physical system
    chrono::ChSystemNSC my_system;

    // Create two bodies
    auto ground = chrono_types::make_shared<chrono::ChBody>();
    ground->SetFixed(true);
    my_system.AddBody(ground);

    auto rotating_body = chrono_types::make_shared<chrono::ChBody>();
    rotating_body->SetPos(chrono::ChVector3d(0, 0, 0));
    my_system.AddBody(rotating_body);

    // Create a rotational motor and set its properties
    auto motor = chrono_types::make_shared<chrono::ChLinkMotorRotationAngle>();
    motor->Initialize(rotating_body, ground, chrono::ChFrame<>(chrono::ChVector3d(0, 0, 0), chrono::QUNIT));
    my_system.AddLink(motor);

    // Define a motion function (e.g., constant angular speed)
    auto motion_function = chrono_types::make_shared<chrono::ChFunctionRamp>(0, chrono::CH_PI / 4); // 45 degrees per second
    motor->SetAngleFunction(motion_function);

    // Simulation loop
    while (my_system.GetChTime() < 2)
    {
        my_system.DoStepDynamics(0.01);
        std::cout << "Time: " << my_system.GetChTime() << " Angle: " << motor->GetMotorAngle() << " Angular Velocity: " << motor->GetMotorAngleDt() << std::endl;
    }

    return 0;
}
