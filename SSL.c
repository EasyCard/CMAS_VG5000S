/* ------------------------------------------------------------ *
 * file:        sslconnect.c                                    *
 * purpose:     Example code for building a SSL connection and  *
 *              retrieving the server certificate               *
 * author:      06/12/2012 Frank4DD                             *
 *                                                              *
 * gcc -lssl -lcrypto -o sslconnect sslconnect.c                *
 * ------------------------------------------------------------ */
/*#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include <openssl/rand.h>
#include <openssl/ssl.h>
#include <openssl/err.h>*/

#include <sys/socket.h>
#include <resolv.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/x509.h>
#include <openssl/x509_vfy.h>
#include "gvar.h"
#include "ssl.h"
#include "ECCAPP.h"


int SSLTEST()
{
    SSL *ssl;
    SSL_CTX *ctx;
    BIO *bio;
    int x;
    int size=0;
  unsigned char  SendPack[1024];
  memset(SendPack,0x00,1024);
 USHORT ret= usReadFileData(SendFile,&size,&SendPack);
  if(ret!=d_OK) return ret;
   // char *request = "GET / HTTP/1.1\r\nHost: www.verisign.com\r\nConnection: Close\r\n\r\n";
    char buf[1024];
    /* Initializing OpenSSL */
    SSL_load_error_strings();
    ERR_load_BIO_strings();
    OpenSSL_add_all_algorithms();
    /* create and set up SSL context */
    ctx = SSL_CTX_new(TLSv1_client_method());
    /* load trust store */

    /* create and set up connect */
    bio = BIO_new_ssl_connect(ctx);
    /* set SSL_MODE_AUTO_RETRY flag */
    BIO_get_ssl(bio, &ssl);
    SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);
    /* Attempt to connect */
    BIO_set_conn_hostname(bio,  "192.168.2.4:7010");
    /* Verify the connection opened and perform the handshake */
    if(BIO_do_connect(bio) <= 0)
    {
        printf("connect error.\n");
        SSL_CTX_free(ctx);
        BIO_free_all(bio);
        return -1;
    }
    /* check cert */
    if(SSL_get_verify_result(ssl) != X509_V_OK)
    {
        printf("cert is not match.\n");
        SSL_CTX_free(ctx);
        BIO_free_all(bio);
        return -1;
    }

    /* send request */
    BIO_write(bio, SendPack, strlen(size));
 
    /* read the response */
    for (;;)
    {
        x = BIO_read(bio, buf, strlen(buf)-1);
        if (x <= 0)
         break;
        buf[x] = 0;
        printf("%s\n", buf);
    }
    BIO_free_all(bio);
    SSL_CTX_free(ctx);
    return 0;
}








BYTE *SSLRead2 (SSL *ssl )
{
  const int readSize = 1024;
  char *rc = NULL;
  int received, count = 0;
  char buffer[1024];

  if (ssl)
    {
      while (1)
        {
          if (!rc)
            rc = malloc (readSize * sizeof (char) + 1);
          else
            rc = realloc (rc, (count + 1) *
                          readSize * sizeof (char) + 1);

          received = SSL_read (ssl, buffer, received);
          buffer[received] = '\0';

          if (received > 0)
            strcat (rc, buffer);

          if (received < readSize)
            break;
          count++;
        }
    }
  
  return rc;
}

/////////////////////////////////////////////////////////////////////////////////////////////



// Simple structure to keep track of the handle, and
// of what needs to be freed later.
typedef struct {
    int socket;
    SSL *sslHandle;
    SSL_CTX *sslContext;
} connection;

// For this example, we'll be testing on openssl.org
#define SERVER  "192.168.2.4"
#define PORT 7020

// Establish a regular tcp connection
int tcpConnect ()
{
  int error, handle;
  struct hostent *host;
  struct sockaddr_in server;
  CTOS_EthernetOpenEx();  
  host = gethostbyname (SERVER);
  handle = socket (AF_INET, SOCK_STREAM, 0);
  if (handle == -1)
    {
      perror ("Socket");
      handle = 0;
    }
  else
    {
      server.sin_family = AF_INET;
      server.sin_port = htons (PORT);
      server.sin_addr = *((struct in_addr *) host->h_addr);
      bzero (&(server.sin_zero), 8);

      error = connect (handle, (struct sockaddr *) &server,
                       sizeof (struct sockaddr));
      if (error == -1)
        {
          perror ("Connect");
          handle = 0;
        }
    }

  return handle;
}

// Establish a connection using an SSL layer
connection *sslConnect (void)
{
  connection *c;

  c = malloc (sizeof (connection));
  c->sslHandle = NULL;
  c->sslContext = NULL;

  c->socket = tcpConnect ();
  if (c->socket)
    {
      // Register the error strings for libcrypto & libssl
      SSL_load_error_strings ();
      // Register the available ciphers and digests
      SSL_library_init ();
 //     SSL_CTX_set_verify( tlsctx, SSL_VERIFY_PEER, verify_callback );
      // New context saying we are a client, and using SSL 2 or 3
    c->sslContext = SSL_CTX_new (TLSv1_client_method ());
   //   c->sslContext = SSL_CTX_new (TLSv1_client_method());
      if (c->sslContext == NULL)
        ERR_print_errors_fp (stderr);

      // Create an SSL struct for the connection
      c->sslHandle = SSL_new (c->sslContext);
      if (c->sslHandle == NULL)
        ERR_print_errors_fp (stderr);

      // Connect the SSL struct to our connection
      if (!SSL_set_fd (c->sslHandle, c->socket))
        ERR_print_errors_fp (stderr);

      // Initiate SSL handshake
      if (SSL_connect (c->sslHandle) != 1)
        ERR_print_errors_fp (stderr);
    }
  else
    {
      perror ("Connect failed");
    }

  return c;
}

// Disconnect & free connection struct
void sslDisconnect (connection *c)
{
  if (c->socket)
    close (c->socket);
  if (c->sslHandle)
    {
      SSL_shutdown (c->sslHandle);
      SSL_free (c->sslHandle);
    }
  if (c->sslContext)
    SSL_CTX_free (c->sslContext);

  free (c);
}

// Read all available text from the connection
char *sslRead (connection *c)
{
  const int readSize = 1024;
  char *rc = NULL;
  int received, count = 0;
  char buffer[1024];

  if (c)
    {
      while (1)
        {
          if (!rc)
            rc = malloc (readSize * sizeof (char) + 1);
          else
            rc = realloc (rc, (count + 1) *
                          readSize * sizeof (char) + 1);

          received = SSL_read (c->sslHandle, buffer, readSize);
          buffer[received] = '\0';

          if (received > 0)
              memcpy(rc,buffer,received);
          //  strcat (rc, buffer);

          if (received < readSize)
            break;
          count++;
        }
    }
   usWriteFile(RecvFile,rc,received);
  return rc;
}

// Write text to the connection
int sslWrite (connection *c, unsigned char *buf,int size)
{
  int ret;
  if (c)
        ret=SSL_write (c->sslHandle, buf,size);
  return  ret;
}

// Very basic main: we send GET / and print the response.
int SSLSendandRecv ()
{
  connection *c;
  char *response;
  BYTE recvbuf[1024];
  c = sslConnect ();
  int size=0;
  unsigned char  SendPack[1024];
  memset(SendPack,0x00,sizeof(SendPack));
  USHORT   ret=usReadFileData(SendFile,&size,(BYTE *)&SendPack);
  if(ret!=d_OK) return ret;
  
  
  int iret=sslWrite (c, SendPack,size);
  
  response = sslRead (c);
 
  sslDisconnect (c);
  free (response);

  return 0;
}