#include <iostream>
#include <ctime>

int main()  {
    time_t now = time(NULL);
    tm ptime = *localtime(&now);
    //YYYY-MM-DD
    std::cout << ptime.tm_year + 1900 << '-' << ptime.tm_mon + 1 << '-' << ptime.tm_mday << std::endl;
    return 0;
}