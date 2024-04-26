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

    double sphere_radius = 1.25;

    double rot_angle = 50.0 * chrono::CH_DEG_TO_RAD;
    // Make a red Sphere and a Green Box
    auto vis_mat_red = chrono_types::make_shared<chrono::ChVisualMaterial>();
    vis_mat_red->SetDiffuseColor(chrono::ChColor(1.0f, 0.0f, 0.0f));

    auto vis_mat_green = chrono_types::make_shared<chrono::ChVisualMaterial>();
    vis_mat_green->SetDiffuseColor(chrono::ChColor(0.0f, 1.0f, 0.0f));

    auto vis_sphere = chrono_types::make_shared<chrono::ChVisualShapeSphere>(sphere_radius);
    vis_sphere->AddMaterial(vis_mat_red);

    auto vis_box = chrono_types::make_shared<chrono::ChVisualShapeBox>(2.1, 1.3, 1.8);
    vis_box->AddMaterial(vis_mat_green);

    auto visual_model_sphere = chrono_types::make_shared<::chrono::ChVisualModel>();
    visual_model_sphere->AddShape(vis_sphere, chrono::ChFramed());

    // Set Some Physical Properties of the sphere.  
    auto the_sphere_body = std::make_shared<chrono::ChBody>();
    the_sphere_body->SetMass(6.0);
    the_sphere_body->SetInertia(chrono::ChVector3d(1.0, 1.0, 1.0));
    the_sphere_body->SetPos(chrono::ChVector3d(0, 0, 0));

    auto visual_model_box = chrono_types::make_shared<::chrono::ChVisualModel>();
    visual_model_box->AddShape(vis_box, chrono::ChFramed());

    auto the_box_body = std::make_shared<chrono::ChBody>();
    // the_box_body->SetMass(5.0);

    chrono::ChFramed box_frame(chrono::ChVector3d(4.0, 2.3, 1.778), 0);

    //Set the physical properties of the box.  
    the_box_body->SetCoordsys(chrono::ChCoordsys(box_frame.GetCoordsys()));
    the_box_body->SetAngVelLocal(chrono::ChVector3d(rot_angle,0,0));
    
    the_box_body->SetRotDt2(chrono::QuatFromAngleX(0));
    the_box_body->SetInertia(chrono::ChMatrix33d(2.0));
    the_box_body->SetLinVel(chrono::ChVector3d(1,0,0));
    


    // the_box_body->SetLinVel(chrono::ChVector3d(-1,0,0));

    the_sphere_body->AddVisualModel(visual_model_sphere);

    the_box_body->AddVisualModel(visual_model_box);

    auto sys = chrono::ChSystemNSC();

    sys.Add(the_sphere_body);
    sys.Add(the_box_body);

    sys.SetGravitationalAcceleration(0.0);

    auto vis_system = chrono_types::make_shared<chrono::irrlicht::ChVisualSystemIrrlicht>();
    vis_system->AttachSystem(&sys);
    vis_system->SetWindowSize(800, 600);
    vis_system->SetWindowTitle("I made a Demo!!!");
    vis_system->Initialize();
    vis_system->AddLogo();
    vis_system->AddSkyBox();
    vis_system->AddCamera(chrono::ChVector3d(-2, 4, -2));
    vis_system->AddTypicalLights();

    std::size_t counter = 0;
    std::cout << "Rotation angle should be " << rot_angle << std::endl;
    std::cout << "Prior angular Velocity is " << the_box_body->GetAngVelLocal() << std::endl;
    while (vis_system->Run())
    {
        vis_system->BeginScene();
        vis_system->Render();
        chrono::irrlicht::tools::drawGrid(vis_system.get(), 0.5, 0.5, 12, 12,
                                          chrono::ChCoordsys<>(chrono::ChVector3d(0, 0, 0), chrono::QuatFromAngleX(chrono::CH_PI_2)),
                                          chrono::ChColor(0.31f, 0.43f, 0.43f), true);

        vis_system->EndScene();
        sys.DoStepDynamics(0.01);
        if (counter < 10)
        {
            std::cout << the_box_body->GetAngVelLocal() << std::endl;

            ++counter;
        }
    }

    return 0;
}