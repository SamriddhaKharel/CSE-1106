// Chat Network Application
// Jason Losh

//-----------------------------------------------------------------------------
// Compile notes for C99 code
//-----------------------------------------------------------------------------

// gcc -std=c99 -o chat chat.c udp.c

//-----------------------------------------------------------------------------
// Device includes, defines, and assembler directives
//-----------------------------------------------------------------------------

#include <stdlib.h>          // EXIT_ codes
#include <stdbool.h>         // bool
#include <stdio.h>           // printf, scanf
#include <string.h>          // strlen, strcmp

#include "udp.h"

#define SERVER_LISTENER_PORT 4096
#define CLIENT_LISTENER_PORT 4097

#define MAX_CHARS_PER_MESSAGE 80

//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    char *remoteIp;
    char *mode;
    int remotePort;

    char str[MAX_CHARS_PER_MESSAGE+1];
    bool quit = false;

    bool sendMode;

    // Verify arguments are good
    bool goodArguments = (argc == 3);
    if (goodArguments)
    {
        remoteIp = argv[1];
        mode = argv[2];
        goodArguments = (strcmp(mode, "server") == 0) || (strcmp(mode, "client") == 0);
    }
    if (!goodArguments)
    {
        printf("usage: chat IPV4_ADDRESS MODE\n");
        printf("  where:\n");
        printf("  IPV4_ADDRESS is address of the remote machine\n");
        printf("  MODE is either client or server\n");
        exit(EXIT_FAILURE);
    }

    // Determine if client or server
    bool client = strcmp(mode, "client") == 0;
    bool client1 = strcmp(mode, "server") == 0;

    // TODO: Open listener port number dependent on client/server role   
    if (client)
    {
        openListenerPort(remoteIp, 4097);
    }
    else
    {
        openListenerPort(remoteIp, 4096);
    }

    // TODO: Determine remote port that you will send data to
    //       If you are server, send to client port, and vice versa
    if (client)
    {
        remotePort = 4096;
    }
    else
    {
        remotePort = 4097;
    }
    // TODO: Determine if it is your turn to send data or not,
    //       based on server or client mode
    if (client)
        sendMode = 1;
    if (client1)
        sendMode = 0;
    // Start chat loop, alternating between sending and receiving messages
    while(!quit)
    {
        // send text
        if (sendMode)
        {
            // TODO: Add code to get string from user and send
            
            printf("TX: ");
            scanf("%s", str); 
            sendData(remoteIp, remotePort, str);
            // TODO: Handle an error is sendData returns false
            // TODO: Leave while loop if QUIT was sent
            if(strcmp(str, "QUIT") == 0)
                quit = 1;        
        }
        // wait for text
        else
        {
            // TODO: Add code to wait for a string from remote user
            receiveData(str, 80);
            printf("RX: %s\n", str);
            // TODO: Leave while loop if QUIT is received
            if(strcmp(str, "QUIT") == 0)
            quit = 1;            
        }
        // alternate between send and receive mode
        sendMode = !sendMode;
    }

    // TODO: Close listener port
    closeListenerPort();
    return EXIT_SUCCESS;
}
