#include <iostream>
#include <ctime>
#include <random>
#include <iomanip>
#include <sstream>

int main(int argc, char *argv[])
{
    std::uniform_int_distribution<int> dist1 ( 0,1000 ); 
   // std::uniform_int_distribution<int> dist2 ( 0,2 );
    std::mt19937 gen ( time ( NULL ) ); 
    int n_operations;
    if(argc==2){   
       std::istringstream iss( argv[1] );
       if (iss >> n_operations){}
    }else n_operations=dist1 ( gen );
    int n_comm=0;
    
    std::cout<<n_operations<<"\n";
    for( int i = 0; i < n_operations; i++ )
    {
        if(n_comm==0) std::cout<<"F "<< dist1(gen) << "\n";
    }
 
    return 0;
} 