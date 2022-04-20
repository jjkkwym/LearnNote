file(GLOB_RECURSE SRCS easylogger/*.c)

add_library(elog STATIC ${SRCS})
target_include_directories(elog PUBLIC easylogger/inc)
target_include_directories(elog PRIVATE easylogger/plugins/file)
