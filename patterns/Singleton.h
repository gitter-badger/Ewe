#ifndef SINGLETON_H_
#define SINGLETON_H_

namespace patterns {

  class Singleton;

  class SingletonDestroyer {
  private:
    Singleton* p_instance;
  public:
    ~SingletonDestroyer ();
    void initialize (Singleton* p);
  };

  class Singleton {
  private:
    static Singleton* p_instance;
    static SingletonDestroyer destroyer;
  protected:
    Singleton () { }
    Singleton (const Singleton&);
    Singleton& operator=(Singleton&);
    ~Singleton () { }
    friend class SingletonDestroyer;
  public:
    static Singleton& getInstance ();
  };

}

#endif // SINGLETON_H_
