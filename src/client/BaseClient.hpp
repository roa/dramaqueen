#ifndef DRAMAQUEEN_CLIENT_HPP
#define DRAMAQUEEN_CLIENT_HPP

#include <iostream>
#include <string.h>
#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#include <sys/socket.h>
#include <netdb.h>
#include <fcntl.h>

#include "../logger/Logger.hpp"
#include "../config/Config.hpp"

namespace Dramaqueen
{

class BaseClient
{
public:
    BaseClient( std::string _host, std::string _command );
    ~BaseClient();

    std::string run();

private:

    std::string key;
    std::string cert;

    std::string host;
    std::string command;

    BIO     *bio;
    SSL_CTX *ctx;
    SSL     *ssl;

    Logger  *logger;

    void initBaseClient();
    void initCTX();
    void initBio();
    void destroyBio();
    std::string connectToServer();
    std::string sendToServer();
    std::string recvFromServer();
    std::string intro();

};

}

#endif
