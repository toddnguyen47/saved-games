add_library(byte_conversion byte_conversion.cpp)
add_library(crc32 crc32.cpp)

add_library(ups ups.cpp)
target_link_libraries(ups crc32 byte_conversion)

add_library(nups nups_cli.cpp)
target_link_libraries(nups ups)

add_executable(NupsCli main.cpp)
target_link_libraries(NupsCli nups)
