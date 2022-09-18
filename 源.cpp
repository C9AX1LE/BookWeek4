#include<iostream>
using namespace std;
template <class T>
class queue
{
public:
    virtual ~queue() {};
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual T& front() = 0;
    virtual void pop() = 0;
    virtual void push(const T& theElement) = 0;
};
template<class T>
class arrayQueue :public queue<T>
{
    arrayQueue(int initialCapacity = 10);
    ~arrayQueue() { delete[]queue; }
    bool empty()const
    {
        if (queuefront == queuerear)
            return true;
        return false;
    }
    int size() const
    {
        return (queuerear - queuefront + capacity) % capacity;
    }
    T& front()
    {
        if (queuefront == queuerear)
        {
            cout << "The queue is empty!" << endl;
            return false;
        }
        return queue[queuefront];
    }
    void pop()
    {
        if (queuefront == queuerear)
            cout << "The queue is empty!" << endl;
        queue[queuefront].~T;
        queuefront = (queuefront + 1) % capacity;
    }
    void push(const T& theElement);
private:
    int capacity;
    int queuefront;
    int queuerear;
    T* queue;
};

template<class T>
arrayQueue<T>::arrayQueue(int initialCapacity)
{
    if (initialCapacity < 1)
        cout << "InitialCapacity must >0!" << endl;
    capacity = initialCapacity;
    queue = new T[capacity];
    queuefront = 0;
    queuerear = 0;
}

template<class T>
void arrayQueue<T>::push(const T& theElement)
{
    if ((queuerear + 1) % capacity == queuefront)
    {
        T* temp = new T[2 * capacity];
       if (queuefront == 0)
            copy(queuefront, queuerear, temp);
        else
        {
            copy(queuefront, queue + capacity, temp);
            copy(queue, queuerear, temp + queue + capacity - queuefront);
        }
        queuefront = 0;
        queuerear = capacity - 1;
        delete[]queue;
        queue = temp;
    }
    queue[queuerear] = theElement;
    queuerear = (queuerear + 1) % capacity;
}
