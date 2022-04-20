file(GLOB_RECURSE SRCS ./*.c)
file(GLOB_RECURSE HEADERS ./*.h)

add_library(utils_standard_c STATIC ${SRCS})

target_include_directories(utils_standard_c PUBLIC .)