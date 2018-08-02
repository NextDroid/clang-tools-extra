// RUN: %check_clang_tidy %s misc-public-struct-members %t

struct A
{
    private:
        // CHECK-MESSAGES: :[[@LINE+1]]:13: warning: struct contains non-public data member [misc-public-struct-members]
        int a;  
    protected:
        // CHECK-MESSAGES: :[[@LINE+1]]:13: warning: struct contains non-public data member [misc-public-struct-members]
        int b;

};


struct B
{
    int c; // OK(1)
    public:
        int d; // OK(2)
};
