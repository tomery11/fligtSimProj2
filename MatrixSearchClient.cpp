//
// Created by t on 1/15/19.
//

#include "MatrixSearchClient.h"
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <iostream>
#include <cstring>
#include <string>

void *threadFunc(void *data) {
    try {
        Data *data1;
        data1 = (Data *) data;

        //int portno;
        ssize_t n;
        struct sockaddr_in serv_addr;
        struct hostent *server;

        char buffer[256];

        /* Create a socket point */
        int sockfd = socket(AF_INET, SOCK_STREAM, 0);

        if (sockfd < 0) {
            throw "socket creation failed";
        }

        server = gethostbyname(data1->ipAddress.c_str());

        if (server == NULL) {
            throw "bad host name";
        }

        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
        serv_addr.sin_port = htons((uint16_t)data1->port);

        /* Now connect to the server */
        while (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
            sleep(1);
        }
        //send the message

        memset(buffer, 0, 256);
        strcpy(buffer, data1->messsage.c_str());
        /* Send message to the server */
        n = write(sockfd, buffer, strlen(buffer));

        if (n < 0) {
            throw "write to socket failed";
        }
        cout << "sent: " << data1->messsage << endl;
        //read server response
        memset(buffer, 0, 256);
        n = read(sockfd, buffer, 255);

        if (n < 0) {
            throw "reading from socket failed";
        }
        printf("%s\n", buffer);

        close(sockfd);

    } catch (char const *exception) {
        printf("%s",exception);
    }
}

void MatrixSearchClient::open(string ipAddress, int port, string messsage) {
    //create a thread to talk with each client, one after the other
    //pthread_t threadID;
    this->data = new Data;
    data->port = port;
    data->messsage = messsage;
    data->ipAddress = ipAddress;

    //start the thread
    //int rc = pthread_create(&threadID, NULL, serverThreadFunc, (void *)serverData);
    int rc = pthread_create(&this->threadID, nullptr, threadFunc, (void *)data);
    if (rc) {
        throw "unable to create thread";
    }
}

MatrixSearchClient::~MatrixSearchClient() {
    //close the thread
    void *res;
    int s = pthread_join(threadID, &res);
    cout << "back from join client" << endl;
    if (s != 0) {
        throw "error in join thread";
    }
    //free memory allocated by thread
    //free(res);
    cout << "after free memory thread" << endl;
    delete this->data;
    this->data = nullptr;
    cout << "end of client" << endl;
}
