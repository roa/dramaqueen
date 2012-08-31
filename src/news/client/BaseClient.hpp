/**
    the baseclient is called to connect to dramaqueen nodes to execute
    commands invoked via daemons or xmpp interface.
    after that the baseclient reads the output from the node and
    delivers it to the main-dramaqueen node.
    to use baseclients, you have to enable the xmpp interface via config.
**/

#ifndef DRAMAQUEEN_CLIENT_HPP
#define DRAMAQUEEN_CLIENT_HPP

#include <iostream>
#include <string.h>
#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <sstream>
#include <sys/socket.h>
#include <netdb.h>
#include <fcntl.h>

#include "../../config/Config.hpp"
#include "../../helper/Helper.hpp"

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

    bool shouldRun;

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
