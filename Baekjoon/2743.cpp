/*
입력
첫째 줄에 영어 소문자와 대문자로만 이루어진 단어가 주어진다. 단어의 길이는 최대 100이다.

출력
첫째 줄에 입력으로 주어진 단어의 길이를 출력한다.
*/

#include <iostream>
#include <string>

int main()
{
    std::string word;
    std::cin>>word;
    std::cout<<word.length();
    return 0;
}