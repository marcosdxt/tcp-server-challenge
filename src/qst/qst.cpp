#include <qst.h>

QST::QST() {

}

std::vector<uint8_t> QST::decode(const std::vector<uint8_t> &args) {
    uint8_t message[4] = {"ola"};

    std::vector<uint8_t> result(message,message+4);

    return result;
}