// RUN: %check_clang_tidy %s misc-class-member-data-access-check %t

class A //ok-POD
{
    int a; //ok, pod
    int a1; //ok, pod
};


class B //non-POD
{
    public:
        int b0; // problematic
// CHECK-MESSAGES: :[[@LINE-1]]:13: warning: non-POD class member data should be private [misc-class-member-data-access-check]
        B() {}
        int test_meth_b()
        {
            int b2 = 1;
            return b2;
        }
    private:
        int b1; //okay
};

struct C
{
    private:
        int c; //okay, since struct
};

