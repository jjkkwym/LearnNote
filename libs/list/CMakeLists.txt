file(GLOB_RECURSE SRCS ./*.c)
file(GLOB_RECURSE HEADERS ./*,h)

add_library(list STATIC ${SRCS})

target_include_directories(list PUBLIC .)
