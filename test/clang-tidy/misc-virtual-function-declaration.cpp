// RUN: %check_clang_tidy %s misc-virtual-function-declaration %t


struct A {
  virtual void f() {}
  virtual void g() {}
  virtual void h() {}
  virtual void i() {}
  virtual void j() {}
  virtual void k() {}
  virtual void l() {}
  virtual void m() {}
};

struct B : public A {
  void f() {}  // problematic
// CHECK-MESSAGES: :[[@LINE-1]]:8: warning: virtual functions should be declared with exactly one of "virtual", "override", or "final" [misc-virtual-function-declaration]

  void g() final {} //okay
  void h() override {} //okay
  virtual void i() {} //okay
  
  virtual void j() final {} //problematic
// CHECK-MESSAGES: :[[@LINE-1]]:16: warning: virtual functions should be declared with exactly one of "virtual", "override", or "final" [misc-virtual-function-declaration]
  virtual void l() override {} //problematic
// CHECK-MESSAGES: :[[@LINE-1]]:16: warning: virtual functions should be declared with exactly one of "virtual", "override", or "final" [misc-virtual-function-declaration]
  void k() override final {} //problematic
// CHECK-MESSAGES: :[[@LINE-1]]:8: warning: virtual functions should be declared with exactly one of "virtual", "override", or "final" [misc-virtual-function-declaration]
  virtual void m() override final {} //problematic
// CHECK-MESSAGES: :[[@LINE-1]]:16: warning: virtual functions should be declared with exactly one of "virtual", "override", or "final" [misc-virtual-function-declaration]
};

