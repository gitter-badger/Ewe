#include <memory>

namespace patterns {

using std::shared_ptr;

template<typename... Args>
class Command {
protected:
  virtual ~Command() = 0;
public:
  //If you will know args count : const unsigned numargs = sizeof...(Args);
  virtual void execute(Args...) = 0;
};

template<class Subject, typename... Args>
class MethodExecuteCommand : public Command <Args...> {
protected:
  typedef void (Subject:: *Action) (Args...);

  shared_ptr<Subject> subject_;
  Action action_;
public:
  MethodExecuteCommand(shared_ptr<Subject> s, Action a)
    : subject_(s) { action_ = a; };

  void exectute(Args... aa) {
    this->subject_ ->* this->action_(aa...);
  };
};

}
