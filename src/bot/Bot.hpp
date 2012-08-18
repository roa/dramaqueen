#ifndef DRAMAQUEEN_BOT_HPP
#define DRAMAQUEEN_BOT_HPP

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <thread>

#include <gloox/client.h>
#include <gloox/loghandler.h>
#include <gloox/messagehandler.h>
#include <gloox/connectionlistener.h>
#include <gloox/message.h>

#include "../config/Config.hpp"

using namespace gloox;

namespace Dramaqueen
{

class Bot : public MessageHandler, LogHandler, ConnectionListener
{
public:
    Bot();

    ~Bot();

    void connectToXMPP();
    Client* getJ();

private:
   Client* j;

   Config* config;

   void initXMPP();
   virtual void onConnect();
   virtual void onDisconnect( ConnectionError e );
   virtual bool onTLSConnect( const CertInfo& info );
   virtual void handleMessage( const Message& stanza, MessageSession* session = 0 );
   virtual void handleLog( LogLevel level, LogArea area, const std::string& message );
};

}
#endif
