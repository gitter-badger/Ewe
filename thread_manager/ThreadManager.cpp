#include "ThreadManager.h"

#include <algorithm>

using std::for_each;

void thread_manager::ThreadManager::add(ThreadSubject * tc) {
  commands_.push_back(tc);
}

void thread_manager::ThreadManager::start ( ) {
  for (auto c : commands_)
    threads_.push_back(std::thread([&c] () { c->start(); }));
}

void thread_manager::ThreadManager::stop() {
  for (auto& c : commands_) c->stop();
  for (auto& t : threads_) t.join();

  commands_.clear();
  threads_.clear();
}
