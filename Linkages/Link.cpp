#include "chrono/assets/ChVisualMaterial.h"
#include "chrono/assets/ChVisualShapeBox.h"
#include "chrono/physics/ChBody.h"
#include <string>
#include "chrono/physics/ChLinkLock.h"
#include "chrono/physics/ChLinkMate.h"
#include "chrono/physics/ChSystemNSC.h"
#include "chrono_irrlicht/ChVisualSystemIrrlicht.h"

int main()
{
    auto vis_mat_red = chrono_types::make_shared<chrono::ChVisualMaterial>();
    vis_mat_red->SetDiffuseColor(chrono::ChColor(1.0f, 0.0f, 0.0f));

    auto vis_mat_green = chrono_types::make_shared<chrono::ChVisualMaterial>();
    vis_mat_green->SetDiffuseColor(chrono::ChColor(0.0f, 1.0f, 0.0f));

    auto vis_box_ind = chrono_types::make_shared<chrono::ChVisualShapeBox>(0.5, 0.5, 0.5);
    vis_box_ind->AddMaterial(vis_mat_red);

    auto vis_box_dep = chrono_types::make_shared<chrono::ChVisualShapeBox>(0.5, 0.5, 0.5);
    vis_box_dep->AddMaterial(vis_mat_green);

    auto vis_box_ind_model = chrono_types::make_shared<::chrono::ChVisualModel>();
    auto vis_box_dep_model = chrono_types::make_shared<::chrono::ChVisualModel>();

    vis_box_ind_model->AddShape(vis_box_ind);
    vis_box_dep_model->AddShape(vis_box_dep);

    auto independent_body = chrono_types::make_shared<chrono::ChBody>();
    auto dependent_body = chrono_types::make_shared<chrono::ChBody>();

    independent_body->SetPos(chrono::ChVector3d(2, 0, 0));
    independent_body->SetMass(2.3);

    dependent_body->SetPos(chrono::ChVector3d(0, -1, 0));
    dependent_body->SetMass(2.3);

    chrono::ChVector3d velocity_coordinates(1, 0, 0);
    // chrono::ChVector3d velocity_coordinates(0, 0, 0);

    dependent_body->SetLinVel(velocity_coordinates);

    auto some_link = chrono_types::make_shared<chrono::ChLinkMateFix>();
    some_link->Initialize(independent_body, dependent_body);

    some_link->SetConstrainedCoords(1, 1, 1, 1, 1, 1);

    independent_body->AddVisualModel(vis_box_ind_model);
    dependent_body->AddVisualModel(vis_box_dep_model);

    auto phys_system = chrono::ChSystemNSC();
    phys_system.Add(independent_body);
    phys_system.Add(dependent_body);
    phys_system.Add(some_link);

    phys_system.SetGravitationalAcceleration(0.0);

    auto vis_system = chrono_types::make_shared<chrono::irrlicht::ChVisualSystemIrrlicht>();
    vis_system->AttachSystem(&phys_system);
    vis_system->SetWindowSize(800, 600);
    vis_system->SetWindowTitle("I made a Demo!!!");
    vis_system->Initialize();
    vis_system->AddLogo();
    vis_system->AddSkyBox();
    vis_system->AddCamera(chrono::ChVector3d(-2, 4, -2));
    vis_system->AddTypicalLights();

    double timestep = 0.01;
    double total_sim_time = 0.0;
    double force_duration = .01;
    chrono::ChVector3d applied_force(0,0,.3);
    while (vis_system->Run())
    {
        vis_system->BeginScene();
        vis_system->Render();

        chrono::irrlicht::tools::drawGrid(vis_system.get(), 0.5, 0.5, 12, 12,
                                          chrono::ChCoordsys<>(chrono::ChVector3d(0, 0, 0), chrono::QuatFromAngleX(chrono::CH_PI_2)),
                                          chrono::ChColor(0.31f, 0.43f, 0.43f), true);

        // if (total_sim_time <= force_duration)
        // {
        //     independent_body->AccumulateForce(applied_force,independent_body->GetPos(),false);
        // }
        
        vis_system->EndScene();
        phys_system.DoStepDynamics(timestep);
        // total_sim_time += timestep;
    }

    return 0;
}
