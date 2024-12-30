#include <iostream>

int main()
{
    int max = 100;
    std::string s;
    for(int i = 0; i < max; i++)
    {
        std::getline(std::cin, s);
        std::cout<<s<<std::endl;
    }
    
}