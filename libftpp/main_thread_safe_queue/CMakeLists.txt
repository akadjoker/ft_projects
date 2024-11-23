project(main_thread_safe_queue)
cmake_policy(SET CMP0072 NEW)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ")

if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}   -D_CRT_SECURE_NO_WARNINGS")
    if (MSVC)
        if(CMAKE_BUILD_TYPE MATCHES Debug)
            add_compile_options(/RTC1 /Od /Zi)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /fsanitize=address")
        endif()     
    endif()

endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_compile_options(
    -Wall 
   -Wextra
   -Werror
)

find_package(Threads REQUIRED)


file(GLOB SOURCES "src/*.cpp")
add_executable(main_thread_safe_queue   ${SOURCES})


target_include_directories(libftpp PUBLIC  include src)



if(CMAKE_BUILD_TYPE MATCHES Debug)

if (UNIX)
target_compile_options(main_thread_safe_queue PRIVATE -g  -D_DEBUG -DVERBOSE)
target_link_options(main_thread_safe_queue PRIVATE  -lpthread  -g  -D_DEBUG) 
endif()


elseif(CMAKE_BUILD_TYPE MATCHES Release)
    target_compile_options(main_thread_safe_queue PRIVATE -O3   -DNDEBUG )
    target_link_options(main_thread_safe_queue PRIVATE -O3   -DNDEBUG )
endif()

target_link_libraries(main_thread_safe_queue libftpp )

if (WIN32)
    target_link_libraries(main_thread_safe_queue Winmm.lib)
endif()


if (UNIX)
    target_link_libraries(main_thread_safe_queue  m )
endif()
