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
        setgid( pw->pw_gid );
        setuid( pw->pw_uid );
    }
}

}

}
