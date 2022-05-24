#pragma once

// User-defined Headers
#include "../Source/ProjectManager.h"
#include "../Source/Prefabs/Sphere.h"
#include "../Source/Render/Camera.h"
#include "../Source/Render/Shader.h"
#include "../../MicroLightPlugin/Manager/MicroLightPluginForHoloGraphicEngine.h"

#include <string>
 
using namespace HoloGraphicEngine;
 
int main(int argc, char **argv)
{
	int windowposx = 400;
	int windowposy = 100;
	int windowwidth = 1400;
	int windowheight = 1200;


	// Initialize the Project Manager
	ProjectManager* Project = new ProjectManager();
	Project->Init(windowposx, windowposy, windowwidth, windowheight);
	 
	Camera*	Camera= Project->GetCamera();
	Camera->SetViewport(0, 0, windowwidth, windowheight);
	Camera->Stereo = true;

	// Setup camera's initial position
	Project->GetCamera()->SetPosition(glm::vec3(0, 0, 5));
	Shader* mShader = new Shader();
	// Setup Cube's Vertex and Fragment Shaders
	mShader->CreateProgram("sphere_shader", "Resources\\Shaders\\sphere_vertex_shader.glsl", "Resources\\Shaders\\sphere_fragment_shader.glsl");

	// Create the Cube and set its shader program
	Sphere* sphere = new Sphere();
	sphere->SetProgram(mShader->GetShader("sphere_shader"));

	// Create a icosphere of radius 1 with 32 slices and 32 stacks
	sphere->Create(1, 32, 32);

	sphere->SetPosition(glm::vec3(0,1,0));

	// Add cube to Project's Scene 
	Project->GetScene()->AddModel3D("sphere", sphere);


	//Creat MicroLightPlugin and add to run

	MicroLightPluginForHoloGraphicEngine* mMicroLightPlugin = new MicroLightPluginForHoloGraphicEngine();


	 string argv_str(argv[0]);
	 string base = argv_str.substr(0, argv_str.find_last_of("/"));
	   base = argv_str.substr(0, argv_str.find_last_of("\\"));
	 
	 string FullPath = base + "\\ImageDll.dll";
	//Set Image.dll FullPath
	Project->AddPlugin(FullPath,mMicroLightPlugin);

	// Run the Engine
	Project->Run();

	// Delete the Engine Object when rendering loop is finished
	delete Project;
	return 0;
}