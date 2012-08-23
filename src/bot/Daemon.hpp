#ifndef DRAMAQUEEN_DAEMON_HPP
#define DRAMAQUEEN_DAEMON_HPP

#include <iostream>
#include <lua.hpp>

#include "../logger/Logger.hpp"

#include <gloox/client.h>
#include <gloox/loghandler.h>
#include <gloox/messagehandler.h>
#include <gloox/connectionlistener.h>
#include <gloox/message.h>

using namespace gloox;

namespace Dramaqueen
{

class Daemon
{

public:
    Daemon( std::string _daemonName, Client* _j );
    ~Daemon();
    void observe();
private:

    Logger* logger;
    Client* j;

    std::string daemonDir;
    std::string daemonName;
    std::string scriptName;

    int checkTime;

    void load();
    std::string executeScript( std::string script );
};

class DaemonForge
{
public:
    std::string daemonName;
    Client* j;
    explicit DaemonForge( std::string const& daemon_, Client* _j );
    void operator()() const
    {
        std::cout << daemonName << std::endl;
        Daemon * test;
        test = new Daemon( daemonName, j );
        test->observe();
        delete test;
    }
};

}

#endif
