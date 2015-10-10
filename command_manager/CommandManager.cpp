#include "CommandManager.h"

void command_manager::CommandManager::addQueue (command_manager::ID id, std::shared_ptr<std::queue<command_manager::Command>> q) {
  this->queues_ [id] = q;
}

void command_manager::CommandManager::push (command_manager::Command& a) {
  this->commands_.push (a);
}

void command_manager::CommandManager::process () {
  while (this->commands_.size() > 0) {
    auto& a = this->commands_.front ( );
    this->queues_ [a.to]->push (a);
    this->commands_.pop ( );
  }
}