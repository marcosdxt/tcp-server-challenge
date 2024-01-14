#include <qst.h>
#include <qst_message.h>
#include <string.h>
#include <iostream>

QST::QST() {

}

std::vector<uint8_t> QST::decode(const std::vector<uint8_t> &args) {
    QSTmessage *payload = QSTmessageFactory::create((uint8_t*)args.data(),args.size());
    std::vector<uint8_t> result;

    if(payload) {

        switch(payload->getType()) {
            case QSTmessage::login_request: {
                    QSTLoginRequest *loginRequest = reinterpret_cast<QSTLoginRequest*>(payload);
                    std::cout << "New login request for user:" << loginRequest->getUserName() << ",password: " << loginRequest->getPassword();

                    QSTLoginResponse response;

                    response.setSequence(payload->getSequence());
                    response.setStatus(QSTmessage::OK);

                    result = response.toBuffer();
                }
                break;
            case QSTmessage::echo_request:
                break;
        }

        delete payload;

    }

    return result;
} 

// login
// echo -n "44000001 6d6172636f730000000000000000000000000000000000000000000000000000 3132333400000000000000000000000000000000000000000000000000000000" | xxd -r -p | nc localhost 8080

