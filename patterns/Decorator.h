namespace patterns {

  template<class T>
  class Decorator : public T { 
  private:
    T* base_;
  public:
    Decorator (T* t) : base_ (t);
  };

}