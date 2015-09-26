#include <vector>
#include <queue>
#include <memory>
#include <thread>

namespace thread_manager {
  using std::vector;
  using std::queue;
  using std::shared_ptr;
  using std::thread;
  using std::for_each;

  class ThreadSubject;

  class ThreadCommand: public MethodExecuteCommand<ThreadSubject> {
  private:
    void (ThreadSubject:: *KillMethod) ();
    shared_ptr<KillMethod> remove_;
  public:
    ThreadCommand (shared_ptr<ThreadSubject> s, shared_ptr<Action> a, shared_ptr<KillMethod> k)
      : remove_(k) { this->MethodExecuteCommand(s, a); }
  };

  /**
    логика такая: приходят команды запустить воркеров графики логики и прочего.
    запускаем в потоках, храним их вектор
    когда приходит команда синхронизироваться, синхронизируемся.
    но при этом должны еще как то завершаться эти потоки.
    надо придумать как в ThreadSubject реализовать механизм информирования потоков, что им надо завершаться.
    внешне это будет выглядеть как "завершись", и то же самое будет делаться в деструкторе менеджера.
    надо подумать, как потоки будут взаимодействовать.
    нужно прокинуть зависимости между проектами
  */

  class ThreadManager {
  private:
    vector<ThreadCommand> threads;
  public:
    void start() {
      for_each(threads.begin, threads.end, [] (ThreadCommand tc) { tc.execute(); });
    };
    void stop();
  };
}