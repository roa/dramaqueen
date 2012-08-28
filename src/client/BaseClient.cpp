#include "BaseClient.hpp"

namespace Dramaqueen
{

BaseClient::BaseClient( std::string _host, std::string _command ) :
    host( _host ), command( _command )
{
    logger = Logger::getSingletonPtr();
    initBaseClient();
}

BaseClient::~BaseClient()
{

}

std::string BaseClient::run()
{
    std::string response;
    response.append( connectToServer() );
    if( !response.empty() )
    {
        return response;
    }
    response.append( sendToServer() );
    if( !response.empty() )
    {
        return response;
    }
    /**
        TODO:
        add handling if returned message is empty
    **/
    response.append( intro() );
    response.append( recvFromServer() );

    destroyBio();

    return response;
}

void BaseClient::initBaseClient()
{
    ssl  = NULL;
    SSL_load_error_strings();
    SSL_library_init();
    ERR_load_BIO_strings();
    OpenSSL_add_all_algorithms();
    initCTX();
    initBio();
}

void BaseClient::initCTX()
{
    /**
        TODO:
        check return values
    **/
    ctx  = NULL;
    cert = Config::getSingletonPtr()->getSSLCert();
    key  = Config::getSingletonPtr()->getSSLKey();
    ctx = SSL_CTX_new(SSLv23_client_method());
    SSL_CTX_use_certificate_file( ctx, cert.c_str(), SSL_FILETYPE_PEM );
    SSL_CTX_use_PrivateKey_file( ctx, key.c_str(), SSL_FILETYPE_PEM );
}

void BaseClient::initBio()
{
    bio = BIO_new_ssl_connect( ctx );

    if( bio == NULL )
    {
        logger->log( "could not initialize bio" );
    }
    /**
        TODO:
        check return values
    **/
    BIO_get_ssl( bio, ssl );
    BIO_set_conn_hostname( bio, ( char * )host.c_str() );
}

void BaseClient::destroyBio()
{
    if ( !BIO_set_close( bio, BIO_CLOSE ) )
    {
        logger->log( "setting close flag n BaseClient failed" );
    }
    BIO_free( bio );
}

std::string BaseClient::connectToServer()
{
    std::stringstream answer;
    if( BIO_do_connect( bio ) <= 0 )
    {
        logger->log( "connect failed" );
        /**
        TODO: remove this crap

        FILE * mystream = fopen( "/tmp/rand", "w+");
        fclose( mystream );
        **/
        ERR_print_errors_fp( stderr );

        if ( !BIO_set_close( bio, BIO_CLOSE ) )
        {
            logger->log( "setting close flag n BaseClient failed" );
        }
        BIO_free( bio );
        answer  <<  std::endl << intro()
                << "Could not connect to server: "
                <<  host << std::endl;
    }
    return answer.str();
}

std::string BaseClient::sendToServer()
{
    std::stringstream answer;

    if( BIO_write( bio, command.c_str(), command.size() ) <= -1 )
    {
        logger->log( "send to server failed: ", host );
        answer  << std::endl << intro()
                << "send to server "
                << host
                << " failed";
    }

    return answer.str();
}

std::string BaseClient::recvFromServer()
{
    std::string answer = "";
    char rbuffer[4096];
    memset( rbuffer, '\0', sizeof( rbuffer ) );
    int r = -1;
    while( r < 0 )
    {
        r = BIO_read( bio, rbuffer, sizeof( rbuffer ) );
        if( r > 0 )
        {
            answer.append( rbuffer );
        }
        if( r == 0 )
        {
            break;
        }
        if( r < 0 )
        {
            if( !BIO_should_retry( bio ) )
            {
                break;
            }
        }
    }
    return answer;
}

std::string BaseClient::intro()
{
    std::stringstream intro;
    intro << std::endl << "Report from "
          << host      << ":" << std::endl;
    return intro.str();
}

}
