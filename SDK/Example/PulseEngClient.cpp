// PulseEngClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

typedef PULSE_STATUS (*lpfnTransportCreate)(PPS_TRANSPORT *pTransport, PS_TRANSPORT_TYPE TransportType);
typedef PULSE_STATUS (*lpfnTransportGetInterfaceCount)(PPS_TRANSPORT pTransport, uint32_t *pInterfaceCount);
typedef PULSE_STATUS (*lpfnTransportGetInterfaceName)(PPS_TRANSPORT pTransport, uint32_t InterfaceIndex, char *pcInterfaceNameBuffer, uint32_t *pcbBufSize);
typedef PULSE_STATUS (*lpfnTransportSetInterfaceName)(PPS_TRANSPORT pTransport, char *lpcInterfaceName);
typedef PULSE_STATUS (*lpfnTransportSetInterfaceIndex)(PPS_TRANSPORT pTransport, uint32_t InterfaceIndex);
typedef PULSE_STATUS (*lpfnTransportSetRawDataCallback)(PPS_TRANSPORT pTransport, lpfnRawDataCallback RawDataCallback, uintptr_t Context);
typedef PULSE_STATUS (*lpfnTransportResetConnection)(PPS_TRANSPORT pTransport);
typedef PULSE_STATUS (*lpfnTransportDestroy)(PPS_TRANSPORT pTransport);

typedef PULSE_STATUS (*lpfnEngCreateEngine)(PPS_ENGINE *ppEngine);
typedef PULSE_STATUS (*lpfnEngAssignTransport)(PPS_ENGINE pEngine, PPS_TRANSPORT pTransport);
typedef PULSE_STATUS (*lpfnEngSetRequestTimeout)(PPS_ENGINE pEngine, uint32_t Timeout);
typedef PULSE_STATUS (*lpfnEngStart)(PPS_ENGINE pEngine);
typedef PULSE_STATUS (*lpfnEngStop)(PPS_ENGINE pEngine);
typedef PULSE_STATUS (*lpfnEngDestroyEngine)(PPS_ENGINE pEngine);

typedef PULSE_STATUS (*lpfnPsPing)(PPS_ENGINE pEngine);
typedef PULSE_STATUS (*lpfnPsGo)(PPS_ENGINE pEngine);
typedef PULSE_STATUS (*lpfnPsBreakIn)(PPS_ENGINE pEngine);
typedef PULSE_STATUS (*lpfnPsStep)(PPS_ENGINE pEngine, uint8_t SuppressInterrupts);
typedef PULSE_STATUS (*lpfnPsSwitchCpu)(PPS_ENGINE pEngine, uint64_t TargetCpuIndex);
typedef PULSE_STATUS (*lpfnPsReboot)(PPS_ENGINE pEngine);

typedef PULSE_STATUS (*lpfnPsReadVirtualMemory)(PPS_ENGINE pEngine, uint64_t PageTableAddress, uint16_t SelectorValue, uint64_t Offset, void* pBuffer, uint64_t cbToRead, uint64_t *pcbRead);
typedef PULSE_STATUS (*lpfnPsWriteVirtualMemory)(PPS_ENGINE pEngine, uint64_t PageTableAddress, uint16_t SelectorValue, uint64_t Offset, void* pBuffer, uint64_t cbToWrite, uint64_t *pcbWritten);
typedef PULSE_STATUS (*lpfnPsReadLinearMemory)(PPS_ENGINE pEngine, uint64_t PageTableAddress, uint64_t Address, void* pBuffer, uint64_t cbToRead, uint64_t *pcbRead);
typedef PULSE_STATUS (*lpfnPsWriteLinearMemory)(PPS_ENGINE pEngine, uint64_t PageTableAddress, uint64_t Address, void* pBuffer, uint64_t cbToWrite, uint64_t *pcbWritten);
typedef PULSE_STATUS (*lpfnPsReadPhysicalMemory)(PPS_ENGINE pEngine, uint64_t Address, void* pBuffer, uint64_t cbToRead, uint64_t *pcbRead);
typedef PULSE_STATUS (*lpfnPsWritePhysicalMemory)(PPS_ENGINE pEngine, uint64_t Address, void* pBuffer, uint64_t cbToWrite, uint64_t *pcbWritten);

