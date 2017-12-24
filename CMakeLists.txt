cmake_minimum_required(VERSION 2.8)
project(MalaMatematika)

find_package(Qt4 COMPONENTS QtCore QtGui QtSql QtNetwork REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_AUTORCC on)

include_directories(
    ${QT_INCLUDE}
    ${CMAKE_CURRENT_BINARY_DIR}
)
include_directories(include/)

include(${QT_USE_FILE})

set(SOURCES
    src/core/database.cpp
    src/ui/dcoredata.cpp
    src/ui/dappeals.cpp
    src/ui/wpeoples.cpp
    src/ui/mainwindow.cpp
    src/main.cpp
)

set(HEADERS
    include/ui/wpeoples.h
    include/ui/dcoredata.h
    include/ui/dappeals.h
    include/ui/mainwindow.h
)

set(UI
    res/ui/wpeoples.ui
    res/ui/dcoredata.ui
    res/ui/dappeals.ui
    res/ui/mainwindow.ui
)

set(RESOURCES
)

foreach(MOCheader ${HEADERS})
    QT4_WRAP_CPP(MOCsrc ${MOCheader})
endforeach(MOCheader)

foreach(UIheader ${UI})
    QT4_WRAP_UI(UIsrc ${UIheader})
endforeach(UIheader)

add_executable(${PROJECT_NAME} ${SOURCES} ${MOCsrc} ${RESOURCES} ${UIsrc})
target_link_libraries(${PROJECT_NAME}
    ${QT_QTCORE_LIBRARY}
    ${QT_QTGUI_LIBRARY}
    ${QT_QTSQL_LIBRARY}
    ${QT_QTNETWORK_LIBRARY}
)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
