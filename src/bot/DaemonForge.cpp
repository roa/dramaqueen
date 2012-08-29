#include "DaemonForge.hpp"

namespace Dramaqueen
{

std::string Daemon::executeScript( std::string script )
{
    FILE* pipe = popen( script.c_str(), "r" );
    if ( !pipe ) return "ERROR";
    char buffer[128];
    std::string result = "";
    while( !feof( pipe ) )
    {
        if( fgets( buffer, 128, pipe ) != NULL )
            result += buffer;
    }
    pclose( pipe );
    return result;
}

DaemonForge::DaemonForge( std::string const& daemon_, Client* _j, ConnectionError* _ce ) : daemonName( daemon_ ), j( _j ), ce( _ce )
{

}

}
