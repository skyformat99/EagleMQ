/*
   Copyright (c) 2012, Stanislav Yakush(st.yakush@yandex.ru)
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the EagleMQ nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
   ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
   DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
   ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef __PROTOCOL_BINARY_H__
#define __PROTOCOL_BINARY_H__

#include <stdint.h>

#define EG_FLUSH_USER_FLAG 0
#define EG_FLUSH_QUEUE_FLAG 1

typedef enum ProtocolBinaryMagic {
	EG_PROTOCOL_REQ = 0x70,
	EG_PROTOCOL_RES = 0x80,
	EG_PROTOCOL_EVENT = 0x90
} ProtocolBinaryMagic;

typedef enum ProtocolCommand {
	/* system commands (10..15) */
	EG_PROTOCOL_CMD_AUTH = 0xA,
	EG_PROTOCOL_CMD_PING = 0xB,
	EG_PROTOCOL_CMD_STAT = 0xC,
	EG_PROTOCOL_CMD_SAVE = 0xD,
	EG_PROTOCOL_CMD_FLUSH = 0xE,
	EG_PROTOCOL_CMD_DISCONNECT = 0xF,

	/* user control commands (30..34) */
	EG_PROTOCOL_CMD_USER_CREATE = 0x1E,
	EG_PROTOCOL_CMD_USER_LIST = 0x1F,
	EG_PROTOCOL_CMD_USER_RENAME = 0x20,
	EG_PROTOCOL_CMD_USER_SET_PERM = 0x21,
	EG_PROTOCOL_CMD_USER_DELETE = 0x22,

	/* queue commands (35..46) */
	EG_PROTOCOL_CMD_QUEUE_CREATE = 0x23,
	EG_PROTOCOL_CMD_QUEUE_DECLARE = 0x24,
	EG_PROTOCOL_CMD_QUEUE_EXIST = 0x25,
	EG_PROTOCOL_CMD_QUEUE_LIST = 0x26,
	EG_PROTOCOL_CMD_QUEUE_SIZE = 0x27,
	EG_PROTOCOL_CMD_QUEUE_PUSH = 0x28,
	EG_PROTOCOL_CMD_QUEUE_GET = 0x29,
	EG_PROTOCOL_CMD_QUEUE_POP = 0x2A,
	EG_PROTOCOL_CMD_QUEUE_SUBSCRIBE = 0x2B,
	EG_PROTOCOL_CMD_QUEUE_UNSUBSCRIBE = 0x2C,
	EG_PROTOCOL_CMD_QUEUE_PURGE = 0x2D,
	EG_PROTOCOL_CMD_QUEUE_DELETE = 0x2E
} ProtocolCommand;

