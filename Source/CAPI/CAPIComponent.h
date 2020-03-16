#pragma once

#include "CAPI.h"

extern "C" {
    DLLExport char * STDCALL getComponentName(CComponent component);
    // DLLExport void STDCALL setComponentName(CComponent const char *name);
    DLLExport void STDCALL setComponentEntity(CComponent component, CEntity entity);
}

