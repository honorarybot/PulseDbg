#include <stdint.h>

#pragma once

typedef int64_t PULSE_STATUS;

#define PULSE_SUCCESS(x) (((int32_t)x)>=0)

#define PULSE_STATUS_SUCCESS                                       0x00000000
#define PULSE_STATUS_PARTIAL_READ                                  0x00000005
#define PULSE_STATUS_PARTIAL_WRITE                                 0x00000006
#define PULSE_STATUS_UNSUCCESSFUL                                  0xC0000000
#define PULSE_STATUS_TIMEOUT                                       0xC0000002
#define PULSE_STATUS_ENGINE_INIT_FAILED                            0xC0000003
#define PULSE_STATUS_INSUFFICIENT_RESOURCES                        0xC0000008
#define PULSE_STATUS_TRANSPORT_INIT_FAILED                         0xC000000A
#define PULSE_STATUS_INVALID_PARAMETER                             0xC000000E
#define PULSE_STATUS_NOT_SUPPORTED                                 0xC000000D
#define PULSE_STATUS_INVALID_TRANSLATION                           0xC0000017
#define PULSE_STATUS_NO_PACKET                                     0xC0000018
#define PULSE_STATUS_BUFFER_OVERFLOW                               0xC000001A
#define PULSE_STATUS_INVALID_CHECKSUM                              0xC000001B
#define PULSE_STATUS_INVALID_START_OF_PACKET                       0xC0000046
#define PULSE_STATUS_INVALID_END_OF_PACKET                         0xC000001C
#define PULSE_STATUS_INVALID_PACKET                                0xC000001D
#define PULSE_STATUS_INVALID_CPU_MODE                              0xC000001F
#define PULSE_STATUS_PACKET_TOO_LARGE                              0xC0000020
#define PULSE_STATUS_TRANSPORT_RESET_FAILED                        0xC000002A
#define PULSE_STATUS_READ_FAILED                                   0xC000002B
#define PULSE_STATUS_WRITE_FAILED                                  0xC000002C
#define PULSE_STATUS_DEVICE_NOT_FOUND                              0xC000002D
#define PULSE_STATUS_DEVICE_MISCONFIGURATION                       0xC000002E
#define PULSE_STATUS_DEVICE_INIT_FAILED                            0xC000002F
#define PULSE_STATUS_GENERAL_PROTECTION                            0xC0000045
#define PULSE_STATUS_PATTERN_NOT_FOUND                             0xC0000060
#define PULSE_STATUS_BREAKPOINT_TABLE_EMPTY                        0xC0000050
#define PULSE_STATUS_BREAKPOINT_NOT_FOUND                          0xC0000051
#define PULSE_STATUS_BREAKPOINT_TABLE_FULL                         0xC0000052
#define PULSE_STATUS_BREAKPOINT_NOT_HIT                            0xC0000053
#define PULSE_STATUS_FILTER_TABLE_FULL                             0xC0000054
#define PULSE_STATUS_FILTER_TABLE_EMPTY                            0xC0000055
#define PULSE_STATUS_FILTER_NOT_FOUND                              0xC0000056
#define PULSE_STATUS_NOT_ALIGNED                                   0xC0000061
#define PULSE_STATUS_INVALID_ACCESS_SIZE                           0xC0000062
#define PULSE_STATUS_INVALID_TYPE                                  0xC0000063
#define PULSE_STATUS_INVALID_LENGTH                                0xC0000064
#define PULSE_STATUS_INVALID_REQUEST                               0xC0000065
