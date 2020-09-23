add_library(crc32 crc32.cpp)
add_library(vector_concat vector_concat.cpp)

add_library(ups ups.cpp)
target_link_libraries(ups crc32 vector_concat)

add_library(nups nups_cli.cpp)
target_link_libraries(nups ups)

add_executable(NupsCli main.cpp)
target_link_libraries(NupsCli nups)
