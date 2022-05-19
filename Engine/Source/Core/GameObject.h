#pragma once

// User-defined Headers
#include "VertexFormat.h"
#include "Camera.h"

// External Headers
#include "glew.h"
#include "freeglut.h"

// System Headers
#include <vector>
#include <iostream>

namespace HoloGraphicEngine
{
	/**
	 * Interface Class for Rendered Objects in our Engine
	 */
	class GameObject
	{
	public:

		/**
		 * Abstract Base Class Destructor
		 */
		virtual ~GameObject() = 0;

		/**
		 * Every renderable object has a Draw call
		 */
		virtual void Draw() = 0;

		/**
		* Every renderable object has a Draw call that takes a camera object as input
		* @param camera object which has the projection_matrix and the view matrix
		*/
		virtual void Draw(glm::mat4 view_matrix, glm::mat4 projection_matrix) = 0;

		/**
		 * Every renderable object has a Update call
		 */
		virtual void Update() = 0;

		/**
		 * Set a shader program for this object
		 */
		virtual void SetProgram(GLuint shader_name) = 0;

		/**
		 * Teardown this object
		 */
		virtual void Destroy() = 0;

		/**
		 * Set texture of the object
		 * @param texture_name Name of the texture
		 * @param texture Identifier of the texture
		 */
		virtual void SetTexture(std::string texture_name, GLuint texture) = 0;

		/**
		* Returns texture of the object
		* @param texture_name Name of the texture
		* @return texture ID associated with provided texture name
		*/
		virtual const GLuint GetTexture(std::string texture_name) const = 0;

		/**
		 * Get the vertex array object of this object
		 * @return Identifier for the vao of this object
		 */
		virtual GLuint GetVao() const = 0;

		/**
		 * Get the vertex buffer objects of this object
		 * @return vector of identifiers for the vbos of this object
		 */
		virtual const std::vector<GLuint>& GetVbos() const = 0;



		/**
	* Sets the camera position
	* @param position New camera position
	*/
		void SetPosition(const glm::vec3& position);

		/**
		* Returns the camera position
		* @return Current camera position
		*/
		glm::vec3 GetPosition();

		/**
		 * Translate the camera by some amount. If local is TRUE (default) then the translation should
		 * be applied in the local-space of the camera. If local is FALSE, then the translation is
		 * applied in world-space
		 */
		void Translate(const glm::vec3& delta, bool local = true);

		/**
		* Sets the camera rotation
		* @param rotation New camera rotation
		*/
		void SetRotation(const glm::quat& rotation);

		/**
		* Return the current camera rotation
		* @return Current camera rotation
		*/
		glm::quat GetRotation() const;

		/**
		* Sets the Euler Angles
		* @param euler_angles Vector of Euler Angles
		*/
		void SetEulerAngles(const glm::vec3& euler_angles);

		/**
		* Return the Euler Angles
		* @return Vector of Euler Angles
		*/
		glm::vec3 GetEulerAngles() const;

		/**
		* Rotates the Camera by some amount
		* @param rotation Rotation amount
		*/
		void Rotate(const glm::quat& rotation);

		/**
		* Returns the Model Matrix
		* @return Model matrix of the camera
		*/
		glm::mat4 GetModelMatrix();
 
		// Constants
		static const glm::vec3 LOCAL_FORWARD;
		static const glm::vec3 LOCAL_UP;
		static const glm::vec3 LOCAL_RIGHT;

		// Queries
		glm::vec3 Forward() const {
			return rotation_ * LOCAL_FORWARD;
		}

		glm::vec3 Right() const {
			return rotation_ * LOCAL_RIGHT;
		}

		glm::vec3 Up() const {
			return rotation_ * LOCAL_UP;
		}

		private:

			/* Internally model matrix updating method */
			void UpdateModelMatrix();

			/* Current Position of the camera */
			glm::vec3 position_;

			/* Current Rotation of the camera */
			glm::quat rotation_;

			/* Current  model Matrix */
			glm::mat4 model_matrix_;

			/* Is the view dirty? */
			bool is_view_dirty_;
	};

	// Inline Default Destructor Implementation
	inline GameObject::~GameObject() {}


	// Set the camera position
	inline	void  GameObject::SetPosition(const glm::vec3& position) {
		position_ = position;
		is_view_dirty_ = true;
	}

	// Returns the camera position
	inline	glm::vec3 GameObject::GetPosition() {
		return position_;
	}

	// Translate the camera by delta
	inline	void GameObject::Translate(const glm::vec3& delta, bool local /* = true */) {
		if (local)
			position_ += rotation_ * delta;
		else
			position_ += delta;
		is_view_dirty_ = true;
	}

	// Sets the camera rotation
	inline	void GameObject::SetRotation(const glm::quat& rotation) {
		rotation_ = rotation;
		is_view_dirty_ = true;
	}

	// Returns the camera rotation
	inline	glm::quat GameObject::GetRotation() const {
		return rotation_;
	}

	// Set the Euler Angles
	inline	void GameObject::SetEulerAngles(const glm::vec3& euler_angles) {
		rotation_ = glm::quat(glm::radians(euler_angles));
	}

	// Returns the Euler Angles
	inline	glm::vec3 GameObject ::GetEulerAngles() const {
		return glm::degrees(glm::eulerAngles(rotation_));
	}

	// Rotates the camera by provided quaternion
	inline	void GameObject::Rotate(const glm::quat& rotate_by) {
		rotation_ = rotation_ * rotate_by;
		is_view_dirty_ = true;
	}

	// Returns the projection matrix
	inline	glm::mat4 GameObject::GetModelMatrix() {
		UpdateModelMatrix();
		return model_matrix_;
	}

	// Updates the model matrix
	inline	void GameObject::UpdateModelMatrix() {
		if (is_view_dirty_) {
			glm::mat4 translate = glm::translate(position_);
			// Since we know the rotation matrix is ortho-normalized, we can simply 
			// transpose the rotation matrix instead of inversing.
			glm::mat4 rotate = glm::transpose(glm::toMat4(rotation_));
			model_matrix_ = rotate * translate;
			is_view_dirty_ = false;
		}
	}


}