#include <ecs/manager/systems_manager.hpp>

namespace ecs {
namespace manager {

SystemsManager* SystemsManager::instance_ = nullptr;

void SystemsManager::Initialize(unsigned char* memory_ptr) {
  if (instance_ != nullptr) {
    throw std::logic_error("System already initialized.");
  }
  std::size_t number_of_system_types = system::System::GetSystemTypesCount();
  instance_ = new (memory_ptr) SystemsManager(number_of_system_types);
}

void SystemsManager::Destroy() {
  for (auto system : instance_->systems_) {
    if (system != nullptr) {
      system->ShutDown();
    }
  }
  instance_->~SystemsManager();
  instance_ = nullptr;
}

SystemsManager::SystemsManager(const std::size_t& number_of_system_types)
    : kNumberOfSystemTypes_(number_of_system_types),
      systems_(number_of_system_types, nullptr),
      systems_topological_order_(),
      dependency_graph_(std::vector<std::vector<std::size_t>>(
          number_of_system_types, std::vector<std::size_t>(number_of_system_types, 0))) {
}

SystemsManager& SystemsManager::Instance() {
  if (instance_ == nullptr) {
    throw std::logic_error("SystemsManager is not initialized.");
  }

  return *instance_;
}

void SystemsManager::AddSystem(system::System* system) {
  systems_[system->GetSystemTypeId() - 1] = system;
}

void SystemsManager::AddDependency(system::System* dependent, system::System* independent) {
  dependency_graph_[dependent->GetSystemTypeId() - 1][independent->GetSystemTypeId() - 1] = 1;
}

void SystemsManager::SetUp() {
  FindTopologicalOrder();
  for (auto system : systems_topological_order_) {
    if (system != nullptr) {
      system->SetUp();
    }
  }
}

void SystemsManager::FindTopologicalOrder() {
  std::vector<char> color(kNumberOfSystemTypes_, 'w');
  for (std::size_t i = 0; i < color.size(); ++i) {
    if (color[i] == 'w') {
      Dfs(color, i);
    }
  }
}

void SystemsManager::Dfs(std::vector<char>& color, std::size_t& source) {
  color[source] = 'g';

  for (std::size_t i = 0; i < kNumberOfSystemTypes_; ++i) {
    if (dependency_graph_[source][i] == 1 && color[i] == 'w') {
      Dfs(color, i);
    } else if (color[i] == 'g' && dependency_graph_[source][i] == 1) {
      throw std::logic_error("WrongDependency");
    }
  }
  color[source] = 'b';
  systems_topological_order_.push_back(systems_[source]);
}

void SystemsManager::PreUpdate() {
  for (auto system : systems_topological_order_) {
    if (system != nullptr) {
      system->PreUpdate();
    }
  }
}

void SystemsManager::Update() {
  for (auto system : systems_topological_order_) {
    if (system != nullptr) {
      system->Update();
    }
  }
}

void SystemsManager::PostUpdate() {
  for (auto system : systems_topological_order_) {
    if (system != nullptr) {
      system->PostUpdate();
    }
  }
}

}  // namespace manager
}  // namespace ecs