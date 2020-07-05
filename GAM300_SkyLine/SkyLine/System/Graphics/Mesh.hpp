#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Texture.h"
#include "Vertex.h"

using namespace std;

class Mesh {
  friend class Model;
  public:
    /*  Functions  */
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);

    const vector<Vertex>&        getVertices()  { return vertices_; }
    const vector<unsigned int>&  getIndices()   { return indices_;  }
    const vector<Texture>&       getTextures_() { return textures_; }

    int numberVertices()       const { return static_cast<int>(vertices_.size()); }
    int numberIndices()        const { return static_cast<int>(indices_.size());  }
    int numberTextures() const { return static_cast<int>(textures_.size()); }

    unsigned int getVAO() const { return VAO_; }
    unsigned int getVBO() const { return VBO_; }
    unsigned int getEBO() const { return EBO_; }

  private:
    // Render Data
    unsigned int VAO_, VBO_, EBO_;

    /*  Mesh Data  */
    vector<Vertex> vertices_;
    vector<unsigned int> indices_;
    vector<Texture> textures_;

    /*  Functions    */
    void bindMesh();
};