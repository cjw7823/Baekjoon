#include <iostream>

int main()
{
    std::string s;
    int i;
    std::cin>>s;
    std::cin>>i;
    std::cout<<s.at(i-1);
    return 0;
}