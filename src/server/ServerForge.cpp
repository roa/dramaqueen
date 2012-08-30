#include "ServerForge.hpp"

namespace Dramaqueen
{

void ServerForge::operator() () const
{
    BaseServer *server;
    server = new BaseServer();
    server->run();
    delete server;
}

}
