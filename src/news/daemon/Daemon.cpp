#include "Daemon.hpp"

namespace Dramaqueen
{

Daemon::Daemon( std::string _daemonName, Client* _j, ConnectionError* _ce ) : j( _j ), daemonName( _daemonName ), ce( _ce )
{
    daemonDir = Config::getSingletonPtr()->getDaemonDir();
    shouldRun = true;
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

        shouldRun = false;
    }

    lua_getglobal( L, "checkTime" );
    if( !lua_isnumber( L, 1 ) )
    {
        shouldRun = false;
    }
    else
    {
        checkTime = lua_tointeger( L, 1 );
        script << " to " << checkTime;
    }

    lua_pop( L, 1 );

    lua_getglobal( L, "script" );
    if( !lua_isstring( L, 1 ) )
    {
        shouldRun = false;
    }
    else
    {
        scriptName = lua_tostring( L, 1 );
    }

    lua_pop( L, 1 );

    lua_getglobal( L, "recipients" );
    if( !lua_istable( L, 1 ) )
    {
        shouldRun = false;
    }
    else
    {
        lua_pushnil( L );

        while( lua_next( L, 1 ) != 0 )
        {
            recipients.push_back( lua_tostring( L, -1 ) );
            lua_pop( L, 1 );
        }
    }

    if( recipients.size() == 0 )
    {
        shouldRun = false;
    }

    lua_pop( L, 1 );

    lua_getglobal( L, "hosts" );
    if( !lua_istable( L, 1 ) )
    {
        shouldRun = false;
    }
    else
    {
        lua_pushnil( L );

        while( lua_next( L, 1 ) != 0 )
        {
            hosts.push_back( lua_tostring( L, -1 ) );
            lua_pop( L, 1 );
        }
    }

    if( hosts.size() == 0 )
    {
        shouldRun = false;
    }

    lua_close( L );
}

void Daemon::observe()
{
    while( shouldRun )
    {
        sleep( checkTime );

        if( ! *ce == ConnNoError )
        {
            break;
        }
        if( j == NULL )
        {
            break;
        }

        Message::MessageType type = Message::MessageType::Chat;
        for( std::vector<std::string>::iterator it = recipients.begin(); it != recipients.end(); ++it )
        {
            std::string recipient = *it;
            std::string content = contactHosts( scriptName );
            Message msg( type, recipient, content );
            if( !content.empty() )
                j->send( msg );
        }

    }
}

std::string Daemon::contactHosts( std::string command )
{
    std::string results;
    for( std::vector<std::string>::iterator it = hosts.begin(); it != hosts.end(); ++it )
    {
        std::string currentHost = *it;
        /**
            TODO:
            parallelize it!
        **/
        BaseClient baseclient( currentHost, command );
        results.append( baseclient.run() );
    }
    return results;
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

}