typedef PULSE_STATUS (*lpfnPsGetContext)(PPS_ENGINE pEngine, PPS_CTX pContext, uint64_t RegMask, PS_CPU_MODE *pCpuMode);
typedef PULSE_STATUS (*lpfnPsSetContext)(PPS_ENGINE pEngine, PPS_CTX pContext, uint64_t RegMask);
typedef PULSE_STATUS (*lpfnPsGetExtendedContext)(PPS_ENGINE pEngine, PPS_CTX_EXT pContextExt, uint64_t ExtRegMask);
typedef PULSE_STATUS (*lpfnPsSetExtendedContext)(PPS_ENGINE pEngine, PPS_CTX_EXT pContextExt, uint64_t ExtRegMask);

typedef PULSE_STATUS (*lpfnPsReadIo)(PPS_ENGINE pEngine, uint16_t Port, uint16_t AccessSize, void *pBuffer, uint32_t cbToRead, uint64_t *pcbRead);
typedef PULSE_STATUS (*lpfnPsWriteIo)(PPS_ENGINE pEngine, uint16_t Port, uint16_t AccessSize, void *pBuffer, uint32_t cbToWrite, uint64_t *pcbWritten);

typedef PULSE_STATUS (*lpfnPsGetStateInfo)(PPS_ENGINE pEngine, PPS_STATE_INFO pStateInfo);
typedef PULSE_STATUS (*lpfnPsGetCpuInfo)(PPS_ENGINE pEngine, uint8_t *pActiveCpu, uint8_t *pCpuCount);

typedef PULSE_STATUS (*lpfnPsCpuId)(PPS_ENGINE pEngine, uint32_t Leaf, uint32_t Subleaf, uint32_t CpuIdData[4]);
typedef PULSE_STATUS (*lpfnPsReadMsr)(PPS_ENGINE pEngine, uint32_t MsrNumber, uint64_t *pMsrValue);
typedef PULSE_STATUS (*lpfnPsWriteMsr)(PPS_ENGINE pEngine, uint32_t MsrNumber, uint64_t MsrValue);

typedef PULSE_STATUS (*lpfnPsSearchVirtualMemory)(PPS_ENGINE pEngine, uint64_t PageTableAddress, uint16_t Selector, uint64_t StartOffset, uint64_t EndOffset, void* pPattern, uint32_t PatternSize, uint32_t SearchStep, uint8_t IgnoreGaps, uint64_t *pResult);
typedef PULSE_STATUS (*lpfnPsSearchLinearMemory)(PPS_ENGINE pEngine, uint64_t PageTableAddress, uint64_t StartAddress, uint64_t EndAddress, void* pPattern, uint32_t PatternSize, uint32_t SearchStep, uint8_t IgnoreGaps, uint64_t *pResult);
typedef PULSE_STATUS (*lpfnPsSearchPhysicalMemory)(PPS_ENGINE pEngine, uint64_t StartAddress, uint64_t EndAddress, void* pPattern, uint32_t PatternSize, uint32_t SearchStep, uint8_t IgnoreGaps, uint64_t *pResult);

typedef PULSE_STATUS (*lpfnPsWalkPageVirtual)(PPS_ENGINE pEngine, uint64_t PageTableAddress, uint16_t Selector, uint64_t Offset, PPS_PAGE_WALK_INFO pPageWalkInfo);
typedef PULSE_STATUS (*lpfnPsWalkPageLinear)(PPS_ENGINE pEngine, uint64_t PageTableAddress, uint64_t Address, PPS_PAGE_WALK_INFO pPageWalkInfo);
typedef PULSE_STATUS (*lpfnPsVirtualToPhysical)(PPS_ENGINE pEngine, uint64_t PageTableAddress, uint16_t Selector, uint64_t Offset, uint64_t *pPhysicalAddress);
typedef PULSE_STATUS (*lpfnPsLinearToPhysical)(PPS_ENGINE pEngine, uint64_t PageTableAddress, uint64_t Address, uint64_t *pPhysicalAddress);

typedef PULSE_STATUS (*lpfnPsSetBreakPoint)(PPS_ENGINE pEngine, uint64_t PhysicalAddress, uint32_t *pBreakPointId);
typedef PULSE_STATUS (*lpfnPsRemoveBreakPoint)(PPS_ENGINE pEngine, uint32_t BreakPointId);
typedef PULSE_STATUS (*lpfnPsClearBreakPoints)(PPS_ENGINE pEngine);

typedef PULSE_STATUS (*lpfnPsAddBreakPointFilter)(PPS_ENGINE pEngine, uint32_t BreakPointId, uint64_t PageTable, uint64_t Address, uint64_t ThreadBase, uint16_t Selector);
typedef PULSE_STATUS (*lpfnPsRemoveBreakPointFilter)(PPS_ENGINE pEngine, uint32_t BreakPointId, uint64_t PageTable, uint64_t Address, uint64_t ThreadBase, uint16_t Selector);

