#include <memory>
#include <chrono>
#include <functional>
#include <string>
#include <sstream>
#include <vector>
#include "rclcpp/rclcpp.hpp"
#include "dvl_message/msg/dvl.hpp"

using std::placeholders::_1;

class Subscriber : public rclcpp::Node {
public:
    inline Subscriber();

private:
    inline void ShowMessage(dvl_message::msg::DVL::SharedPtr data);
    rclcpp::Subscription<dvl_message::msg::DVL>::SharedPtr subscriber_; 

};

Subscriber::Subscriber() : Node("a50_dvl_sub"){
    std::string dvl_topic;
    this->declare_parameter<std::string>("Dvl_Topic", "VelocityReport");

    this->get_parameter("Dvl_Topic", dvl_topic);
    subscriber_ = this->create_subscription<dvl_message::msg::DVL>(dvl_topic, 1, std::bind(&Subscriber::ShowMessage, this , _1)); //10
}

void Subscriber::ShowMessage(dvl_message::msg::DVL::SharedPtr data){

    std::ostringstream tt;
    tt << data->time ;
    std::string t (tt.str());

    std::ostringstream Vxx;
    Vxx << data->vx ;
    std::string Vx (Vxx.str());

    std::ostringstream Vyy;
    Vyy << data->vy ;
    std::string Vy (Vyy.str());

    std::ostringstream Vzz;
    Vzz << data->vz ;
    std::string Vz (Vzz.str());

    std::ostringstream altt;
    altt << data->altitude ;
    std::string r (altt.str());
  
   std::string v  = data->valid;
    

    std::string dataString = "time: " +t +","+"Vx: "+Vx+","+"Vy: "+Vy+","+"Vz: "+Vz+","+"altitude: "+r+","+"valid? "+v;
    std::cout<<dataString<<std::endl;
}

/////////////////////////////////////////////////////////////

int main(int argc, char **argv){
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Subscriber>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    exit(0);
}
