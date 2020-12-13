#include "systems_manager.hpp"

ecs::SystemsManager* ecs::SystemsManager::instance_ = nullptr;

void ecs::SystemsManager::Initialize() {
  if (instance_ != nullptr) {
    throw std::logic_error("System already initialized.");
  }
  std::size_t number_of_system_types = System::systems_types_counter_;
  instance_ = new SystemsManager(number_of_system_types);
}

ecs::SystemsManager::SystemsManager(std::size_t& number_of_system_types)
    : kNumberOfSystemTypes(number_of_system_types),
      systems_(number_of_system_types, nullptr),
      systems_topological_order_(),
      dependency_graph_(std::vector<std::vector<std::size_t>>(number_of_system_types,
                                                              std::vector<std::size_t>(number_of_system_types, 0))) {
}

ecs::SystemsManager& ecs::SystemsManager::Instance() {
  if (instance_ == nullptr) {
    throw std::logic_error("SystemsManager is not initialized.");
  }

  return *instance_;
}

void ecs::SystemsManager::AddSystem(ecs::System* system) {
  systems_[system->GetSystemTypeId()] = system;
}

void ecs::SystemsManager::AddDependency(System* dependent, System* independent) {
  dependency_graph_[dependent->GetSystemTypeId()][independent->GetSystemTypeId()] = 1;
}

void ecs::SystemsManager::SetUp() {
  FindTopologicalOrder();
  for (auto system : systems_topological_order_) {
    system->SetUp();
  }
}

void ecs::SystemsManager::FindTopologicalOrder() {
  std::vector<char> color(kNumberOfSystemTypes, 'w');
  for (std::size_t i = 0; i < color.size(); ++i) {
    if (color[i] == 'w') {
      Dfs(color, i);
    }
  }
}

void ecs::SystemsManager::Dfs(std::vector<char> color, std::size_t source) {
  color[source] = 'g';

  for (std::size_t i = 0; i < kNumberOfSystemTypes; ++i) {
    if (dependency_graph_[source][i] == 1 && color[i] == 'w') {
      Dfs(color, i);
    } else if (color[i] == 'g') {
      throw std::logic_error("WrongDependency");
    }
  }
  color[source] = 'b';
  systems_topological_order_.push_back(systems_[source]);
}

void ecs::SystemsManager::PreUpdate() {
  for (auto system : systems_topological_order_) {
    system->PreUpdate();
  }
}

void ecs::SystemsManager::Update() {
  for (auto system : systems_topological_order_) {
    system->Update();
  }
}

void ecs::SystemsManager::PostUpdate() {
  for (auto system : systems_topological_order_) {
    system->PostUpdate();
  }
}

void ecs::SystemsManager::Destroy() {
  //for (auto system : instance_->systems_) {
    //system->ShutDown();
  //}
  //instance_->~SystemsManager();
  instance_ = nullptr;
}

