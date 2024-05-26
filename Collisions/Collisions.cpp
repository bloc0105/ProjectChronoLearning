#include "chrono/physics/ChSystemNSC.h"
#include "chrono/physics/ChBody.h"
#include "chrono/physics/ChLoadsBody.h"
#include "chrono/physics/ChContactMaterialNSC.h"
#include "chrono/collision/ChCollisionShapeBox.h"
#include "chrono/collision/ChCollisionSystem.h"
#include "chrono_irrlicht/ChVisualSystemIrrlicht.h"
#include "chrono/assets/ChVisualMaterial.h"

int main()
{
    // Create a physical system
    chrono::ChSystemNSC my_system;

    // Create two bodies
    auto the_ground = chrono_types::make_shared<chrono::ChBody>();
    the_ground->SetPos(chrono::ChVector3d(0, 0, 0));
    the_ground->SetFixed(true);
    auto ground_collision = the_ground->GetCollisionModel();

    auto coll_material = chrono_types::make_shared<chrono::ChContactMaterialNSC>();
    auto coll_shape = chrono_types::make_shared<chrono::ChCollisionShapeBox>(coll_material, 100, 0.2, 100);

    ground_collision->Clear();
    ground_collision->AddShape(coll_shape);
    the_ground->EnableCollision(true);
    my_system.AddBody(the_ground);

    auto vis_mat_red = chrono_types::make_shared<chrono::ChVisualMaterial>();
    vis_mat_red->SetDiffuseColor(chrono::ChColor(1.0f, 0.0f, 0.0f));

    auto vis_mat_green = chrono_types::make_shared<chrono::ChVisualMaterial>();
    vis_mat_green->SetDiffuseColor(chrono::ChColor(0.0f, 1.0f, 0.0f));

    auto vis_ground = chrono_types::make_shared<chrono::ChVisualShapeBox>(100, 0.2, 100);
    vis_ground->AddMaterial(vis_mat_green);

    auto visual_model_ground = chrono_types::make_shared<chrono::ChVisualModel>();
    visual_model_ground->AddShape(vis_ground, chrono::ChFramed());
    the_ground->AddVisualModel(visual_model_ground);

    auto the_body = chrono_types::make_shared<chrono::ChBody>();
    the_body->SetPos(chrono::ChVector3d(0, 10, 0));

    auto coll_shape_box = chrono_types::make_shared<chrono::ChCollisionShapeBox>(coll_material, 1, 1, 1);

    auto vis_box = chrono_types::make_shared<chrono::ChVisualShapeBox>(1, 1, 1);
    vis_box->AddMaterial(vis_mat_red);
    
    auto visual_model_box = chrono_types::make_shared<chrono::ChVisualModel>();
    visual_model_box->AddShape(vis_box, chrono::ChFramed());
    the_body->AddVisualModel(visual_model_box);

    // the_body->AddVisualShape(vis_box);

    my_system.Add(the_body);
    my_system.Add(the_ground);

    my_system.SetCollisionSystemType(chrono::ChCollisionSystem::Type::BULLET);
    
    auto vis_system = chrono_types::make_shared<chrono::irrlicht::ChVisualSystemIrrlicht>();
    vis_system->AttachSystem(&my_system);
    vis_system->SetWindowSize(800, 600);
    vis_system->SetWindowTitle("I made a Demo!!!");
    vis_system->Initialize();
    vis_system->AddLogo();
    vis_system->AddSkyBox();
    vis_system->AddCamera(chrono::ChVector3d(-2, 4, -2));
    vis_system->AddTypicalLights();

    std::size_t counter = 0;
    while (vis_system->Run())
    {
        vis_system->BeginScene();
        vis_system->Render();

        chrono::irrlicht::tools::drawGrid(vis_system.get(), 0.5, 0.5, 12, 12,
                                          chrono::ChCoordsys<>(chrono::ChVector3d(0, 0, 0), chrono::QuatFromAngleX(chrono::CH_PI_2)),
                                          chrono::ChColor(0.31f, 0.43f, 0.43f), true);

        vis_system->EndScene();
        my_system.DoStepDynamics(0.01);
    }

    return 0;
}
