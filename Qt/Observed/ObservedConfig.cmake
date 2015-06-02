# BOOST

FIND_PACKAGE( Boost REQUIRED )
IF ( Boost_FOUND )
  INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
ENDIF()

FILE( GLOB Observed_RAW_SRCS "${Observed_DIR}/src/*.cpp" )
FILE( GLOB Observed_QTUI_HEADERS "${Observed_DIR}/include/*.h" )

QT5_WRAP_CPP( Observed_QTUI_HEADERS_MOC ${Observed_QTUI_HEADERS}) 

SET( Observed_SRCS ${Observed_RAW_SRCS} ${Observed_QTUI_HEADERS_MOC} )
SET( Observed_INCLUDE_DIRS "${Observed_DIR}/include" )
