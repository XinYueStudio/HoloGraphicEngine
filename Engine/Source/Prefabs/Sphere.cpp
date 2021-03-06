// User-defined Headers
#include "Sphere.h"

// External Headers
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

// System Headers
#include <vector>
#include <iostream>

// Define PI for local use
#define M_PI 3.1415926535897932384626433832795
#define M_2PI M_PI * 2
namespace HoloGraphicEngine
{
	void Sphere::Create(float radius, float slices, float stacks) {

		for (int i = 0; i <= stacks; ++i) {

			// V texture coordinate
			double V = i / static_cast<double>(stacks);
			double phi = V * M_PI;

			for (int j = 0; j <= slices; ++j)
			{
				// U texture coordinate
				double U = j / static_cast<double>(slices);
				double theta = U * M_2PI;

				double X = cos(theta) * sin(phi);
				double Y = cos(phi);
				double Z = sin(theta) * sin(phi);

				// Add this vertex (with white color)
				vertices.push_back(VertexFormat(glm::vec3(X, Y, Z) * radius, glm::vec4(1, 1, 1, 1)));
			}
		}

		for (int i = 0; i < slices * stacks + slices; ++i) {
			indices.push_back(i);
			indices.push_back(static_cast<GLuint>(i + slices + 1));
			indices.push_back(static_cast<GLuint>(i + slices));

			indices.push_back(static_cast<GLuint>(i + slices + 1));
			indices.push_back(static_cast<GLuint>(i));
			indices.push_back(static_cast<GLuint>(i + 1));
		}

		GLuint vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		GLuint vbo, ibo;
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ibo);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexFormat), vertices.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat),
			(void*)(offsetof(VertexFormat, VertexFormat::color)));
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		this->vbos.push_back(vbo);
		this->vbos.push_back(ibo);
		this->vao = vao;
	}

	void Sphere::Update() {}

	void Sphere::Draw(glm::mat4 view_matrix, glm::mat4 projection_matrix) {
		// Map shader variables
		glUseProgram(program);
		glUniformMatrix4fv(glGetUniformLocation(program, "model_matrix"), 1, false, &(GetModelMatrix())[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(program, "view_matrix"), 1, false, &(view_matrix)[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(program, "projection_matrix"), 1, false, &(projection_matrix)[0][0]);
		glBindVertexArray(vao);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
	}
}