#pragma once
#ifndef P2P_LOGIC_SHARED_HEADER_H
#define P2P_LOGIC_SHARED_HEADER_H

#ifdef P2P_LOGIC_SHARED_BUILD_DLL
#   define P2P_LOGIC_EXPORTS __declspec(dllexport)
#else
#   define P2P_LOGIC_EXPORTS __declspec(dllimport)
#endif

#include "shlwapi.h"
#include "Tlhelp32.h"

#define CHARACTERSEPARATORSTR    _TEXT("\\")
#define CHARACTERSEPARATORCHR    _TEXT('\\')
#define STRINGNULLTERMINATECHAR  _TEXT('\0')

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

    P2P_LOGIC_EXPORTS int InitP2pLogicModule(int value);


#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* COMMONDLL_H */