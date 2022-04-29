cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(blink_combined C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

# The build process is roughly:
# 1. Build a combined bootloader + app ELF         (NAME_combined_nohdr.elf)
# 2. Extract the app binary from that ELF          (NAME_app.bin)
# 3. Calculate the checksum of the app binary      (NAME_hdr.bin)
# 4. Update the header section in the ELF from 1.  (NAME_combined.elf)

# The combined uf2 file doesn't work, something must get confused by the
# combined package. So, disable uf2 for now, instead you can load either the
# ${NAME}_combined.bin or ${NAME}_combined.elf with picotool
set(PICO_NO_UF2 1)

set(NAME blink)

add_executable(${NAME}
	"blink.c"
)

target_link_libraries(${NAME}
	pico_stdlib_headers
	pico_stdlib
	hardware_watchdog
	hardware_structs
)

set_target_properties(${NAME}	PROPERTIES COMPILE_FLAGS "-Wall")

add_subdirectory(bootloader)

bootloader_build_combined(${NAME})
