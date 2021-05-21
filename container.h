#include <iostream>
template <typename T>
class Container{
public:
    Container()
        : m_size(0)
        , m_first(nullptr)
        , m_last(nullptr)
    {}


    void PushBack(T& elem){
        Node* newnode = new Node(elem);
        if (m_last != nullptr)
        {m_last->next = newnode; }
        else
        {m_first=newnode; }
        newnode->previous = m_last;
        m_last = newnode;
        ++m_size;
    }

    void PushForward(T elem) {
        Node* newnode = new Node(T);
        if(m_first!=nullptr)
        {m_first->previous = newnode;}
        else
        {m_last = newnode; }
        newnode->next = m_first;
        m_first = newnode;
        ++m_size;
    }
    T const GetFirst() { return m_first->elem; }
    T const GetLast() { return m_last->elem; };
    void DeleteFirst() {
        Node* second = m_first->next;
        delete m_first;
        m_first = second;
        m_first->previous = nullptr;
        --m_size;
    }
    void DeleteLast() {
        Node* prev = m_last->previous;
        delete m_last;
        m_last = prev;
        m_last->next = nullptr;
        --m_size;
    }
    
    size_t const GetLength() { return m_size; }
    
    bool IsEmpty() { if (m_size == 0) return true; else return false; }
    
    void Reverse() {
        Node* curr = m_first;
        while (curr != nullptr) {
            Node* tmp = curr->next;
            curr->next = curr->previous; 
            curr->previous = tmp;
            curr = tmp;
        }
        Node* tmp = m_first;
        m_first = m_last;
        m_first->previous = nullptr;
        m_last = tmp;
        m_last->next = nullptr;

    }

    void Swap(Container& otherContainer) {
        Node* tmp_first = otherContainer.m_first;
        Node* tmp_last = otherContainer.m_last;
        otherContainer.m_first = m_first;
        otherContainer.m_last = m_last;
        m_first=tmp_first;
        m_last = tmp_last;
    }

    void Clear() {
        while(!IsEmpty())
        {DeleteLast();}
    }

    ~Container() {}
    
    struct Node {
    public:
        Node(T data)
            :elem(data)
            , next(nullptr)
            , previous(nullptr)
        {}
        T elem;
        Node* next;
        Node* previous;

    };

    class Iterator
    {
    public:
        Iterator(Node* el)
            :pointer(el)
        {}
        bool operator!=(const Iterator& left) {
            return (left.pointer != pointer);
        }
        Iterator operator++() {
            pointer=pointer->next;
            return pointer;
        }
        Iterator operator--() {
            pointer = pointer->previous;
            return pointer;
        }
        ~Iterator() {};
        T operator*() { return pointer->elem; }
        T* operator->() { return &(pointer->elem); }

    private:
        Node* pointer;  
    };

    Iterator begin() {
        return Iterator(m_first);
    }

    Iterator end() {
        return Iterator(nullptr);
    }
private:
           
    Node* m_first, * m_last;
    size_t m_size;

};