//
//  Pulse engine function globals
//

typedef struct _PULSE_INTERFACE
{
	// Transport functions
	lpfnTransportCreate TransportCreate = NULL;
	lpfnTransportGetInterfaceCount TransportGetInterfaceCount = NULL;
	lpfnTransportGetInterfaceName TransportGetInterfaceName = NULL;
	lpfnTransportSetInterfaceName TransportSetInterfaceName = NULL;
	lpfnTransportSetInterfaceIndex TransportSetInterfaceIndex = NULL;
	lpfnTransportSetRawDataCallback TransportSetRawDataCallback = NULL;
	lpfnTransportResetConnection TransportResetConnection = NULL;
	lpfnTransportDestroy TransportDestroy = NULL;

	// Engine auxiliary functions
	lpfnEngCreateEngine EngCreateEngine = NULL;
	lpfnEngAssignTransport EngAssignTransport = NULL;
	lpfnEngSetRequestTimeout EngSetRequestTimeout = NULL;
	lpfnEngStart EngStart = NULL;
	lpfnEngStop EngStop = NULL;
	lpfnEngDestroyEngine EngDestroyEngine = NULL;

	// Engine useful functions
	lpfnPsPing PsPing = NULL;
	lpfnPsGo PsGo = NULL;
	lpfnPsBreakIn PsBreakIn = NULL;
	lpfnPsStep PsStep = NULL;
	lpfnPsSwitchCpu PsSwitchCpu = NULL;
	lpfnPsReboot PsReboot = NULL;
	lpfnPsReadVirtualMemory PsReadVirtualMemory = NULL;
	lpfnPsWriteVirtualMemory PsWriteVirtualMemory = NULL;
	lpfnPsReadLinearMemory PsReadLinearMemory = NULL;
	lpfnPsWriteLinearMemory PsWriteLinearMemory = NULL;
	lpfnPsReadPhysicalMemory PsReadPhysicalMemory = NULL;
	lpfnPsWritePhysicalMemory PsWritePhysicalMemory = NULL;
	lpfnPsGetContext PsGetContext = NULL;
	lpfnPsSetContext PsSetContext = NULL;
	lpfnPsGetExtendedContext PsGetExtendedContext = NULL;
	lpfnPsSetExtendedContext PsSetExtendedContext = NULL;
	lpfnPsReadIo PsReadIo = NULL;
	lpfnPsWriteIo PsWriteIo = NULL;
	lpfnPsGetStateInfo PsGetStateInfo = NULL;
	lpfnPsGetCpuInfo PsGetCpuInfo = NULL;
	lpfnPsCpuId PsCpuId = NULL;
	lpfnPsReadMsr PsReadMsr = NULL;
	lpfnPsWriteMsr PsWriteMsr = NULL;
	lpfnPsSearchVirtualMemory PsSearchVirtualMemory = NULL;
	lpfnPsSearchLinearMemory PsSearchLinearMemory = NULL;
	lpfnPsSearchPhysicalMemory PsSearchPhysicalMemory = NULL;
	lpfnPsWalkPageVirtual PsWalkPageVirtual = NULL;
	lpfnPsWalkPageLinear PsWalkPageLinear = NULL;
	lpfnPsVirtualToPhysical PsVirtualToPhysical = NULL;
	lpfnPsLinearToPhysical PsLinearToPhysical = NULL;
	lpfnPsSetBreakPoint PsSetBreakPoint = NULL;
	lpfnPsRemoveBreakPoint PsRemoveBreakPoint = NULL;
	lpfnPsClearBreakPoints PsClearBreakPoints = NULL;
	lpfnPsAddBreakPointFilter PsAddBreakPointFilter = NULL;
	lpfnPsRemoveBreakPointFilter PsRemoveBreakPointFilter = NULL;
} PULSE_INTERFACE, *PPULSE_INTERFACE;

PULSE_INTERFACE Pulse;

