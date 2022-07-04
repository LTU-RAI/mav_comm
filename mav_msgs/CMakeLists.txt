cmake_minimum_required(VERSION 3.5)
project(mav_msgs)


find_package(rosidl_default_generators REQUIRED)
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
    "msg/Actuators.msg"
    "msg/AttitudeThrust.msg"
    "msg/FilteredSensorData.msg"
    "msg/GpsWaypoint.msg"
    "msg/RateThrust.msg"
    "msg/RollPitchYawrateThrust.msg"
    "msg/Status.msg"
    "msg/TorqueThrust.msg"
    )

ament_package()
