const int maxsize = 50;
enum bool{false, true};
template <class T>
class Stack{
public:
    Stack();
    virtual void Push(const T& x) = 0;
    virtual bool Pop(T& x) = 0;
    virtual bool getTop(T& x) const = 0;
    virtual bool IsEmpty() const = 0;
    virtual bool IsFull() const = 0;
    virtual int getSize() const = 0;


};


# include <assert.h>
# include <iostream.h>
# include "stack.h"
const int stackIncreament = 20;
template <class T>
class SeqStack: public Stack<T> {
    public:
        SeqStack(int sz = 50);
        ~SeqStack() {delete[]elements;}
        void Push(const T& x);
        bool Pop(T& x);
        bool getTop(T& x);
        bool IsEmpty() const {return (top == -1)? true:false;}
        bool IsFull() const {return (top == maxSize -1)? true:false;}
        int getSize() const {return top+1;}
        void MakeEmpty() {top = -1;}
        friend ostream& operator << (ostream& os, SeqStack<T>& s){
            private:
                T * elements;
                int top;
                int maxSize;
                void overflowProcess();
        
        }



};


