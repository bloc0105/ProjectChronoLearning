#include "chrono/assets/ChVisualMaterial.h"
#include "chrono/assets/ChVisualShapeBox.h"
#include "chrono/physics/ChBody.h"
#include <string>
#include "chrono/physics/ChLinkLock.h"

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
    chrono::ChCoordsys velocity_coordinates(chrono::ChVector3d(0, 0, 0), chrono::ChQuaterniond(1, 0, 0, 0));
    chrono::ChCoordsys acceleration_coordinates(chrono::ChVector3d(0, 0, 0), chrono::ChQuaterniond(1, 0, 0, 0));

    chrono::ChFramed the_main_frame(position_coordinates);

    std::string marker_name = "Whatever";
    std::string other_marker_name = "A Marker";

    // chrono::ChMarker independent_marker(marker_name,independent_body.get(),independent_body->GetCoordsys(),
    //                                     independent_body->GetCoordsysDt(),independent_body->GetCoordsysDt2());

    // chrono::ChMarker dependent_marker(other_marker_name,dependent_body.get(),dependent_body->GetCoordsys(),
    //                 dependent_body->GetCoordsysDt(),dependent_body->GetCoordsysDt2());

    auto some_link = chrono_types::make_shared<chrono::ChLinkLock>();
    some_link->Initialize(independent_body,dependent_body,the_main_frame);

    std::cout << "Before" << std::endl << "------------------------------------------------------------------------" << std::endl;

    std::cout << "Independent: " << independent_body->GetPos() << std::endl;
    std::cout << "Dependent: " << dependent_body->GetPos() << std::endl << std::endl;

    // And now we move the thing

    independent_body->SetPos(chrono::ChVector3d(5,2,3));

    std::cout << "After" << std::endl << "--------------------------------------------------------------------------" << std::endl;


    std::cout << "Independent: " << independent_body->GetPos() << std::endl;
    std::cout << "Dependent: " << dependent_body->GetPos() << std::endl << std::endl;



    
    return 0;
}
