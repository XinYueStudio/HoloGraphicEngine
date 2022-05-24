#pragma once

// User-defined Headers
#include "../Source/ProjectManager.h"
#include "../Source/Prefabs/Cube.h"
#include "../Source/Render/Camera.h"
#include "../Source/Render/Shader.h"
#include "../Source/Utilities/Utilities.h"
#include "../../MicroLightPlugin/Manager/MicroLightPluginForHoloGraphicEngine.h"

#include <string>

using namespace HoloGraphicEngine;

int main(int argc, char **argv) 
{
	// Initialize the Engine Manager
// Initialize the Engine Manager
	int windowposx = 400;
	int windowposy = 100;
	int windowwidth = 1400;
	int windowheight = 1200;


	// Initialize the Project Manager
	ProjectManager* Project = new ProjectManager();
	Project->Init(windowposx, windowposy, windowwidth, windowheight);

	Camera*	Camera = Project->GetCamera();
	Camera->SetViewport(0, 0, windowwidth, windowheight);
	Camera->Stereo = true;

	// Setup camera's initial position
	Project->GetCamera()->SetPosition(glm::vec3(0, 0, 5));

	// Setup Cube's Vertex and Fragment Shaders
	Shader* mShader = new Shader();
	mShader->CreateProgram("cubeShader", "Resources\\Shaders\\cube_vertex_shader.glsl", "Resources\\Shaders\\cube_fragment_shader.glsl");

	// Create the Cube and set its shader program
	Cube* cube = new Cube();
	cube->SetProgram(mShader->GetShader("cubeShader"));
	cube->Create();

	unsigned int texture = Utilities::LoadBMPTexture("Resources\\Textures\\Crate.bmp");
	cube->SetTexture("Crate", texture);

	// Add cube to Engine's Model Manager
	Project->GetScene()->AddModel3D("cube", cube);

	//Creat MicroLightPlugin and add to run

	MicroLightPluginForHoloGraphicEngine* mMicroLightPlugin = new MicroLightPluginForHoloGraphicEngine();


	string argv_str(argv[0]);
	string base = argv_str.substr(0, argv_str.find_last_of("/"));
	base = argv_str.substr(0, argv_str.find_last_of("\\"));

	string FullPath = base + "\\ImageDll.dll";
	//Set Image.dll FullPath
	Project->AddPlugin(FullPath, mMicroLightPlugin);

	// Run the Project
	Project->Run();

	// Delete the Project Object when rendering loop is finished
	delete Project;
	return 0;
}
