#include <iostream>
#include <thread>

#include "server/BaseServer.hpp"
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

int main( int argc, char **argv )
{
    BaseServer *dramaqueen;
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

    dramaqueen = new BaseServer( _j );
    dramaqueen->drama();

    delete dramaqueen;
    t.join();

    return 0;
}
