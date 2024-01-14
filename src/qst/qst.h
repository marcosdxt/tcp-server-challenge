#ifndef _QST_H_
#define _QST_H_

#include <server.h>

class QST: public RequestHandler {

public:
    QST();
    std::vector<uint8_t> decode(const std::vector<uint8_t> &args);

};




#endif// _QST_H_