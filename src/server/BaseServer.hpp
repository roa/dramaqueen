#ifndef DRAMAQUEEN_BASESERVER_HPP
#define DRAMAQUEEN_BASESERVER_HPP

#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <errno.h>
#include <sstream>
#include <pwd.h>

#include <gloox/client.h>
#include <gloox/loghandler.h>
#include <gloox/messagehandler.h>
#include <gloox/connectionlistener.h>
#include <gloox/message.h>

#include "../config/Config.hpp"
#include "../logger/Logger.hpp"

using namespace gloox;

namespace Dramaqueen
{

class BaseServer
{
private:
    SSL_CTX* ctx;
    char *cert;
    char *key;
    BIO *abio;
    BIO *client;
    SSL *ssl;
    char *host;
    passwd *pw;

    Config* config;
    Logger* logger;
    Client* j;

    void dropRights();

public:
    BaseServer( Client *_j );
    ~BaseServer();
    void drama();

};

}

#endif
