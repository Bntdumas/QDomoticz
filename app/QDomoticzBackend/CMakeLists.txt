
set(QDomoticzBackend_HDRS
	QDomoticzBackend.h
	QDomoticzBackend_global.h
	QDomoticzController.h
        DomoticzObjects.h
	ScenesModel.h
	SwitchesModel.h
)

set(QDomoticzBackend_SRCS
	QDomoticzBackend.cpp
	QDomoticzController.cpp
	ScenesModel.cpp
	SwitchesModel.cpp
)

add_library(QDomoticzBackend SHARED ${QDomoticzBackend_SRCS} ${QDomoticzBackend_HDRS})
target_link_libraries(QDomoticzBackend Qt5::Network)
