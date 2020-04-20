/* See LICENSE file for copyright and license details. */

#define LIBAXL_ERROR 0

struct libaxl_error_request {
#define LIBAXL_ERROR_REQUEST 1
	uint8_t             __zero;
	uint8_t             code;
	uint16_t            sequence_number;
	uint32_t            __unused1;
	uint16_t            minor_opcode;
	uint8_t             major_opcode;
	uint8_t             __unused[21];
};

struct libaxl_error_value {
#define LIBAXL_ERROR_VALUE 2
	uint8_t             __zero;
	uint8_t             code;
	uint16_t            sequence_number;
	uint32_t            bad_value;
	uint16_t            minor_opcode;
	uint8_t             major_opcode;
	uint8_t             __unused[21];
};

struct libaxl_error_window {
#define LIBAXL_ERROR_WINDOW 3
	uint8_t             __zero;
	uint8_t             code;
	uint16_t            sequence_number;
	uint32_t            bad_resource_id;
	uint16_t            minor_opcode;
	uint8_t             major_opcode;
	uint8_t             __unused[21];
};

struct libaxl_error_pixmap {
#define LIBAXL_ERROR_PIXMAP 4
	uint8_t             __zero;
	uint8_t             code;
	uint16_t            sequence_number;
	uint32_t            bad_resource_id;
	uint16_t            minor_opcode;
	uint8_t             major_opcode;
	uint8_t             __unused[21];
};

struct libaxl_error_atom {
#define LIBAXL_ERROR_ATOM 5
	uint8_t             __zero;
	uint8_t             code;
	uint16_t            sequence_number;
	uint32_t            bad_resource_id;
	uint16_t            minor_opcode;
	uint8_t             major_opcode;
	uint8_t             __unused[21];
};

struct libaxl_error_cursor {
#define LIBAXL_ERROR_CURSOR 6
	uint8_t             __zero;
	uint8_t             code;
	uint16_t            sequence_number;
	uint32_t            bad_resource_id;
	uint16_t            minor_opcode;
	uint8_t             major_opcode;
	uint8_t             __unused[21];
};

struct libaxl_error_font {
#define LIBAXL_ERROR_FONT 7
	uint8_t             __zero;
	uint8_t             code;
	uint16_t            sequence_number;
	uint32_t            bad_resource_id;
	uint16_t            minor_opcode;
	uint8_t             major_opcode;
	uint8_t             __unused[21];
};

struct libaxl_error_match {
#define LIBAXL_ERROR_MATCH 8
	uint8_t             __zero;
	uint8_t             code;
	uint16_t            sequence_number;
	uint32_t            __unused1;
	uint16_t            minor_opcode;
	uint8_t             major_opcode;
	uint8_t             __unused[21];
};

struct libaxl_error_drawable {
#define LIBAXL_ERROR_DRAWABLE 9
	uint8_t             __zero;
	uint8_t             code;
	uint16_t            sequence_number;
	uint32_t            bad_resource_id;
	uint16_t            minor_opcode;
	uint8_t             major_opcode;
	uint8_t             __unused[21];
};

struct libaxl_error_access {
#define LIBAXL_ERROR_ACCESS 10
	uint8_t             __zero;
	uint8_t             code;
	uint16_t            sequence_number;
	uint32_t            __unused1;
	uint16_t            minor_opcode;
	uint8_t             major_opcode;
	uint8_t             __unused[21];
};

struct libaxl_error_alloc {
#define LIBAXL_ERROR_ALLOC 11
	uint8_t             __zero;
	uint8_t             code;
	uint16_t            sequence_number;
	uint32_t            __unused1;
	uint16_t            minor_opcode;
	uint8_t             major_opcode;
	uint8_t             __unused[21];
};

struct libaxl_error_colormap {
#define LIBAXL_ERROR_COLORMAP 12
	uint8_t             __zero;
	uint8_t             code;
	uint16_t            sequence_number;
	uint32_t            bad_resource_id;
	uint16_t            minor_opcode;
	uint8_t             major_opcode;
	uint8_t             __unused[21];
};

struct libaxl_error_gcontext {
#define LIBAXL_ERROR_GCONTEXT 13
	uint8_t             __zero;
	uint8_t             code;
	uint16_t            sequence_number;
	uint32_t            bad_resource_id;
	uint16_t            minor_opcode;
	uint8_t             major_opcode;
	uint8_t             __unused[21];
};

struct libaxl_error_id_choice {
#define LIBAXL_ERROR_ID_CHOICE 14
	uint8_t             __zero;
	uint8_t             code;
	uint16_t            sequence_number;
	uint32_t            bad_resource_id;
	uint16_t            minor_opcode;
	uint8_t             major_opcode;
	uint8_t             __unused[21];
};

struct libaxl_error_name {
#define LIBAXL_ERROR_NAME 15
	uint8_t             __zero;
	uint8_t             code;
	uint16_t            sequence_number;
	uint32_t            __unused1;
	uint16_t            minor_opcode;
	uint8_t             major_opcode;
	uint8_t             __unused[21];
};

struct libaxl_error_length {
#define LIBAXL_ERROR_LENGTH 16
	uint8_t             __zero;
	uint8_t             code;
	uint16_t            sequence_number;
	uint32_t            __unused1;
	uint16_t            minor_opcode;
	uint8_t             major_opcode;
	uint8_t             __unused[21];
};

struct libaxl_error_implementation {
#define LIBAXL_ERROR_IMPLEMENTATION 17
	uint8_t             __zero;
	uint8_t             code;
	uint16_t            sequence_number;
	uint32_t            __unused1;
	uint16_t            minor_opcode;
	uint8_t             major_opcode;
	uint8_t             __unused[21];
};

union libaxl_error {
	struct {
		uint8_t     __zero;
		uint8_t     code;
		uint16_t    sequence_number;
		uint32_t    __detail;
		uint16_t    minor_opcode;
		uint8_t     major_opcode;
	};
#include "libaxl-errors-structs.h"
};
