include_directories (${enki_SOURCE_DIR})

if (CMAKE_HOST_UNIX)
	add_definitions("-fPIC")
	add_definitions("--std=c++11")
endif (CMAKE_HOST_UNIX)

add_library(enki
	Geometry.cpp
	Types.cpp
	PhysicalEngine.cpp
	BluetoothBase.cpp
	interactions/IRSensor.cpp
	interactions/CircularCam.cpp
	interactions/Bluetooth.cpp
	interactions/ActiveSoundSource.cpp
	interactions/Microphone.cpp
   interactions/LightSource.cpp
   interactions/LightSourceFromAbove.cpp
   interactions/LightSensor.cpp
   interactions/VibrationSensor.cpp
   interactions/VibrationActuator.cpp
	robots/DifferentialWheeled.cpp
	robots/khepera/Khepera.cpp
	robots/e-puck/EPuck.cpp
	robots/s-bot/Sbot.cpp
	robots/s-bot/SbotObject.cpp
	robots/marxbot/Marxbot.cpp
)

install(DIRECTORY . 
	DESTINATION include/enki/
	FILES_MATCHING PATTERN "*.h"
)
install(TARGETS enki ARCHIVE DESTINATION lib)
