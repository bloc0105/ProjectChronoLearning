#include "chrono/physics/ChSystemSMC.h"
#include "chrono/fea/ChMesh.h"
#include "chrono/fea/ChNodeFEAxyz.h"
#include "chrono/fea/ChContinuumMaterial.h"
#include "chrono/fea/ChElementTetraCorot_4.h"

int main()
{
    // Create a physical system
    chrono::ChSystemSMC my_system;

    auto my_mesh = chrono_types::make_shared<chrono::fea::ChMesh>();

    auto mesh_node1 = chrono_types::make_shared<chrono::fea::ChNodeFEAxyz>(chrono::ChVector3d(0, 0, 0));
    auto mesh_node2 = chrono_types::make_shared<chrono::fea::ChNodeFEAxyz>(chrono::ChVector3d(0, 0, 1));
    auto mesh_node3 = chrono_types::make_shared<chrono::fea::ChNodeFEAxyz>(chrono::ChVector3d(0, 1, 0));
    auto mesh_node4 = chrono_types::make_shared<chrono::fea::ChNodeFEAxyz>(chrono::ChVector3d(1, 0, 0));

    my_mesh->AddNode(mesh_node1);
    my_mesh->AddNode(mesh_node2);
    my_mesh->AddNode(mesh_node3);
    my_mesh->AddNode(mesh_node4);


    mesh_node1->SetMass(0.01);
    mesh_node2->SetMass(0.01);

    mesh_node2->SetForce(chrono::ChVector3d(0, 0, 0));

    auto fea_material = chrono_types::make_shared<chrono::fea::ChContinuumElastic>();

    fea_material->SetYoungModulus(0.01e9);
    fea_material->SetPoissonRatio(0.3);

    auto fea_element = chrono_types::make_shared<chrono::fea::ChElementTetraCorot_4>();

    my_mesh->AddElement(fea_element);

    fea_element->SetNodes(mesh_node1, mesh_node2, mesh_node3, mesh_node4);

    fea_element->SetMaterial(fea_material);

     my_system.Add(my_mesh);

    double timestep = 0.01;

    for (double i = 0.0; i < 1.0; i += timestep)
    {
        my_system.DoStepDynamics(timestep);

        // Output some information to the console
        std::cout << "Time: " << my_system.GetChTime()
                  << " Node1 Position: " << mesh_node1->GetPos()
                  << " Node2 Position: " << mesh_node2->GetPos()
                  << " Node3 Position: " << mesh_node3->GetPos()
                  << " Node4 Position: " << mesh_node4->GetPos()
                  << std::endl;
    }

    return 0;
}
