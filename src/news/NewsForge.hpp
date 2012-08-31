/**
    the newsforge object is supposed to initialize the
    complete message system( bot, daemonforge... later more ;> ).
    it initialized the bot in a separate thread and keeps track of its status.
    if a bot dies, it tries to spawn a new one. also it spawns a daemonforge for
    every daemon config file it can find. daemonforges can track bot status via
    messenger and connectionerror objects. newsforge keeps them updated to ensure,
    that daemons can detect failures.
**/
#ifndef DRAMAQUEEN_NEWSFORGE_HPP
#define DRAMAQUEEN_NEWSFORGE_HPP

#include <dirent.h>

#include <iostream>
#include <thread>

#include "bot/Bot.hpp"
#include "daemon/DaemonForge.hpp"
#include "../config/Config.hpp"
#include "../helper/Helper.hpp"

namespace Dramaqueen
{

class NewsForge
{

public:

    void operator() ();
    explicit NewsForge();
    ~NewsForge();

private:

    Client* j;
    ConnectionError* ce;
    Bot* bot;

    void initNews();
    void initDaemonForge( std::string daemonDir, Client* _j, ConnectionError* ce );
    void initBot();
    void startBot();
    void destroyBot();

};

}

#endif
