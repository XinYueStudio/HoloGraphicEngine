// User-defined Headers
#include "Scene.h"

// External Headers
#include "../glm/gtx/transform.hpp"
#include "../glm/gtc/matrix_transform.hpp"
namespace HoloGraphicEngine
{
	// Scene Default Constructor - Construct shader manager and model manager here
	Scene::Scene() {
		glEnable(GL_DEPTH_TEST);
	}

	// Delete shader manager and model manager here
	Scene::~Scene() {

		// Delete 3D models
		for (auto model : model_map_3d_)
			delete model.second;
		model_map_3d_.clear();

		// Delete 2D models
		for (auto model : model_map_2d_)
			delete model.second;
		model_map_2d_.clear();
	 
	}

	/**
	 * Call model manager's Update() which updates every model in the
	 * model manager's internal map
	 */
	void Scene::NotifyBeginFrame() {
		// Translate camera to handle key press
		Camera_->Translate(Camera::CAMERA_TRANSLATION);
		if (Camera::MOUSE_STATE == 0) {
			Camera_->Rotate(Camera::MOUSE_ROTATION_X);
			Camera_->Rotate(Camera::MOUSE_ROTATION_Y);
		}


		Update();
	}

	/**
	 * Clear OpenGL bits and call the model manager's Draw() which draws
	 * every model in the model manager's internal map
	 */
	void Scene::NotifyDisplayFrame()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0, 0.0, 0.0, 1.0);

	
		glm::vec4 Viewport = Camera_->GetViewport();

	
		if (Camera_->Stereo)
		{

			glViewport(static_cast<GLint>(Viewport.x), static_cast<GLint>(Viewport.y), static_cast<GLsizei>(Viewport.z*0.5f), static_cast<GLsizei>(Viewport.w));
		}
		else
		{
			glViewport(static_cast<GLint>(Viewport.x), static_cast<GLint>(Viewport.y), static_cast<GLsizei>(Viewport.z), static_cast<GLsizei>(Viewport.w));
		}
		Draw();
		Draw(Camera_->GetViewMatrix(), Camera_->GetProjectionMatrix());
		 
		
		if (Camera_->Stereo)
		{
			glViewport(static_cast<GLint>(Viewport.z*0.5f), static_cast<GLint>(Viewport.y), static_cast<GLsizei>(Viewport.z*0.5f), static_cast<GLsizei>(Viewport.w));
			Draw();
			Draw(Camera_->GetViewMatrix(), Camera_->GetProjectionMatrix());
		 
		}
		
	}

	// Nothing to do here (for now)
	void Scene::NotifyEndFrame()
	{

	}

	// Nothing to do here (for now)
	void Scene::NotifyReshape(int width, int height, int previous_width, int previous_height) {

		float aspect_ratioscale = 1.0f;
		if (Camera_->Stereo)
		{
			aspect_ratioscale = 0.5f;
		}
		float aspect_ratio = (float)(glutGet(GLUT_WINDOW_WIDTH)*aspect_ratioscale) / (float)glutGet(GLUT_WINDOW_HEIGHT);
		float angle = 45.0f, near_value = 0.1f, far_value = 5000.0f;
		Camera_->SetProjectionMatrix(angle, aspect_ratio, near_value, far_value);
		Camera_->SetViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	}

 

	// Set the camera manager
	void Scene::SetCamera(Camera*& Camera) {
		Camera_ = Camera;
	}



	// Fetch model from internal map (by name) and call model.Destroy()
	void Scene::DeleteModel2D(const std::string& model_name) {
		GameObject* model = model_map_2d_[model_name];
		model->Destroy();
		model_map_2d_.erase(model_name);
	}

	// Fetch model from internal map (by name) and return a const reference to this model
	const GameObject& Scene::GetModel2D(const std::string& model_name) const {
		return (*model_map_2d_.at(model_name));
	}

	// Fetch model from internal map (by name) and call model.Destroy()
	void Scene::DeleteModel3D(const std::string& model_name) {
		GameObject* model = model_map_3d_[model_name];
		model->Destroy();
		model_map_3d_.erase(model_name);
	}

	// Fetch model from internal map (by name) and return a const reference to this model
	const GameObject& Scene::GetModel3D(const std::string& model_name) const {
		return (*model_map_3d_.at(model_name));
	}


	void Scene::AddModel2D(const std::string& model_name, GameObject* object) {
		model_map_2d_[model_name.c_str()] = object;
	}

	void Scene::AddModel3D(const std::string& model_name, GameObject* object) {
		model_map_3d_[model_name.c_str()] = object;
	}



	// Call model.Update() for each model in the internal map
	void Scene::Update() {
		for (auto model : model_map_2d_)
			model.second->Update();
		for (auto model : model_map_3d_)
			model.second->Update();
	}

	// Call model.Draw() for each 2d model in the internal map
	void Scene::Draw() {
		for (auto model : model_map_2d_)
			model.second->Draw();
	}

	// Call model.Draw() for each 3d model in the internal map
	void Scene::Draw(glm::mat4 view_matrix, glm::mat4 projection_matrix) {
		for (auto model : model_map_3d_)
			model.second->Draw(view_matrix, projection_matrix);
	}





}
