#include "NewsForge.hpp"

namespace Dramaqueen
{

NewsForge::NewsForge()
{

}

NewsForge::~NewsForge()
{
}

void NewsForge::initDaemonForge( std::string daemonDir, Client* _j, ConnectionError* ce )
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

void NewsForge::initBot()
{
    bot = new Bot();
    j = bot->getJ();
    ce = bot->getCE();
}

void NewsForge::startBot()
{
    bot->connectToXMPP();
    j = NULL;
    ce = NULL;
}

void NewsForge::operator() ()
{
    while( true )
    {
        int i = 0;
        bool initDaemon = false;
        initBot();
        std::thread botThread( &NewsForge::startBot, *this );
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
        delete bot;
    }
}



}
