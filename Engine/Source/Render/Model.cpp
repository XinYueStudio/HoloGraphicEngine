// User-defined Headers
#include "Model.h"
namespace HoloGraphicEngine
{
	// Call Destroy and cleanup vao and vbos of the model
	Model::~Model() {
		Destroy();
	}

	// Draw methods will be overridden
	void Model::Draw() {}
	void Model::Draw(glm::mat4 view_matrix, glm::mat4 projection_matrix) {}

	// Update method will be overridden
	void Model::Update() {}

	// Set the shader program of this model
	void Model::SetProgram(GLuint program) {
		this->program = program;
	}

	// Return model's vao
	GLuint Model::GetVao() const {
		return vao;
	}

	// Return const reference to model's vbos vector
	const std::vector<GLuint>& Model::GetVbos() const {
		return vbos;
	}

	// Delete vao and vbos
	void Model::Destroy() {
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(static_cast<GLsizei>(vbos.size()), &vbos[0]);
		vbos.clear();
	}

	// Set new texture for this model in the model's internal map
	void Model::SetTexture(std::string texture_name, GLuint texture) {
		if (texture == 0) return;
		textures[texture_name] = texture;
	}

	// Return texture from internal map with given texture name
	const GLuint Model::GetTexture(std::string texture_name) const {
		return textures.at(texture_name);
	}
}