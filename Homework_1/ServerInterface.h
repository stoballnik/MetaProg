#pragma once

class ServerInterface {
public:
    virtual int getData() = 0;
    virtual void update(int) = 0;
};
