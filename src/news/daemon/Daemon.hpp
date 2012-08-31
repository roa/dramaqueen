/**
    daemons are started via the daemonforge object, which
    is part of the newsforge message system.
    each daemon runs in a separate thread with its own daemonforge. daemons die easy and often as
    they depend on other parts of the message system. if a daemon detects a
    failure in the message system it dies and exists. after that it is restarted
    by the daemonforge object.
    daemons have their own configs, which are placed in the daemon directory. daemon config scripts
    must not start with an dot and have to end with ".lua" suffix.
    a typical daemon config looks like that:

    >>>>
    #!/usr/bin/lua

    checkTime = 1
    script    = "script.lua"
    recipients = { "roa@localhost" }
    hosts = { "localhost:9898" }

    <<<<

    checkTime is the intervall in seconds. the script, specified by "script" is expected
    in the scriptDir specified by main config file.
    recipients describes a standard xmpp user. u can name as many as you want.
    hosts is also a table, which describes on which hosts the script should be executed. the script
    must be placed on all hosts specified in "hosts". hosts have to be formated this way:
    "<hosts>:<port>"
**/
#ifndef DRAMAQUEEN_DAEMON_HPP
#define DRAMAQUEEN_DAEMON_HPP

#include <iostream>
#include <lua.hpp>

#include "../../config/Config.hpp"
#include "../client/BaseClient.hpp"
#include "../../helper/Helper.hpp"

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
    Daemon( std::string _daemonName, Client* _j, ConnectionError* ce );
    ~Daemon();
    void observe();
private:

    Client* j;
    ConnectionError* ce;

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
