#pragma once
#include <map>
#include <memory>
#include "Model.hpp"
#include <string>

// Manages all the models, duh. You should only have one of these
// Otherwise something has gone wrong and you're SOL
class ModelManager {
  public:
    // Wut r u doing, ModelManager needs to have filenames to the models
    // Dont use this, in fact I DELETED it so hah
    ModelManager() = delete;

    // Constructor that takes a vector of filenames
    ModelManager(std::vector<std::string>& fileNames);

    ~ModelManager() { }

    // CALL ONLY ONCE
    //Initialize all the models so OpenGL knows how to render them
    void initialize();

    // Get a model by its name
    std::shared_ptr<Model> getModel(std::string modelName);

    // Get the total number of unique models
    int getNumModels() { return static_cast<int>(models_.size()); }

  private:
    // Key is the name of the model without the file extension ".model"
    // value is a pointer to the model itself
    std::map<std::string, std::shared_ptr<Model> > models_;
};