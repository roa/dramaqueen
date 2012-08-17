#include "BaseServer.hpp"

namespace Dramaqueen
{

BaseServer::BaseServer()
{

}

BaseServer::~BaseServer()
{

}

void BaseServer::dropRights()
{
    pw = getpwnam( "roa" );
    if (getuid() == 0) {
    if (setgid( 1000 ) != 0)
        printf("setgid: Unable to drop group privileges: %s", strerror(errno));
    if (setuid( 1000 ) != 0)
        printf("setuid: Unable to drop user privileges: %s", strerror(errno));
    }
}

void BaseServer::drama()
{
    dropRights();
    while( true )
    {
        sleep( 1 );
    }
}

}
