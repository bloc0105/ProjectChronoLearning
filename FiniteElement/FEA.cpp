#include "chrono/physics/ChSystemSMC.h"
#include "chrono/fea/ChMesh.h"
#include "chrono/fea/ChNodeFEAxyz.h"
#include "chrono/fea/ChContinuumMaterial.h"
#include "chrono/fea/ChElementTetraCorot_4.h"
#include "chrono/solver/ChSolverPMINRES.h"

int main()
{
    chrono::ChSystemSMC my_system;

    auto my_mesh = chrono_types::make_shared<chrono::fea::ChMesh>();

    // Create nodes
    auto mesh_node1 = chrono_types::make_shared<chrono::fea::ChNodeFEAxyz>(chrono::ChVector3d(0, 0, 0));
    auto mesh_node2 = chrono_types::make_shared<chrono::fea::ChNodeFEAxyz>(chrono::ChVector3d(0, 0, 1));
    auto mesh_node3 = chrono_types::make_shared<chrono::fea::ChNodeFEAxyz>(chrono::ChVector3d(0, 1, 0));
    auto mesh_node4 = chrono_types::make_shared<chrono::fea::ChNodeFEAxyz>(chrono::ChVector3d(1, 0, 0));

    my_mesh->AddNode(mesh_node1);
    my_mesh->AddNode(mesh_node2);
    my_mesh->AddNode(mesh_node3);
    my_mesh->AddNode(mesh_node4);

    // Set node masses
    double node_mass = 0.01;
    mesh_node1->SetMass(node_mass);
    mesh_node2->SetMass(node_mass);
    mesh_node3->SetMass(node_mass);
    mesh_node4->SetMass(node_mass);

    // Set forces (optional, demonstrating zero force)
    mesh_node2->SetForce(chrono::ChVector3d(0, 0, 0));

    // Create and set up material
    auto fea_material = chrono_types::make_shared<chrono::fea::ChContinuumElastic>();
    fea_material->SetYoungModulus(207e9); // Adjusted Young's modulus for steel
    fea_material->SetPoissonRatio(0.3);

    // Create and set up element
    auto fea_element = chrono_types::make_shared<chrono::fea::ChElementTetraCorot_4>();
    fea_element->SetNodes(mesh_node1, mesh_node2, mesh_node3, mesh_node4);
    fea_element->SetMaterial(fea_material);

    // Add element to the mesh
    my_mesh->AddElement(fea_element);

mesh_node1->SetFixed(true);

    // Add mesh to the system
    my_system.Add(my_mesh);

    // Solver and timestepper settings
    auto solver = chrono_types::make_shared<chrono::ChSolverPMINRES>();
    my_system.SetSolver(solver);
    solver->SetMaxIterations(100);
    solver->SetTolerance(1e-10);
    solver->EnableDiagonalPreconditioner(true);
    solver->SetVerbose(true);

    // Perform static linear analysis
    my_system.DoStaticLinear();

    // Output some information to the console
    std::cout << "Node1 Position: " << mesh_node1->GetPos()
              << " Node2 Position: " << mesh_node2->GetPos()
              << " Node3 Position: " << mesh_node3->GetPos()
              << " Node4 Position: " << mesh_node4->GetPos()
              << std::endl;

    return 0;
}
