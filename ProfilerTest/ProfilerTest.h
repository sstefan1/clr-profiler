#pragma once

#include <cor.h>
#include <corprof.h>
#include <atomic>

class Profiler : public ICorProfilerCallback3
{
private:
	std::atomic<int> refCount;
	ICorProfilerInfo *corProfilerInfo;
public:
	Profiler();
	virtual ~Profiler();

#pragma endregion


#pragma region ICorProfilerCallback

	HRESULT __stdcall DLLGetClasObject(REFCLSID rclsid, REFIID riid, LPVOID FAR *ppv);
	HRESULT __stdcall Initialize(IUnknown *pICorProfilerInfoUnk) override;
	HRESULT __stdcall Shutdown(void) override;
	HRESULT __stdcall AppDomainCreationStarted(AppDomainID appDomainId) override;
	HRESULT __stdcall AppDomainCreationFinished(AppDomainID appDomainId, HRESULT hrStatus) override;
	HRESULT __stdcall AppDomainShutdownStarted(AppDomainID appDomainId) override;
	HRESULT __stdcall AppDomainShutdownFinished(AppDomainID appDomainId, HRESULT hrStatus) override;
	HRESULT __stdcall AssemblyLoadStarted(AssemblyID assemblyId) override;
	HRESULT __stdcall AssemblyLoadFinished(AssemblyID assemblyId, HRESULT hrStatus) override;
	HRESULT __stdcall AssemblyUnloadStarted(AssemblyID assemblyId) override;
	HRESULT __stdcall AssemblyUnloadFinished(AssemblyID assemblyId, HRESULT hrStatus) override;
	HRESULT __stdcall ModuleLoadStarted(ModuleID moduleId) override;
	HRESULT __stdcall ModuleLoadFinished(ModuleID moduleId, HRESULT hrStatus) override;
	HRESULT __stdcall ModuleUnloadStarted(ModuleID moduleId) override;
	HRESULT __stdcall ModuleUnloadFinished(ModuleID moduleId, HRESULT hrStatus) override;
	HRESULT __stdcall ModuleAttachedToAssembly(ModuleID moduleId, AssemblyID AssemblyId) override;
	HRESULT __stdcall ClassLoadStarted(ClassID classId) override;
	HRESULT __stdcall ClassLoadFinished(ClassID classId, HRESULT hrStatus) override;
	HRESULT __stdcall ClassUnloadStarted(ClassID classId) override;
	HRESULT __stdcall ClassUnloadFinished(ClassID classId, HRESULT hrStatus) override;
	HRESULT __stdcall FunctionUnloadStarted(FunctionID functionId) override;
	HRESULT __stdcall JITCompilationStarted(FunctionID functionId, BOOL fIsSafeToBlock) override;
	HRESULT __stdcall JITCompilationFinished(FunctionID functionId, HRESULT hrStatus, BOOL fIsSafeToBlock) override;
	HRESULT __stdcall JITCachedFunctionSearchStarted(FunctionID functionId, BOOL *pbUseCachedFunction) override;
	HRESULT __stdcall JITCachedFunctionSearchFinished(FunctionID functionId, COR_PRF_JIT_CACHE result) override;
	HRESULT __stdcall JITFunctionPitched(FunctionID functionId) override;
	HRESULT __stdcall JITInlining(FunctionID callerId, FunctionID calleeId, BOOL *pfShouldInline) override;
	HRESULT __stdcall ThreadCreated(ThreadID threadId) override;
	HRESULT __stdcall ThreadDestroyed(ThreadID threadId) override;
	HRESULT __stdcall ThreadAssignedToOSThread(ThreadID managedThreadId, DWORD osThreadId) override;
	HRESULT __stdcall RemotingClientInvocationStarted(void) override;
	HRESULT __stdcall RemotingClientSendingMessage(GUID *pCookie, BOOL fIsAsync) override;
	HRESULT __stdcall RemotingClientReceivingReply(GUID *pCookie, BOOL fIsAsync) override;
	HRESULT __stdcall RemotingClientInvocationFinished(void) override;
	HRESULT __stdcall RemotingServerReceivingMessage(GUID *pCookie, BOOL fIsAsync) override;
	HRESULT __stdcall RemotingServerInvocationStarted(void) override;
	HRESULT __stdcall RemotingServerInvocationReturned(void) override;
	HRESULT __stdcall RemotingServerSendingReply(GUID *pCookie, BOOL fIsAsync) override;
	HRESULT __stdcall UnmanagedToManagedTransition(FunctionID functionId, COR_PRF_TRANSITION_REASON reason) override;
	HRESULT __stdcall ManagedToUnmanagedTransition(FunctionID functionId, COR_PRF_TRANSITION_REASON reason) override;
	HRESULT __stdcall RuntimeSuspendStarted(COR_PRF_SUSPEND_REASON suspendReason) override;
	HRESULT __stdcall RuntimeSuspendFinished(void) override;
	HRESULT __stdcall RuntimeSuspendAborted(void) override;
	HRESULT __stdcall RuntimeResumeStarted(void) override;
	HRESULT __stdcall RuntimeResumeFinished(void) override;
	HRESULT __stdcall RuntimeThreadSuspended(ThreadID threadId) override;
	HRESULT __stdcall RuntimeThreadResumed(ThreadID threadId) override;
	HRESULT __stdcall MovedReferences(ULONG cMovedObjectIDRanges, ObjectID oldObjectIDRangeStart[], ObjectID newObjectIDRangeStart[], ULONG cObjectIDRangeLength[]) override;
	HRESULT __stdcall ObjectAllocated(ObjectID objectId, ClassID classId) override;
	HRESULT __stdcall ObjectsAllocatedByClass(ULONG cClassCount, ClassID classIds[], ULONG cObjects[]) override;
	HRESULT __stdcall ObjectReferences(ObjectID objectId, ClassID classId, ULONG cObjectRefs, ObjectID objectRefIds[]) override;
	HRESULT __stdcall RootReferences(ULONG cRootRefs, ObjectID rootRefIds[]) override;
	HRESULT __stdcall ExceptionThrown(ObjectID thrownObjectId) override;
	HRESULT __stdcall ExceptionSearchFunctionEnter(FunctionID functionId) override;
	HRESULT __stdcall ExceptionSearchFunctionLeave(void) override;
	HRESULT __stdcall ExceptionSearchFilterEnter(FunctionID functionId) override;
	HRESULT __stdcall ExceptionSearchFilterLeave(void) override;
	HRESULT __stdcall ExceptionSearchCatcherFound(FunctionID functionId) override;
	HRESULT __stdcall ExceptionOSHandlerEnter(UINT_PTR __unused) override;
	HRESULT __stdcall ExceptionOSHandlerLeave(UINT_PTR __unused) override;
	HRESULT __stdcall ExceptionUnwindFunctionEnter(FunctionID functionId) override;
	HRESULT __stdcall ExceptionUnwindFunctionLeave(void) override;
	HRESULT __stdcall ExceptionUnwindFinallyEnter(FunctionID functionId) override;
	HRESULT __stdcall ExceptionUnwindFinallyLeave(void) override;
	HRESULT __stdcall ExceptionCatcherEnter(FunctionID functionId, ObjectID objectId) override;
	HRESULT __stdcall ExceptionCatcherLeave(void) override;
	HRESULT __stdcall COMClassicVTableCreated(ClassID wrappedClassId, REFGUID implementedIID, void *pVTable, ULONG cSlots) override;
	HRESULT __stdcall COMClassicVTableDestroyed(ClassID wrappedClassId, REFGUID implementedIID, void *pVTable) override;
	HRESULT __stdcall ExceptionCLRCatcherFound(void) override;
	HRESULT __stdcall ExceptionCLRCatcherExecute(void) override;

#pragma endregion

#pragma region ICorProfilerCallback2

