#include <iostream>
#include <thread>

#include "server/BaseServer.hpp"
#include "client/BaseClient.hpp"
#include "logger/Logger.hpp"
#include "bot/Bot.hpp"
#include "config/Config.hpp"

using namespace Dramaqueen;

void startBot()
{
    Bot bot;
    bot.connectToXMPP();
}

void startServer()
{
    BaseServer *server;
    server = new BaseServer();
    server->run();
    delete server;
}

int main( int argc, char **argv )
{
    Logger::getSingletonPtr()->log( "starting..." );

    int opt = 0;
    std::string confFile = "/home/roa/programming/dramaqueen/config/init.lua";

    if( argc < 2 )
    {
        Logger::getSingletonPtr()->log( "no config specified ");
        Logger::getSingletonPtr()->log( "exiting..." );
        exit( 0 );
    }

    while( ( opt = getopt( argc, argv, "c:") ) != -1)
    {
        switch( opt )
        {
            case 'c':
            {
                confFile = optarg;
                Logger::getSingletonPtr()->log( "using config: ", confFile );
                break;
            }
            default:
            {
                Logger::getSingletonPtr()->log( "no config given: use default value" );
            }
        }
    }

    Config* config = Config::getSingletonPtr( confFile );

    if( config->getXmpp() )
    {
        std::thread botThread( startBot );
        std::thread srvThread( startServer );

        srvThread.join();
        botThread.join();
    }
    else
    {
        std::thread srvThread( startServer );
        srvThread.join();
    }

    return 0;
}
