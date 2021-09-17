#include <iostream>
#include <ctime>
#include <random>
#include <iomanip>
#include <sstream>

int main(int argc, char *argv[])
{
    std::uniform_int_distribution<int> dist1 ( 0,1000 ); 
    std::uniform_int_distribution<int> dist2 ( 0,5 );
    std::mt19937 gen ( time ( NULL ) );
    int n_operations;
    if(argc==2){   
       std::istringstream iss( argv[1] );
       if (iss >> n_operations){}
    }else n_operations=dist1 ( gen ); 
    int n_comm;
    
    std::cout<<n_operations<<"\n";
    for( int i = 0; i < n_operations; i++ )
    {
        n_comm = dist2 ( gen );
        if(n_comm==0) std::cout<<"F "<<dist1(gen) << "\n"; // push_front
        if(n_comm==1) std::cout<<"B "<<dist1(gen) << "\n"; // push_back
        if(n_comm==2) std::cout<<"f "<< "\n"; // pop_front
        if(n_comm==3) std::cout<<"b "<< "\n"; // pop_back
        if(n_comm==4) std::cout<<"R "<<dist1(gen)<<" "<<dist1(gen)<<"\n"; // find and erase
        if(n_comm==5) std::cout<<"S " << "\n"; // size
    
    }
 
    return 0;
} 