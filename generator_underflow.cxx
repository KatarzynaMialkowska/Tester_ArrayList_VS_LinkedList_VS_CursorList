#include <iostream>
#include <ctime>
#include <random>
#include <iomanip>

int main(int argc, char *argv[])
{
    std::uniform_int_distribution<int> dist1 ( 0,1000 ); //klasa szablonowa
    //std::uniform_int_distribution<int> dist2 ( 0,2 ); //klasa szablonowa 0-A, 1-D, 2-S
    std::mt19937 gen ( time ( NULL ) ); //generator pseudolosowy Mersenne Twister 32bit
    int n_operations;
    if(argc == 2) n_operations=atoi(argv[2]);
    else n_operations=dist1 ( gen ); //liczba operacji
    int n_comm=1;
    
    std::cout<<n_operations<<"\n";
    for( int i = 0; i < n_operations; i++ )
    {
        if(n_comm==1) std::cout<<"f "<<"\n"; //argument
    }
 
    return 0;
} 