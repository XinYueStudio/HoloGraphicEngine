#pragma once
// External Headers
#include "glew.h"
#include "freeglut.h"
#define GLM_FORCE_RADIANS
#include "glm.hpp"
#include "gtx\quaternion.hpp"
#include "gtx\transform.hpp"
#include "gtc\type_ptr.hpp"

// System Headers
#include <iostream>

namespace HoloGraphicEngine
{

	class Camera 
	{
	public:

		/**
		 * Camera Default Constructor
		 */
		Camera();

		/**
		 * Camera Default Constructor
		 * @screen_width Width of the screen
		 * @screen_height Height of the screen
		 */
		Camera(int screen_width, int screen_height);
		/**
		 * Camera Default Constructor
		 * @screen_width Width of the screen
		 * @screen_height Height of the screen
		 */
		Camera(int position_x, int position_y,  int screen_width, int screen_height);

		/**
		 * Set the view port of the camera
		 * @x X value to set in view port
		 * @y Y value to set in view port
		 * @width Width of the screen
		 * @height Height of the screen
		 */
		void SetViewport(int x, int y, int width, int height);

		/**
		 * Get the view port
		 * @return View port of the camera
		 */
		glm::vec4 GetViewport() const;

		/**
		 * Sets the projection matrix
		 * @param field_of_view Field of View
		 * @param aspect_ratio Aspect Ratio for the projection
		 * @param z_near_value Near Clip Plane Z Value
		 * @param z_far_value Far Clip Plane Z Value
		 */
		void SetProjectionMatrix(float field_of_view, float aspect_ratio, float z_near_value, float z_far_value);

		/**
		* Calls UpdateViewMatrix() to update the view_matrix_
		* member
		*/
		void ApplyViewMatrix();

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
		* Returns the Projection Matrix
		* @return projection matrix of the camera
		*/
		glm::mat4 GetProjectionMatrix();

		/**
		* Returns the View Matrix
		* @return view matrix of the camera
		*/
		glm::mat4 GetViewMatrix();

		/**
		 * Static Variables keeping track of key presses
		 */
		static int KEY_W, KEY_A, KEY_S, KEY_D, KEY_Q, KEY_E, KEY_SHIFT;
		static glm::vec3 CAMERA_TRANSLATION;

		/**
		 * Static Variables keeping track of mouse position and state
		 */
		static int MOUSE_STATE; 
		static glm::ivec2 MOUSE_POSITION;
		static glm::quat MOUSE_ROTATION_X, MOUSE_ROTATION_Y;

		/**
		 * Keypress callback that will enable camera translation
		 * @param c Character corresponding to the key press
		 */
		static void KeyPressCallback(unsigned char c, int x, int y);

		/**
		* Key release callback that will enable resetting camera translation
		* @param c Character corresponding to the key release
		*/
		static void KeyReleaseCallback(unsigned char c, int x, int y);

		/**
		 * Mouse Press Callback
		 * @param button Button that was pressed
		 * @param state State of the button press
		 * @param x X value of mouse position
		 * @param y Y value of mouse posiiton
		 */
		static void MousePressCallback(int button, int state, int x, int y);

		/**
		* Mouse Motion Callback
		* Called when user holds down and moves mouse
		* @param x X value of mouse position
		* @param y Y value of mouse posiiton
		*/
		static void MouseMoveCallback(int x, int y);

		/**
		 * Callback to track special key presses, e.g., SHIFT
		 * @param key Pressed key
		 */
		static void SpecialKeyPressCallback(int key, int x, int y);

		/**
		* Callback to track special key releases, e.g., SHIFT
		* @param key Released key
		*/
		static void SpecialKeyReleaseCallback(int key, int x, int y);

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

		bool Stereo=false;

	protected:

		/* Internally view matrix updating method */
		void UpdateViewMatrix();

		/* View port of the camera */
		glm::vec4 view_port_;

		/* Current Position of the camera */
		glm::vec3 position_;

		/* Current Rotation of the camera */
		glm::quat rotation_;

		/* Current View Matrix */
		glm::mat4 view_matrix_;

		/* Current Projection Matrix */
		glm::mat4 projection_matrix_;


	private:

		/* Is the view dirty? */
		bool is_view_dirty_;

	
	};
}