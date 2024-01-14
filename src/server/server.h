#ifndef _SERVER_H_
#define _SERVER_H_

#include <vector>
#include <stdint.h>
#include <sys/epoll.h>

class RequestHandler {

public:    
    virtual std::vector<uint8_t> decode(const std::vector<uint8_t> &args) = 0;

};


class QstServer {

public:    
    QstServer(uint16_t port, RequestHandler *handler, uint16_t max_connections=100);
    void start();    

private:
    uint16_t port;
    uint16_t max_connections;
    RequestHandler *handler;

    void socketInit(int &serverSocket);
    void epollInit(int &epollFd, epoll_event &event, int serverSocket);
};


#endif//_SERVER_H_