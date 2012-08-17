#include "BaseServer.hpp"

namespace Dramaqueen
{

BaseServer::BaseServer()
{
    config = Config::getSingletonPtr();
    logger = Logger::getSingletonPtr();
}

BaseServer::~BaseServer()
{

}

void BaseServer::dropRights()
{
    pw = getpwnam( config->getUser().c_str() );
    if (getuid() == 0) {
        if (setgid( 1000 ) != 0)
            logger->log( "setgid: Unable to drop group privileges: ", strerror( errno ) );
        if (setuid( 1000 ) != 0)
            logger->log( "setuid: Unable to drop user privileges: ", strerror( errno ) );
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
