cmake_policy(VERSION 3.16)
project(Demo VERSION 0.1)
cmake_minimum_required(VERSION 3.9)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_PREFIX_PATH $ENV{QTDIR594})
find_package(Qt5 COMPONENTS Widgets Core Gui Multimedia REQUIRED)
# set the path of uic
# SET(QT_UIC_EXECUTABLE /usr/bin/uic)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./build)
# set auto make moc files
SET(CMAKE_AUTOMOC ON)
# auto compile ui to header
set(CMAKE_AUTOUIC ON)
# set auto transport the rcc files
SET(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# set the source
FILE(GLOB SOURCE_FILES "source/*.cpp")

# set the header 
FILE(GLOB HEADER_FILES "headers/*.h")

# handle the ui files
#FILE(GLOB UI "ui/*.ui")
#SET(CMAKE_AUTOUIC_SEARCH_PATHS "ui")
#SET(RCC_FILES res.qrc)
#qt5_wrap_ui(UI_HEADERS ${UI})

#FILE(GLOB UI_FILES "ui/*.ui") 

add_custom_target(format
    COMMAND clang-format -i source/*
    && clang-format -i header/*
    )
add_custom_target(code_check
    COMMAND scan-build --use-analyzer `which clang++` make
    )
#QT_WRAP_UI(WRAP_FILES ${UI_FILES})
ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES} )
target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Core Qt5::Gui Qt5::Multimedia)
