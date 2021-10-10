cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(test_project C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

#set(PICO_BARE_METAL 1)

pico_sdk_init()

add_executable(blink_noboot2 blink.c)

pico_add_extra_outputs(blink_noboot2)

set_target_properties(blink_noboot2 PROPERTIES COMPILE_FLAGS "-Wall")

pico_set_linker_script(blink_noboot2 ${CMAKE_CURRENT_SOURCE_DIR}/blink_noboot2.ld)

target_link_libraries(blink_noboot2 pico_stdlib_headers pico_stdlib hardware_watchdog hardware_structs)
