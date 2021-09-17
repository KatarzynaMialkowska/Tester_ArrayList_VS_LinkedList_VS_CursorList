#pragma once

#include <iostream>
#include <stdexcept>

template <class T, int N> 
class ArrayList {
    T *S; // dinamic array
    int id; // array size 
   
public: 
    struct Iterator; // nested iterator class 
    ArrayList(); // default constructor
    ArrayList(const ArrayList<T,N>& obj); // copy constructor
    ArrayList(ArrayList<T,N>&& obj); // move constructor
    ~ArrayList(); // destructor
    
    ArrayList& operator=(const ArrayList<T,N>& obj); //copy opereator=
    ArrayList& operator=(ArrayList<T,N>&& obj); //move opereator=

    template<class U>
    void push_front(U&& x);
    T pop_front();

    template<class U>
    void push_back(U&& x);
    T pop_back(); 
    Iterator find(const T& x){
            T *t = nullptr;
            for(int i=0;i<id;i++){
                if(x==S[i]){
                    t=&S[i];
                    return Iterator(t);
                }
            }throw std::invalid_argument("no element found");
        
    }

    Iterator erase(Iterator x){
       for (int i = x-begin(); i<id; ++i) {
            S[i]=S[i+1];
        } 
        --id;
        x;
        return x;
    }

    template<class U>
    Iterator insert(Iterator it, U&& x){
        if(full()) 
        throw std::out_of_range("ArrayList Overflow");
        int tmp=it-begin(); 
        for (int i = id; i>=tmp; i--) {
            S[i]=S[i-1];
        } 
        S[tmp]=x;
        id++;
        return it;
    }

    int size() const;
    bool empty() const;
    bool full() const; 
    
    int remove(const T& x);
    template<class U>
    void view(U&& elem);

    Iterator begin(){
        return Iterator(S);
    }
    Iterator end(){
        T *t = &S[id]; 
        return Iterator (t);
    } 

};

template <class T, int N>
ArrayList<T, N>::ArrayList(): S(new T[N]), id(0){}

template <class T, int N>
ArrayList<T, N>::ArrayList(const ArrayList<T,N>& obj) : S(new T[N]), id(obj.id){
    for(int i=0;i<id;i++)S[i]=obj.S[i];
}

template <class T, int N>
ArrayList<T, N>::ArrayList(ArrayList<T,N>&& obj) :  S(obj.S), id(obj.id){
    obj.id = 0;
    obj.S = nullptr;
}


template <class T, int N>
ArrayList<T, N>::~ArrayList(){
    if (S != nullptr)
        delete [] S;
}

template <class T, int N>
ArrayList<T, N>& ArrayList<T, N>::operator=(const ArrayList<T,N> &obj){
    if(this!=&obj){
        delete [] S;
        id=obj.id;
        S = new T[N];
        for(int i = 0; i < id; i++) S[i] = obj.S[i];
    }
    return *this;

}

template <class T, int N>
ArrayList<T, N>& ArrayList<T, N>::operator=(ArrayList<T,N> &&obj){
    if(this!=&obj){
        delete [] S;
        id=obj.id;
        S = obj.S;
        obj.id = 0;
        obj.S=nullptr;
    }
    return *this;

}

template <class T, int N>
template<class U>
void ArrayList<T, N>::push_front(U&& x){
    
    if(full()) 
        throw std::out_of_range("ArrayList Overflow");

    if(empty()){
        S[0]=std::forward<U>(x);
        id++; 
    }else{
        for(int i=id;i>0;i--){
            S[i]=S[(i-1)];
        }
        S[0]=std::forward<U>(x);
        id++;
    }
}

template <class T, int N>
template<class U>
void ArrayList<T, N>::push_back(U&& x){
    
    if(full()) 
        throw std::out_of_range("ArrayList Overflow");

    S[id]=std::forward<U>(x);
    id++;
}

template <class T, int N>
T ArrayList<T, N>::pop_front(){
    if(empty()) 
        throw std::out_of_range("ArrayList Underflow");
    T x = S[0];
    for(int i=0;i<id;i++){
        S[i]=S[(i+1)];
    }
    id--;
    return std::move(x);
}

template <class T, int N>
T ArrayList<T, N>::pop_back (){
    if(empty()) 
        throw std::out_of_range("ArrayList Underflow");
    T x = S[(id-1)];
    id--;
    return std::move(x);
}

template <class T, int N>
int ArrayList<T, N>::remove(const T& x){
    int count=0;
    for(int i=0;i<id;i++){
        if(S[i]==x){
            for(int j=i;j<id;j++){
                S[j]=S[j+1];
            }
            ++count;
            --id;
        }
        
    }
    return count;
}

template <class T, int N>
int ArrayList<T,N>::size() const{return id;}

template <class T, int N>
bool ArrayList<T, N>::empty() const{
    return id==0;
}

template <class T, int N>
bool ArrayList<T, N>::full() const{
    return id>=N;
}


template <class T, int N>
template<class U>
void ArrayList<T, N>::view(U&& elem){
    if(elem>=0 && elem<id) std::cout<<S[elem]<<"\n";
}


template <class T, int N> 
struct ArrayList<T, N>::Iterator{
    T *pointer;
public:
  Iterator(T* x) : pointer(x) {}
  Iterator(const Iterator& it) : pointer(it.pointer) {}
  Iterator(Iterator&& it) : pointer(it.pointer) {it.pointer = nullptr;}
  Iterator& operator++() {++pointer; return *this;}
  Iterator operator++(T) {Iterator tmp(*this); operator++(); return tmp;}
  Iterator& operator--() {--pointer; return *this;}
  Iterator operator--(T) {Iterator tmp(*this); operator--(); return tmp;}
  int operator-(const Iterator& it) {return pointer-it.pointer;}
  Iterator operator-(int x) {return pointer-x;}
  Iterator operator+(int x) {return pointer+x;}
  bool operator==(const Iterator& it) const {return pointer==it.pointer;}
  bool operator!=(const Iterator& it) const {return pointer!=it.pointer;}
  T& operator*() {return *pointer;}
};