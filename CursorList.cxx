#include "CursorList.hxx"
#include <cassert>
#include <iostream>
#include <vector>
#include <iterator>
#include <chrono>
#include <string>
#include <sstream>
int main(int argc, char *argv[]) {
   
    //auto start = std::chrono::high_resolution_clock::now();
    std::ios_base::sync_with_stdio(false);

    CursorList<int,3000>s1;

   int n_operations, x, y;
   char s;
    
   std::cin >> n_operations;

   while(n_operations!=0){
      std::cin >> s;

      switch(s){
         case 'F':
            std::cin >> x;
            if(!s1.full()){
                s1.push_front(x);
            }else std::cout<<"ArrayList Overflow"<<"\n";
            break;
         case 'B':
            std::cin >> x;
            if(!s1.full()){
                s1.push_back(x);
            }else std::cout<<"ArrayList Overflow"<<"\n";
            break; 
         case 'f':
            if(!s1.empty()) std::cout<<s1.pop_front()<<"\n";
            else std::cout<<"EMPTY"<<"\n";
            break;
         case 'b':
            if(!s1.empty()) std::cout<<s1.pop_back()<<"\n";
            else std::cout<<"EMPTY"<<"\n";
            break;
         case 'R':
            std::cin >> x;
            std::cin >> y;
               try {
                  s1.insert(s1.erase(s1.find(x)),y);
                  std::cout << "TRUE"<<"\n";
               }catch (const std::invalid_argument& ia) {
                  std::cout << "FALSE"<<"\n";
               }

            break;

         case 'S':
            std::cout<<s1.size()<<"\n";
            break;

         default:
            break;
        }
      //   std::cout<<"\n \t ";
      //   for(auto &a : s1)
      //       std::cout<<a<<" ";

      //    std::cout<<'\n';
        
        n_operations--;
   }
  return 0;
}