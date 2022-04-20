file(GLOB_RECURSE SRCS ./*.c)
file(GLOB_RECURSE HEADERS ./*,h)

add_library(cJSON STATIC ${SRCS})

target_include_directories(cJSON PUBLIC .)
