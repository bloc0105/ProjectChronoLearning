#include "chrono/physics/ChSystemNSC.h"
#include "chrono/fea/ChMesh.h"
#include "chrono/fea/ChNodeFEAxyz.h"
#include "chrono/fea/ChContinuumMaterial.h"
#include "chrono/fea/ChElementTetraCorot_4.h"
#include "chrono/solver/ChSolverPMINRES.h"
#include "chrono/physics/ChBodyEasy.h"
#include "chrono_cascade/ChCascadeBodyEasy.h"
#include "chrono_cascade/ChCascadeDoc.h"
#include "chrono_cascade/ChVisualShapeCascade.h"

#include "chrono_irrlicht/ChVisualSystemIrrlicht.h"

int main()
{

    auto vis_mat_red = chrono_types::make_shared<chrono::ChVisualMaterial>();
    vis_mat_red->SetDiffuseColor(chrono::ChColor(1.0f, 0.0f, 0.0f));

    auto vis_mat_yellow = chrono_types::make_shared<chrono::ChVisualMaterial>();
    vis_mat_yellow->SetDiffuseColor(chrono::ChColor(1.0f, 1.0f, 0.0f));

    auto vis_mat_blue = chrono_types::make_shared<chrono::ChVisualMaterial>();
    vis_mat_blue->SetDiffuseColor(chrono::ChColor(0.0f, 0.0f, 1.0f));

    auto alignToYAxis = [&](std::shared_ptr<chrono::ChBody> body)
    {
        chrono::ChQuaternion<> rotation1;
        rotation1.SetFromAngleX(-chrono::CH_PI_2); // 1: rotate 90 deg on X axis
        chrono::ChQuaternion<> rotation2;
        rotation2.SetFromAngleY(chrono::CH_PI);                      // 2: rotate 180 deg on vertical Y axis
        chrono::ChQuaternion<> tot_rotation = rotation2 * rotation1; // rotate on 1 then on 2, using quaternion product
        chrono::ChFrameMoving<> root_frame(chrono::ChVector3<>(0, 0, 0), tot_rotation);

        body->ConcatenatePreTransformation(root_frame);
    };

    std::shared_ptr<chrono::cascade::ChCascadeBodyEasy> body_pad1;
    std::shared_ptr<chrono::cascade::ChCascadeBodyEasy> body_pad2;
    std::shared_ptr<chrono::cascade::ChCascadeBodyEasy> body_switch;
    std::shared_ptr<chrono::cascade::ChCascadeBodyEasy> body_spring;

    chrono::ChSystemNSC the_system;

    chrono::cascade::ChCascadeDoc the_doc;

    bool load_ok = the_doc.Load_STEP("/ProjectChronoLearning/LightSwitch/LightSwitchReduced-All.step");
    if (load_ok)
    {

        TopoDS_Shape shape;
        // the_doc.Dump(std::cout);
        if (the_doc.GetNamedShape(shape, "Spring"))
        {
            std::cout << " NOt Seg Faulted yet";
            body_spring = chrono_types::make_shared<chrono::cascade::ChCascadeBodyEasy>(shape,
                                                                                        1000, // density
                                                                                        true, // add a visualization
                                                                                        false // add a collision model
            );
            alignToYAxis(body_spring);
        }
        if (the_doc.GetNamedShape(shape, "Bumper1"))
        {
            body_pad1 = chrono_types::make_shared<chrono::cascade::ChCascadeBodyEasy>(shape,
                                                                                      1000, // density
                                                                                      true, // add a visualization
                                                                                      false // add a collision model
            );
            alignToYAxis(body_pad1);
        }
        if (the_doc.GetNamedShape(shape, "Bumper2"))
        {
            body_pad2 = chrono_types::make_shared<chrono::cascade::ChCascadeBodyEasy>(shape,
                                                                                      1000, // density
                                                                                      true, // add a visualization
                                                                                      false // add a collision model
            );
            alignToYAxis(body_pad2);
        }
        if (the_doc.GetNamedShape(shape, "Switch"))
        {
            body_switch = chrono_types::make_shared<chrono::cascade::ChCascadeBodyEasy>(shape,
                                                                                        1000, // density
                                                                                        true, // add a visualization
                                                                                        false // add a collision model
            );
            alignToYAxis(body_switch);
        }
    }

    else
    {
        std::cout << "The Step File Was not loaded correctly";
    }


    body_pad1->SetFixed(true);
    body_pad2->SetFixed(true);
    body_spring->SetFixed(true);
    body_switch->SetFixed(true);

    // the_system.Add(body_pad1);
    // the_system.Add(body_pad2);
    // the_system.Add(body_spring);
    // the_system.Add(body_switch);


    auto vis_system = chrono_types::make_shared<chrono::irrlicht::ChVisualSystemIrrlicht>();
    vis_system->AttachSystem(&the_system);
    vis_system->SetWindowSize(800, 600);
    vis_system->SetWindowTitle("I made a Demo!!!");
    vis_system->Initialize();
    vis_system->AddLogo();
    vis_system->AddSkyBox();
    vis_system->AddCamera(chrono::ChVector3d(-2, 4, -2));
    vis_system->AddTypicalLights();

    
    while (vis_system->Run())
    {
        vis_system->BeginScene();
        vis_system->Render();

        chrono::irrlicht::tools::drawGrid(vis_system.get(), 0.5, 0.5, 12, 12,
                                          chrono::ChCoordsys<>(chrono::ChVector3d(0, 0, 0), chrono::QuatFromAngleX(chrono::CH_PI_2)),
                                          chrono::ChColor(0.31f, 0.43f, 0.43f), true);

        vis_system->EndScene();
        the_system.DoStepDynamics(0.01);
    }

    return load_ok;
}
