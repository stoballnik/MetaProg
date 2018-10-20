#pragma once
class User;

class ObserverInterface
{
public:
    virtual void notify(int) = 0;
    virtual void subscribe(User*) = 0;
    virtual void unsubscribe(User*) = 0;
};
