cmake_minimum_required(VERSION 3.5)
project(learning_tf2_cpp)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(rclcpp REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(turtlesim REQUIRED)
find_package(message_filters REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)

if(TARGET tf2_geometry_msgs::tf2_geometry_msgs)
  get_target_property(_include_dirs tf2_geometry_msgs::tf2_geometry_msgs INTERFACE_INCLUDE_DIRECTORIES)
else()
  set(_include_dirs ${tf2_geometry_msgs_INCLUDE_DIRS})
endif()

find_file(TF2_CPP_HEADERS
  NAMES tf2_geometry_msgs.hpp
  PATHS ${_include_dirs}
  NO_CACHE
  PATH_SUFFIXES tf2_geometry_msgs
)

add_executable(static_turtle_tf2_broadcaster 
   src/MainFramePublisherStatic.cpp
   src/FramePublisherStatic.cpp
)
ament_target_dependencies(
   static_turtle_tf2_broadcaster
   geometry_msgs
   rclcpp
   tf2
   tf2_ros
)

add_executable(dynamic_turtle_tf2_broadcaster 
    src/MainFramePublisherDynamic.cpp
    src/FramePublisherDynamic.cpp
)
ament_target_dependencies(
    dynamic_turtle_tf2_broadcaster
    geometry_msgs
    rclcpp
    tf2
    tf2_ros
    turtlesim
)

add_executable(dynamic_turtle_tf2_listener 
    src/MainFrameListenerDynamic.cpp
    src/FrameListenerDynamic.cpp
)
ament_target_dependencies(
    dynamic_turtle_tf2_listener
    geometry_msgs
    rclcpp
    tf2
    tf2_ros
    turtlesim
)

add_executable(dynamic_turtle_tf2_listener_debug 
    src/MainFrameListenerDynamic.cpp
    src/FrameListenerDynamicDebug.cpp
)
ament_target_dependencies(
    dynamic_turtle_tf2_listener_debug
    geometry_msgs
    rclcpp
    tf2
    tf2_ros
    turtlesim
)

add_executable(fixed_frame_tf2_broadcaster 
    src/MainFrameFixedBroadcaster.cpp
    src/FrameFixedBroadcaster.cpp
)
ament_target_dependencies(
    fixed_frame_tf2_broadcaster
    geometry_msgs
    rclcpp
    tf2_ros
)

add_executable(dynamic_frame_tf2_broadcaster 
    src/MainFrameDynamicBroadcaster.cpp
    src/FrameDynamicBroadcaster.cpp
)
ament_target_dependencies(
    dynamic_frame_tf2_broadcaster
    geometry_msgs
    rclcpp
    tf2_ros
)

add_executable(turtle_tf2_message_filter 
    src/MainPointStampedListener.cpp
    src/PointStampedListener.cpp
    )
ament_target_dependencies(
  turtle_tf2_message_filter
  geometry_msgs
  message_filters
  rclcpp
  tf2
  tf2_geometry_msgs
  tf2_ros
)

if(EXISTS ${TF2_CPP_HEADERS})
  target_compile_definitions(turtle_tf2_message_filter PUBLIC -DTF2_CPP_HEADERS)
endif()

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

install(TARGETS
   static_turtle_tf2_broadcaster
   dynamic_turtle_tf2_broadcaster
   dynamic_turtle_tf2_listener
   dynamic_turtle_tf2_listener_debug
   fixed_frame_tf2_broadcaster
   dynamic_frame_tf2_broadcaster
   turtle_tf2_message_filter
   DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY launch
   DESTINATION share/${PROJECT_NAME})

ament_package()
