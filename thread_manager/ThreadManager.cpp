#include "ThreadManager.h"

void thread_manager::ThreadSubject::processCommands ( ) {
  while (this->commands_.size () > 0) {
    auto& c = this->commands_.front ();
    processCommand (c);
    this->commands_.pop ();
  }
}

std::shared_ptr<std::queue<command_manager::Command>> thread_manager::ThreadSubject::getQueueLink ( ) {
  return std::make_shared<std::queue<command_manager::Command>> (this->commands_);
}

command_manager::ID thread_manager::ThreadSubject::getId () {
  return this->id;
}

thread_manager::ThreadManager::ThreadManager ( ) {
  this->commandManager_.addQueue (
    command_manager::ID::THREAD_MANAGER,
    std::make_shared<std::queue<command_manager::Command>>(
      this->commands_
    )
  );
}

void thread_manager::ThreadManager::add(ThreadSubject * tc) {
  this->subjects_.push_back (tc);
  this->commandManager_.addQueue (tc->getId ( ), tc->getQueueLink ( ));
}

void thread_manager::ThreadManager::start ( ) {
  for (auto c : subjects_)
    threads_.push_back(std::thread([&c] () { c->start(); }));
}

void thread_manager::ThreadManager::stop() {
  for (auto& c : subjects_) c->stop ();
  for (auto& t : threads_) t.join();

  subjects_.clear ();
  threads_.clear();
}

void thread_manager::ThreadManager::listen ( ) {
  //while (true) {
  //  auto a = std::chrono::milliseconds (100);
  //  std::this_thread::sleep_for (a);

  //  commandManager_.process ();

  //  while (this->commands_.size () > 0) {
  //    auto& c = this->commands_.front ();
  //    switch (c.commandType) {
  //      case command_manager::CommandType::KILL: {
  //        this->stop ( );
  //        return;
  //      }
  //      default: break;
  //    }
  //    this->commands_.pop ();
  //  }

  //  // TODO: commands from OS
  //  // all -> pause();
  //  // all -> unpause();
  //}
}
