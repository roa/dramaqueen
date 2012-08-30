#ifndef DRAMAQUEEN_DAEMONFORGE_HPP
#define DRAMAQUEEN_DAEMONFORGE_HPP

#include "Daemon.hpp"

namespace Dramaqueen
{

class DaemonForge
{

public:

    explicit DaemonForge( std::string const& daemon_, Client* _j, ConnectionError* _ce );
    void operator()() const;

private:

    std::string daemonName;
    Client* j;
    ConnectionError* ce;

};

}

#endif
