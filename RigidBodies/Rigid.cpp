#include "chrono/physics/ChBody.h"
#include "chrono/physics/ChBodyEasy.h"
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

    double sphere_radius = 13.4;
    auto vis_mat = chrono_types::make_shared<chrono::ChVisualMaterial>();
    vis_mat->SetDiffuseColor(chrono::ChColor(1.0f, 0.0f, 0.0f));

    auto vis_sphere = chrono_types::make_shared<chrono::ChVisualShapeSphere>(sphere_radius);
    vis_sphere->AddMaterial(vis_mat);


    auto visual_model = chrono_types::make_shared<::chrono::ChVisualModel>();
    visual_model->AddShape(vis_sphere,chrono::ChFramed());

    auto the_sphere = std::make_shared<chrono::ChBody>();
    the_sphere->SetMass(6.0);
    the_sphere->SetInertia(chrono::ChVector3d(1.0,1.0,1.0));
    the_sphere->SetPos(chrono::ChVector3d(0,0,0));

    the_sphere->AddVisualModel(visual_model);

    auto sys = chrono::ChSystemNSC();
    
    sys.Add(the_sphere);

    sys.SetGravitationalAcceleration(0.0);

    auto vis_system = chrono_types::make_shared<chrono::irrlicht::ChVisualSystemIrrlicht>();
    vis_system->AttachSystem(&sys);
    vis_system->SetWindowSize(800,600);
    vis_system->SetWindowTitle("I made a Demo!!!");
    vis_system->Initialize();
    vis_system->AddLogo();
    vis_system->AddSkyBox();
    vis_system->AddCamera(chrono::ChVector3d(-2,3,-4));
    vis_system->AddTypicalLights();

    while (vis_system->Run())
    {
        vis_system->BeginScene();
        vis_system->Render();
                chrono::irrlicht::tools::drawGrid(vis_system.get(), 0.5, 0.5, 12, 12,
                                  chrono::ChCoordsys<>(chrono::ChVector3d(0, 0, 0), chrono::QuatFromAngleX(chrono::CH_PI_2)),
                                  chrono::ChColor(0.31f, 0.43f, 0.43f), true);

        vis_system->EndScene();
        sys.DoStepDynamics(0.01);
    }
    

    return 0;
}