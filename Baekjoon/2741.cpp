/*
입력
첫째 줄에 100,000보다 작거나 같은 자연수 N이 주어진다.

출력
첫째 줄부터 N번째 줄 까지 차례대로 출력한다.
*/

#include <iostream>

int main()
{
    int a;
    std::cin>>a;
    for(int i = 1; i <= a; i++)
        std::cout<<i<<"\n";
    return 0;
}