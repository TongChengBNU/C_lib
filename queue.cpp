#include <assert.h>
#include <iostream.h>
#include "Queue.h"

const int maxSize = 50;
enum bool{false, true};
template <class T>

class Queue{
    public:
        Queue(){};
        ~Queue(){};
        virtual void InQueue(const T& x) = 0;
        virtual bool DeQueue(T& x) = 0;
        virtual bool getFront(T& x) = 0;
        virtual bool IsEmpty()const = 0;
        virtual bool IsFull()const = 0;
        virtual int getSize()const = 0;
};

class SeqQueue: public Queue<T> {
    public:
        SeqQueue(int sz = 10);
        ~SeqQueue() {delete[] elements;}
        /* If queue is full, do overflow process; */
        bool InQueue(const T& x);
        /* If queue is None, do underflow process; */
        bool DeQueue(T& x);
        bool getFront(T& x);

        void makeEmpty() {front = rear = 0;}
        bool IsEmpty()const {return (front == rear) ? true : false;}
        bool IsFull()const
        {return ( (rear+1) % maxSize == front ) ? true : false;}
        
        int getSize()const {return (rear-)}
        

    protected:

};


