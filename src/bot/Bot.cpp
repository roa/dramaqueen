#include "Bot.hpp"

using namespace gloox;

namespace Dramaqueen
{

Bot::Bot()
{
    config = Config::getSingletonPtr();
    initXMPP();
}

Bot::~Bot()
{
}

void Bot::connectToXMPP()
{
    if( j->connect( false ) )
    {
        ConnectionError ce = ConnNoError;
        while( ce == ConnNoError )
        {
          ce = j->recv();
        }
    }
}

Client* Bot::getJ()
{
    return j;
}

void Bot::initXMPP()
{
    JID jid( config->getXmppUser() );

    j = new Client( jid, config->getXmppPasswd() );

    j->registerConnectionListener( this );
    j->registerMessageHandler( this );
    j->logInstance().registerLogHandler( LogLevelDebug, LogAreaAll, this );
}

void Bot::onConnect()
{

}

void Bot::onDisconnect( ConnectionError e )
{

}

bool Bot::onTLSConnect( const CertInfo& info )
{
    return true;
}

void Bot::handleMessage( const Message& stanza, MessageSession* session )
{
    if( !stanza.body().empty() )
    {
        BaseClient baseclient;
        std::string answer = baseclient.run();
        Message::MessageType type = Message::MessageType::Chat;
        Message msg( type, stanza.from(), answer );
        j->send( msg );
    }
}

void Bot::handleLog( LogLevel level, LogArea area, const std::string& message )
{
    //printf("log: level: %d, area: %d, %s\n", level, area, message.c_str() );
}

}
