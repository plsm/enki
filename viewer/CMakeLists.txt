# SDL
find_package(SDL)
if (SDL_FOUND)
	include_directories(${SDL_INCLUDE_DIR})
	set(EXTRA_LIBS ${SDL_LIBRARY} ${EXTRA_LIBS})
	add_definitions("-DUSE_SDL")
	message("SDL found")
endif (SDL_FOUND)

set(QT_USE_QTOPENGL TRUE)
find_package(Qt4)

if (QT4_FOUND)
	find_package(OpenGL REQUIRED)
	include(${QT_USE_FILE})
	add_definitions(${QT_DEFINITIONS})
	
	if (CMAKE_HOST_UNIX)
		add_definitions("-fPIC")
	endif (CMAKE_HOST_UNIX)
	
	set(viewer_lib_SRCS
		Viewer.cpp
		EPuckModel.cpp
		objects/EPuckBody.cpp
		objects/EPuckRest.cpp
		objects/EPuckRing.cpp
		objects/EPuckWheelLeft.cpp
		objects/EPuckWheelRight.cpp
		MarxbotModel.cpp
		objects/MarxbotBase.cpp
		objects/MarxbotWheel.cpp)
	set(viewer_test_SRCS Playground.cpp)
	
	qt4_automoc(${viewer_lib_SRCS})
	qt4_automoc(${viewer_test_SRCS})
	
	qt4_add_resources(viewer_lib_RCC_SRCS enki-viewer-textures.qrc)
	
	include_directories (${enki_SOURCE_DIR} ${OPENGL_INCLUDE_DIR} ${CMAKE_BINARY_DIR}/viewer)
	
	link_directories (${enki_BINARY_DIR})
	
	add_library (enkiviewer ${viewer_lib_SRCS} ${viewer_lib_RCC_SRCS})
	add_executable(enkiplayground ${viewer_test_SRCS})
	
	target_link_libraries(enkiplayground enkiviewer enki ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${EXTRA_LIBS})

	set(ENKI_VIEWER_HDR
		Viewer.h
	)
	install(FILES ${ENKI_VIEWER_HDR}
		DESTINATION include/viewer/
	)
	install(TARGETS enkiviewer ARCHIVE DESTINATION lib)
endif (QT4_FOUND)
