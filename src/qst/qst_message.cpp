#include <qst_message.h>
#include <string.h>

QSTmessage::QSTmessage() {

}

QSTmessage::~QSTmessage() {

}

QSTmessage::qstMessageType QSTmessage::getType() const {

    return (QSTmessage::qstMessageType)msg_type;
}

bool QSTmessage::isValidBuffer(uint8_t *buffer, uint16_t size) {


    if (size >= 4) {

        uint16_t len = buffer[0] | buffer[1] << 8;
        qstMessageType type = static_cast<qstMessageType>(buffer[2]);
        uint8_t sequence = buffer[3];

        if (type > QSTmessage::echo_response)
            return false;

        if (len != size)
            return false;

        switch (type){
        case QSTmessage::login_request:
            if (size != 68)
                return false;
            break;
        case QSTmessage::login_response:
            if (size != 6)
                return false;
            break;
        case QSTmessage::echo_response:
        case QSTmessage::echo_request:
        {
            if (size < 6)
                return false;

            uint16_t ln = buffer[5] | buffer[6] << 8;
            if ((ln + 4) != size)
                return false;
        }
        break;
        }

        return true;
    }

    return false;
}

void QSTmessage::exportHeader(uint8_t *buffer) {

    memcpy(buffer, &msg_size, 2);
    memcpy(&buffer[2], &msg_type, 1);
    memcpy(&buffer[3], &msg_sequence, 1);
}

uint8_t QSTmessage::getSequence() {

    return msg_sequence;
}

void QSTmessage::setSequence(uint8_t sequence) {

    msg_sequence = sequence;
}

QSTLoginRequest::QSTLoginRequest():QSTmessage() {

    this->msg_type = QSTmessage::login_request;
}

bool QSTLoginRequest::fromBuffer(uint8_t *buffer, uint16_t size) {

    if(!isValidBuffer(buffer,size))
      return false;

    userName.assign(reinterpret_cast<char*>(&buffer[4]), 32);
    password.assign(reinterpret_cast<char*>(&buffer[36]), 32);

    return true;
}
    
std::vector<uint8_t> QSTLoginRequest::toBuffer() {
    uint8_t buffer[64]={0};

    exportHeader(buffer);

    memcpy(&buffer[4], userName.data(), userName.size());
    memcpy(&buffer[36], password.data(), password.size());
    
    std::vector<uint8_t> result(buffer,buffer + 64);

    return result;
}

std::string QSTLoginRequest::getUserName() {

    return userName;
}

std::string QSTLoginRequest::getPassword() {
    
    return password;
}

QSTLoginResponse::QSTLoginResponse():QSTmessage() {

    this->msg_type = QSTmessage::login_response;
}

bool QSTLoginResponse::fromBuffer(uint8_t *buffer, uint16_t size) {

    if(!isValidBuffer(buffer, size))
      return false;

    status = static_cast<QSTLoginResponse::qstStatus>(buffer[5] | buffer[6]<<8);

    return true;
}
    
std::vector<uint8_t> QSTLoginResponse::toBuffer() {
    uint8_t buffer[6] = {0};
    
    msg_size = 6;

    exportHeader(buffer);

    uint16_t _status = status;
    memcpy(&buffer[4], &_status, 2);

    std::vector<uint8_t> result(buffer, buffer + 6);
    return result;
}

QSTmessage::qstStatus QSTLoginResponse::getStatus() {

    return this->status;
}

void QSTLoginResponse::setStatus(QSTmessage::qstStatus status) {

    this->status = status;
}

QSTEchoRequest::QSTEchoRequest():QSTmessage() {

    this->msg_type = QSTmessage::echo_request;
}

bool QSTEchoRequest::fromBuffer(uint8_t *buffer, uint16_t size) {

    if(!isValidBuffer(buffer,size))
      return false;

    uint16_t len = buffer[4] | buffer[5]<<8;

    message.assign(reinterpret_cast<char*>(&buffer[6]), len);

    return true;
}
    
std::vector<uint8_t> QSTEchoRequest::toBuffer() {
    uint16_t size = message.size();    
    uint8_t buffer[size + 6];

    msg_size = size;

    exportHeader(buffer);

    memcpy(&buffer[4], &size, 2);
    memcpy(&buffer[6], message.data(), message.size());    

    std::vector<uint8_t> result(buffer, buffer + 6);
    return result;    
}

QSTEchoResponse::QSTEchoResponse():QSTmessage() {

    this->msg_type = QSTmessage::echo_response;
}

bool QSTEchoResponse::fromBuffer(uint8_t *buffer, uint16_t size) {

    if(!isValidBuffer(buffer,size))
      return false;

    uint16_t len = buffer[4] | buffer[5]<<8;

    message.assign(reinterpret_cast<char*>(&buffer[6]), len);

    return true;
}
    
std::vector<uint8_t> QSTEchoResponse::toBuffer() {
    uint16_t size = message.size();    
    uint8_t buffer[size + 6];

    msg_size = size;

    exportHeader(buffer);

    memcpy(&buffer[4], &size, 2);
    memcpy(&buffer[6], message.data(), message.size());    

    std::vector<uint8_t> result(buffer, buffer + 6);
    return result;  
}

QSTmessage *QSTmessageFactory::create(uint8_t *buffer, uint16_t size) {
    QSTmessage *res = NULL;

    if(size >= 4) {
        switch(buffer[2]) {
            case QSTmessage::login_request:
                 res = new QSTLoginRequest();
                 res->fromBuffer(buffer, size);
                 return res;
            case QSTmessage::login_response:
                res =  new QSTLoginResponse();
                res->fromBuffer(buffer, size);
                return res;
            case QSTmessage::echo_request:
                res = new QSTEchoRequest();
                res->fromBuffer(buffer, size);
                return res;
            case QSTmessage::echo_response:
                res = new QSTEchoResponse();
                res->fromBuffer(buffer, size);
                return res;
            default: 
                return NULL;
        }
    }

    return NULL;
}

