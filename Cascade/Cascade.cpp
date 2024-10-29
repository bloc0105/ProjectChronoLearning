// =============================================================================
// PROJECT CHRONO - http://projectchrono.org
//
// Copyright (c) 2014 projectchrono.org
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be found
// in the LICENSE file at the top level of the distribution and at
// http://projectchrono.org/license-chrono.txt.
//
// =============================================================================
//   Show how to use the OpenCASCADE features
//   implemented in the unit_CASCADE:
//
//   - load a 3D model saved in STEP format from a CAD
//   - make Chrono::Engine objects out of those parts
// =============================================================================

#include "chrono/core/ChRealtimeStep.h"
#include "chrono/physics/ChSystemNSC.h"
#include "chrono/physics/ChBodyEasy.h"
#include "chrono_cascade/ChCascadeBodyEasy.h"
#include "chrono_cascade/ChCascadeDoc.h"
#include "chrono_cascade/ChVisualShapeCascade.h"

#include "chrono_irrlicht/ChVisualSystemIrrlicht.h"

int main(int argc, char *argv[])
{
    // Create a ChronoENGINE physical system: all bodies and constraints
    // will be handled by this chrono::ChSystemNSC object.
    chrono::ChSystemNSC sys;

    // Load a STEP file using ChCascadeDoc.
    chrono::cascade::ChCascadeDoc mydoc;

    // Load the STEP model using this command:
    bool load_ok = mydoc.Load_STEP("/ProjectChronoLearning/Cascade/SomeShape-Body.step");

    // Print the contained shapes
    mydoc.Dump(std::cout);

    chrono::ChCollisionModel::SetDefaultSuggestedEnvelope(0.002);
    chrono::ChCollisionModel::SetDefaultSuggestedMargin(0.001);

    // In most CADs the Y axis is horizontal, but we want it vertical.
    // So define a root transformation for rotating all the imported objects.
    chrono::ChQuaternion<> rotation1;
    rotation1.SetFromAngleX(-chrono::CH_PI_2); // 1: rotate 90 deg on X axis
    chrono::ChQuaternion<> rotation2;
    rotation2.SetFromAngleY(chrono::CH_PI);                    // 2: rotate 180 deg on vertical Y axis
    chrono::ChQuaternion<> tot_rotation = rotation2 * rotation1; // rotate on 1 then on 2, using quaternion product
    chrono::ChFrameMoving<> root_frame(chrono::ChVector3<>(0, 0, 0), tot_rotation);

    // Retrieve a sub-shape from the loaded model
    std::shared_ptr<chrono::cascade::ChCascadeBodyEasy> body;

    if (load_ok)
    {
        mydoc.Dump(std::cout);
        TopoDS_Shape shape;
        if (mydoc.GetNamedShape(shape, "Body"))
        {
            // Create the ChBody using the ChCascadeBodyEasy helper:
            body = chrono_types::make_shared<chrono::cascade::ChCascadeBodyEasy>(shape,
                                                                                 1000, // density
                                                                                 true, // add a visualization
                                                                                 false // add a collision model
            );
            sys.Add(body);
            body->SetFixed(true);
            body->GetVisualShape(0)->SetColor(chrono::ChColor(0.0f,1.0f,1.0f));
            // Apply the rotational transformation that was defined above.
            body->ConcatenatePreTransformation(root_frame);
        }
        else
        {
            std::cerr << "WARNING: Desired object not found in document" << std::endl;
        }
    }
    else
    {
        std::cerr << "WARNING: Desired STEP file could not be opened/parsed" << std::endl;
    }

    // Create a large cube as a floor.
    std::shared_ptr<chrono::ChBodyEasyBox> floor(new chrono::ChBodyEasyBox(1, 0.2, 1, 1000));
    floor->SetPos(chrono::ChVector3<>(0, -0.3, 0));
    floor->SetFixed(true);
    floor->GetVisualShape(0)->SetColor(chrono::ChColor(1.0f, 0.0f, 0.0f));
    sys.Add(floor);

    // Create the run-time visualization system
    std::shared_ptr<chrono::ChVisualSystem> vis;

    auto vis_irr = chrono_types::make_shared<chrono::irrlicht::ChVisualSystemIrrlicht>();
    vis_irr->AttachSystem(&sys);
    vis_irr->SetWindowSize(800, 600);
    vis_irr->SetWindowTitle("Load a STEP model from file");
    vis_irr->Initialize();
    vis_irr->AddLogo();
    vis_irr->AddSkyBox();
    vis_irr->AddCamera(chrono::ChVector3<>(0.2, 0.2, -0.3));
    vis_irr->AddTypicalLights();

    vis = vis_irr;

    // Simulation loop
    chrono::ChRealtimeStepTimer realtime_timer;
    double time_step = 0.01;

    while (vis->Run())
    {
        vis->BeginScene();
        vis->Render();
        vis->EndScene();

        sys.DoStepDynamics(time_step);
        realtime_timer.Spin(time_step);
    }

    return 0;
}
