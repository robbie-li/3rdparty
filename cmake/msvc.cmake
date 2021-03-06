set (COMPILER_VERSION "")

if (MSVC OR MSVC_IDE) 
	if ( MSVC_VERSION EQUAL 1400)
		set(COMPILER_VERSION "vc8")
	elseif ( MSVC_VERSION EQUAL 1500)
		set(COMPILER_VERSION "vc9")
	elseif ( MSVC_VERSION EQUAL 1600)
		set(COMPILER_VERSION "vc10")
	elseif ( MSVC_VERSION EQUAL 1700)
		set(COMPILER_VERSION "vc11")
	elseif ( MSVC_VERSION EQUAL 1800)
		set(COMPILER_VERSION "vc12")
	elseif ( MSVC_VERSION EQUAL 1900)
		set(COMPILER_VERSION "vc14")
	endif ()
endif ()
