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
    explicit DaemonForge( std::string const& daemon_, Client* _j );
    void operator()() const
    {
        Daemon * d = new Daemon( daemonName, j );
        d->observe();
        delete d;
    }
private:
};

}

#endif
