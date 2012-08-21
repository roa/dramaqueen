#include "BaseClient.hpp"

namespace Dramaqueen
{

BaseClient::BaseClient()
{
    initBaseClient();
}

BaseClient::~BaseClient()
{

}

std::string BaseClient::run( std::string host, std::string command )
{
    char rbuffer[4096];

    memset( rbuffer, '\0', sizeof( rbuffer ) );

    bio = BIO_new_ssl_connect( ctx );
    if( bio == NULL )
    {
        std::cout << "bio kaputt" << std::endl;
        return "Hup";
    }

    BIO_set_nbio( bio, 1 );

    BIO_get_ssl( bio, ssl );

    BIO_set_conn_hostname( bio, ( char * )host.c_str() );


    if( BIO_do_connect( bio ) <= 0 )
    {
        std::cout << "connect failed" << std::endl;
        if ( !BIO_set_close( bio, BIO_CLOSE ) )
        {
            std::cout << "basd" << std::endl;
        }
        BIO_free( bio );
        return "moep";
    }

    int r = BIO_write( bio, command.c_str(), command.size() );

    r = -1;
    while( r < 0 )
    {
        r = BIO_read( bio, rbuffer, sizeof( rbuffer ) );
        if( r == 0 )
        {
            continue;
        }
        if( r < 0 )
        {
            if( !BIO_should_retry( bio ) )
            {
                continue;
            }
        }
    }
    if ( !BIO_set_close( bio, BIO_CLOSE ) )
    {
        std::cout << "basd" << std::endl;
    }
    BIO_free( bio );
    return rbuffer;
}

void BaseClient::initBaseClient()
{
    cert = "/home/roa/programming/examples/ssl_conn/ssl_example/servercert.pem";
    key  = "/home/roa/programming/examples/ssl_conn/ssl_example/private.key";
    ctx  = NULL;
    ssl  = NULL;
    SSL_load_error_strings();
    SSL_library_init();
    ERR_load_BIO_strings();
    OpenSSL_add_all_algorithms();
    ctx = SSL_CTX_new(SSLv23_client_method());
    SSL_CTX_use_certificate_file( ctx, cert.c_str(), SSL_FILETYPE_PEM );
    SSL_CTX_use_PrivateKey_file( ctx, key.c_str(), SSL_FILETYPE_PEM );
}


}
