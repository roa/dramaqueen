#include "Daemon.hpp"

namespace Dramaqueen
{

Daemon::Daemon( std::string _daemonName, Client* _j, ConnectionError* _ce ) : j( _j ), ce( _ce ), daemonName( _daemonName )
{
    daemonDir = Config::getSingletonPtr()->getDaemonDir();
    shouldRun = true;
    load();
    Helper::log( daemonName, ": initialized Daemon..." );
}

Daemon::~Daemon()
{
    Helper::log( daemonName, ": shut down Daemon" );
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
        Helper::log( daemonName, ": checktime is not a valid value" );
    }
    else
    {
        checkTime = lua_tointeger( L, 1 );
        std::stringstream log;
        log << checkTime;
        Helper::log( daemonName, ": set checkTime to ", log.str() );
    }

    lua_pop( L, 1 );

    lua_getglobal( L, "script" );
    if( !lua_isstring( L, 1 ) )
    {
        shouldRun = false;
        Helper::log( daemonName, ": script is not a valid value" );
    }
    else
    {
        scriptName = lua_tostring( L, 1 );
        Helper::log( daemonName, ": set script to ", scriptName );
    }

    lua_pop( L, 1 );

    lua_getglobal( L, "recipients" );
    if( !lua_istable( L, 1 ) )
    {
        shouldRun = false;
        Helper::log( daemonName, ": recipients is not a valid value" );
    }
    else
    {
        lua_pushnil( L );

        while( lua_next( L, 1 ) != 0 )
        {
            std::string recipient = lua_tostring( L, -1 );
            recipients.push_back( recipient );
            Helper::log( daemonName, ": added recipient", recipient );
            lua_pop( L, 1 );
        }
    }

    if( recipients.size() == 0 )
    {
        shouldRun = false;
        Helper::log( daemonName, ": no valid recipients found" );
    }

    lua_pop( L, 1 );

    lua_getglobal( L, "hosts" );
    if( !lua_istable( L, 1 ) )
    {
        shouldRun = false;
        Helper::log( daemonName, ": hosts is not a valid value" );
    }
    else
    {
        lua_pushnil( L );

        while( lua_next( L, 1 ) != 0 )
        {
            std::string host = lua_tostring( L, -1 );
            hosts.push_back( host );
            Helper::log( daemonName, ": added host", host );
            lua_pop( L, 1 );
        }
    }

    if( hosts.size() == 0 )
    {
        shouldRun = false;
        Helper::log( daemonName, ": no valid hosts found" );
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
            Helper::log( daemonName, ": detected bot error - shutting down daemon" );
            break;
        }
        if( j == NULL )
        {
            Helper::log( daemonName, ": detected bot error - shutting down daemon" );
            break;
        }
        Message::MessageType type = Message::MessageType::Chat;
        std::string content = contactHosts( scriptName );
        for( std::vector<std::string>::iterator it = recipients.begin(); it != recipients.end(); ++it )
        {
            std::string recipient = *it;
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

}
