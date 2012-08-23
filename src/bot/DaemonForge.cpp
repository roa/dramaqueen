#include "DaemonForge.hpp"

namespace Dramaqueen
{

void DaemonForge::operator()() const
{
    Daemon * d = new Daemon( daemonName, j );
    d->observe();
    delete d;
}

DaemonForge::DaemonForge( std::string const& daemon_, Client* _j ) : daemonName( daemon_ ), j( _j )
{

}

}
