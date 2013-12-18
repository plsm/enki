#Find dependencies
find_package(ZeroMQ REQUIRED)
#find_package(nzmqt REQUIRED)
# Right now, we expect that nzmqt headers are installed
# in a standard system location, such as
# /usr/local/include/nzmqt

find_package(OpenGL REQUIRED)
set(QT_USE_QTOPENGL TRUE)

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})


set(nzmqt_INCLUDE_DIR /usr/local/include)

if (CMAKE_HOST_UNIX)
	add_definitions("-fPIC")
endif (CMAKE_HOST_UNIX)

#add_definitions(-DNZMQT_LIB=1)
#set(ext_test_SRCS playground_test.cpp nzmqt.cpp)
set(ext_test_SRCS playground_test.cpp)
set(ext_test_HEADERS playground_ext.h ${nzmqt_INCLUDE_DIR}/nzmqt/nzmqt.hpp)

qt4_wrap_cpp(ext_test_HEADERS_MOC ${ext_test_HEADERS})
	
include_directories (${enki_SOURCE_DIR} 
                     ${ZeroMQ_INCLUDE_DIR} 
                     ${OPENGL_INCLUDE_DIR}
                     ${CMAKE_BINARY_DIR/ext})    

link_directories (${enki_BINARY_DIR})   

add_executable(spawn_server spawn_server.cpp)
target_link_libraries(spawn_server enki ${ZeroMQ_LIBRARY})

add_executable(playground_test ${ext_test_SRCS} ${ext_test_HEADERS_MOC})
target_link_libraries(playground_test enkiviewer enki 
                      ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${ZeroMQ_LIBRARY})
 
