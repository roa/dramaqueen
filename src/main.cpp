#include <iostream>
#include <thread>

#include "Helper.hpp"
#include "news/NewsForge.hpp"
#include "server/ServerForge.hpp"
#include "logger/Logger.hpp"
#include "config/Config.hpp"

using namespace Dramaqueen;
using namespace gloox;

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

    Helper::dropPrivs();

    if( config->getXmpp() )
    {
        std::thread srvThread{ ServerForge() };
        std::thread newsThread{ NewsForge() };

        newsThread.join();
        srvThread.join();
    }
    else
    {
        std::thread srvThread{ ServerForge() };
        srvThread.join();
    }

    return 0;
}
