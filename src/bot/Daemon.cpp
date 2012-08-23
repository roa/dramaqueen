#include "Daemon.hpp"

namespace Dramaqueen
{

Daemon::Daemon( std::string _daemonName, Client* _j ) : j( _j ), daemonName( _daemonName )
{
    daemonDir = "/home/roa/programming/dramaqueen/daemon/";
    logger = Logger::getSingletonPtr();
    load();
}

Daemon::~Daemon()
{

}

void Daemon::load()
{
    std::stringstream script;
    script << daemonDir << daemonName;
    lua_State *L = luaL_newstate();

    if( luaL_loadfile( L, script.str().c_str() ) || lua_pcall( L, 0, 0, 0) )
    {
        logger->log( "Could not load daemon config file: ", script.str().c_str() );
        logger->log( "lua error message:", lua_tostring( L, 1 ) );
        exit( 0 );
    }

    lua_getglobal( L, "checkTime" );
    if( !lua_isnumber( L, 1 ) )
    {
        logger->log( "checkTime is not a number" );
    }
    else
    {
        checkTime = lua_tointeger( L, 1 );
        script << " to " << checkTime;
        logger->log( "set checktime for", script.str().c_str() );
    }

    lua_pop( L, 1 );

    lua_getglobal( L, "script" );
    if( !lua_isstring( L, 1 ) )
    {
        logger->log( "script is not a number" );
    }
    else
    {
        scriptName = lua_tostring( L, 1 );
        logger->log( "set scriptName for daemon to", scriptName );
    }

    lua_pop( L, 1 );

    lua_close( L );
}

void Daemon::observe()
{
    while( true )
    {
        std::string result = executeScript( scriptName);
        if( !result.empty() )
        {
            Message::MessageType type = Message::MessageType::Chat;
            std::string to = "roa@localhost";
            Message msg( type, to, result );
            j->send( msg );
        }
        sleep( checkTime );
    }
}

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

DaemonForge::DaemonForge( std::string const& daemon_, Client* _j ) : daemonName( daemon_ ), j( _j )
{

}

}
