
# link_libraries(cJSON)
# link_libraries(elog)
# link_libraries(list)
# link_libraries(utils_standard_c)
message("current dir:${CMAKE_CURRENT_SOURCE_DIR}")
#file(GLOB_RECURSE mains ${CMAKE_CURRENT_SOURCE_DIR}  *.c *.cpp)
file(GLOB main_files *.c *.cpp)
foreach(main_file ${main_files})
    message("file:${file}")
    get_filename_component(exec_name ${main_file} NAME)
    add_executable(${exec_name} ${main_file})
    target_link_libraries( ${exec_name} ${cJSON} ${elog} ${list} ${utils_standard_c} )
    
endforeach()



# message(STATUS ${mains})
# message("main files:${mains}")
# foreach(mainfile IN LISTS mains)
    # Get file name without directory
    # get_filename_component(mainname ${mainfile} NAME)
    # message("file name:${mainname}")
    # add_executable(${mainname} ${mainfile})
    # set_target_properties(${mainname} PROPERTIES LINKER_LANGUAGE C)
    # target_link_libraries (${mainname} ${PCL_LIBRARIES})
# endforeach()

# add_executable(app_test_libs app_test_libs.c)
# target_link_libraries(app_test_libs whole_libs)
# 
# add_executable(sum sum.cpp)
# target_link_libraries(sum whole_libs)
# 
# add_executable(store store.c)
# target_link_libraries(store whole_libs)