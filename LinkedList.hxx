#pragma once

#include <iostream>
#include <stdexcept>

template <class T> 
class LinkedList {

   struct Node {
        T x; 
        Node* prev; 
        Node* next;

        ~Node(){
            if(next) delete next;
        }
    };
    Node *guard;
    int N;
public: 
    struct Iterator; // nested iterator class 
    LinkedList(); // default constructor
    LinkedList(const LinkedList<T>& obj); // copy constructor
    LinkedList(LinkedList<T>&& obj); // move constructor
    ~LinkedList(); // destructor
    
    LinkedList& operator=(const LinkedList<T>& obj); // copy opereator=
    LinkedList& operator=(LinkedList<T>&& obj); // move opereator=

    template<class U>
    void push_front(U&& v); 
    T pop_front();

    template<class U>
    void push_back(U&& v);
    T pop_back();

    Iterator find(const T& x){
        Iterator it(begin());
   
        while(it!=end())
        {
            if(*it==x) return it;
            ++it;
        }throw std::invalid_argument("no element found");
        
       
    }

    Iterator erase(Iterator it){
        if(it->prev == nullptr && it->next == nullptr){
            it->x = 0;
            guard->prev = nullptr;
            guard->next = nullptr;  
            --N;
            return Iterator(nullptr);
        }else if(it->next == nullptr && it->prev != nullptr){
            it->prev->next = nullptr;
            guard->next = it->prev;
            --N;
            return Iterator(end());
        }else if(it->prev == nullptr &&  it->next != nullptr){
            it->next->prev = nullptr;
            guard->prev = it->next;
            it->x = 0;
            --N;
            return Iterator(begin());
        }else{
            it->prev->next = it->next;
            it->next->prev = it->prev;
            it->x = 0;
            --N;
            return Iterator(it->next);
        }
 
    }

    template<class U>
    Iterator insert(Iterator it, U&& x){
        if(it == end())
        {
            push_back(x);
            return Iterator(guard->prev);
        }else if(it == begin()){
            push_front(x);
            return Iterator(guard->next);
        }else{
            Node *new_obj = new Node();
            Iterator pre = it->prev;
            Iterator ne = it->prev->next;
            new_obj->x = std::forward<U>(x);
            new_obj->prev = it->prev;
            new_obj->next = it->prev->next;
            ne->prev = new_obj; 
            pre->next = new_obj;
                   
            ++N;
            return Iterator(new_obj);
        }

    } 

    int size();
    bool empty() const;
    int remove(const T& x);
    void view();

    Iterator begin(){
        return Iterator(guard->prev);
    }
    Iterator end(){
        return Iterator(nullptr);
    }
    

};

template <class T>
LinkedList<T>::LinkedList(): guard(new Node()), N(0){
    guard->prev = nullptr;
    guard->next = nullptr;
    guard->x = 0;
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T> &obj) {
    std::cout<<"Jestem konstruktorem kopiujacym"<<std::endl; 
    Node *copy = obj.guard->prev;
    guard = new Node();
    N=obj.N;
    while(copy!=nullptr)
    {
        push_back(copy->x);
        copy=copy->next;
    }
}

template <class T>
LinkedList<T>::LinkedList(LinkedList<T>&& obj): guard(nullptr), N(0){
    std::cout<<"Jestem konstruktorem przenoszacym"<<std::endl;
    std::swap(guard, obj.guard);
    std::swap(N, obj.N);
}

template <class T>
LinkedList<T>::~LinkedList(){
    if(guard) delete guard;
}

template <class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T> &obj){
    std::cout<<"Jestem = kopiujacym"<<std::endl;
    if(this!=&obj){
        Node *copy = obj.guard->prev;
        guard = new Node();
        N=obj.N;
        while(copy!=nullptr)
        {
            push_back(copy->x);
            copy=copy->next;
        }
    }
    return *this;
}

