#ifndef DRAMAQUEEN_DAEMON_HPP
#define DRAMAQUEEN_DAEMON_HPP

#include <iostream>
#include <lua.hpp>

#include "../logger/Logger.hpp"
#include "../config/Config.hpp"
#include "../client/BaseClient.hpp"

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
    std::vector<std::string> recipients;
    std::vector<std::string> hosts;

    int checkTime;

    bool shouldRun;

    void load();
    std::string executeScript( std::string script );
    std::string contactHosts( std::string command );

};

}

#endif
