#include <list>
#include <cassert>
#include <iostream>
#include <chrono>
#include <string>
#include <algorithm>
int main(int argc, char *argv[]) {
   
    //auto start = std::chrono::high_resolution_clock::now();
    std::ios_base::sync_with_stdio(false);

   std::list<int> s1; 
   std::list<int>::iterator it; 
   int n_operations, x, y, max=3000;
   char s;
    
   std::cin >> n_operations;

   while(n_operations!=0){
      std::cin >> s;

      switch(s){
         case 'F':
            std::cin >> x;
            if(s1.size()!=max){
                s1.push_front(x);
            }else std::cout<<"ArrayList Overflow"<<"\n";
            
            break;

         case 'B':
            std::cin >> x;
            if(s1.size()!=max){
                s1.push_back(x);
            }else std::cout<<"ArrayList Overflow"<<"\n";

            break; 

         case 'f':
            if(!s1.empty()){
                it=s1.begin();
                s1.pop_front();
                std::cout<<*it<<"\n";
            } 
            else std::cout<<"EMPTY"<<"\n";

            break;

         case 'b':
            if(!s1.empty()){
               it=s1.end();
               --it;
               std::cout<<*it<<"\n";
               s1.pop_back();
            }else std::cout<<"EMPTY"<<"\n";

            break;

         case 'R':
            std::cin >> x;
            std::cin >> y;
            it = std::find (s1.begin(), s1.end(), x); 
            
            if(it!=s1.end()){
                s1.insert(s1.erase(it),y);
                std::cout << "TRUE" <<"\n";
            } 
            else std::cout << "FALSE" <<"\n";

            break;

         case 'S':
            std::cout<<s1.size()<<"\n";
            break;

         default:
            break;
        }
        n_operations--;
   }
  return 0;
}