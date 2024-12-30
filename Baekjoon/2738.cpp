/*

입력
첫째 줄에 행렬의 크기 N 과 M이 주어진다. 둘째 줄부터 N개의 줄에 행렬 A의 원소 M개가 차례대로 주어진다. 이어서 N개의 줄에 행렬 B의 원소 M개가 차례대로 주어진다. N과 M은 100보다 작거나 같고, 행렬의 원소는 절댓값이 100보다 작거나 같은 정수이다.

출력
첫째 줄부터 N개의 줄에 행렬 A와 B를 더한 행렬을 출력한다. 행렬의 각 원소는 공백으로 구분한다.

*/

#include <iostream>

int** Add_Matrix(int** a, int** b, int N, int M);

int main()
{
    int N, M;
    //std::cout<<"N, M 입력: ";
    std::cin>>N>>M;

    int** a = new int*[N];
    for(int i = 0; i < N; i++)
        a[i] = new int[M];
    
    int** b = new int*[N];
    for(int i = 0; i < N; i++)
        b[i] = new int[M];
    
    //std::cout<<"행렬 A 입력: ";
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
            std::cin>>a[i][j];
    }
    
    //std::cout<<"행렬 B 입력: ";
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
            std::cin>>b[i][j];
    }
    
    //std::cout<<"출력\n";

    int** c = Add_Matrix(a, b, N, M);
    //출력
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
            std::cout<<c[i][j]<<" ";
        std::cout<<"\n";
    }

    for(int i = 0; i < N; i++)
    {
        delete[] a[i];
        delete[] b[i];
        delete[] c[i];
    }
    delete[] a;
    delete[] b;
    delete[] c;
    

    return 0;
}

int** Add_Matrix(int** a, int** b, int N, int M)
{
    int** c = new int*[N];
    for(int i = 0; i < N; i++)
    {
        c[i] = new int[M];
        for(int j = 0; j < M; j++)
            c[i][j] = a[i][j] + b[i][j];
    }
    return c;
}
