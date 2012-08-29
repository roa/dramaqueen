#ifndef DRAMAQUEEN_DAEMONFORGE_HPP
#define DRAMAQUEEN_DAEMONFORGE_HPP

#include "Daemon.hpp"

namespace Dramaqueen
{

class DaemonForge
{
public:
    std::string daemonName;
    Client* j;
    ConnectionError* ce;
    explicit DaemonForge( std::string const& daemon_, Client* _j, ConnectionError* _ce );
    void operator()() const
    {
        Daemon * d = new Daemon( daemonName, j, ce );
        d->observe();
        delete d;
    }
private:
};

}

#endif
