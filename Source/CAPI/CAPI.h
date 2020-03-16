#pragma once

#include "stdint.h"
#include <mono/metadata/appdomain.h>
#include <combaseapi.h>

#define DLLExport __declspec( dllexport )
#define STDCALL __stdcall

typedef uintptr_t CEntity;
typedef uintptr_t CComponent;