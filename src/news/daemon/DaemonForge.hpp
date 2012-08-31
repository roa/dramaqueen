/**
    the daemonforge object is used to start daemons and keep
    track of their status. if a daemon dies it is deleted and
    daemonforge tries to spawn a new daemon-
    as dramaqueen daemons are supposed to run forever, daemonforge object never
    stop to try to spawn new daemons and do not check, if all conditions to start
    a daemon are met.
**/
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
