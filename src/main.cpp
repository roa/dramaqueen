#include <iostream>
#include <thread>

#include <sys/types.h>
#include <dirent.h>
#include <pwd.h>

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

Client* j = NULL;
ConnectionError* ce = NULL;

void initDaemonForge( std::string daemonDir, Client* _j, ConnectionError* ce )
{
    DIR* dp = opendir( daemonDir.c_str() );
    while( true )
    {
        struct dirent* dir = readdir( dp );
        if( dir == NULL )
        {
            break;
        }
        std::string currentFile = dir->d_name;
        if( currentFile.find( "." ) == 0 )
        {
            Logger::getSingletonPtr()->log( "daemon skips file: ", currentFile );
            Logger::getSingletonPtr()->log( "daemon config files must not begin with a dot" );
            continue;
        }
        if( currentFile.find( ".lua" ) < currentFile.npos )
        {
            std::thread daemonThread{ DaemonForge( currentFile, _j, ce ) };
            daemonThread.detach();
        }
        else
        {
            Logger::getSingletonPtr()->log( "cannot add daemon for: ", currentFile );
            Logger::getSingletonPtr()->log( "daemon config files must have a lua suffix" );
        }
    }
    closedir( dp );
}

void startBot()
{
    Bot bot;
    j = bot.getJ();
    ce = bot.getCE();
    bot.connectToXMPP();
    j = NULL;
    ce = NULL;
}

void startComm()
{
    while( true )
    {
        int i = 0;
        bool initDaemon = false;
        std::thread botThread( startBot );
        while( true )
        {
            sleep( 5 );

            if( ! ( j == NULL || ce == NULL ) )
            {
                initDaemon = true;
                break;
            }

            if( i++ > 3 )
            {
                break;
            }
        }
        if( initDaemon )
        {
            Logger::getSingletonPtr()->log( "initialized bot..." );
            initDaemonForge( Config::getSingletonPtr()->getDaemonDir(), j, ce );
            Logger::getSingletonPtr()->log( "initialized daemons..." );
        }
        botThread.join();
    }
}

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

        startComm();

        srvThread.join();
    }
    else
    {
        std::thread srvThread{ ServerForge() };
        srvThread.join();
    }

    return 0;
}
