#include "BaseServer.hpp"

namespace Dramaqueen
{

BaseServer::BaseServer()
{
    logger = Logger::getSingletonPtr();
    initServer();
}

BaseServer::~BaseServer()
{
    SSL_CTX_free( ctx );
}

void BaseServer::initServer()
{
    SSL_library_init();
    ERR_load_BIO_strings();
    ERR_load_SSL_strings();
    cert = Config::getSingletonPtr()->getSSLCert();
    key  = Config::getSingletonPtr()->getSSLKey();
    host = Config::getSingletonPtr()->getBind();
    /**
        TODO:
        check return values
    **/
    ctx = SSL_CTX_new(SSLv3_server_method());
    SSL_CTX_use_certificate_file(ctx, cert.c_str(), SSL_FILETYPE_PEM);
    SSL_CTX_use_PrivateKey_file(ctx, key.c_str(), SSL_FILETYPE_PEM);
    abio = BIO_new_accept( ( char * ) host.c_str() );
    if( abio == NULL )
    {
        abort();
    }
    BIO_set_nbio( abio, 0 );
}

void BaseServer::handleClient()
{
    int cfd = BIO_get_fd( client, NULL );
    int r;
    char rbuf[4096];
    std::string tempstr;

    memset( rbuf, '\0', sizeof(rbuf) );

    tempstr.append( rbuf );

    do
    {
        r = SSL_read( ssl, rbuf, sizeof( rbuf ) - 1 );
        if( r < 0 )
        {
            break;
        }
        if( r == 0 )
        {
            break;
        }
        else
        {
            rbuf[r] = '\0';
            tempstr.append( rbuf );
        }
    } while( SSL_pending( ssl ) );

    if( !tempstr.empty() )
    {
        std::string dir = Config::getSingletonPtr()->getScriptDir();
        dir.append( tempstr );
        std::ifstream fileCheck( dir );
        if( fileCheck.good() )
        {
            std::string buffer = executeScript( tempstr );
            if( !buffer.empty() )
            {
                int w = SSL_write( ssl, buffer.c_str(), buffer.size() );
                if( w <= 0 )
                {
                    /**
                        TODO:
                        do something useful on failure
                    **/
                    std::cout << SSL_get_error( ssl, w ) << std::endl;
                }
            }
            else
            {
                close( cfd );
            }
        }
        else
        {
            logger->log( "did not find file: ", tempstr );
        }
    }
    close( cfd );
}

void BaseServer::run()
{
    if( BIO_do_accept( abio ) <= 0 )
    {
        abort();
    }

    fd_set fds;

    int afd = BIO_get_fd( abio,NULL );

    /**
        TODO:
        replace true with abort condition
        from sighandler
    **/
    while( true )
    {
        FD_ZERO( &fds );
        FD_SET( afd, &fds );

        select( afd+1, &fds, NULL, NULL, NULL );

        if( FD_ISSET( afd, &fds ) && BIO_do_accept( abio ) > 0 )
        {
            client = BIO_pop( abio );
            ssl = SSL_new( ctx );
            SSL_set_accept_state( ssl );
            SSL_set_bio( ssl, client, client );
            SSL_accept( ssl );
            handleClient();
            SSL_shutdown(ssl);
            SSL_free(ssl);
        }
    }
}

std::string BaseServer::executeScript( std::string script )
{
    std::string myScriptFolder = Config::getSingletonPtr()->getScriptDir();
    myScriptFolder.append( script.c_str() );
    FILE* pipe = popen( myScriptFolder.c_str(), "r" );
    if ( !pipe ) return "ERROR";
    char buffer[128];
    std::string result = "";
    while( !feof( pipe ) )
    {
        if( fgets( buffer, 128, pipe ) != NULL )
            result += buffer;
    }
    pclose( pipe );
    return result;
}

}
