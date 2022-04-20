
link_libraries(cJSON)
link_libraries(elog)
link_libraries(list)
link_libraries(utils_standard_c)

file(GLOB_RECURSE mains ${CMAKE_CURRENT_SOURCE_DIR}  *.c *.cpp)
message(STATUS ${mains})
foreach(mainfile IN LISTS mains)
    # Get file name without directory
    get_filename_component(mainname ${mainfile} NAME_WE)
    add_executable(${mainname} ${mainfile})
    #target_link_libraries (${mainname} ${PCL_LIBRARIES})
endforeach()

# add_executable(app_test_libs app_test_libs.c)
# target_link_libraries(app_test_libs whole_libs)
# 
# add_executable(sum sum.cpp)
# target_link_libraries(sum whole_libs)
# 
# add_executable(store store.c)
# target_link_libraries(store whole_libs)