typedef enum ProtocolResponseStatus {
	EG_PROTOCOL_SUCCESS = 0x1,
	EG_PROTOCOL_SUCCESS_AUTH = 0xA,
	EG_PROTOCOL_SUCCESS_PING = 0xB,
	EG_PROTOCOL_SUCCESS_STAT = 0xC,
	EG_PROTOCOL_SUCCESS_SAVE = 0xD,
	EG_PROTOCOL_SUCCESS_FLUSH = 0xE,
	EG_PROTOCOL_SUCCESS_USER_CREATE = 0x1E,
	EG_PROTOCOL_SUCCESS_USER_LIST = 0x1F,
	EG_PROTOCOL_SUCCESS_USER_RENAME = 0x20,
	EG_PROTOCOL_SUCCESS_USER_SET_PERM = 0x21,
	EG_PROTOCOL_SUCCESS_USER_DELETE = 0x22,
	EG_PROTOCOL_SUCCESS_QUEUE_CREATE = 0x23,
	EG_PROTOCOL_SUCCESS_QUEUE_DECLARE = 0x24,
	EG_PROTOCOL_SUCCESS_QUEUE_EXIST = 0x25,
	EG_PROTOCOL_SUCCESS_QUEUE_LIST = 0x26,
	EG_PROTOCOL_SUCCESS_QUEUE_SIZE = 0x27,
	EG_PROTOCOL_SUCCESS_QUEUE_PUSH = 0x28,
	EG_PROTOCOL_SUCCESS_QUEUE_GET = 0x29,
	EG_PROTOCOL_SUCCESS_QUEUE_POP = 0x2A,
	EG_PROTOCOL_SUCCESS_QUEUE_SUBSCRIBE = 0x2B,
	EG_PROTOCOL_SUCCESS_QUEUE_UNSUBSCRIBE = 0x2C,
	EG_PROTOCOL_SUCCESS_QUEUE_PURGE = 0x2D,
	EG_PROTOCOL_SUCCESS_QUEUE_DELETE = 0x2E,
	EG_PROTOCOL_ERROR = 0x2,
	EG_PROTOCOL_ERROR_PACKET = 0x3,
	EG_PROTOCOL_ERROR_COMMAND = 0x4,
	EG_PROTOCOL_ERROR_ACCESS = 0x5,
	EG_PROTOCOL_ERROR_AUTH = 0x85,
	EG_PROTOCOL_ERROR_PING = 0x86,
	EG_PROTOCOL_ERROR_STAT = 0x87,
	EG_PROTOCOL_ERROR_SAVE = 0x88,
	EG_PROTOCOL_ERROR_FLUSH = 0x89,
	EG_PROTOCOL_ERROR_USER_CREATE = 0x99,
	EG_PROTOCOL_ERROR_USER_LIST = 0x9A,
	EG_PROTOCOL_ERROR_USER_RENAME = 0x9B,
	EG_PROTOCOL_ERROR_USER_SET_PERM = 0x9C,
	EG_PROTOCOL_ERROR_USER_DELETE = 0x9D,
	EG_PROTOCOL_ERROR_QUEUE_CREATE = 0x9E,
	EG_PROTOCOL_ERROR_QUEUE_DECLARE = 0x9F,
	EG_PROTOCOL_ERROR_QUEUE_EXIST = 0xA0,
	EG_PROTOCOL_ERROR_QUEUE_LIST = 0xA1,
	EG_PROTOCOL_ERROR_QUEUE_SIZE = 0xA2,
	EG_PROTOCOL_ERROR_QUEUE_PUSH = 0xA3,
	EG_PROTOCOL_ERROR_QUEUE_GET = 0xA4,
	EG_PROTOCOL_ERROR_QUEUE_POP = 0xA5,
	EG_PROTOCOL_ERROR_QUEUE_SUBSCRIBE = 0xA6,
	EG_PROTOCOL_ERROR_QUEUE_UNSUBSCRIBE = 0xA7,
	EG_PROTOCOL_ERROR_QUEUE_PURGE = 0xA8,
	EG_PROTOCOL_ERROR_QUEUE_DELETE = 0xA9
} ProtocolResponseStatus;

typedef enum ProtocolEventType {
	EG_PROTOCOL_EVENT_NOTIFY = 0x1,
	EG_PROTOCOL_EVENT_MESSAGE = 0x2
} ProtocolEventType;

#pragma pack(push, 1)

typedef struct ProtocolRequestHeader {
	uint16_t magic;
	uint8_t cmd;
	uint8_t noack;
	uint32_t bodylen;
} ProtocolRequestHeader;

typedef struct ProtocolResponseHeader {
	uint16_t magic;
	uint8_t cmd;
	uint8_t status;
	uint32_t bodylen;
} ProtocolResponseHeader;

typedef struct ProtocolEventHeader {
	uint16_t magic;
	uint8_t cmd;
	uint8_t type;
	uint32_t bodylen;
} ProtocolEventHeader;

typedef struct ProtocolRequestAuth {
	ProtocolRequestHeader header;
	struct {
		char name[32];
		char password[32];
	} body;
} ProtocolRequestAuth;

typedef ProtocolRequestHeader ProtocolRequestPing;
typedef ProtocolRequestHeader ProtocolRequestStat;

typedef struct ProtocolRequestSave {
	ProtocolRequestHeader header;
	struct {
		uint8_t async;
	} body;
} ProtocolRequestSave;

typedef struct ProtocolRequestFlush {
	ProtocolRequestHeader header;
	struct {
		uint32_t flags;
	} body;
} ProtocolRequestFlush;

