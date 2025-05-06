cmake_minimum_required(VERSION 3.8)
project(stm_comm)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(sources
  "src/stm_comm.cpp"
  "src/StmComm.cpp")

set(includes
  "include/StmComm.hpp")


# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(PkgConfig)
pkg_check_modules(SERIAL libserial)
find_package(custom_msg REQUIRED) 


add_executable(stm_comm ${sources} ${includes})

ament_target_dependencies(stm_comm
  rclcpp
  SERIAL
  custom_msg
)

target_include_directories(stm_comm PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  ${SERIAL_INCLUDE_DIRS}
  #"../custom_msg/install/custom_msg/include/custom_msg"
  )
target_compile_features(stm_comm PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17

install(TARGETS stm_comm
  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
