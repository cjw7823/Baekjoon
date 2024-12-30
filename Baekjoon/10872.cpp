/*
입력
첫째 줄에 정수 N(0 ≤ N ≤ 12)이 주어진다.

출력
첫째 줄에 N!을 출력한다.
*/

#include <iostream>

int get_factorial(int a);

int main()
{
    int a;
    std::cin>>a;
    std::cout<< get_factorial(a);
    return 0;
}

int get_factorial(int a)
{
    if(a == 0)
        return 1;
    else
        return a * get_factorial(a-1);
}