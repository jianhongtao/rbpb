#ifndef QUEUE_H
#define QUEUE_H

#include <QMutex>
#include <QWaitCondition>
#include <QQueue>

// The queue with synchronization an EOF
template <class T> class Queue
{
public:
    Queue(){hasEof = false;}
    ~Queue(){}

public:
    // Adds data to the tail of the queue.
    void put(const T& data)
    {
        mutex.lock();

        queue.enqueue(data);
        if(queue.size() == 1)
        {
            cond.wakeAll();
        }

        mutex.unlock();
    }

    // Removes the head item from the queue and returns it
    // If the queue has receive EOF signal, this function will return false immediately
    // If the queue is empty and set block, this function will wait
    // If the queue is empty and set unblock, this function will return false immediately
    // If thie queue is not empty, this function will return true
    bool get(T& data, bool block = true)
    {
        bool ret;

        mutex.lock();

        while(true)
        {
            if(hasEof)
            {
                ret = false;
                break;
            }

            if(queue.isEmpty())
            {
                if(block)
                {
                    cond.wait(&mutex);
                }
                else
                {
                    ret = false;
                    break;
                }
            }

            if(hasEof)
            {
                ret = false;
                break;
            }

            if(!(queue.isEmpty()))
            {
                data = queue.dequeue();
                ret = true;
                break;
            }
        }

        mutex.unlock();

        return ret;
    }

    // Send EOF signal
    void eof()
    {
        mutex.lock();
        hasEof = true;
        cond.wakeAll();
        mutex.unlock();
    }

    // Get the length of queue
    qint32 length()
    {
        mutex.lock();
        qint32 length = queue.length();
        mutex.unlock();

        return length;
    }

public:
    QMutex mutex;
    QWaitCondition cond;
    QQueue<T> queue;
    bool hasEof;
};

#endif // QUEUE_H
