cmake_minimum_required(VERSION 3.5)
project(dvl_message)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()


# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)
find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME} "msg/DVL.msg" "msg/SerialArray.msg")

set(CMAKE_CXX_FLAGS "-O2 -Wall -Wextra -Wpedantic")


ament_package()
