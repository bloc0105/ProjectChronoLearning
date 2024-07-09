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
        return body;
    };

    chrono::ChSystemNSC the_system;

    chrono::cascade::ChCascadeDoc the_doc;

    bool load_ok = the_doc.Load_STEP("/ProjectChronoLearning/LightSwitch/LightSwitchReduced-All.step");
    if (load_ok)
    {

        the_doc.Dump(std::cout);
    }
    else
    {
        std::cout << "The Step File Was not loaded correctly";
    }

    return load_ok;
}
