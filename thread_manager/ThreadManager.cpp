#include "ThreadManager.h"

#include <algorithm>

using std::for_each;

void thread_manager::ThreadManager::add(ThreadSubject * tc) {
  commands_.push_back(tc);
}

void thread_manager::ThreadManager::start() {
  for_each(commands_.begin(), commands_.end(), [&] (ThreadSubject * tc) {
    threads_.push_back(std::thread([&tc] () { tc->start(); }));
  });
}

void thread_manager::ThreadManager::stop() {
  for_each(commands_.begin(), commands_.end(), [] (ThreadSubject * tc) { tc->stop(); });
  commands_.clear();

  for_each(threads_.begin(), threads_.end(), [] (std::thread& t) { t.join(); });
  threads_.clear();
}
