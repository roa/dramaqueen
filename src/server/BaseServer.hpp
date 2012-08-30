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
#include <fstream>
#include "../config/Config.hpp"

namespace Dramaqueen
{

class BaseServer
{
private:
    SSL_CTX* ctx;
    std::string cert;
    std::string key;
    std::string host;

    BIO *abio;
    BIO *client;
    SSL *ssl;

    void initServer();
    void handleClient();
    std::string executeScript( std::string script );

public:
    BaseServer();
    ~BaseServer();
    void run();

};

}

#endif
