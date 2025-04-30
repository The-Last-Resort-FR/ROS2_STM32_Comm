#include "StmComm.hpp"

namespace STComm {
    SerialComm::SerialComm(std::string busPath) {
        mPort = new SerialPort(busPath);
        mPort->SetBaudRate(BaudRate::BAUD_1152000);
        mPort->SetCharacterSize(CharacterSize::CHAR_SIZE_8);
        mPort->SetFlowControl(FlowControl::FLOW_CONTROL_NONE);
        mPort->SetParity(Parity::PARITY_NONE);
        mPort->SetStopBits(StopBits::STOP_BITS_1);
    }
    
    SerialComm::~SerialComm() {
        mPort->Close();
        delete mPort;
    }
    
    SerialResponse* SerialComm::SendDeviceCommand(DeviceCommands c) {
        DataBuffer request;
        DataBuffer response;
        request.push_back(c);
        mPort->Write(request);
        mPort->Read(response);
        try {
            return VecToSerialResponse(response);
        }
        catch (std::exception& e) {
            std::cout << "exception caught in serial communication: " << e.what() << std::endl;
            return nullptr;
        }
    
    }
    
    SerialResponse* SerialComm::SendCommand(Commands c, uint16_t arg) {
        DataBuffer request;
        DataBuffer response;
        request.push_back(c >> 8 & 0x00FF);
        request.push_back(c & 0x00FF);
        request.push_back(arg >> 8 & 0x00FF);
        request.push_back(arg & 0x00FF);
    
        mPort->Write(request);
        mPort->Read(response);
        try {
            return VecToSerialResponse(response);
        }
        catch (std::exception& e) {
            std::cout << "exception caught in serial communication: " << e.what() << std::endl;
            return nullptr;
        }
    }
    
    SerialResponse* SerialComm::VecToSerialResponse(const std::vector<uint8_t>& v) {
        if(v.size() != 9) throw std::runtime_error("Invalid response size");
        SerialResponse* s = new SerialResponse;
        uint8_t* repArray = (uint8_t*)s;
        for(uint8_t i = 0; i < 9; i++) {
            repArray[i] = v.data()[i];
        }
        return s;
    }

    StmComm::StmComm(std::string busPath): SerialComm(busPath) {

    }

    StmComm::~StmComm() {

    }

    bool StmComm::SetTrigFrequ(uint16_t f) {
        (void)f;
        return COMM_OK;
    }

    bool StmComm::StartTrig() {
        return COMM_OK;
    }

    bool StmComm::StopTrig() {
        return COMM_OK;
    }

    uint16_t StmComm::GetTrigFreq() {
        return 0;
    }

    bool StmComm::GetTrigStatus() {
        return COMM_OK;
    }
}