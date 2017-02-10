set(3RDPARTY_LIBRARY_ROOT $ENV{3RDPARTY_LIBRARY_ROOT})

include(${3RDPARTY_LIBRARY_ROOT}/cmake/platform.cmake)

if(WIN32)
  include(${3RDPARTY_LIBRARY_ROOT}/cmake/msvc.cmake)
else()
  set(COMPILER_VERSION gcc)
endif()

macro(include_3rdparty_libraries)
  set(_INC_DIR "")
  foreach(LIB ${ARGN})
    set(_INC_DIR 
		${_INC_DIR} 
		${3RDPARTY_LIBRARY_ROOT}/3rdparty/${LIB}/include
		${3RDPARTY_LIBRARY_ROOT}/3rdparty/${LIB}/include/${PLATFORM}
		${3RDPARTY_LIBRARY_ROOT}/3rdparty/${LIB}/include/${PLATFORM}/${COMPILER_VERSION})
  endforeach()

  list(REMOVE_DUPLICATES _INC_DIR)

  include_directories(${_INC_DIR})
endmacro()

macro(use_3rdparty_libraries)
  set(_INC_DIR "")
  set(_LIB_DIR "")
  
  foreach(LIB ${ARGN})
    set(_INC_DIR 
		${_INC_DIR} 
		${3RDPARTY_LIBRARY_ROOT}/3rdparty/${LIB}/include
		${3RDPARTY_LIBRARY_ROOT}/3rdparty/${LIB}/include/${PLATFORM}
		${3RDPARTY_LIBRARY_ROOT}/3rdparty/${LIB}/include/${PLATFORM}/${COMPILER_VERSION})
    set(_LIB_DIR 
		${_LIB_DIR} 
		${3RDPARTY_LIBRARY_ROOT}/3rdparty/${LIB}/lib
		${3RDPARTY_LIBRARY_ROOT}/3rdparty/${LIB}/lib/${PLATFORM}
		${3RDPARTY_LIBRARY_ROOT}/3rdparty/${LIB}/lib/${PLATFORM}/${COMPILER_VERSION})
  endforeach()
  
  list(REMOVE_DUPLICATES _INC_DIR)
  list(REMOVE_DUPLICATES _LIB_DIR)

  include_directories(${_INC_DIR})
  link_directories(${_LIB_DIR})
endmacro()