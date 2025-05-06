#include <cstdio>
#include <cstring>

#include <rclcpp/rclcpp.hpp>

#include "StmComm.hpp"
#include "custom_msg/srv/stcommand.hpp"

static STComm::SerialComm *pScomm = nullptr;

void SrvCommandHandler(const std::shared_ptr<custom_msg::srv::Stcommand::Request> request, std::shared_ptr<custom_msg::srv::Stcommand::Response> response) {
    if(pScomm == nullptr) {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "SerialComm isn't initialized");
        return;
    }

    STComm::SerialResponse* sr = nullptr;
    if(request->type == 0) {
        sr = pScomm->SendDeviceCommand((STComm::DeviceCommands)request->command);
    }
    else {
        sr = pScomm->SendCommand((STComm::Commands)request->command, request->arg);
    }

    if(sr == nullptr) {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "SerialComm gave an empty answer");
        return;
    }
    mempcpy(&(response->response), sr, sizeof(STComm::SerialResponse));
    delete sr;
}

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("stm_comm_server");
    STComm::SerialComm sc("/dev/ttyACM0");
    pScomm = &sc;

    rclcpp::Service<custom_msg::srv::Stcommand>::SharedPtr service = node->create_service<custom_msg::srv::Stcommand>("send_stm_commands",  &SrvCommandHandler);
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to receive commands");

    rclcpp::spin(node);
    rclcpp::shutdown();
}