typedef ProtocolRequestHeader ProtocolRequestDisconnect;

typedef struct ProtocolRequestUserCreate {
	ProtocolRequestHeader header;
	struct {
		char name[32];
		char password[32];
		uint64_t perm;
	} body;
} ProtocolRequestUserCreate;

typedef ProtocolRequestHeader ProtocolRequestUserList;

typedef struct ProtocolRequestUserRename {
	ProtocolRequestHeader header;
	struct {
		char from[32];
		char to[32];
	} body;
} ProtocolRequestUserRename;

typedef struct ProtocolRequestUserSetPerm {
	ProtocolRequestHeader header;
	struct {
		char name[32];
		uint64_t perm;
	} body;
} ProtocolRequestUserSetPerm;

typedef struct ProtocolRequestUserDelete {
	ProtocolRequestHeader header;
	struct {
		char name[32];
	} body;
} ProtocolRequestUserDelete;

typedef struct ProtocolRequestQueueCreate {
	ProtocolRequestHeader header;
	struct {
		char name[64];
		uint32_t max_msg;
		uint32_t max_msg_size;
		uint32_t flags;
	} body;
} ProtocolRequestQueueCreate;

typedef struct ProtocolRequestQueueDeclare {
	ProtocolRequestHeader header;
	struct {
		char name[64];
	} body;
} ProtocolRequestQueueDeclare;

typedef struct ProtocolRequestQueueExist {
	ProtocolRequestHeader header;
	struct {
		char name[64];
	} body;
} ProtocolRequestQueueExist;

typedef ProtocolRequestHeader ProtocolRequestQueueList;

typedef struct ProtocolRequestQueueSize {
	ProtocolRequestHeader header;
	struct {
		char name[64];
	} body;
} ProtocolRequestQueueSize;

typedef struct ProtocolRequestQueueGet {
	ProtocolRequestHeader header;
	struct {
		char name[64];
	} body;
} ProtocolRequestQueueGet;

typedef struct ProtocolRequestQueuePop {
	ProtocolRequestHeader header;
	struct {
		char name[64];
	} body;
} ProtocolRequestQueuePop;

typedef struct ProtocolRequestQueueSubscribe {
	ProtocolRequestHeader header;
	struct {
		char name[64];
		uint32_t flags;
	} body;
} ProtocolRequestQueueSubscribe;

typedef struct ProtocolRequestQueueUnsubscribe {
	ProtocolRequestHeader header;
	struct {
		char name[64];
	} body;
} ProtocolRequestQueueUnsubscribe;

typedef struct ProtocolRequestQueuePurge {
	ProtocolRequestHeader header;
	struct {
		char name[64];
	} body;
} ProtocolRequestQueuePurge;

typedef struct ProtocolRequestQueueDelete {
	ProtocolRequestHeader header;
	struct {
		char name[64];
	} body;
} ProtocolRequestQueueDelete;

typedef struct ProtocolResponseStat {
	ProtocolResponseHeader header;
	struct {
		struct {
			uint8_t major;
			uint8_t minor;
			uint8_t patch;
		} version;
		uint32_t uptime;
		float used_cpu_sys;
		float used_cpu_user;
		uint32_t used_memory;
		uint32_t used_memory_rss;
		float fragmentation_ratio;
		uint32_t clients;
		uint32_t users;
		uint32_t queues;
		uint32_t resv1;
		uint32_t resv2;
		uint32_t resv3;
		uint32_t resv4;
	} body;
} ProtocolResponseStat;

typedef struct ProtocolResponseQueueExist {
	ProtocolResponseHeader header;
	struct {
		uint32_t status;
	} body;
} ProtocolResponseQueueExist;

typedef struct ProtocolResponseQueueSize {
	ProtocolResponseHeader header;
	struct {
		uint32_t size;
	} body;
} ProtocolResponseQueueSize;

typedef struct ProtocolEventQueueNotify {
	ProtocolEventHeader header;
	struct {
		char name[64];
	} body;
} ProtocolEventQueueNotify;

#pragma pack(pop)

#endif
