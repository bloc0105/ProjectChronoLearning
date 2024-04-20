#include "chrono/physics/ChBody.h"
#include "chrono/physics/ChBodyEasy.h"
#include "chrono/physics/ChSystemNSC.h"
#include "chrono_irrlicht/ChVisualSystemIrrlicht.h"
#include "chrono/assets/ChVisualMaterial.h"
#include "chrono/assets/ChColor.h"
#include "chrono/core/ChCoordsys.h"
#include "chrono/core/ChTypes.h"
#include "chrono/geometry/ChSphere.h"

int main()
{

    double sphere_radius = 13.4;
    auto vis_mat = chrono_types::make_shared<chrono::ChVisualMaterial>();
    vis_mat->SetDiffuseColor(chrono::ChColor(0.9f, 0.4f, 0.2f));


    auto vis_sphere = chrono_types::make_shared<chrono::ChVisualShapeSphere>(sphere_radius);
    vis_sphere->AddMaterial(vis_mat);


    auto visual_model = chrono_types::make_shared<::chrono::ChVisualModel>(sphere_radius,sphere_radius,sphere_radius);
    visual_model->AddShape(vis_sphere,chrono::ChFramed());

    auto the_sphere = std::make_shared<chrono::ChBody>();
    the_sphere->SetMass(6.0);
    the_sphere->SetInertia(chrono::ChVector3d(1.0,1.0,1.0));
    the_sphere->SetPos(chrono::ChVector3d(0,0,0));

    the_sphere->AddVisualModel(visual_model);


    return 0;
}