#include "Helper.hpp"

namespace Dramaqueen
{

namespace Helper
{

void dropPrivs()
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

}

}
