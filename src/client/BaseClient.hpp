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

namespace Dramaqueen
{

class BaseClient
{
public:
    BaseClient();
    ~BaseClient();

    std::string run( std::string host, std::string command );

private:

    std::string key;
    std::string cert;
    //std::string host;

    BIO     *bio;
    SSL_CTX *ctx;
    SSL     *ssl;

    void initBaseClient();
};

}

#endif
