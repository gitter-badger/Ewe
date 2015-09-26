#include "ThreadManager.h"

#include <algorithm>

using std::make_shared;
using std::for_each;

void thread_manager::ThreadCommand::stop() {
  subject_->stop();
}

void thread_manager::ThreadManager::start() {
  for_each(threads_.begin(), threads_.end(), [&] (ThreadCommand& tc) { 
    threads__.push_back(thread([&tc] () { tc.execute(); }));
  });
}

void thread_manager::ThreadManager::stop() {
  for_each(threads_.begin(), threads_.end(), [] (ThreadCommand& tc) { tc.stop(); });
  for_each(threads__.begin(), threads__.end(), [] (thread& t) { t.join(); });
}
