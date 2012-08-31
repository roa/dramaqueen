#include <iostream>
#include <thread>

#include "helper/Helper.hpp"
#include "news/NewsForge.hpp"
#include "server/ServerForge.hpp"
#include "config/Config.hpp"

using namespace Dramaqueen;

int main( int argc, char **argv )
{
    int opt = 0;
    std::string confFile = "";

    if( argc < 2 )
    {
        std::cerr << "need config" << std::endl;
        /**
            TODO:
            more informative help
        **/
        exit( 0 );
    }

    while( ( opt = getopt( argc, argv, "c:") ) != -1)
    {
        switch( opt )
        {
            case 'c':
            {
                confFile = optarg;
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
