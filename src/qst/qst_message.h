#ifndef _QST_TYPES_H_
#define _QST_TYPES_H_

#include <stdint.h>
#include <vector>
#include <string>

/*******************************************************************************
 * Base payload
*******************************************************************************/
class QSTmessage {

public:
    enum qstMessageType {
        login_request  = 0,
        login_response = 1,
        echo_request   = 2,
        echo_response  = 3
    };

    enum qstStatus {
        FAILED = 0,
        OK = 1
    };

    QSTmessage();

    ~QSTmessage();

    virtual bool fromBuffer(uint8_t *buffer, uint16_t size) = 0;
    
    virtual std::vector<uint8_t> toBuffer() = 0;

    QSTmessage::qstMessageType getType() const;

    uint8_t getSequence();

    void setSequence(uint8_t sequence);

protected:
    qstMessageType type;
    uint16_t msg_size;
    uint8_t msg_type;
    uint8_t msg_sequence;

    bool isValidBuffer(uint8_t *buffer, uint16_t size);

    void exportHeader(uint8_t *buffer);
};

/*********************************************************************************
 * Login request payload
*********************************************************************************/
class QSTLoginRequest: public QSTmessage {

public:
    QSTLoginRequest();

    bool fromBuffer(uint8_t *buffer, uint16_t size);
    
    std::vector<uint8_t> toBuffer();

    std::string getUserName();

    std::string getPassword();
    
private:
    std::string userName;
    std::string password;

};

/*********************************************************************************
 * Login response payload
*********************************************************************************/
class QSTLoginResponse: public QSTmessage {

public:
    QSTLoginResponse();

    bool fromBuffer(uint8_t *buffer, uint16_t size);
    
    std::vector<uint8_t> toBuffer();    

    QSTmessage::qstStatus getStatus();

    void setStatus(QSTmessage::qstStatus status);

private:    
    qstStatus status;
};

/*********************************************************************************
 * Echo request payload
*********************************************************************************/
class QSTEchoRequest: public QSTmessage {

public:
    QSTEchoRequest();

    bool fromBuffer(uint8_t *buffer, uint16_t size);
    
    std::vector<uint8_t> toBuffer();    

private:
    std::string message;    
};


/*********************************************************************************
 * Echo response payload
*********************************************************************************/
class QSTEchoResponse: public QSTmessage {

public:
    QSTEchoResponse();

    bool fromBuffer(uint8_t *buffer, uint16_t size);
    
    std::vector<uint8_t> toBuffer();    

private:
    std::string message;    
};

/*********************************************************************************
 * Echo response payload
*********************************************************************************/
class QSTmessageFactory {

public:
    static QSTmessage *create(uint8_t *buffer, uint16_t size);
};


#endif//_QST_TYPES_H_