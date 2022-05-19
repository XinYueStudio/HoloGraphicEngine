#pragma once

// User-defined Headers

#include "../Source/Core/Init/listener.h"
#include "../Source/Render/Shader.h"
#include "../Source/Render/Camera.h"
#include "../Source/Core/GameObject.h"
#include "../Source/Prefabs/Triangle.h"
#include "../Source/Prefabs/Quad.h"
#include <map>


namespace HoloGraphicEngine
{
	/**
	 * Scene Class
	 * Override Notification Methods
	 */
	class Scene : public Core::ListenerInterface
	{
	public:
		/* Scene Default Constructor */
		Scene();

		/* Scene Default Destructor */
		~Scene();

		/**
		 * Calls every model's update
		 */
		virtual void NotifyBeginFrame();

		/**
		 * Sets up OpenGL bits and calls every model's draw
		 */
		virtual void NotifyDisplayFrame();

		/**
		* Post-draw operations on all models
		*/
		virtual void NotifyEndFrame();

		/**
		 * Calls every model's reshape handler
		 * @param width New window width
		 * @param height New window height
		 * @param previous_width Previous window width
		 * @param previous_height Previous window height
		 */
		virtual void NotifyReshape(int width, int height, int previous_width, int previous_height);

		/**
		* Set camera manager of the scene manager
		* @param Pointer to the camera manager
		*/
		void SetCamera(Camera*& Camera);

 
		/**
		* This method deletes a 2D model in the internal map
		* @param model_name Name of the model to delete
		*/
		void DeleteModel2D(const std::string& model_name);

		/**
		* This method fetches a 2D model from the internal map
		* @param model_name Name of the model to fetch
		* @return Constant Reference to the model fetched from the internal map
		*/
		const GameObject& GetModel2D(const std::string& model_name) const;

		/**
		* This method deletes a 3D model in the internal map
		* @param model_name Name of the model to delete
		*/
		void DeleteModel3D(const std::string& model_name);

		/**
		* This method fetches a 3D model from the internal map
		* @param model_name Name of the model to fetch
		* @return Constant Reference to the model fetched from the internal map
		*/
		const GameObject& GetModel3D(const std::string& model_name) const;

		/**
		* Adds a new 2D model to the model map
		* @param model_name Name of the model
		* @param object Pointer to the object to store
		*/
		void AddModel2D(const std::string& model_name, GameObject* object);

		/**
		 * Adds a new 3D model to the model map
		 * @param model_name Name of the model
		 * @param object Pointer to the object to store
		 */
		void AddModel3D(const std::string& model_name, GameObject* object);


	private:
		/**
	 * This method calls the Draw() methods of each Object in
	 * the manager's internal map
	 */
		void Draw();

		/**
		* Every renderable object has a Draw call that takes a camera object as input
		* @param camera object which has the projection_matrix and the view matrix
		*/
		void Draw(glm::mat4 view_matrix, glm::mat4 projection_matrix);

		/**
		* This method calls the Update() methods of each Object in
		* the manager's internal map
		*/
		void Update();


		/**
		 * Internal map of 2D models
		 * Key: Model Name
		 * Value: Model Object
		 */
		std::map<std::string, GameObject*> model_map_2d_;

		/**
		* Internal map of 3D models
		* Key: Model Name
		* Value: Model Object
		*/
		std::map<std::string, GameObject*> model_map_3d_;


		/* Scene has a Camera to take care of view and projection matrices */
		Camera* Camera_;


	};
}
