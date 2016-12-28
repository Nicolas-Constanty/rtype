#pragma once

#ifndef DLL_EXPORT_HPP_
#define DLL_EXPORT_HPP_

#if defined (_WIN32) && defined (BUILD_SHARED_LIBS)
#if defined (_MSC_VER)
#pragma warning(disable: 4251)
#endif
#if defined(EXPORT_LIB)
#define  LIB_EXPORT __declspec(dllexport)
#else
#define  LIB_EXPORT __declspec(dllimport)
#endif
#else
#define LIB_EXPORT
#endif

#if defined(EXPORT_PREF)
	#define  PREF_EXPORT __declspec(dllexport)
#else
	#if defined(NO_EXPORT)
		#define PREF_EXPORT
	#else
		#define  PREF_EXPORT __declspec(dllimport)
	#endif
#endif

#endif // !DLL_EXPORT_HPP_