#include <cstdlib>
#include <server.h>
#include <qst.h>

const int PORT = 8080;
const int MAX_EVENTS = 10;

int main() {
    QstServer *server;

    server = new QstServer(PORT, new QST(), MAX_EVENTS);
    if(!server)
        return -1;

    server->start();

    delete server;

    return 0;
}
