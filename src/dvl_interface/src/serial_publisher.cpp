#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "dvl_message/msg/serial_array.hpp"
#include "Serial.hpp"


using std::placeholders::_1;
typedef unsigned char uint8_t;

Serial serial; //Serial port instance

class Publisher : public rclcpp::Node{
public:
    inline Publisher();
    inline void publish(std::string num);
private:
    rclcpp::Publisher<dvl_message::msg::SerialArray>::SharedPtr publisher_;

};

Publisher::Publisher() : Node("serial1"){
    std::string input_topic;
    std::string output_topic;
    this->declare_parameter<std::string>("Port", "/dev/ttyUSB1");
    this->declare_parameter<std::int64_t>("Baud_Rate",115200); //9600
    this->declare_parameter<std::string>("Input_Topic", "TxSerial1");
    this->declare_parameter<std::string>("Output_Topic", "RxSerial1");
    this->get_parameter("Output_Topic", output_topic);
    this->get_parameter("Input_Topic", input_topic);
    publisher_ = this->create_publisher<dvl_message::msg::SerialArray>(output_topic, 1 ); //10

}

void Publisher::publish(std::string num){
    auto message = dvl_message::msg::SerialArray();
    message.data = num;
    publisher_->publish(message);
}




int main(int argc, char **argv){
    std::string port_name;
    //Serial serial;
    unsigned int baud_rate;
    std::vector<unsigned char> buffer ;

    rclcpp::init(argc, argv);
    auto node = std::make_shared<Publisher>();

    node->get_parameter("Port", port_name);
    node->get_parameter("Baud_Rate", baud_rate);

    if(!serial.open(port_name, baud_rate)){
        RCLCPP_ERROR(node->get_logger(), "couldn't open serial port, \"%s\"", port_name.c_str());
        rclcpp::shutdown();
        //return -1;
        exit(-1);
    }

    //rclcpp::spin(node);

    while(rclcpp::ok()){
        buffer = serial.read();
        std::string sentance (buffer.begin(), buffer.end() );
        node->publish(sentance);
        RCLCPP_DEBUG(node->get_logger(), "published");
        rclcpp::spin_some(node);
    }
    //serial.close();
    //rclcpp::shutdown();
    exit(0);
}
