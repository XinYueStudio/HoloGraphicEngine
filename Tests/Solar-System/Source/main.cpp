#pragma once

// User-defined Headers
#include "../Source/ProjectManager.h"
#include "../Source/Prefabs/Sphere.h"
#include "../Source/Prefabs/Skybox.h"
#include "../Source/Prefabs/SolarSystem.h"
#include "../Source/Prefabs/Earth.h"
#include "../Source/Render/Camera.h"
#include "../Source/Render/Shader.h"
#include "../Source/Utilities/Utilities.h"

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

	Camera*	Camera = Project->GetCamera();
	Camera->SetViewport(0, 0, windowwidth, windowheight);
	Camera->Stereo = true;

	// Setup camera's initial position
	Project->GetCamera()->SetPosition(glm::vec3(0, 0, 300));

	// Setup Earth's Vertex and Fragment Shaders
	Shader* mShader = new Shader();
	mShader->CreateProgram("earth_shader", "Resources\\Shaders\\earth_vertex_shader.glsl", "Resources\\Shaders\\earth_fragment_shader.glsl");
	mShader->CreateProgram("sun_shader", "Resources\\Shaders\\sun_vertex_shader.glsl", "Resources\\Shaders\\sun_fragment_shader.glsl");
	mShader->CreateProgram("skybox_shader", "Resources\\Shaders\\skybox_vertex_shader.glsl", "Resources\\Shaders\\skybox_fragment_shader.glsl");

	// Create the skybox and set its shader program
	Skybox* skybox = new Skybox();

	// Set the Skybox's Program
	skybox->SetProgram(mShader->GetShader("skybox_shader"));

	// Load Cube-Map for Skybox
	std::vector<std::string> faces = {
		"Resources\\Textures\\SkyboxPositiveX.png",
		"Resources\\Textures\\SkyboxNegativeX.png",
		"Resources\\Textures\\SkyboxPositiveY.png",
		"Resources\\Textures\\SkyboxNegativeY.png",
		"Resources\\Textures\\SkyboxPositiveZ.png",
		"Resources\\Textures\\SkyboxNegativeZ.png"
	};
	unsigned int skybox_texture_id = Utilities::LoadCubeMapTexture(faces);
	skybox->SetTexture("skybox_texture", skybox_texture_id);
	skybox->Create();

	// Create the Earth and set its shader program
	SolarSystem* system = new SolarSystem();

	std::map<std::string, std::string> textures = {
		std::make_pair("sun", "Resources\\Textures\\Sun.dds"),
		std::make_pair("mercury", "Resources\\Textures\\Mercury.dds"),
		std::make_pair("venus", "Resources\\Textures\\Venus.dds"),
		std::make_pair("earth", "Resources\\Textures\\Earth.dds"),
		std::make_pair("moon", "Resources\\Textures\\Moon.dds"),
		std::make_pair("mars", "Resources\\Textures\\Mars.dds"),
		std::make_pair("jupiter", "Resources\\Textures\\Jupiter.dds"),
		std::make_pair("saturn", "Resources\\Textures\\Saturn.dds"),
		std::make_pair("uranus", "Resources\\Textures\\Uranus.dds"),
		std::make_pair("neptune", "Resources\\Textures\\Neptune.dds"),
	};

	// Load and Set Textures from Textures Map
	for (auto const& texture : textures)
		system->SetTexture(texture.first, Utilities::LoadDDSTexture(texture.second));

	// Set the Earth's Program
	system->SetProgram(mShader->GetShader("earth_shader"));

	// Create a icosphere of radius 1 with 32 slices and 32 stacks
	system->Create(0.3f, 32, 32);

	// Add cube to Engine's Model Manager
	Project->GetScene()->AddModel3D("skybox", skybox);
	Project->GetScene()->AddModel3D("system", system);

	// Run the Engine
	Project->Run();

	// Delete the Project Object when rendering loop is finished
	delete Project;
	return 0;
}