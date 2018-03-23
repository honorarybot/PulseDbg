#include "ps_status.h"
#include "ps_ctx.h"

#pragma once

//
//  Transport-related functions
//

typedef void* PPS_TRANSPORT;
typedef void* PPS_ENGINE;

typedef enum _PS_TRANSPORT_TYPE
{
	pttInvalid = 0,
	pttSerial = 1,
	pttPipe = 9,
	pttLocal = 10,
	pttMax = 10
} PS_TRANSPORT_TYPE, *PPS_TRANSPORT_TYPE;

typedef struct _PS_STATE_INFO
{
	uint8_t  Running;
	uint8_t  EventCode;
} PS_STATE_INFO, *PPS_STATE_INFO;

#define PS_MAX_PAGE_TABLE_ENTRIES 4

typedef enum _PS_PAGE_WALK_MODE
{
	pwmNone = 0,
	pwm32 = 1,
	pwmPae = 2,
	pwmLvl4 = 3
} PS_PAGE_WALK_MODE;

typedef struct _PS_PAGE_WALK_INFO
{
	uint16_t    NumEntries;
	uint16_t    MaxEntries;
	uint16_t    PageWalkMode;
	uint8_t     LastValidEntry;
	uint8_t     ValidTranslation;
	uint64_t    Entry[PS_MAX_PAGE_TABLE_ENTRIES];
} PS_PAGE_WALK_INFO, *PPS_PAGE_WALK_INFO;

// Transport raw data callback
typedef void (*lpfnRawDataCallback)(uintptr_t Context, void *pRawDataBuffer, uint32_t RawDataSize);

PULSE_STATUS TransportCreate(PPS_TRANSPORT *pTransport, PS_TRANSPORT_TYPE TransportType);
PULSE_STATUS TransportGetInterfaceCount(PPS_TRANSPORT pTransport, uint32_t *pInterfaceCount);
PULSE_STATUS TransportGetInterfaceName(PPS_TRANSPORT pTransport, uint32_t InterfaceIndex, char *pcInterfaceNameBuffer, uint32_t *pcbBufSize);
PULSE_STATUS TransportSetInterfaceName(PPS_TRANSPORT pTransport, char *lpcInterfaceName);
PULSE_STATUS TransportSetInterfaceIndex(PPS_TRANSPORT pTransport, uint32_t InterfaceIndex);
PULSE_STATUS TransportSetRawDataCallback(PPS_TRANSPORT pTransport, lpfnRawDataCallback RawDataCallback, uintptr_t Context);
PULSE_STATUS TransportResetConnection(PPS_TRANSPORT pTransport);
PULSE_STATUS TransportDestroy(PPS_TRANSPORT pTransport);

PULSE_STATUS  EngCreateEngine(PPS_ENGINE *ppEngine);
PULSE_STATUS  EngAssignTransport(PPS_ENGINE pEngine, PPS_TRANSPORT pTransport);
PULSE_STATUS  EngSetRequestTimeout(PPS_ENGINE pEngine, uint32_t Timeout);
PULSE_STATUS  EngStart(PPS_ENGINE pEngine);
PULSE_STATUS  EngStop(PPS_ENGINE pEngine);
PULSE_STATUS  EngDestroyEngine(PPS_ENGINE pEngine);

PULSE_STATUS  PsPing(PPS_ENGINE pEngine);
PULSE_STATUS  PsGo(PPS_ENGINE pEngine);
PULSE_STATUS  PsBreakIn(PPS_ENGINE pEngine);
PULSE_STATUS  PsStep(PPS_ENGINE pEngine, uint8_t SuppressInterrupts);
PULSE_STATUS  PsSwitchCpu(PPS_ENGINE pEngine, uint64_t TargetCpuIndex);
PULSE_STATUS  PsReboot(PPS_ENGINE pEngine);

PULSE_STATUS  PsReadVirtualMemory(PPS_ENGINE pEngine, uint64_t PageTableAddress, uint16_t SelectorValue, uint64_t Offset, void* pBuffer,
	uint64_t cbToRead, uint64_t *pcbRead);
PULSE_STATUS  PsWriteVirtualMemory(PPS_ENGINE pEngine, uint64_t PageTableAddress, uint16_t SelectorValue, uint64_t Offset, void* pBuffer,
	uint64_t cbToWrite, uint64_t* pcbWritten);
PULSE_STATUS  PsReadLinearMemory(PPS_ENGINE pEngine, uint64_t PageTableAddress, uint64_t Address, void* pBuffer,
	uint64_t cbToRead, uint64_t *pcbRead);
PULSE_STATUS  PsWriteLinearMemory(PPS_ENGINE pEngine, uint64_t PageTableAddress, uint64_t Address, void* pBuffer,
	uint64_t cbToWrite, uint64_t* pcbWritten);
