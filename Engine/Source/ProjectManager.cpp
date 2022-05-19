// User-defined Headers
#include "ProjectManager.h"
namespace  HoloGraphicEngine
{
	// Default Constructor
	ProjectManager::ProjectManager() {}

	// Initialize Window, Context, FrameBufferInfo, OpenGL & all Managers
	bool ProjectManager::Init(int position_x, int position_y, int width, int height)
	{
		// Setup window information
		Core::WindowInfo window(std::string("Engine"), position_x, position_y, width, height, true);

		// Setup OpenGL context information
		Core::ContextInfo context(4, 5, true);

		// Setup FrameBuffer information
		Core::FrameBufferInfo framebuffer_info(true, true, true, true);

		// Initialize GLUT
		Core::Init::InitGLUT::Init(window, context, framebuffer_info);

		// Setup Scene Manager
		Scene_ = new Scene();
		Core::Init::InitGLUT::SetListener(Scene_);
 
		// Create the Scene's Camera Manager
		Camera_ = new Camera();
		Scene_->SetCamera(Camera_);

		glutKeyboardFunc(Camera::KeyPressCallback);
		glutKeyboardUpFunc(Camera::KeyReleaseCallback);
		glutMouseFunc(Camera::MousePressCallback);
		glutMotionFunc(Camera::MouseMoveCallback);
		glutSpecialFunc(Camera::SpecialKeyPressCallback);
		glutSpecialUpFunc(Camera::SpecialKeyReleaseCallback);


		return true;
	}

	// Main Engine Loop
	void ProjectManager::Run() {
		Core::Init::InitGLUT::Run();
	}

	// Return Scene Manager
	Scene* ProjectManager::GetScene() const {
		return Scene_;
	}
 

	// Return Camera Manager
	Camera* ProjectManager::GetCamera() const {
		return Camera_;
	}


	// Cleanup managers
	ProjectManager::~ProjectManager() {
		// Delete Scene Manager
		if (Scene_)
			delete Scene_;
	}
}