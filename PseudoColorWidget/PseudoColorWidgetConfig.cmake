FILE( GLOB PseudoColorWidget_RAW_SRCS "${PseudoColorWidget_DIR}/src/*.cpp" )
FILE( GLOB PseudoColorWidget_QTUI_HEADERS "${PseudoColorWidget_DIR}/include/*.h" )
FILE( GLOB PseudoColorWidget_QTUI_SRCS "${PseudoColorWidget_DIR}/src/*.ui" )

QT5_WRAP_UI( PseudoColorWidget_QTUI_H_SRCS ${PseudoColorWidget_QTUI_SRCS} )
QT5_WRAP_CPP( PseudoColorWidget_QTUI_HEADERS_MOC ${PseudoColorWidget_QTUI_HEADERS}) 

SET( PseudoColorWidget_SRCS ${PseudoColorWidget_RAW_SRCS} ${PseudoColorWidget_QTUI_H_SRCS} ${PseudoColorWidget_QTUI_HEADERS_MOC} )
SET( PseudoColorWidget_INCLUDE_DIRS "${PseudoColorWidget_DIR}/include" )
