#pragma once
#include "ServerInterface.h"
#include "ObserverInterface.h"
#include <iostream>

class Server: public ServerInterface
{
    int data;
    ObserverInterface* observer;
public:
    Server(int _data=0, ObserverInterface* _observer=nullptr):data(_data), observer(_observer){}
    
    int getData()
    {
        std::cout << "Server:: Server send this data: " << data << std::endl;
        return data;
    }
    void update(int newData)
    {
        data = newData;
        std::cout << "Server:: Change server data to: " << data << std::endl;
        if(observer){
            observer->notify(data);
        }
    }
};
