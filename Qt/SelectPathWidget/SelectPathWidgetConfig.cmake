# QTSJIS
FIND_PATH( QTSJIS_INCLUDE_DIRS qtsjis.hpp PATH ${SelectPathWidget_DIR}/../../tool/include/ )
INCLUDE_DIRECTORIES( ${QTSJIS_INCLUDE_DIRS} )

FILE( GLOB SelectPathWidget_RAW_SRCS "${SelectPathWidget_DIR}/src/*.cpp" )
FILE( GLOB SelectPathWidget_QTUI_HEADERS "${SelectPathWidget_DIR}/include/*.h" )
FILE( GLOB SelectPathWidget_QTUI_SRCS "${SelectPathWidget_DIR}/src/*.ui" )

QT5_WRAP_UI( SelectPathWidget_QTUI_H_SRCS ${SelectPathWidget_QTUI_SRCS} )
QT5_WRAP_CPP( SelectPathWidget_QTUI_HEADERS_MOC ${SelectPathWidget_QTUI_HEADERS}) 

SET( SelectPathWidget_SRCS ${SelectPathWidget_RAW_SRCS} ${SelectPathWidget_QTUI_H_SRCS} ${SelectPathWidget_QTUI_HEADERS_MOC} )
SET( SelectPathWidget_INCLUDE_DIRS "${SelectPathWidget_DIR}/include" )
