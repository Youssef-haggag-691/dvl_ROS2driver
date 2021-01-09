cmake_minimum_required(VERSION 3.5)
project(dvl_interface)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

set(CMAKE_CXX_FLAGS "-O2 -Wall -Wextra -Wpedantic")



# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(dvl_message REQUIRED)

add_executable(Rx src/serial_publisher.cpp include/SerialPort/Linux_Serial.cpp)
target_include_directories(Rx PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/SerialPort)
ament_target_dependencies(Rx rclcpp dvl_message)

add_executable(Parser src/serial_subscriber.cpp)
ament_target_dependencies(Parser rclcpp dvl_message)

add_executable(Dvl src/dvl_subscriber.cpp)
ament_target_dependencies(Dvl rclcpp dvl_message)




install(TARGETS Rx Parser Dvl DESTINATION lib/${PROJECT_NAME})

ament_package()