bool InitializeLibrary(wchar_t *lpwPulseDllPath)
{
	bool bResult = true;

	HINSTANCE hPulseDll = LoadLibrary(lpwPulseDllPath);
	if (hPulseDll == NULL)
		return false;

	RtlZeroMemory(&Pulse, sizeof(PULSE_INTERFACE));

	// Lookup functions
	Pulse.TransportCreate = (lpfnTransportCreate)GetProcAddress(hPulseDll, "TransportCreate");
	bResult &= (Pulse.TransportCreate != NULL);
	Pulse.TransportGetInterfaceCount = (lpfnTransportGetInterfaceCount)GetProcAddress(hPulseDll, "TransportGetInterfaceCount");
	bResult &= (Pulse.TransportGetInterfaceCount != NULL);
	Pulse.TransportGetInterfaceName = (lpfnTransportGetInterfaceName)GetProcAddress(hPulseDll, "TransportGetInterfaceName");
	bResult &= (Pulse.TransportGetInterfaceName != NULL);
	Pulse.TransportSetInterfaceName = (lpfnTransportSetInterfaceName)GetProcAddress(hPulseDll, "TransportSetInterfaceName");
	bResult &= (Pulse.TransportSetInterfaceName != NULL);
	Pulse.TransportSetInterfaceIndex = (lpfnTransportSetInterfaceIndex)GetProcAddress(hPulseDll, "TransportSetInterfaceIndex");
	bResult &= (Pulse.TransportSetInterfaceIndex != NULL);
	Pulse.TransportSetRawDataCallback = (lpfnTransportSetRawDataCallback)GetProcAddress(hPulseDll, "TransportSetRawDataCallback");
	bResult &= (Pulse.TransportSetRawDataCallback != NULL);
	Pulse.TransportResetConnection = (lpfnTransportResetConnection)GetProcAddress(hPulseDll, "TransportResetConnection");
	bResult &= (Pulse.TransportResetConnection != NULL);
	Pulse.TransportDestroy = (lpfnTransportDestroy)GetProcAddress(hPulseDll, "TransportDestroy");
	bResult &= (Pulse.TransportDestroy != NULL);

	Pulse.EngCreateEngine = (lpfnEngCreateEngine)GetProcAddress(hPulseDll, "EngCreateEngine");
	bResult &= (Pulse.EngCreateEngine != NULL);
	Pulse.EngAssignTransport = (lpfnEngAssignTransport)GetProcAddress(hPulseDll, "EngAssignTransport");
	bResult &= (Pulse.EngAssignTransport != NULL);
	Pulse.EngSetRequestTimeout = (lpfnEngSetRequestTimeout)GetProcAddress(hPulseDll, "EngSetRequestTimeout");
	bResult &= (Pulse.EngSetRequestTimeout != NULL);
	Pulse.EngStart = (lpfnEngStart)GetProcAddress(hPulseDll, "EngStart");
	bResult &= (Pulse.EngStart != NULL);
	Pulse.EngStop = (lpfnEngStop)GetProcAddress(hPulseDll, "EngStop");
	bResult &= (Pulse.EngStop != NULL);
	Pulse.EngDestroyEngine = (lpfnEngDestroyEngine)GetProcAddress(hPulseDll, "EngDestroyEngine");
	bResult &= (Pulse.EngDestroyEngine != NULL);

	Pulse.PsPing = (lpfnPsPing)GetProcAddress(hPulseDll, "PsPing");
	bResult &= (Pulse.PsPing != NULL);
	Pulse.PsGo = (lpfnPsGo)GetProcAddress(hPulseDll, "PsGo");
	bResult &= (Pulse.PsGo != NULL);
	Pulse.PsBreakIn = (lpfnPsBreakIn)GetProcAddress(hPulseDll, "PsBreakIn");
	bResult &= (Pulse.PsBreakIn != NULL);
	Pulse.PsStep = (lpfnPsStep)GetProcAddress(hPulseDll, "PsStep");
	bResult &= (Pulse.PsStep != NULL);
	Pulse.PsSwitchCpu = (lpfnPsSwitchCpu)GetProcAddress(hPulseDll, "PsSwitchCpu");
	bResult &= (Pulse.PsSwitchCpu != NULL);
	Pulse.PsReboot = (lpfnPsReboot)GetProcAddress(hPulseDll, "PsReboot");
	bResult &= (Pulse.PsReboot != NULL);
	Pulse.PsReadVirtualMemory = (lpfnPsReadVirtualMemory)GetProcAddress(hPulseDll, "PsReadVirtualMemory");
	bResult &= (Pulse.PsReadVirtualMemory != NULL);
	Pulse.PsWriteVirtualMemory = (lpfnPsWriteVirtualMemory)GetProcAddress(hPulseDll, "PsWriteVirtualMemory");
	bResult &= (Pulse.PsWriteVirtualMemory != NULL);
	Pulse.PsReadLinearMemory = (lpfnPsReadLinearMemory)GetProcAddress(hPulseDll, "PsReadLinearMemory");
	bResult &= (Pulse.PsReadLinearMemory != NULL);
	Pulse.PsWriteLinearMemory = (lpfnPsWriteLinearMemory)GetProcAddress(hPulseDll, "PsWriteLinearMemory");
	bResult &= (Pulse.PsWriteLinearMemory != NULL);
	Pulse.PsReadPhysicalMemory = (lpfnPsReadPhysicalMemory)GetProcAddress(hPulseDll, "PsReadPhysicalMemory");
	bResult &= (Pulse.PsReadPhysicalMemory != NULL);
	Pulse.PsWritePhysicalMemory = (lpfnPsWritePhysicalMemory)GetProcAddress(hPulseDll, "PsWritePhysicalMemory");
	bResult &= (Pulse.PsWritePhysicalMemory != NULL);
	Pulse.PsGetContext = (lpfnPsGetContext)GetProcAddress(hPulseDll, "PsGetContext");
	bResult &= (Pulse.PsGetContext != NULL);
	Pulse.PsSetContext = (lpfnPsSetContext)GetProcAddress(hPulseDll, "PsSetContext");
	bResult &= (Pulse.PsSetContext != NULL);
	Pulse.PsGetExtendedContext = (lpfnPsGetExtendedContext)GetProcAddress(hPulseDll, "PsGetExtendedContext");
	bResult &= (Pulse.PsGetExtendedContext != NULL);
	Pulse.PsSetExtendedContext = (lpfnPsSetExtendedContext)GetProcAddress(hPulseDll, "PsSetExtendedContext");
	bResult &= (Pulse.PsSetExtendedContext != NULL);
	Pulse.PsReadIo = (lpfnPsReadIo)GetProcAddress(hPulseDll, "PsReadIo");
	bResult &= (Pulse.PsReadIo != NULL);
	Pulse.PsWriteIo = (lpfnPsWriteIo)GetProcAddress(hPulseDll, "PsWriteIo");
	bResult &= (Pulse.PsWriteIo != NULL);
	Pulse.PsGetStateInfo = (lpfnPsGetStateInfo)GetProcAddress(hPulseDll, "PsGetStateInfo");
	bResult &= (Pulse.PsGetStateInfo != NULL);
	Pulse.PsGetCpuInfo = (lpfnPsGetCpuInfo)GetProcAddress(hPulseDll, "PsGetCpuInfo");
	bResult &= (Pulse.PsGetCpuInfo != NULL);
	Pulse.PsCpuId = (lpfnPsCpuId)GetProcAddress(hPulseDll, "PsCpuId");
	bResult &= (Pulse.PsCpuId != NULL);
	Pulse.PsReadMsr = (lpfnPsReadMsr)GetProcAddress(hPulseDll, "PsReadMsr");
	bResult &= (Pulse.PsReadMsr != NULL);
	Pulse.PsWriteMsr = (lpfnPsWriteMsr)GetProcAddress(hPulseDll, "PsWriteMsr");
	bResult &= (Pulse.PsWriteMsr != NULL);
	Pulse.PsSearchVirtualMemory = (lpfnPsSearchVirtualMemory)GetProcAddress(hPulseDll, "PsSearchVirtualMemory");
	bResult &= (Pulse.PsSearchVirtualMemory != NULL);
	Pulse.PsSearchLinearMemory = (lpfnPsSearchLinearMemory)GetProcAddress(hPulseDll, "PsSearchLinearMemory");
	bResult &= (Pulse.PsSearchLinearMemory != NULL);
	Pulse.PsSearchPhysicalMemory = (lpfnPsSearchPhysicalMemory)GetProcAddress(hPulseDll, "PsSearchPhysicalMemory");
	bResult &= (Pulse.PsSearchPhysicalMemory != NULL);
	Pulse.PsWalkPageVirtual = (lpfnPsWalkPageVirtual)GetProcAddress(hPulseDll, "PsWalkPageVirtual");
	bResult &= (Pulse.PsWalkPageVirtual != NULL);
	Pulse.PsWalkPageLinear = (lpfnPsWalkPageLinear)GetProcAddress(hPulseDll, "PsWalkPageLinear");
	bResult &= (Pulse.PsWalkPageLinear != NULL);
	Pulse.PsVirtualToPhysical = (lpfnPsVirtualToPhysical)GetProcAddress(hPulseDll, "PsVirtualToPhysical");
	bResult &= (Pulse.PsVirtualToPhysical != NULL);
	Pulse.PsLinearToPhysical = (lpfnPsLinearToPhysical)GetProcAddress(hPulseDll, "PsLinearToPhysical");
	bResult &= (Pulse.PsLinearToPhysical != NULL);
	Pulse.PsSetBreakPoint = (lpfnPsSetBreakPoint)GetProcAddress(hPulseDll, "PsSetBreakPoint");
	bResult &= (Pulse.PsSetBreakPoint != NULL);
	Pulse.PsRemoveBreakPoint = (lpfnPsRemoveBreakPoint)GetProcAddress(hPulseDll, "PsRemoveBreakPoint");
	bResult &= (Pulse.PsRemoveBreakPoint != NULL);
	Pulse.PsClearBreakPoints = (lpfnPsClearBreakPoints)GetProcAddress(hPulseDll, "PsClearBreakPoints");
	bResult &= (Pulse.PsClearBreakPoints != NULL);
	Pulse.PsAddBreakPointFilter = (lpfnPsAddBreakPointFilter)GetProcAddress(hPulseDll, "PsAddBreakPointFilter");
	bResult &= (Pulse.PsAddBreakPointFilter != NULL);
	Pulse.PsRemoveBreakPointFilter = (lpfnPsRemoveBreakPointFilter)GetProcAddress(hPulseDll, "PsRemoveBreakPointFilter");
	bResult &= (Pulse.PsRemoveBreakPointFilter != NULL);

	if (!bResult)
	{
		Pulse.TransportCreate = NULL;
		Pulse.TransportGetInterfaceCount = NULL;
		Pulse.TransportGetInterfaceName = NULL;
		Pulse.TransportSetInterfaceName = NULL;
		Pulse.TransportSetInterfaceIndex = NULL;
		Pulse.TransportSetRawDataCallback = NULL;
		Pulse.TransportResetConnection = NULL;
		Pulse.TransportDestroy = NULL;

		Pulse.EngCreateEngine = NULL;
		Pulse.EngAssignTransport = NULL;
		Pulse.EngSetRequestTimeout = NULL;
		Pulse.EngStart = NULL;
		Pulse.EngStop = NULL;
		Pulse.EngDestroyEngine = NULL;

		Pulse.PsPing = NULL;
		Pulse.PsGo = NULL;
		Pulse.PsBreakIn = NULL;
		Pulse.PsStep = NULL;
		Pulse.PsSwitchCpu = NULL;
		Pulse.PsReboot = NULL;
		Pulse.PsReadVirtualMemory = NULL;
		Pulse.PsWriteVirtualMemory = NULL;
		Pulse.PsReadLinearMemory = NULL;
		Pulse.PsWriteLinearMemory = NULL;
		Pulse.PsReadPhysicalMemory = NULL;
		Pulse.PsWritePhysicalMemory = NULL;
		Pulse.PsGetContext = NULL;
		Pulse.PsSetContext = NULL;
		Pulse.PsGetExtendedContext = NULL;
		Pulse.PsSetExtendedContext = NULL;
		Pulse.PsReadIo = NULL;
		Pulse.PsWriteIo = NULL;
		Pulse.PsGetStateInfo = NULL;
		Pulse.PsGetCpuInfo = NULL;
		Pulse.PsCpuId = NULL;
		Pulse.PsReadMsr = NULL;
		Pulse.PsWriteMsr = NULL;
		Pulse.PsSearchVirtualMemory = NULL;
		Pulse.PsSearchLinearMemory = NULL;
		Pulse.PsSearchPhysicalMemory = NULL;
		Pulse.PsWalkPageVirtual = NULL;
		Pulse.PsWalkPageLinear = NULL;
		Pulse.PsVirtualToPhysical = NULL;
		Pulse.PsLinearToPhysical = NULL;
		Pulse.PsSetBreakPoint = NULL;
		Pulse.PsRemoveBreakPoint = NULL;
		Pulse.PsClearBreakPoints = NULL;
		Pulse.PsAddBreakPointFilter = NULL;
		Pulse.PsRemoveBreakPointFilter = NULL;

		FreeLibrary(hPulseDll);
	}

	return true;
}

