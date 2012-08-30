#include "ServerForge.hpp"

namespace Dramaqueen
{

void ServerForge::operator() () const
{
    /**
        TODO:
        add Logging!
    **/
    BaseServer *server;
    server = new BaseServer();
    server->run();
    delete server;
}

}
