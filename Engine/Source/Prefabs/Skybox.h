#pragma once

// User-defined Headers
#include "../Source/Render/Model.h"

namespace HoloGraphicEngine
{

		/**
		* Skybox Class
		*/
		class Skybox : public Model
		{
		public:

			/**
			* (1) Create the set of vertices
			* (2) Create and bind vbo and vao
			*/
			void Create();

			/**
			* Overrides Model's Draw method
			* (1) Use Shader Program
			* (2) Bind avo
			* (3) Draw vertices
			*/
			virtual void Draw(glm::mat4 view_matrix, glm::mat4 projection_matrix) override final;

			/**
			* Update rotation of the cube
			*/
			virtual void Update() override final;
		};
	 
}