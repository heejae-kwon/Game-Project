#include "ModelManager.h"

ModelManager::ModelManager(std::vector<std::string>& fileNames)
{
  for (auto const & fileName : fileNames)
  {
    std::string modelName = fileName.substr(fileName.find_last_of('/') + 1, fileName.find_last_of('.') - fileName.find_last_of('/') - 1);
    models_.emplace(modelName, make_shared<Model>(fileName));
  }
}

void ModelManager::initialize()
{
  for (auto const & kv : models_)
  {
    kv.second->bindMeshes();
  }
}

std::shared_ptr<Model> ModelManager::getModel(std::string modelName)
{
  return models_.at(modelName);
}