#include "lock.h"
#include <iostream>
#include <unistd.h>

int main()
{
    // 客户端1
    raichu::lock::ReadWriteLock *lock1 = new raichu::lock::ReadWriteLock("localhost:2182", "/lock");

    lock1->lockRead();
    std::cout << "I am testNode 1" << std::endl;

    std::cout << ("I am TestNode 1");
    std::cout << ("睡眠10s 之后释放分布式读锁, 开始倒计时");
    for (int i = 0; i < 10; i++)
    {
        std::cout << (10 - i);
        sleep(1);
    }

    lock1->unLockRead();

    // 客户端2
    raichu::lock::ReadWriteLock *lock2 = new raichu::lock::ReadWriteLock("localhost:2182", "/lock");

    lock2->lockRead();
    std::cout << ("I am TestNode 2");
    lock2->unLockRead();

    // 客户端3
    raichu::lock::ReadWriteLock *lock3 = new raichu::lock::ReadWriteLock("localhost:2182", "/lock");

    lock3->lockWrite();
    std::cout << ("I am testNode 3");
    std::cout << ("睡眠10s 之后释放分布式写锁, 开始倒计时");
    for (int i = 0; i < 10; i++)
    {
        std::cout << (10 - i);

        sleep(1);
    }
    lock3->unLockWrite();

    // 客户端4
    raichu::lock::ReadWriteLock *lock4 = new raichu::lock::ReadWriteLock("localhost:2182", "/lock");

    lock4->lockRead();
    std::cout << ("I am TestNode 4");
    lock4->unLockRead();

    delete lock1;
    delete lock2;
    delete lock3;
    delete lock4;

    return 0;
}