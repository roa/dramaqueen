#include "DaemonForge.hpp"

namespace Dramaqueen
{

DaemonForge::DaemonForge( std::string const& daemon_, Client* _j, ConnectionError* _ce ) : daemonName( daemon_ ), j( _j ), ce( _ce )
{

}

void DaemonForge::operator()() const
{
    Daemon * d = new Daemon( daemonName, j, ce );
    d->observe();
    delete d;
}

}
