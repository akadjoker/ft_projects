cmake_minimum_required(VERSION 3.10)
cmake_policy(SET CMP0072 NEW)

project(libftpp)

add_subdirectory(libftpp)
add_subdirectory(main_pool)
add_subdirectory(main_data_buffer)
add_subdirectory(main_memento)
add_subdirectory(main_observer)
add_subdirectory(main_singleton)
add_subdirectory(main_state_machine)
add_subdirectory(main_thread_safe)
add_subdirectory(main_thread_safe_queue)
add_subdirectory(main_thread)
add_subdirectory(main_worker_pool)
add_subdirectory(main_persistent_worker)


add_subdirectory(main_client)
add_subdirectory(main_server)


