#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
static constexpr int NIL = (-1); // adress "empty"
template <class T, int N> 
class CursorList {
  
    struct Node { // nested node class 
        T x;
        int next;
   
    };
    Node arr[N];
    int head;
    int tail;
    int size_;
    int spare;
  public: 
    struct Iterator; // nested iterator class 
    CursorList(); 
    CursorList(const CursorList<T,N>& obj); // copy constructor
    CursorList(CursorList<T,N>&& obj); // move constructor
    ~CursorList(); //destructor
        
    CursorList& operator=(const CursorList<T,N>& obj); //copy opereator=
    CursorList& operator=(CursorList<T,N>&& obj); //move opereator=

    template<class U>
    void push_front(U&& v);
    T pop_front();

    template<class U>
    void push_back(U&& x);

    T pop_back(); 

    int free_place(){
            int temp;
            temp = spare;
            spare = arr[spare].next;
            return temp;
   
    }
    
    void de_free_place(int id){
        arr[id].next = free_place();
        spare = id;
    }
    
    Iterator find(const T& x){
        Iterator it = begin();
        Iterator it2 = end();
        if(!empty()){
            while(it != it2){
                if(*it == x)return it;
                ++it;
            }throw std::invalid_argument("no element found");
        }else throw std::invalid_argument("no element found");
     
    }

    Iterator erase(Iterator it){
    if(empty()) 
        throw std::out_of_range( "CursorList Underflow");

        Iterator it2 = it;
        if(it == begin()){
            pop_front();
            it = begin();
            return it;
        }else if(++it2 == end()){
            pop_back();
            it = end();    
            return it;
        }else{ 

            Iterator it2 = begin();
            int id;
            while(it2 != it)
            {
                id = it2.index;
                ++it2;
            }
            it2; 
     
            arr[id].next = arr[it2.index].next;

            de_free_place(it.index);
            
            --size_; 
            return Iterator(arr, arr[id].next);
        }

       
    }


    template<class U>
    Iterator insert(Iterator it, U&& x){
        if(full()) 
            throw std::out_of_range( "CursorList Overflow");
     

        if(it == begin()){
            push_front(x);
            it = begin();
            return it;
        }else if(it == end())
        {
            push_back(x);
            return it;
        }else{  
            int free;
            free = free_place();
            Iterator it2 = begin();
            int id;
            while(it2 != it)
            {
                id = it2.index;
                ++it2;
            } 
            arr[free].x = std::forward<U>(x);
            arr[free].next = arr[id].next;
            arr[id].next = free;
            ++size_;
            return Iterator(arr, arr[id].next );
        }
        

    }


    int size() const; 
    bool empty() const;
    bool full() const; 
    
    int remove(const T& x);
    template<class U> 
    void view(U&& elem);

    Iterator begin(){
        return Iterator(arr, head);
    }
    Iterator end(){
        return Iterator(arr, arr[tail].next);
    }

};

template <class T, int N> 
CursorList<T, N>:: CursorList():  head(NIL), tail(NIL), size_(0), spare(0) {
    for(int i = 0; i < (N-1); i++)
    {    
        arr[i].next = (i+1); 
    }
    arr[(N-1)].next = NIL;
}

template <class T, int N> 
CursorList<T, N>:: CursorList(const CursorList<T,N>& obj): head(obj.head), tail(obj.tail), size_(obj.size_), spare(obj.spare){
    for(int i = 0; i < N; i++)
    {   
        arr[i].x = obj.arr[i].x;
        arr[i].next = obj.arr[i].next; 
    }
}

template <class T, int N> 
CursorList<T, N>::CursorList(CursorList<T,N>&& obj): arr(std::move(obj.arr)), head(std::move(obj.head)), tail(std::move(obj.tail)), size_(std::move(obj.size_)), spare(std::move(obj.spare)){  
    obj.head = NIL;
    obj.arr[obj.spare].next = NIL;
    obj.tail = NIL;
    obj.size_ = 0;
    obj.spare = 0;

}


template <class T, int N> 
CursorList<T, N>:: ~CursorList(){}

