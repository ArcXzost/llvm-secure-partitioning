#include <stdio.h>
__attribute__((section("secure_var"))) int passkey = 0;
int globalCount = 9;

void function5()
{
    printf("Function 5 called\n");
}

void function6()
{
    printf("Function 6 called\n");
}

void function2()
{
    printf("Function 2 called\n");
    function5();
}

void function3()
{
    printf("Function 3 called\n");
    function6();
}

void function4()
{
    printf("Function 4 called\n");
}

void function7()
{
    passkey++;
    printf("Function 7 called\n");
}

void function8()
{
    printf("The Global Function count is : %d\n", globalCount);
    printf("Function 8 called\n");
}

__attribute__((section("secure"))) void function1()
{
    printf("Function 1 called\n");
    function2();
    function3();
    function4();
}

int main()
{
    function1();

    function7();
    function8();

    printf("Main Function Terminates");

    return 0;
}
