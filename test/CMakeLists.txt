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

#file(GLOB_RECURSE mains ${CMAKE_CURRENT_SOURCE_DIR}  *.c *.cpp)
file(GLOB main_files *.c *.cpp)
foreach(main_file ${main_files})
    message("file:${file}")
    get_filename_component(exec_name ${main_file} NAME)
    add_executable(${exec_name} ${main_file})
    #target_link_libraries( ${exec_name} cJSON elog list utils_standard_c
endforeach()


#add_test(NAME test_test COMMAND test)
add_test(NAME test_at_cmd COMMAND at_cmd)