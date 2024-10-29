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
#include <TopExp_Explorer.hxx>
#include <TopoDS_Iterator.hxx>
#include <BRepTools.hxx>

#include "chrono_irrlicht/ChVisualSystemIrrlicht.h"

// Recursively explore the hierarchy of shapes
std::vector<std::shared_ptr<chrono::cascade::ChCascadeBodyEasy>> ExploreShape(const TopoDS_Shape &shape, chrono::cascade::ChCascadeDoc &the_doc, const char *name)
{
    TopExp_Explorer explorer;
    int counter = 0;

    std::vector<std::shared_ptr<chrono::cascade::ChCascadeBodyEasy>> chrono_shapes;
    // Iterate over solids, compounds, or other sub-shapes
    for (explorer.Init(shape, TopAbs_SOLID); explorer.More(); explorer.Next())
    {
        TopoDS_Shape sub_shape = explorer.Current();

        std::shared_ptr<chrono::cascade::ChCascadeBodyEasy> easy_body = chrono_types::make_shared<chrono::cascade::ChCascadeBodyEasy>(
            sub_shape, // sub_shape instead of shape
            1000,      // density
            true,      // add a visualization
            false      // add a collision model
        );

        chrono_shapes.push_back(easy_body);
    }

    return chrono_shapes; // Return nullptr if nothing is found
}

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

    chrono::ChSystemNSC the_system;

    chrono::cascade::ChCascadeDoc the_doc;

    bool load_ok = the_doc.Load_STEP("/ProjectChronoLearning/LightSwitch/LightSwitchReduced-All.step");

std::vector<std::shared_ptr<chrono::cascade::ChCascadeBodyEasy>> easy_bodies;
    if (load_ok)
    {

        TopoDS_Shape shape;
        TopoDS_Shape othershape;
        the_doc.Dump(std::cout);

        std::cout << std::endl
                  << std::endl;

        bool x = the_doc.GetRootShape(shape, 1);

        // bool g = the_doc.GetNamedShape(shape, "Spring");

        shape.DumpJson(std::cout);

        std::cout << std::endl
                  << std::endl;

         easy_bodies = ExploreShape(shape, the_doc, "Switch");
    }

    else
    {
        std::cout << "The Step File Was not loaded correctly";
        return load_ok;
    }
    unsigned short int how_many_bodies = easy_bodies.size();

    for (std::shared_ptr<chrono::cascade::ChCascadeBodyEasy> each_body : easy_bodies)
    {

        each_body->SetFixed(true);
        the_system.Add(each_body);
        each_body->GetVisualShape(0)->SetColor(chrono::ChColor(0.0f,1.0f,1.0f));

    }

    // Create a large cube as a floor.
    std::shared_ptr<chrono::ChBodyEasyBox> floor(new chrono::ChBodyEasyBox(1, 0.2, 1, 1000));
    floor->SetPos(chrono::ChVector3<>(0, -0.3, 0));
    floor->SetFixed(true);
    floor->GetVisualShape(0)->SetColor(chrono::ChColor(1.0f, 0.0f, 0.0f));
    the_system.Add(floor);


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
