#include "ServerForge.hpp"

namespace Dramaqueen
{

void ServerForge::operator() () const
{
    Helper::log( "initializing server..." );
    BaseServer *server;
    server = new BaseServer();
    server->run();
    Helper::log( "server crashed or exited" );
    delete server;
}

}
