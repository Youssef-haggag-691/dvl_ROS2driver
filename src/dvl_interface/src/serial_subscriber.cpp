#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "dvl_message/msg/serial_array.hpp"
#include "dvl_message/msg/dvl.hpp"


using std::placeholders::_1;

class Subscriber : public rclcpp::Node {
public:
    inline Subscriber();
private:
    inline void ShowMessage(dvl_message::msg::SerialArray::SharedPtr data);
    rclcpp::Subscription<dvl_message::msg::SerialArray>::SharedPtr subscriber_;
    rclcpp::Publisher<dvl_message::msg::DVL>::SharedPtr publisher_;
    float _t;
    float _vx;
    float _vy;
    float _vz;
    float _fom;
    float _alt;
    std::string _valid;
    std::string _status;
    void parse(std::string sentance);
    void publish(dvl_message::msg::SerialArray::SharedPtr packet);

};

Subscriber::Subscriber() : Node("serial_sub1"){
    std::string input_topic;
    this->declare_parameter<std::string>("input_topic", "RxSerial1");
    this->get_parameter("input_topic", input_topic);
    publisher_ = this->create_publisher<dvl_message::msg::DVL>("VelocityReport", 1 ); 
    subscriber_ = this->create_subscription<dvl_message::msg::SerialArray>(input_topic, 1, std::bind(&Subscriber::publish, this , _1)); //10
}

void Subscriber::ShowMessage(dvl_message::msg::SerialArray::SharedPtr data){
     RCLCPP_INFO(this->get_logger(), "I heard: '%s'",  data->data.c_str());
    
}
void Subscriber::parse(std::string sentance){
        // author : Mariam 

        char firstLetter = sentance.at(0);

        if(firstLetter == 'w'){

          if(sentance.length() < 3){
            std::cout<<"sentance is too short "<<std::endl;
            }

            else {
             int arr[8];
             int i;
             size_t found = 0;
             for(i=0;i<8;i++){
                found = sentance.find("," , found+1); 
                arr[i] = found;
                }
             std::string time = sentance.substr(arr[0]+1,arr[1]-arr[0]-1);
             std::stringstream geek(time);
             geek >> _t; 
             std::string vx = sentance.substr(arr[1]+1,arr[2]-arr[1]-1);
             std::stringstream vv(vx);
             vv >> _vx; 
             std::string vy = sentance.substr(arr[2]+1,arr[3]-arr[2]-1);
             std::stringstream vvy(vy);
             vvy >> _vy; 
             std::string vz = sentance.substr(arr[3]+1 , arr[4]-arr[3]-1);
             std::stringstream vvz(vz);
             vvz >> _vz; 
             std::string fom = sentance.substr(arr[4]+1,arr[5]-arr[4]-1);
             std::stringstream f(fom);
             f >> _fom; 
             std::string altitude = sentance.substr(arr[5]+1,arr[6]-arr[5]-1);
             std::stringstream a (altitude);
             a >> _alt; 
             std::string valid = sentance.substr(arr[6]+1,arr[7]-arr[6]-1);
             std::string status = sentance.substr(arr[7]+1,1);
             std::stringstream v(valid);
             v >> _valid;
             std::stringstream s(status);
             s >> _status;
            }  
        }

        else{
            std::cout<< "invalid format " <<std::endl;
            }

    }

    void Subscriber::publish(dvl_message::msg::SerialArray::SharedPtr packet)
    {
    RCLCPP_INFO(this->get_logger(), "I heard: '%s'",  packet->data.c_str());
    std::string buffer = packet->data;
    parse(buffer); 
     auto report = dvl_message::msg::DVL();
     report.time = _t;
     report.vx = _vx;
     report.vy = _vy;
     report.vz = _vz;
     report.altitude = _alt;
     report.fom = _fom;
     report.status = _status;
     report.valid = _valid;
     publisher_->publish(report);

    }


int main(int argc, char **argv){
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Subscriber>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    exit(0);
}




