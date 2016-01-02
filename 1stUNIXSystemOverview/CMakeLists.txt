PROJECT (UNIX_APUE)
#显示路径信息
MESSAGE(STATUS "UNIX:This is BINARY dir" ${UNIX_APUE_BINARY_DIR})
MESSAGE(STATUS "UNIX:This is SOURCE dir" ${UNIX_APUE_SOURCE_DIR})

#设置错误函数和包裹函数
SET(LIB_FUNC_ERR_SRC ../func_err.cpp)
MESSAGE(STATUS "UNIX:This is func_err dir" ${LIB_FUNC_ERR_SRC})

#设置list all files编译文件
SET(LIST_ALL_FILES_SRC_LIST listAllFilesP4.cpp)

#设置stdin to stdout编译文件
SET(STDIN_TO_STDOUT_SRC_LIST stdin2stdoutP7.cpp)

#设置stdin to stdout编译文件
SET(STDIN_TO_STDOUT2_SRC_LIST stdin2stdoutP8.cpp)

#设置打印进程id编译文件
SET(PRINT_PROCESS_ID_SRC_LIST printProcessIDP9.cpp)

#设置标准输入执行程序编译文件
SET(STDIN_2_EXEC_SRC_LIST stdin2execP9.cpp)

#连接库
ADD_LIBRARY(FuncErr STATIC ${LIB_FUNC_ERR_SRC} )


#输出可执行文件
ADD_EXECUTABLE(listAllFiles ${LIST_ALL_FILES_SRC_LIST})
TARGET_LINK_LIBRARIES(listAllFiles FuncErr)

#输出可执行文件
ADD_EXECUTABLE(stdin2stdout ${STDIN_TO_STDOUT_SRC_LIST})
TARGET_LINK_LIBRARIES(stdin2stdout FuncErr)

#输出可执行文件
ADD_EXECUTABLE(stdin2stdout2 ${STDIN_TO_STDOUT2_SRC_LIST})
TARGET_LINK_LIBRARIES(stdin2stdout2 FuncErr)

#输出可执行文件
ADD_EXECUTABLE(printProcessID ${PRINT_PROCESS_ID_SRC_LIST})
TARGET_LINK_LIBRARIES(printProcessID FuncErr)

#输出可执行文件
ADD_EXECUTABLE(stdin2exec ${STDIN_2_EXEC_SRC_LIST})
TARGET_LINK_LIBRARIES(stdin2exec FuncErr)

 