PULSE_STATUS  PsReadPhysicalMemory(PPS_ENGINE pEngine, uint64_t Address, void* pBuffer,
	uint64_t cbToRead, uint64_t *pcbRead);
PULSE_STATUS  PsWritePhysicalMemory(PPS_ENGINE pEngine, uint64_t Address, void* pBuffer,
	uint64_t cbToWrite, uint64_t* pcbWritten);

PULSE_STATUS  PsGetContext(PPS_ENGINE pEngine, PPS_CTX pContext, uint64_t RegMask, PS_CPU_MODE *pCpuMode);
PULSE_STATUS  PsSetContext(PPS_ENGINE pEngine, PPS_CTX pContext, uint64_t RegMask);
PULSE_STATUS  PsGetExtendedContext(PPS_ENGINE pEngine, PPS_CTX_EXT pContextExt, uint64_t ExtRegMask);
PULSE_STATUS  PsSetExtendedContext(PPS_ENGINE pEngine, PPS_CTX_EXT pContextExt, uint64_t ExtRegMask);

PULSE_STATUS  PsReadIo(PPS_ENGINE pEngine, uint16_t Port, uint16_t AccessSize, void *pBuffer, uint32_t cbToRead, uint64_t *pcbRead);
PULSE_STATUS  PsWriteIo(PPS_ENGINE pEngine, uint16_t Port, uint16_t AccessSize, void *pBuffer, uint32_t cbToWrite, uint64_t *pcbWritten);

PULSE_STATUS  PsGetStateInfo(PPS_ENGINE pEngine, PPS_STATE_INFO pStateInfo);
PULSE_STATUS  PsGetCpuInfo(PPS_ENGINE pEngine, uint8_t *pActiveCpu, uint8_t *pCpuCount);
PULSE_STATUS  PsCpuId(PPS_ENGINE pEngine, uint32_t Leaf, uint32_t Subleaf, uint32_t CpuIdData[4]);

PULSE_STATUS  PsReadMsr(PPS_ENGINE pEngine, uint32_t MsrNumber, uint64_t *pMsrValue);
PULSE_STATUS  PsWriteMsr(PPS_ENGINE pEngine, uint32_t MsrNumber, uint64_t MsrValue);

PULSE_STATUS  PsSearchVirtualMemory(PPS_ENGINE pEngine, uint64_t PageTableAddress, uint16_t Selector, uint64_t StartOffset, uint64_t EndOffset,
	void* pPattern, uint32_t PatternSize, uint32_t SearchStep, uint8_t IgnoreGaps, uint64_t *pResult);
PULSE_STATUS  PsSearchLinearMemory(PPS_ENGINE pEngine, uint64_t PageTableAddress, uint64_t StartAddress, uint64_t EndAddress,
	void* pPattern, uint32_t PatternSize, uint32_t SearchStep, uint8_t IgnoreGaps, uint64_t *pResult);
PULSE_STATUS  PsSearchPhysicalMemory(PPS_ENGINE pEngine, uint64_t StartAddress, uint64_t EndAddress,
	void* pPattern, uint32_t PatternSize, uint32_t SearchStep, uint8_t IgnoreGaps, uint64_t *pResult);

PULSE_STATUS  PsWalkPageVirtual(PPS_ENGINE pEngine, uint64_t PageTableAddress, uint16_t Selector, uint64_t Offset,
	PPS_PAGE_WALK_INFO pPageWalkInfo);
PULSE_STATUS  PsWalkPageLinear(PPS_ENGINE pEngine, uint64_t PageTableAddress, uint64_t Address,
	PPS_PAGE_WALK_INFO pPageWalkInfo);

PULSE_STATUS  PsVirtualToPhysical(PPS_ENGINE pEngine, uint64_t PageTableAddress, uint16_t Selector, uint64_t Offset, uint64_t *pPhysicalAddress);
PULSE_STATUS  PsLinearToPhysical(PPS_ENGINE pEngine, uint64_t PageTableAddress, uint64_t Address, uint64_t *pPhysicalAddress);

PULSE_STATUS  PsSetBreakPoint(PPS_ENGINE pEngine, uint64_t PhysicalAddress, uint32_t *pBreakPointId);
PULSE_STATUS  PsRemoveBreakPoint(PPS_ENGINE pEngine, uint32_t BreakPointId);
PULSE_STATUS  PsClearBreakPoints(PPS_ENGINE pEngine);

PULSE_STATUS  PsAddBreakPointFilter(PPS_ENGINE pEngine, uint32_t BreakPointId, uint64_t PageTable, uint64_t Address, uint64_t ThreadBase, uint16_t Selector);
PULSE_STATUS  PsRemoveBreakPointFilter(PPS_ENGINE pEngine, uint32_t BreakPointId, uint64_t PageTable, uint64_t Address, uint64_t ThreadBase, uint16_t Selector);