template <class T, int N> 
CursorList<T, N>& CursorList<T, N>::operator=(const CursorList<T,N> &obj){
      if(this!=&obj){
        head=obj.head;
        tail=obj.tail;
        spare=obj.spare;
        size_=obj.size_;
        int id = obj.head;
        while(id!=tail){
            arr[id].x=obj.arr[id].x;
            arr[id].next=obj.arr[id].next;
            id=arr[id].next;
        }
        arr[id].x=obj.arr[id].x;
        arr[id].next=NIL;
    }
    return *this;

}

 template <class T, int N> CursorList<T, N>& CursorList<T, N>::operator= (CursorList<T,N> &&obj){
   
        if(this!=&obj){
        
        head=obj.head;
        tail=obj.tail;
        spare-obj.spare;
        size_=obj.size_;
        int id = obj.head;
        while(id!=tail){
            arr[id].x=obj.arr[id].x;
            arr[id].next=obj.arr[id].next;
            id=arr[id].next;
        }
        arr[id].x=obj.arr[id].x;
        arr[id].next=NIL;

        while(id!=tail){
            obj.arr[id].x=0;
            id=obj.arr[id].next;
            obj.arr[id].next=NIL;
            
        }
        obj.arr[id].x=0;
        obj.arr[id].next=NIL;
        obj.head = NIL;
        obj.arr[obj.spare].next = NIL;
        obj.tail = NIL;
        obj.size_ = 0;
        obj.spare = 0;
    }
    return *this;


}

template <class T, int N>
template<class U>
void CursorList<T, N>::push_front(U&& v){
   if(full()) 
       throw std::out_of_range( "CursorList Overflow");

    int free;
    free = free_place();
    if(empty()){
        head = free;
        tail = free;
        arr[free].x = std::forward<U>(v);
    }else{
        arr[free].x = std::forward<U>(v);
        arr[tail].next = spare;
        arr[free].next = head;
        head = free; 
    }
    ++size_;
}
template <class T, int N>
template<class U>
void CursorList<T,N>::push_back(U&& x){
    if(full()) 
        throw std::out_of_range( "CursorList Overflow");
    int free;
    free = free_place();
    if(empty()){
        head = free;
        tail = free;
        arr[free].x = std::forward<U>(x);  
    }else{
        arr[free].x = std::forward<U>(x);  
        arr[tail].next = free;
        tail = free;
        arr[tail].next = spare;
    }
    ++size_;
}

template <class T, int N>
T CursorList<T, N>::pop_front(){
    if(empty()) 
        throw std::out_of_range( "CursorList Underflow");
        T temp;
        int id = head;
        temp = arr[head].x;
        head = arr[head].next;
    
        de_free_place(id);
        
        --size_;
        return std::move(temp);
}

template <class T, int N>
T CursorList<T, N>::pop_back(){
    if(empty()) 
        throw std::out_of_range( "CursorList Underflow");
        int id;
        T temp;
        temp = arr[tail].x;
       
        
        Iterator it2 = begin();
        if(size_!=(1)){ 
        Iterator it(arr, tail);
            while(it2!=it)
                {
                    id = it2.index;
                    ++it2;
                }
            de_free_place(tail);
            tail = id;
        }else{
            id = tail;
            de_free_place(id);
            tail = NIL;
        }
     
        --size_;
        return std::move(temp);
}

template <class T, int N>
int CursorList<T, N>::remove(const T& x){
        Iterator it(begin());
        int count=0;

        while(it != end()){
            if(*it == x){
                erase(it);
                it = begin();
                ++count; 
                continue;
            }
            ++it;
        }
    return count;
}

template <class T, int N>
int CursorList<T,N>::size() const{return size_;}

template <class T, int N>
bool CursorList<T, N>::empty() const{
    return size_==0;
}

template <class T, int N>
bool CursorList<T, N>::full() const{
    return size_==N;
}


template <class T, int N>
template<class U>
void CursorList<T, N>::view(U&& elem){
    if(elem>=0 && elem<size_) std::cout<<elem<<") "<<arr[elem].x<<" next)"<<arr[elem].next <<"\n";
}

template <class T, int N> 
struct CursorList<T, N>:: Iterator {
      
    Node* pointer;   
    int index;  
public:
    Iterator(Node* x, int id) : pointer(x), index(id) {}
    Iterator(const Iterator& it) : pointer(it.pointer), index(it.index) {}
    Iterator(Iterator&& it) : pointer(it.pointer), index(it.index) {it.pointer = nullptr;}
    ~Iterator(){pointer=nullptr; index=NIL;}
    Iterator() = delete;               
    Iterator& operator++() {index=pointer[index].next; return *this;}
    T& operator*()const {return pointer[index].x;}
    bool operator==(const Iterator& it) const{return (index == it.index);}
    bool operator!=(const Iterator& it) const{ return !(*this == it);}
    Iterator& operator=(const Iterator& it) = default;
    Iterator& operator=(Iterator&& it) {
        index=it.index; 
        pointer=it.pointer; 
        it.pointer=nullptr; 
        it.index=NIL; 
        return *this;}      
    };
