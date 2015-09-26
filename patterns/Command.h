#include <memory>

namespace patterns {
  using std::shared_ptr;

  template<typename... Args>
  class Command {
  protected:
    virtual Command ( ) = 0;
    virtual ~Command ( ) = 0;
  public:
    //If you will know args count : const unsigned numargs = sizeof...(Args);
    virtual void execute (const Args& ...) = 0;
  };

  template<class Subject, typename... Args>
  class MethodExecuteCommand : public Command<typename... Args> {
  private:
    void (Subject:: *Action) (Args...);

    shared_ptr<Subject> subject_;
    shared_ptr<Action> action_;
  public:
    MethodExecuteCommand (shared_ptr<Subject> s, shared_ptr<Action> a) 
      : subject_(s), action_(a) {};
    ~MethodExecuteCommand ( ) {
      delete subject_;
      delete action_;
    };
    void exectute (const Args& aa...) {
      this->subject_ ->* this->action_ (aa...);
    };
  };

}