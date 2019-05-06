#pragma once

#include <ObjBase.h>

static HMODULE hProfiler;

// {CB787C6E-14A1-43F8-91F4-DF35887E9049}
//static const GUID CLSID_Profiler = {
//    0xcb787c6e,
//    0x14a1,
//    0x43f8,
//    {0x91, 0xf4, 0xdf, 0x35, 0x88, 0x7e, 0x90, 0x49}};

// {4C20F663-CF29-4F26-9FF5-2C28BB884511}
static const GUID CLSID_Profiler =
{ 0x4c20f663, 0xcf29, 0x4f26, { 0x9f, 0xf5, 0x2c, 0x28, 0xbb, 0x88, 0x45, 0x11 } };


const WCHAR FName[] = L"Profiler COM";
const WCHAR VerInd[] = L"Profiler.Component";
const WCHAR ProgId[] = L"Profiler.Component.1";

STDAPI DllInstall(char *s);
STDAPI DllRegisterServer();
STDAPI DllUnregisterServer();

HRESULT RegisterServer(HMODULE hModule, const CLSID &clsid,
                       const WCHAR *szFriendlyName, const WCHAR *szVerIndProgID,
                       const WCHAR *szProgID);


HRESULT UnregisterServer(const CLSID &clsid, const WCHAR *szVerIndProgID,
                         const WCHAR *szProgID);