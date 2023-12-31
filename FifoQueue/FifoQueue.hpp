#pragma once
#include <vector>
#include <pthread.h>
#include <iostream>

template<typename T>
class FifoQueue
{
public:
    FifoQueue(){pthread_mutex_init(&_mtx,NULL);}

    ~FifoQueue(){pthread_mutex_destroy(&_mtx);}

    bool isEmpty(){return _vector.size() == 0;}

    void enqueue(const T& item)
    {
        pthread_mutex_lock(&_mtx);
        _vector.push_back(item);
        pthread_mutex_unlock(&_mtx);
    }

    T dequeue()
    {
        pthread_mutex_lock(&_mtx);
        if (isEmpty())
        {
            pthread_mutex_unlock(&_mtx);
            return NULL;
        }

        T item = _vector.front();
        _vector.erase(_vector.begin());
        pthread_mutex_unlock(&_mtx);
        return item;
    }

private:
    std::vector<T> _vector;
    pthread_mutex_t _mtx;
};


