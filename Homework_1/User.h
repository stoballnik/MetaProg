#pragma once
#include "ServerInterface.h"
#include "ObserverInterface.h"
#include <iostream>

class User
{
    int data;
public:
    User(int _data=0): data(_data){}
    
    void updateLocal(int newData)
    {
        data = newData;
        std::cout<< "User:: Change user data to: " << data << std::endl;
    }
    
    void updateLocal(ServerInterface* serv)
    {
        data = serv->getData();
        std::cout<< "User:: Change user data to: " << data << std::endl;
    }
    
    void notify(int data)
    {
        updateLocal(data);
    }
    
    void updateServerData(ServerInterface* serv, int data)
    {
        serv->update(data);
    }
    
    void subscribe(ObserverInterface* obs)
    {
        obs->subscribe(this);
    }
    void unsubscribe(ObserverInterface* obs)
    {
        obs->unsubscribe(this);
    }
};
