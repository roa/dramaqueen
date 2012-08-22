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
    int opt = 0;
    std::string logDest  = "log/dev.log";
    std::string confFile = "/home/roa/programming/dramaqueen/config/init.lua";

    if( argc < 3 )
    {
        std::cerr << "need log and config" << std::endl;
        exit( 0 );
    }

    while( ( opt = getopt( argc, argv, "c:l:") ) != -1)
    {
        switch( opt )
        {
            case 'c':
            {
                confFile = optarg;
                break;
            }
            case 'l':
            {
                logDest = optarg;
                break;
            }
            default:
            {
                /**
                TODO:
                do something useful
                **/
            }
        }
    }
    Logger* logger = Logger::getSingletonPtr( logDest );
    logger->log( "initialized dramaqueen...");
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
