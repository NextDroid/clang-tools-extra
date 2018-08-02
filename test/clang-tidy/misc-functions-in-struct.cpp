// RUN: %check_clang_tidy %s misc-functions-in-struct %t

struct A
{
    void f() {};
    // CHECK-MESSAGES: :[[@LINE-1]]:10: warning: structs should not provide member functions or methods [misc-functions-in-struct]
};

void awesome_f2();

class B
{
    void f() {};
};
