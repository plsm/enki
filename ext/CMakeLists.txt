#Find dependencies
find_package(ZeroMQ REQUIRED)

# boost::for_each is used within WorldExt
find_package(Boost REQUIRED)

# Set up compilation of protobuffer files
find_package(Protobuf REQUIRED)
set(Proto_FILES messages/base_msgs.proto
                  messages/sensor_msgs.proto)
set(PROTOBUF_IMPORT_DIRS ${PROTOBUF_IMPORT_DIRS}
                         ${enki_SOURCE_DIR}/ext/messages)
PROTOBUF_GENERATE_CPP(ProtoSources ProtoHeaders ${Proto_FILES})

set(test_ext_SOURCES WorldExt.cpp
                     handlers/EPuckHandler.cpp
                     TestWorldExt.cpp
                     ${ProtoSources})

include_directories (${enki_SOURCE_DIR}
                     ${enki_BINARY_DIR}
                     ${ZeroMQ_INCLUDE_DIR})

link_directories (${enki_BINARY_DIR})

add_executable(test_ext ${test_ext_SOURCES})
target_link_libraries(test_ext enki ${ZeroMQ_LIBRARY} ${PROTOBUF_LIBRARY})

find_package(Qt4)

# Build PlaygroundExt only if we have QT4
if (QT4_FOUND)
    find_package(OpenGL REQUIRED)
    set(QT_USE_QTOPENGL TRUE)
    
    include(${QT_USE_FILE})
    add_definitions(${QT_DEFINITIONS})
        
    if (CMAKE_HOST_UNIX)
    	add_definitions("-fPIC")
    endif (CMAKE_HOST_UNIX)

    set(playground_ext_SOURCES PlaygroundExtMain.cpp
                               handlers/EPuckHandler.cpp
                               PlaygroundExt.cpp
                               WorldExt.cpp
                               ${ProtoSources})
    
    # For MOC-ing
    set(ext_QT_HEADERS PlaygroundExt.h)
    
    qt4_wrap_cpp(ext_QT_HEADERS_MOC ${ext_QT_HEADERS})
    	
    include_directories (${enki_SOURCE_DIR} 
                         ${ZeroMQ_INCLUDE_DIR} 
                         ${OPENGL_INCLUDE_DIR}
                         ${CMAKE_BINARY_DIR/ext})    
    
    link_directories (${enki_BINARY_DIR})   
    
    add_executable(playground_ext ${playground_ext_SOURCES} ${ext_QT_HEADERS_MOC})
    target_link_libraries(playground_ext enki
                                         enkiviewer
                                         ${QT_LIBRARIES} 
                                         ${OPENGL_LIBRARIES} 
                                         ${ZeroMQ_LIBRARY}
                                         ${PROTOBUF_LIBRARY})
endif (QT4_FOUND)     
