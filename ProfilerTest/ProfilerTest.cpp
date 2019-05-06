// ProfilerTest.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "ProfilerTest.h"
#include "ClassFactory.h"
#include "Logger.h"
#include "Registry.h"

// extern const GUID CLSID_Profiler;

Profiler::Profiler() : refCount(0), corProfilerInfo(nullptr) {}

Profiler::~Profiler() {
  if (this->corProfilerInfo != nullptr) {
    this->corProfilerInfo->Release();
    this->corProfilerInfo = nullptr;
  }
}

ULONG g_ServerLocks = 0;
ULONG g_Components = 0;

STDAPI DllCanUnloadNow() {
  HRESULT rc = E_UNEXPECTED;
  if ((g_ServerLocks == 0) && (g_Components == 0))
    rc = S_OK;
  else
    rc = S_FALSE;
  return rc;
};

STDAPI DllGetClassObject(REFCLSID clsid, REFIID iid, LPVOID FAR *ppv) {
  HRESULT rc = E_UNEXPECTED;

  if (clsid == CLSID_Profiler) {
    ClassFactory<Profiler> *cf = new ClassFactory<Profiler>();
    rc = cf->QueryInterface(iid, ppv);
    cf->Release();
  } else
    rc = CLASS_E_CLASSNOTAVAILABLE;
  return rc;
};

#pragma region ICorProfilerCallback
HRESULT STDMETHODCALLTYPE Profiler::Initialize(IUnknown *pICorProfilerInfoUnk) {
  LOG(INFO);
  auto queryInterfaceResult = pICorProfilerInfoUnk->QueryInterface(
      __uuidof(ICorProfilerInfo),
      reinterpret_cast<void **>(&this->corProfilerInfo));

  if (FAILED(queryInterfaceResult))
    return E_FAIL;

  LOG(INFO);

  DWORD eventMask = COR_PRF_ALL;

  auto hr = this->corProfilerInfo->SetEventMask(eventMask);

  if (hr != S_OK)
    printf("ERROR: Profiler SetEventMask failed (HRESULT: %d)", hr);

  printf("ERROR: Profiler SetEventMask failed (HRESULT: %d)", hr);
  LOG(INFO);

  return S_OK;
}

