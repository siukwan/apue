PROJECT (UNIX_APUE)
#显示路径信息
MESSAGE(STATUS "UNIX:This is BINARY dir" ${UNIX_APUE_BINARY_DIR})
MESSAGE(STATUS "UNIX:This is SOURCE dir" ${UNIX_APUE_SOURCE_DIR})

#设置错误函数和包裹函数
SET(LIB_FUNC_ERR_SRC ../func_err.cpp)
MESSAGE(STATUS "UNIX:This is func_err dir" ${LIB_FUNC_ERR_SRC})

#设置list all files编译文件
SET(LIST_ALL_FILES_SRC_LIST listAllFilesP4.cpp)

#连接库
ADD_LIBRARY(FuncErr STATIC ${LIB_FUNC_ERR_SRC} )

#输出可执行文件
ADD_EXECUTABLE(listAllFiles ${LIST_ALL_FILES_SRC_LIST})
TARGET_LINK_LIBRARIES(listAllFiles FuncErr)





 