// RUN: %check_clang_tidy %s misc-struct-inheritance %t

struct A // OK(1)
{
    void f();
};

struct B: public A
// CHECK-MESSAGES: :[[@LINE-1]]:8: warning: structs should not inherit from structs or classes [misc-struct-inheritance]
{
    int a;
};

class C // OK(2)
{
    int a;
};

struct D: C
// CHECK-MESSAGES: :[[@LINE-1]]:8: warning: structs should not inherit from structs or classes [misc-struct-inheritance]
{
    int d;
};

