// RUN: %check_clang_tidy %s nextdroid-virtual-shadowing %t
// REQUIRES: shell

struct A {
  void f() {}
};

struct B : public A {
  // CHECK-MESSAGES: :[[@LINE+1]]:3: warning: method hides non-virtual method from a base class [nextdroid-virtual-shadowing]
  virtual void f() {}  // problematic
};

struct C {
  virtual void f() {}  // OK(1)
};

struct D : public C {
  virtual void f() {}  // OK(2)
};
