#Find dependencies
find_package(ZeroMQ REQUIRED)

set(test_ext_SOURCES WorldExt.cpp
                     TestWorldExt.cpp)

set(test_client_SOURCES test_client.cpp)

include_directories (${enki_SOURCE_DIR}
                     ${ZeroMQ_INCLUDE_DIR})

link_directories (${enki_BINARY_DIR})

add_executable(test_ext ${test_ext_SOURCES})
target_link_libraries(test_ext enki ${ZeroMQ_LIBRARY})

add_executable(test_client ${test_client_SOURCES})
target_link_libraries(test_client ${ZeroMQ_LIBRARY})

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
    
    set(playground_ext_SOURCES playground_ext_main.cpp)
    
    # For MOC-ing
    set(ext_QT_HEADERS playground_ext.h ${nzmqt_INCLUDE_DIR}/nzmqt/nzmqt.hpp)
    
    qt4_wrap_cpp(ext_QT_HEADERS_MOC ${ext_QT_HEADERS})
    	
    include_directories (${enki_SOURCE_DIR} 
                         ${ZeroMQ_INCLUDE_DIR} 
                         ${OPENGL_INCLUDE_DIR}
                         ${CMAKE_BINARY_DIR/ext})    
    
    link_directories (${enki_BINARY_DIR})   
    
    add_executable(test_client ${test_client_SOURCES})
    target_link_libraries(test_client ${ZeroMQ_LIBRARY})
    
    add_executable(playground_ext ${playground_ext_SOURCES} ${ext_QT_HEADERS_MOC})
    target_link_libraries(playground_ext enkiviewer enki 
                          ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${ZeroMQ_LIBRARY})
endif (QT4_FOUND)     