void TestRawDataCallback(uintptr_t Context, void *pRawDataBuffer, uint32_t RawDataSize)
{
	UNREFERENCED_PARAMETER(Context);
	printf("%.*s", RawDataSize, (char*)pRawDataBuffer);
}

int main()
{
	if (!InitializeLibrary(L"PulseEng.dll"))
		return GetLastError();

	PULSE_STATUS   status = PULSE_STATUS_SUCCESS;
	PPS_TRANSPORT  TransportHandle = NULL;
	PPS_ENGINE     EngineHandle = NULL;

	// TransportCreate creates a transport instance. It's a first step in creating a transport for engine
	status = Pulse.TransportCreate(&TransportHandle, pttPipe);
	if (status != PULSE_STATUS_SUCCESS)
	{
		printf("TransportCreate failed with status %llx\n", status);
		return 0;
	}

	//
	//  You can enumerate transport interfaces like this
	//

	uint32_t InterfaceCount = 0;

	// TransportGetInterfaceCount tell available interfaces for the current transport type
	// N.B. Transport might not have enumerable interfaces (like pipe names or network addresses),
	// in that case specify interface name, f.e. "\\.\pipe\com_1", "192.168.13.37:50100"
	status = Pulse.TransportGetInterfaceCount(TransportHandle, &InterfaceCount);
	if (status != PULSE_STATUS_SUCCESS)
	{
		printf("TransportGetInterfaceCount failed with status %llx\n", status);
		Pulse.TransportDestroy(TransportHandle);
		return 0;
	}

	for (uint32_t iFace = 0; iFace < InterfaceCount; iFace++)
	{
		char     cInterfaceName[50] = { 0 };
		uint32_t cbBuf = 50;

		// cbBuf is an in/out parameter
		status = Pulse.TransportGetInterfaceName(TransportHandle, iFace, cInterfaceName, &cbBuf);
		if (status == PULSE_STATUS_SUCCESS)
		{
			printf("%d: %s\n", iFace, cInterfaceName);
		}
	}

	// Raw data callback is used to output the logs from the hypervisor
	status = Pulse.TransportSetRawDataCallback(TransportHandle, TestRawDataCallback, 0);
	if (status != PULSE_STATUS_SUCCESS)
	{
		printf("TransportSetRawDataCallback failed with status %llx\n", status);
		Pulse.TransportDestroy(TransportHandle);
		return 0;
	}

	// We need to set interface in order to try if it even works
	status = Pulse.TransportSetInterfaceIndex(TransportHandle, 0);
	if (status != PULSE_STATUS_SUCCESS)
	{
		status = Pulse.TransportSetInterfaceName(TransportHandle, "\\\\.\\pipe\\com_1");
		if (status != PULSE_STATUS_SUCCESS)
		{
			printf("TransportSetInterfaceIndex failed with status %llx\n", status);
			Pulse.TransportDestroy(TransportHandle);
			return 0;
		}
	}

	//
	//  Now launch the debug engine
	//

	// Create pulse debug engine instance
	status = Pulse.EngCreateEngine(&EngineHandle);
	if (status != PULSE_STATUS_SUCCESS)
	{
		printf("EngCreateEngine failed with status %llx\n", status);
		Pulse.TransportDestroy(TransportHandle);
		return 0;
	}

	// Transport assignment is required before start
	status = Pulse.EngAssignTransport(EngineHandle, TransportHandle);
	if (status != PULSE_STATUS_SUCCESS)
	{
		printf("EngAssignTransport failed with status %llx\n", status);
		Pulse.EngDestroyEngine(EngineHandle);
		Pulse.TransportDestroy(TransportHandle);
		return 0;
	}

	status = Pulse.EngStart(EngineHandle);
	if (status != PULSE_STATUS_SUCCESS)
	{
		printf("EngStart failed with status %llx\n", status);
		Pulse.EngDestroyEngine(EngineHandle);
		Pulse.TransportDestroy(TransportHandle);
		return 0;
	}

	// Ping function tests the transport connectivity
	status = Pulse.PsPing(EngineHandle);

	// Even though you can technically call any function while the guest is running,
	// there's a delay in a result due to polling rate. So if you need to perform
	// some sort of introspection, it is better to stop the guest with "BreakIn" function
	// N.B. BreakIn doesn't work on live targets (because it would deadlock otherwise)
	status = Pulse.PsBreakIn(EngineHandle);

	// Test random useful function
	char TestBuf[65536] = { 0 };
	Pulse.PsReadPhysicalMemory(EngineHandle, 0x1000, &TestBuf, sizeof(TestBuf), NULL);
	Pulse.PsReadPhysicalMemory(EngineHandle, 0x1000, &TestBuf, sizeof(TestBuf), NULL);
	Pulse.PsReadPhysicalMemory(EngineHandle, 0x1000, &TestBuf, sizeof(TestBuf), NULL);
	Pulse.PsReadPhysicalMemory(EngineHandle, 0x1000, &TestBuf, sizeof(TestBuf), NULL);
	Pulse.PsReadPhysicalMemory(EngineHandle, 0x1000, &TestBuf, sizeof(TestBuf), NULL);
	Pulse.PsReadPhysicalMemory(EngineHandle, 0x1000, &TestBuf, sizeof(TestBuf), NULL);
	Pulse.PsReadPhysicalMemory(EngineHandle, 0x1000, &TestBuf, sizeof(TestBuf), NULL);

	PS_CPU_MODE CpuMode;
	PS_CTX PsCtx = { 0 };
	Pulse.PsGetContext(EngineHandle, &PsCtx, 0, &CpuMode);
	Pulse.PsGetContext(EngineHandle, &PsCtx, DBG_CTX_PART_FULL_MASK, NULL);

	Pulse.PsReadVirtualMemory(EngineHandle, PsCtx.cr3, PsCtx.ds, PsCtx.rip, &TestBuf, sizeof(TestBuf), NULL);
	Pulse.PsReadVirtualMemory(EngineHandle, PsCtx.cr3, PsCtx.ds, PsCtx.rip, &TestBuf, sizeof(TestBuf), NULL);
	Pulse.PsReadVirtualMemory(EngineHandle, PsCtx.cr3, PsCtx.ds, PsCtx.rip, &TestBuf, sizeof(TestBuf), NULL);
	Pulse.PsReadVirtualMemory(EngineHandle, PsCtx.cr3, PsCtx.ds, PsCtx.rip, &TestBuf, sizeof(TestBuf), NULL);
	Pulse.PsReadVirtualMemory(EngineHandle, PsCtx.cr3, PsCtx.ds, PsCtx.rip, &TestBuf, sizeof(TestBuf), NULL);
	Pulse.PsReadVirtualMemory(EngineHandle, PsCtx.cr3, PsCtx.ds, PsCtx.rip, &TestBuf, sizeof(TestBuf), NULL);
	Pulse.PsReadVirtualMemory(EngineHandle, PsCtx.cr3, PsCtx.ds, PsCtx.rip, &TestBuf, sizeof(TestBuf), NULL);
	Pulse.PsReadVirtualMemory(EngineHandle, PsCtx.cr3, PsCtx.ds, PsCtx.rip, &TestBuf, sizeof(TestBuf), NULL);
	Pulse.PsReadVirtualMemory(EngineHandle, PsCtx.cr3, PsCtx.ds, PsCtx.rip, &TestBuf, sizeof(TestBuf), NULL);

	Pulse.PsReadLinearMemory(EngineHandle, PsCtx.cr3, PsCtx.rip, &TestBuf, sizeof(TestBuf), NULL);
	Pulse.PsReadLinearMemory(EngineHandle, PsCtx.cr3, PsCtx.rip, &TestBuf, sizeof(TestBuf), NULL);
	Pulse.PsReadLinearMemory(EngineHandle, PsCtx.cr3, PsCtx.rip, &TestBuf, sizeof(TestBuf), NULL);
	Pulse.PsReadLinearMemory(EngineHandle, PsCtx.cr3, PsCtx.rip, &TestBuf, sizeof(TestBuf), NULL);
	Pulse.PsReadLinearMemory(EngineHandle, PsCtx.cr3, PsCtx.rip, &TestBuf, sizeof(TestBuf), NULL);
	Pulse.PsReadLinearMemory(EngineHandle, PsCtx.cr3, PsCtx.rip, &TestBuf, sizeof(TestBuf), NULL);
	Pulse.PsReadLinearMemory(EngineHandle, PsCtx.cr3, PsCtx.rip, &TestBuf, sizeof(TestBuf), NULL);
	Pulse.PsReadLinearMemory(EngineHandle, PsCtx.cr3, PsCtx.rip, &TestBuf, sizeof(TestBuf), NULL);

	PS_CTX_EXT PsCtxExt = { 0 };
	Pulse.PsGetExtendedContext(EngineHandle, &PsCtxExt, 0xFFFFFFFFFFFFFFFF);

	// Let the target go
	status = Pulse.PsGo(EngineHandle);

	// Cleanup
	status = Pulse.EngDestroyEngine(EngineHandle);
	status = Pulse.TransportDestroy(TransportHandle);

	return 0;
}
