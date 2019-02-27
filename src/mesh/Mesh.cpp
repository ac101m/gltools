#include <GLT/Mesh.hpp>
using namespace GLT;


// Constructor, with automatic indices
Mesh::Mesh(std::vector<vertex_t> vertices) {
  this->vertices = vertices;
  this->indices.reserve(vertices.size());
  for(unsigned i = 0; i < this->vertices.size(); i++) {
    this->indices.push_back(i);
  }
  this->vertexBuffer = VertexBuffer(this->vertices, this->indices);
}


// Construct the mesh
Mesh::Mesh(std::vector<vertex_t> vertices,
           std::vector<unsigned> indices,
           std::vector<Texture> textures) :
           vertices(vertices), indices(indices), textures(textures) {
  this->vertexBuffer = VertexBuffer(this->vertices, this->indices);
}


// Compute tangents
void Mesh::GenTangentSpaceBasis(void) {

  // Clear vertex tangents and bitangents
  for(unsigned i = 0; i < this->vertices.size(); i++) {
    this->vertices[i].tangent = glm::vec3(0, 0, 0);
    this->vertices[i].bitangent = glm::vec3(0, 0, 0);
  }

  // Iterate over triangles
  vertex_t *v[3];
  for(unsigned i = 0; i < this->indices.size(); i += 3) {
    for(unsigned j = 0; j < 3; j++) v[j] = &this->vertices[this->indices[i + j]];

    // Calculate deltas
    glm::vec3 dPos1 = v[1]->position - v[0]->position;
    glm::vec3 dPos2 = v[2]->position - v[0]->position;
    glm::vec2 dUV1 = v[1]->uv - v[0]->uv;
    glm::vec2 dUV2 = v[2]->uv - v[0]->uv;

    // Calculate tan and bitan
    float r = 1.0f / (dUV1.x * dUV2.y - dUV1.y * dUV2.x);
    glm::vec3 tan = (dPos1 * dUV2.y - dPos2 * dUV1.y) * r;
    glm::vec3 bitan = (dPos2 * dUV1.x - dPos1 * dUV2.x) * r;

    for(unsigned j = 0; j < 3; j++) {
      v[j]->tangent += tan;
      v[j]->bitangent += bitan;
    }
  }

  // Normalise tangents and bitangents
  for(unsigned i = 0; i < this->vertices.size(); i++) {
    this->vertices[i].tangent = glm::normalize(this->vertices[i].tangent);
    this->vertices[i].bitangent = glm::normalize(this->vertices[i].bitangent);
  }
}


// Auto generate normals
void Mesh::AutoGenerateNormals(void) {

  // Reset vertex normals
  for(unsigned i = 0; i < this->vertices.size(); i++) {
    this->vertices[i].normal = glm::vec3(0, 0, 0);
  }

  // Add up face normals
  vertex_t *v[3];
  for(unsigned i = 0; i < this->indices.size(); i += 3) {
    for(unsigned j = 0; j < 3; j++) v[j] = &this->vertices[this->indices[i + j]];
    glm::vec3 faceNormal = glm::cross(
      v[1]->position - v[0]->position,
      v[2]->position - v[0]->position);
    for(unsigned j = 0; j < 3; j++) v[j]->normal += faceNormal;
  }

  // Normalise vertex normals
  for(unsigned i = 0; i < this->vertices.size(); i++) {
    this->vertices[i].normal = glm::normalize(this->vertices[i].normal);
  }

  // Once normals are generated, generate tangents and bitangents
  this->GenTangentSpaceBasis();

  // Regenerate the vertex buffer
  this->vertexBuffer = VertexBuffer(this->vertices, this->indices);
}


// Print all the things
void Mesh::Print(void) {
  vertex_t *v[3];
  for(unsigned i = 0; i < this->indices.size(); i += 3) {
    std::cout << "[POLY " << i / 3 << "][INDEX " << "" << "]\n";
    for(unsigned j = 0; j < 3; j++) v[j] = &this->vertices[this->indices[i + j]];
    for(unsigned j = 0; j < 3; j++) {
      v[j]->Print();
    }
  }
}


// Draw routine
void Mesh::Draw(Camera& camera, ShaderProgram& shader, glm::mat4& m) {

  // Multiply out the matrices IN THE RIGHT FUCKING ORDER THIS TIME
  // GOD DMAN NON-COMMUTATIVE BASTARDS FKN 4 HOURS RIGHT THERE
  glm::mat4 mvp = camera.GetProjMat() * camera.GetViewMat() * m;
  glm::mat3 mv3 = glm::mat3(camera.GetViewMat() * m);

  // Shader uniform setup
  shader.SetMat4("mMx", m);
  //shader.SetMat4("vMx", camera.GetViewMat());
  //shader.SetMat3("mv3Mx", mv3);
  shader.SetMat4("mvpMx", mvp);

  // Bind textures to texture units
  std::string name = "texture0";
  for(unsigned i = 0; i < this->textures.size(); i++) {
    name[7] = 48 + i;
    shader.SetTexture(i, name, this->textures[i]);
  }

  // Draw the things
  this->vertexBuffer.Bind();
  glDrawElements(
    GL_TRIANGLES,
    this->vertexBuffer.GetIndexBufferLength(),
    GL_UNSIGNED_INT, 0);
  this->vertexBuffer.Unbind();

  // Set texture back to texture 0
  glActiveTexture(GL_TEXTURE0);
}
