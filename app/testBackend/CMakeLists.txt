include_directories(../QDomoticzBackend)

set(testBackend_HDRS
	QDomoticzTest.h
)

set(testBackend_SRCS
	QDomoticzTest.ui	
	QDomoticzTest.cpp
	main.cpp
)

add_executable(testBackend ${testBackend_SRCS} ${testBackend_HDRS})
target_link_libraries(testBackend Qt5::Widgets Qt5::Gui QDomoticzBackend)
