cmake_minimum_required(VERSION 3.0)
project(SmallWM)

find_package(X11 REQUIRED)

add_compile_definitions(WITH_BORDERS)

SET(HEADER_FILES
    src/actions.h
    src/clientmodel-events.h
    src/common.h
    src/configparse.h
    src/utils.h
    src/x-events.h
    src/xdata.h
    src/logging/file.h
    src/logging/logging.h
    src/logging/stream.h
    src/logging/syslog.h
    src/model/changes.h
    src/model/client-model.h
    src/model/desktop-type.h
    src/model/focus-cycle.h
    src/model/screen.h
    src/model/unique-multimap.h
    src/model/x-model.h
)

set(SOURCE_FILES
    src/clientmodel-events.cpp
    src/configparse.cpp
    src/smallwm.cpp
    src/utils.cpp
    src/x-events.cpp
    src/xdata.cpp
    src/logging/file.cpp
    src/logging/logging.cpp
    src/logging/stream.cpp
    src/logging/syslog.cpp
    src/model/changes.cpp
    src/model/client-model.cpp
    src/model/focus-cycle.cpp
    src/model/screen.cpp
    src/model/x-model.cpp
)

add_subdirectory(libs/inih)

add_executable(smallwm ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries(smallwm inih X11::Xrandr)

install(TARGETS smallwm DESTINATION bin)
install(FILES ${HEADER_FILES} DESTINATION include/smallwm-molasses)
