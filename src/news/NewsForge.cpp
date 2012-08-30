#include "NewsForge.hpp"

namespace Dramaqueen
{

NewsForge::NewsForge()
{
    sleep( 5 );
}

NewsForge::~NewsForge()
{

}

void NewsForge::operator() ()
{
    initNews();
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

            continue;
        }
        if( currentFile.find( ".lua" ) < currentFile.npos )
        {
            std::thread daemonThread{ DaemonForge( currentFile, _j, ce ) };
            daemonThread.detach();
        }
        else
        {
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
}

void NewsForge::destroyBot()
{
    j = NULL;
    ce = NULL;
    delete bot;
}

void NewsForge::initNews()
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
            initDaemonForge( Config::getSingletonPtr()->getDaemonDir(), j, ce );
        }
        botThread.join();
        destroyBot();
    }
}



}
