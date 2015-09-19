namespace patterns {

  template<typename Arg0, typename... Args>
  class Command {
  public:
    //If you will know args count : const unsigned numargs = sizeof...(Args);
    virtual void execute (const Arg0&, const Args& ...) = 0;
  };

}