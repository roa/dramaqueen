#include <iostream>
#include <thread>

#include "server/BaseServer.hpp"
#include "logger/Logger.hpp"

using namespace Dramaqueen;

int main( int argc, char **argv )
{
    BaseServer *dramaqueen;
    Logger* logger = Logger::getSingletonPtr();
    logger->log( "starting..." );

    dramaqueen = new BaseServer;
    dramaqueen->drama();

    delete dramaqueen;
    return 0;
}
