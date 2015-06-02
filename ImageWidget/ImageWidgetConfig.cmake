# BOOST
FIND_PACKAGE( Boost REQUIRED )
IF ( Boost_FOUND )
  INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
ENDIF()

FILE( GLOB ImageWidget_RAW_SRCS "${ImageWidget_DIR}/src/*.cpp" )
FILE( GLOB ImageWidget_QTUI_HEADERS "${ImageWidget_DIR}/include/*.h" )

QT5_WRAP_CPP( ImageWidget_QTUI_HEADERS_MOC ${ImageWidget_QTUI_HEADERS}) 

SET( ImageWidget_SRCS ${ImageWidget_RAW_SRCS} ${ImageWidget_QTUI_HEADERS_MOC} )
SET( ImageWidget_INCLUDE_DIRS "${ImageWidget_DIR}/include" )
