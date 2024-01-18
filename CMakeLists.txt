cmake_minimum_required(VERSION 3.0)
project(SmallWM)

find_package(X11 REQUIRED)

add_compile_definitions(WITH_BORDERS)

SET(HEADER_FILES
    src/actions.hpp
    src/clientmodel-events.hpp
    src/common.hpp
    src/configparse.hpp
    src/utils.hpp
    src/x-events.hpp
    src/xdata.hpp
    src/logging/file.hpp
    src/logging/logging.hpp
    src/logging/stream.hpp
    src/logging/syslog.hpp
    src/model/changes.hpp
    src/model/client-model.hpp
    src/model/desktop-type.hpp
    src/model/focus-cycle.hpp
    src/model/screen.hpp
    src/model/unique-multimap.hpp
    src/model/x-model.hpp
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
