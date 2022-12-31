cmake_minimum_required(VERSION 3.5)

project(ffConvert LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INSTALL_PREFIX "/usr")

find_package(wxWidgets REQUIRED COMPONENTS core base)

include(${wxWidgets_USE_FILE})

file(GLOB MySources src/*.cpp)

add_executable(${PROJECT_NAME} ${MySources} )

# Link required libraries to the executable
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES} )

install(FILES resource/ffConvert.desktop DESTINATION share/applications)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
