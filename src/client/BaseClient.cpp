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

std::string BaseClient::run()
{
    char * host_and_port = (char *)host.c_str();
    char rbuffer[4096];
    char buffer[] = "test!";
    int length = sizeof( buffer );
    memset( rbuffer, '\0', sizeof(rbuffer));

    bio = BIO_new_ssl_connect(ctx);
    BIO_get_ssl(bio, ssl);
    BIO_set_conn_hostname(bio, host_and_port);
    /*int r =*/ BIO_write(bio, buffer, length);

//    while (r < 0) {

       /* r =*/ BIO_read(bio, rbuffer, sizeof(rbuffer));
/*        std::cout << "test" << std::endl;
        if (r == 0) {

            //print_ssl_error("Reached the end of the data stream.\n", stdout);
            continue;

        } else if (r < 0) {

            if (!BIO_should_retry(bio)) {

                //print_ssl_error("BIO_read should retry test failed.\n", stdout);
                continue;
            }


        }


    };*/

    std::cout << buffer << std::endl;
    BIO_free(bio);
    return buffer;
}

void BaseClient::initBaseClient()
{
    cert = "/home/roa/programming/examples/ssl_conn/ssl_example/servercert.pem";
    key  = "/home/roa/programming/examples/ssl_conn/ssl_example/private.key";
    host = "localhost:9898";
    ctx = NULL;
    ssl = NULL;
    SSL_load_error_strings();
    SSL_library_init();
    ERR_load_BIO_strings();
    OpenSSL_add_all_algorithms();
    ctx = SSL_CTX_new(SSLv23_client_method());
    SSL_CTX_use_certificate_file(ctx, cert.c_str(), SSL_FILETYPE_PEM);
    SSL_CTX_use_PrivateKey_file(ctx, key.c_str(), SSL_FILETYPE_PEM);
}

}
