#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cerrno>
#include <unistd.h>
#include <arpa/inet.h>
#include <server.h>

QstServer::QstServer(uint16_t port, RequestHandler *handler, uint16_t max_connections) {
  
  this->port = port;
  this->handler = handler;
  this->max_connections = max_connections;
}

void QstServer::socketInit(int &serverSocket) {

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket == -1) {
        perror("Erro ao criar o socket do servidor");
        exit(EXIT_FAILURE);
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);

    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        perror("Erro ao associar o socket ao endereço do servidor");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    if (listen(serverSocket, SOMAXCONN) == -1) {
        perror("Erro ao ouvir conexões");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    std::cout << "\n\n\n Dextro Embedded Solutions \n\n\n";
    std::cout << "Waiting connections on " << port << std::endl;
}

void QstServer::epollInit(int &epollFd, epoll_event &event, int serverSocket) {

    epollFd = epoll_create1(0);

    if (epollFd == -1) {
        perror("Erro ao criar o epoll");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    event.events = EPOLLIN | EPOLLET;
    event.data.fd = serverSocket;
    if (epoll_ctl(epollFd, EPOLL_CTL_ADD, serverSocket, &event) == -1) {
        perror("Erro ao adicionar o socket do servidor ao epoll");
        close(serverSocket);
        close(epollFd);
        exit(EXIT_FAILURE);
    }    
}

void QstServer::start() {
    int serverSocket;
    int epollFd;
    sockaddr_in serverAddress;
    epoll_event event;

    socketInit(serverSocket);
    epollInit(epollFd, event, serverSocket);

    std::vector<epoll_event> events(max_connections);

   for(;;) {

        int numEvents = epoll_wait(epollFd, events.data(), max_connections, -1);

        if (numEvents == -1) {
            perror("Erro em epoll_wait");
            break;
        }

        for (int i = 0; i < numEvents; ++i) {
            if (events[i].data.fd == serverSocket) {
                sockaddr_in clientAddress;
                socklen_t clientSize = sizeof(clientAddress);

                int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientSize);
                if (clientSocket == -1) {
                    perror("Erro ao aceitar a conexão do cliente");
                } else {
                    std::cout << "Nova conexão aceita. Socket do cliente: " << clientSocket << std::endl;

                    event.events = EPOLLIN | EPOLLET;
                    event.data.fd = clientSocket;
                    if (epoll_ctl(epollFd, EPOLL_CTL_ADD, clientSocket, &event) == -1) {
                        perror("Erro ao adicionar o socket do cliente ao epoll");
                        close(clientSocket);
                    }
                }
            } else {
                int clientSocket = events[i].data.fd;
                char buffer[1024];
                int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);

                if (bytesRead <= 0) {
                    if (bytesRead == 0) {
                        std::cout << "Cliente no socket " << clientSocket << " desconectado." << std::endl;
                    } else {
                        perror("Erro ao ler dados do cliente");
                    }

                    epoll_ctl(epollFd, EPOLL_CTL_DEL, clientSocket, nullptr);
                    close(clientSocket);
                } else {
                    buffer[bytesRead] = '\0';
                    std::cout << "Mensagem do cliente no socket " << clientSocket << ": " << buffer << std::endl;
                }
            }
        }
    }

    close(epollFd);
    close(serverSocket);  
}

