#include "ThreadManager.h"

void thread_manager::ThreadManager::start() {
  for_each(threads.begin(), threads.end(), [] (ThreadCommand& tc) { tc.execute(); });
}

void thread_manager::ThreadManager::stop() {
  for_each(threads.begin(), threads.end(), [] (ThreadCommand& tc) { tc.stop(); });
}

void thread_manager::ThreadCommand::stop() {
  subject_->stop();
}
