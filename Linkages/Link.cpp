#include "chrono/assets/ChVisualMaterial.h"
#include "chrono/assets/ChVisualShapeBox.h"
#include "chrono/physics/ChBody.h"
#include <string>

int main()
{
    auto vis_mat_red = chrono_types::make_shared<chrono::ChVisualMaterial>();
    vis_mat_red->SetDiffuseColor(chrono::ChColor(1.0f, 0.0f, 0.0f));

    auto vis_mat_green = chrono_types::make_shared<chrono::ChVisualMaterial>();
    vis_mat_green->SetDiffuseColor(chrono::ChColor(0.0f, 1.0f, 0.0f));

    auto vis_box_green = chrono_types::make_shared<chrono::ChVisualShapeBox>(1, 1, 5);
    vis_box_green->AddMaterial(vis_mat_green);

    auto vis_box_red = chrono_types::make_shared<chrono::ChVisualShapeBox>(1, 1, 5);
    vis_box_red->AddMaterial(vis_mat_red);

    auto independent_body = chrono_types::make_shared<chrono::ChBody>();
    auto dependent_body = chrono_types::make_shared<chrono::ChBody>();

    chrono::ChCoordsys position_coordinates(chrono::ChVector3d(2, 0, 0), chrono::ChQuaterniond(1, 0, 0, 0));
    chrono::ChCoordsys velocity_coordinates(chrono::ChVector3d(0, 0, 0), chrono::ChQuaterniond(0, 0, 0, 0));
    chrono::ChCoordsys acceleration_coordinates(chrono::ChVector3d(0, 0, 0), chrono::ChQuaterniond(0, 0, 0, 0));


    std::string marker_name = "Whatever";
    chrono::ChMarker dependencyFrame(marker_name, independent_body, position_coordinates, velocity_coordinates, acceleration_coordinates);


    
    return 0;
}
