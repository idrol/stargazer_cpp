//
// Created by Idrol on 23-04-2018.
//

#pragma once

#include "CAPI.h"
#include <mono/metadata/object.h>

extern "C" {
    DLLExport CEntity STDCALL createEntity();
    DLLExport void STDCALL setEntityName(CEntity entity, const char *name);
    DLLExport char * STDCALL getEntityName(CEntity entity);
    DLLExport void STDCALL addEntityComponent(CEntity entity, CComponent component);
    DLLExport CComponent STDCALL getEntityComponent(CEntity entity, MonoString *id);
    DLLExport void STDCALL removeEntityComponent(CEntity entity, MonoString *id);
    DLLExport void STDCALL selectEntity(CEntity entity);
    DLLExport void STDCALL deselectEntity(CEntity entity);
}