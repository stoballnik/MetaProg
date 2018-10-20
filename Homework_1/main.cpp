#include <iostream>
#include "Interlayer.h"
#include "User.h"
#include "Server.h"

int main(int argc, const char * argv[]) {
    std::cout<<"TEST OBSERVER" << std::endl;
    User u1 = User(1), u2=User(2), u3=User(3);
    Interlayer<Observer> observer = Interlayer<Observer>();
    Server serv = Server(0, &observer);
    u1.updateServerData(&serv, -1);
    u1.subscribe(&observer);
    u2.updateServerData(&serv, -2);
    u2.subscribe(&observer);
    u3.subscribe(&observer);
    u1.updateServerData(&serv, -3);
    u2.unsubscribe(&observer);
    u3.updateServerData(&serv, -4);
    u1.unsubscribe(&observer);
    u3.unsubscribe(&observer);
//_____________________________________
    
    std::cout<<"\n\nTEST MEDIATOR" << std::endl;
    u1.updateLocal(1);
    u2.updateLocal(2);
    u3.updateLocal(3);
    serv.update(-1);
    Server serv2 = Server(-2), serv3 = Server(-3);
    Interlayer<Mediator> mediator = Interlayer<Mediator>();
    mediator.abbPublisher(&serv);
    mediator.abbPublisher(&serv2);
    mediator.abbPublisher(&serv3);
    u1.updateLocal(&mediator);
    u2.updateLocal(&mediator);
    u3.updateLocal(&mediator);
    
//_____________________________________
    std::cout<<"\n\nTEST PROXY" << std::endl;
    u1.updateLocal(1);
    serv.update(-1);
    Interlayer<Proxy> proxy = Interlayer<Proxy>(&serv);
    u1.updateServerData(&proxy, -1);
    u1.updateServerData(&proxy, -2);
    u1.updateServerData(&proxy, -2);
    return 0;
}
