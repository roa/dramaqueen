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