HRESULT Profiler::Shutdown() {
  if (this->corProfilerInfo != nullptr) {
    LOG(DEBUG);
    this->corProfilerInfo->Release();
    this->corProfilerInfo = nullptr;
  }

  LOG(DEBUG);
  return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::AppDomainCreationStarted(AppDomainID appDomainId)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::AppDomainCreationFinished(AppDomainID appDomainId, HRESULT hrStatus)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::AppDomainShutdownStarted(AppDomainID appDomainId)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::AppDomainShutdownFinished(AppDomainID appDomainId, HRESULT hrStatus)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::AssemblyLoadStarted(AssemblyID assemblyId)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::AssemblyLoadFinished(AssemblyID assemblyId, HRESULT hrStatus)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::AssemblyUnloadStarted(AssemblyID assemblyId)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::AssemblyUnloadFinished(AssemblyID assemblyId, HRESULT hrStatus)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::ModuleLoadStarted(ModuleID moduleId)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::ModuleLoadFinished(ModuleID moduleId, HRESULT hrStatus)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::ModuleUnloadStarted(ModuleID moduleId)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::ModuleUnloadFinished(ModuleID moduleId, HRESULT hrStatus)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::ModuleAttachedToAssembly(ModuleID moduleId, AssemblyID AssemblyId)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::ClassLoadStarted(ClassID classId)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::ClassLoadFinished(ClassID classId, HRESULT hrStatus)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::ClassUnloadStarted(ClassID classId)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::ClassUnloadFinished(ClassID classId, HRESULT hrStatus)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::FunctionUnloadStarted(FunctionID functionId)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::JITCompilationStarted(FunctionID functionId, BOOL fIsSafeToBlock)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::JITCompilationFinished(FunctionID functionId, HRESULT hrStatus, BOOL fIsSafeToBlock)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::JITCachedFunctionSearchStarted(FunctionID functionId, BOOL *pbUseCachedFunction)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::JITCachedFunctionSearchFinished(FunctionID functionId, COR_PRF_JIT_CACHE result)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::JITFunctionPitched(FunctionID functionId)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::JITInlining(FunctionID callerId, FunctionID calleeId, BOOL *pfShouldInline)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::ThreadCreated(ThreadID threadId)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::ThreadDestroyed(ThreadID threadId)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::ThreadAssignedToOSThread(ThreadID managedThreadId, DWORD osThreadId)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::RemotingClientInvocationStarted()
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::RemotingClientSendingMessage(GUID *pCookie, BOOL fIsAsync)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::RemotingClientReceivingReply(GUID *pCookie, BOOL fIsAsync)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::RemotingClientInvocationFinished()
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::RemotingServerReceivingMessage(GUID *pCookie, BOOL fIsAsync)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::RemotingServerInvocationStarted()
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::RemotingServerInvocationReturned()
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::RemotingServerSendingReply(GUID *pCookie, BOOL fIsAsync)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::UnmanagedToManagedTransition(FunctionID functionId, COR_PRF_TRANSITION_REASON reason)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::ManagedToUnmanagedTransition(FunctionID functionId, COR_PRF_TRANSITION_REASON reason)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::RuntimeSuspendStarted(COR_PRF_SUSPEND_REASON suspendReason)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::RuntimeSuspendFinished()
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::RuntimeSuspendAborted()
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::RuntimeResumeStarted()
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::RuntimeResumeFinished()
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::RuntimeThreadSuspended(ThreadID threadId)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::RuntimeThreadResumed(ThreadID threadId)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::MovedReferences(ULONG cMovedObjectIDRanges, ObjectID oldObjectIDRangeStart[], ObjectID newObjectIDRangeStart[], ULONG cObjectIDRangeLength[])
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::ObjectAllocated(ObjectID objectId, ClassID classId)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::ObjectsAllocatedByClass(ULONG cClassCount, ClassID classIds[], ULONG cObjects[])
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::ObjectReferences(ObjectID objectId, ClassID classId, ULONG cObjectRefs, ObjectID objectRefIds[])
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::RootReferences(ULONG cRootRefs, ObjectID rootRefIds[])
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::ExceptionThrown(ObjectID thrownObjectId)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::ExceptionSearchFunctionEnter(FunctionID functionId)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::ExceptionSearchFunctionLeave()
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::ExceptionSearchFilterEnter(FunctionID functionId)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::ExceptionSearchFilterLeave()
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::ExceptionSearchCatcherFound(FunctionID functionId)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::ExceptionOSHandlerEnter(UINT_PTR __unused)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::ExceptionOSHandlerLeave(UINT_PTR __unused)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::ExceptionUnwindFunctionEnter(FunctionID functionId)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::ExceptionUnwindFunctionLeave()
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::ExceptionUnwindFinallyEnter(FunctionID functionId)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::ExceptionUnwindFinallyLeave()
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::ExceptionCatcherEnter(FunctionID functionId, ObjectID objectId)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::ExceptionCatcherLeave()
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::COMClassicVTableCreated(ClassID wrappedClassId, REFGUID implementedIID, void *pVTable, ULONG cSlots)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::COMClassicVTableDestroyed(ClassID wrappedClassId, REFGUID implementedIID, void *pVTable)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::ExceptionCLRCatcherFound()
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Profiler::ExceptionCLRCatcherExecute()
{
	return S_OK;
}

#pragma endregion 

#pragma region ICorProfilerCallback2

HRESULT Profiler::ThreadNameChanged(ThreadID threadId, ULONG cchName, WCHAR name[])
{
	return S_OK;
}

HRESULT Profiler::GarbageCollectionStarted(int cGenerations, BOOL generationCollected[], COR_PRF_GC_REASON reason)
{
	return S_OK;
}

HRESULT Profiler::SurvivingReferences(ULONG cSurvivingObjectIDRanges, ObjectID objectIDRangeStart[], ULONG cObjectIDRangeLength[])
{
	return S_OK;
}

HRESULT Profiler::GarbageCollectionFinished(void)
{
	return S_OK;
}

HRESULT Profiler::FinalizeableObjectQueued(DWORD finalizerFlags, ObjectID objectID)
{
	return S_OK;
}

HRESULT Profiler::RootReferences2(ULONG cRootRefs, ObjectID rootRefIds[], COR_PRF_GC_ROOT_KIND rootKinds[], COR_PRF_GC_ROOT_FLAGS rootFlags[], UINT_PTR rootIds[])
{
	return S_OK;
}

HRESULT Profiler::HandleCreated(GCHandleID handleId, ObjectID initialObjectId)
{
	return S_OK;
}

HRESULT Profiler::HandleDestroyed(GCHandleID handleId)
{
	return S_OK;
}

#pragma endregion

#pragma region ICorProfilerCallback2
HRESULT Profiler::InitializeForAttach(IUnknown* pCorProfilerInfoUnk, void* pvClientData, UINT cbClientData)
{
	return S_OK;
}

HRESULT Profiler::ProfilerAttachComplete()
{
	return S_OK;
}

HRESULT Profiler::ProfilerDetachSucceeded()
{
	return S_OK;
}

#pragma endregion 