	HRESULT __stdcall ThreadNameChanged(ThreadID threadId, ULONG cchName, _In_reads_opt_(cchName)  WCHAR name[]) override;
	HRESULT __stdcall GarbageCollectionStarted(int cGenerations, BOOL generationCollected[], COR_PRF_GC_REASON reason) override;
	HRESULT __stdcall SurvivingReferences(ULONG cSurvivingObjectIDRanges, ObjectID objectIDRangeStart[], ULONG cObjectIDRangeLength[]) override;
	HRESULT __stdcall GarbageCollectionFinished(void) override;
	HRESULT __stdcall FinalizeableObjectQueued(DWORD finalizerFlags, ObjectID objectID) override;
	HRESULT __stdcall RootReferences2(ULONG cRootRefs, ObjectID rootRefIds[], COR_PRF_GC_ROOT_KIND rootKinds[], COR_PRF_GC_ROOT_FLAGS rootFlags[], UINT_PTR rootIds[]) override;
	HRESULT __stdcall HandleCreated(GCHandleID handleId, ObjectID initialObjectId) override;
	HRESULT __stdcall HandleDestroyed(GCHandleID handleId) override;

#pragma endregion

#pragma region ICorProfilerCallback3
	HRESULT STDAPICALLTYPE InitializeForAttach(IUnknown *pCorProfilerInfoUnk, void *pvClientData, UINT cbClientData);
	HRESULT STDAPICALLTYPE ProfilerAttachComplete();
	HRESULT STDAPICALLTYPE ProfilerDetachSucceeded();
#pragma endregion

	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject) override
	{
		if (riid == __uuidof(ICorProfilerCallback7) ||
			riid == __uuidof(ICorProfilerCallback6) ||
			riid == __uuidof(ICorProfilerCallback5) ||
			riid == __uuidof(ICorProfilerCallback4) ||
			riid == __uuidof(ICorProfilerCallback3) ||
			riid == __uuidof(ICorProfilerCallback2) ||
			riid == __uuidof(ICorProfilerCallback) ||
			riid == IID_IUnknown)
		{
			*ppvObject = this;
			this->AddRef();
			return S_OK;
		}

		*ppvObject = nullptr;
		return E_NOINTERFACE;
	}

	ULONG STDMETHODCALLTYPE AddRef() override
	{
		return std::atomic_fetch_add(&this->refCount, 1) + 1;
	}

	ULONG STDMETHODCALLTYPE Release() override
	{
		int count = std::atomic_fetch_add(&this->refCount, 1) - 1;

		if (count <= 0)
			delete this;

		return count;
	}
};
