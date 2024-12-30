/*
입력
첫째 줄에 영어 소문자와 대문자로만 이루어진 단어가 주어진다. 단어의 길이는 최대 100이다.

출력
첫째 줄에 입력으로 주어진 단어에서 대문자는 소문자로, 소문자는 대문자로 바꾼 단어를 출력한다.
*/

#include <iostream>
#include <string>

int main()
{
    std::string word;
    std::cin>>word;
    
    for(int i = 0; i < word.length(); i++)
    {
        if(word[i] <= 90)
            word[i] += 32;
        else
            word[i] -= 32;
    }

    std::cout<<word;

    return 0;
}