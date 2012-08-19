#include <iostream>
#include <thread>

#include "server/BaseServer.hpp"
#include "client/BaseClient.hpp"
#include "logger/Logger.hpp"
#include "bot/Bot.hpp"


using namespace Dramaqueen;

Client* _j = NULL;

void startBot()
{
    Bot bot;
    _j = bot.getJ();
    bot.connectToXMPP();
}

void startServer( Client* _j )
{
    BaseServer *server;
    server = new BaseServer( _j );
    server->run();

    delete server;
}

int main( int argc, char **argv )
{
    Logger* logger = Logger::getSingletonPtr();
    logger->log( "starting..." );

    std::thread t(startBot);

    /**********************************
    *  wait for the Client Pointer to *
    *  get initialized                *
    ***********************************/
    while( _j == NULL )
    {
        sleep( 1 );
    }
    std::cout << "after sleep" << std::endl;
    std::thread t1(startServer,_j);

    t1.join();
    t.join();

    return 0;
}
