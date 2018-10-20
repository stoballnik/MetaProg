#pragma once
#include <set>
#include <vector>
#include "ServerInterface.h"
#include "ObserverInterface.h"
#include "User.h"

enum Role
{
    Proxy,
    Mediator,
    Observer
};

template <Role>
class Interlayer {};

template<>
class Interlayer<Role::Observer>: public ObserverInterface
{
    std::set<User*> subscribers;
public:
    void subscribe(User* subscriber)
    {
        subscribers.insert(subscriber);
        std::cout << "Observer:: Add new subscriber: " << subscriber << std::endl;
    }
    void unsubscribe(User* subscriber)
    {
        subscribers.erase(subscriber);
        std::cout << "Observer:: Remove subscriber: " << subscriber << std::endl;
    }
    void notify(int data)
    {
        for (User* subscriber : subscribers){
            std::cout << "Observer:: Notify subscriber: " << subscriber << "; with data: " << data << std::endl;
            subscriber->updateLocal(data);
        }
    }
};


template<>
class Interlayer<Role::Mediator>: public ServerInterface
{
    std::vector<ServerInterface*> publishers;
public:
    void abbPublisher(ServerInterface* publisher)
    {
        publishers.push_back(publisher);
        std::cout << "Mediator:: Add new publisher: " << publisher << std::endl;
    }
    int getData()
    {
        int n = std::rand() % publishers.size();
        int data = publishers[n]->getData();
        std::cout << "Mediator:: Get data: " << data << "; from publisher: " << publishers[n] << std::endl;
        return data;
    }
    
    void update(int _data)
    {
        int n = std::rand() % publishers.size();
        std::cout << "Mediator:: Update server " << publishers[n] << " with data: " << _data << std::endl;
        publishers[n]->update(_data);
    }
};


template<>
class Interlayer<Role::Proxy>: public ServerInterface
{
    ServerInterface* publisher;
    int data;
    bool changed;
public:
    Interlayer<Role::Proxy>(ServerInterface* _publisher):publisher(_publisher)
    {
        data = publisher->getData();
        changed = false;
    }
    
    int getData()
    {
        if(changed){
            data = publisher->getData();
            changed = false;
        }
        std::cout << "Proxy:: Get data: " << data << std::endl;
        return data;
    }
    
    void update(int _data)
    {
        std::cout << "Proxy:: Update server with data: " << _data << std::endl;
        if(data != _data)
        {
            publisher->update(_data);
            changed = true;
        }
    }
};