template <class T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T> &&obj){
    std::cout<<"Jestem = przenoszacym"<<std::endl;
   if(this!=&obj){
        delete guard;
        N=0;
        guard = new Node();
        std::swap(guard, obj.guard);
        std::swap(N, obj.N);
    }
    return *this;
}

template <class T>
template<class U>
void LinkedList<T>::push_front(U&& v){
    Node *new_obj = new Node();

    if(guard->prev==nullptr){
        new_obj->x = std::forward<U>(v);
        guard->prev = new_obj;
        new_obj->next = nullptr;
        new_obj->prev = nullptr;
    }else{
        new_obj->x = std::forward<U>(v);
        new_obj->prev = nullptr;
        new_obj->next = guard->prev;
        guard->prev->prev = new_obj;
        guard->prev = new_obj;
    }  
    ++N;
    if(guard->next==nullptr)guard->next=new_obj;
}


template <class T>
template<class U>
void LinkedList<T>::push_back(U&& v){
    Node *new_obj = new Node();

    if(guard->next==nullptr){
        new_obj->x = std::forward<U>(v);
        guard->next = new_obj;
        new_obj->next = nullptr;
        new_obj->prev = nullptr;
    }else{
        new_obj->x = std::forward<U>(v);
        new_obj->next = nullptr;
        new_obj->prev= guard->next;
        guard->next->next = new_obj;
        guard->next = new_obj;
    }  
    ++N;
    if(guard->prev==nullptr)guard->prev=new_obj;

}

template <class T>
T LinkedList<T>::pop_front(){
    if(empty()) 
        throw std::out_of_range("LinkedList Underflow"); 

    T temp = guard->prev->x;
    if(N==1){
        guard->prev->x = 0;
        guard->prev = nullptr;
        guard->next = nullptr;
    }else{
        guard->prev->next->prev = nullptr;
        guard->prev = guard->prev->next; 
    }

    --N;
    return std::move(temp);
}

template <class T>
T LinkedList<T>::pop_back (){
    if(empty()) 
        throw std::out_of_range("LinkedList Underflow");
    T temp = guard->next->x;
    if(N==1){
        guard->next->x = 0;
        guard->prev = nullptr;
        guard->next = nullptr;
    }else{
        guard->next->prev->next = nullptr;
        guard->next = guard->next->prev;
    }
    --N;
    return std::move(temp);
}

template <class T>
int LinkedList<T>::remove(const T& x){
    
    Iterator it(begin());
    int count = 0;

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

template <class T>
int LinkedList<T>::size(){return N;}

template <class T>
bool LinkedList<T>::empty() const{
    return N==0;
}


template <class T>
void LinkedList<T>::view(){
    Node *pls = new Node();
    Iterator e(pls);
    int i=0;
    while(pls!=nullptr)
    {
        std::cout<<i<<") "<< pls->x <<"\n";
        pls=pls->next;
        ++i;
    }

}


template <class T> 
struct LinkedList<T>::Iterator{
    Node *pointer;
public:
    Iterator(Node* x) : pointer(x) {}
    Iterator(const Iterator& it) : pointer(it.pointer) {}
    Iterator(Iterator&& it) : pointer(it.pointer) {delete it.pointer;}
    Iterator& operator++() {pointer=pointer->next; return *this;}
    Iterator& operator--() {pointer=pointer->prev; return *this;}
    Node* operator->() { return pointer;}
    bool operator==(const Iterator& it) const {return pointer==it.pointer;}
    bool operator!=(const Iterator& it) const {return pointer!=it.pointer;}
    Iterator& operator=(Node* x){
        this->pointer = x; 
        return *this; 
    } 
    Iterator& operator=(const Iterator& it){
        pointer = it.pointer; 
        return *this; 
    } 
    Iterator& operator=(Iterator&& it){
        Node *temp = pointer;
        pointer = it.pointer;
        it.pointer = temp;
        return *this; 
    } 
    T& operator*() {return pointer->x;}

};