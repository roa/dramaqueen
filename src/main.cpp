#include <iostream>
#include <thread>

#include <sys/types.h>
#include <pwd.h>

#include "news/NewsForge.hpp"
#include "server/BaseServer.hpp"
#include "server/ServerForge.hpp"
#include "news/client/BaseClient.hpp"
#include "logger/Logger.hpp"
#include "config/Config.hpp"
#include "news/bot/Bot.hpp"
#include "news/daemon/Daemon.hpp"
#include "news/daemon/DaemonForge.hpp"

using namespace Dramaqueen;
using namespace gloox;

void dropRights()
{
    passwd *pw = getpwnam( Config::getSingletonPtr()->getUser().c_str() );
    if( getuid() == 0)
    {
        if( setgid( pw->pw_gid ) != 0 )
            Logger::getSingletonPtr()->log( "setgid: Unable to drop group privileges: ", strerror( errno ) );
        if( setuid( pw->pw_uid ) != 0 )
            Logger::getSingletonPtr()->log( "setuid: Unable to drop user privileges: ", strerror( errno ) );
    }
}

int main( int argc, char **argv )
{
    int opt = 0;
    std::string logDest  = "";
    std::string confFile = "";

    if( argc < 3 )
    {
        std::cerr << "need log and config" << std::endl;
        /**
            TODO:
            more informative help
        **/
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
    Logger::getSingletonPtr( logDest )->log( "initialized dramaqueen...");
    Config* config = Config::getSingletonPtr( confFile );

    dropRights();

    if( config->getXmpp() )
    {
        std::thread srvThread{ ServerForge() };
        std::thread newsThread{ NewsForge() };

        newsThread.detach();
        srvThread.join();
    }
    else
    {
        std::thread srvThread{ ServerForge() };
        srvThread.join();
    }

    return 0;
}
