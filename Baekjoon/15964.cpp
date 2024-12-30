#include <iostream>

int SpecialCalculation(int a, int b)
{
    return (a+b)*(a-b);
}

int main()
{
    int a, b;
    std::cin>>a>>b;
    std::cout<< SpecialCalculation(a, b);
    return 0;
}