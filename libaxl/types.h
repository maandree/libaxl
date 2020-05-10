/* See LICENSE file for copyright and license details. */

#if !defined(LIBAXL_H) || (LIBAXL_H < 2)
# error Do not include <libaxl/types.h> directly, include <libaxl.h> instead.
#endif

#include <stddef.h>
#include <stdint.h>

typedef uint32_t    libaxl_id_t;
typedef libaxl_id_t libaxl_window_t;
typedef libaxl_id_t libaxl_pixmap_t;
typedef libaxl_id_t libaxl_cursor_t;
typedef libaxl_id_t libaxl_font_t;
typedef libaxl_id_t libaxl_gcontext_t;
typedef libaxl_id_t libaxl_colormap_t;
typedef libaxl_id_t libaxl_drawable_t;             /* libaxl_window_t or libaxl_pixmap_t */
typedef libaxl_id_t libaxl_fontable_t;             /* libaxl_font_t or libaxl_gcontext_t */
typedef libaxl_id_t libaxl_atom_t;
typedef libaxl_id_t libaxl_visual_t;
typedef uint32_t    libaxl_timestamp_t;
typedef uint32_t    libaxl_keysym_t;
typedef uint8_t     libaxl_keycode_t;
typedef uint8_t     libaxl_button_t;
typedef uint8_t     libaxl_bool_t;
typedef uint16_t    libaxl_keybutmask_t;

struct libaxl_point {
	int16_t            x;
	int16_t            y;
};

struct libaxl_segment {
	int16_t            x1;
	int16_t            y1;
	int16_t            x2;
	int16_t            y2;
};

struct libaxl_rectangle {
	int16_t            x;                    /* rightward offset from upper-left corner */
	int16_t            y;                    /* downward offset from upper-left corner */
	uint16_t           width;
	uint16_t           height;
};

struct libaxl_arc {
	int16_t            x;
	int16_t            y;
	uint16_t           width;
	uint16_t           height;
	int16_t            angle1;
	int16_t            angle2;
};

struct libaxl_char2b {
	uint8_t            byte1;
	uint8_t            byte2;
};

union libaxl_text_item8 {
	struct {
		uint8_t    length_of_string;     /* cannot be LIBAXL_FONT_SHIFT_INDICATOR (= 255) */
		int8_t     delta;
		char      *string;
	};
	struct {
		uint8_t    font_shift_indicator; /* must be LIBAXL_FONT_SHIFT_INDICATOR (= 255) */
		uint8_t    font_byte_3;          /* (most-significant) */
		uint8_t    font_byte_2;
		uint8_t    font_byte_1;
		uint8_t    font_byte_0;          /* (least-significant) */
	};
};

union libaxl_text_item16 {
	struct {
		uint8_t    length_of_string;     /* in number of CHAR2Bs, cannot be LIBAXL_FONT_SHIFT_INDICATOR (= 255) */
		int8_t     delta;
		uint16_t  *string;
	};
	struct {
		uint8_t    font_shift_indicator; /* must be LIBAXL_FONT_SHIFT_INDICATOR (= 255) */
		uint8_t    font_byte_3;          /* (most-significant) */
		uint8_t    font_byte_2;
		uint8_t    font_byte_1;
		uint8_t    font_byte_0;          /* (least-significant) */
	};
};

struct libaxl_coloritem {
	uint32_t           pixel;
	uint16_t           red;
	uint16_t           green;
	uint16_t           blue;
	uint8_t            flags;                /* See libaxl-consts.h */
	uint8_t            __unused;
};

struct libaxl_timecoord {
	libaxl_timestamp_t time;
	int16_t            x;
	int16_t            y;
};

struct libaxl_fontprop {
	libaxl_atom_t      name;
	uint32_t           value;                /* <32-bits> */
};

struct libaxl_charinfo {
	int16_t            left_side_bearing;
	int16_t            right_side_bearing;
	int16_t            character_width;
	int16_t            ascent;
	int16_t            descent;
	uint16_t           attributes;
};

struct libaxl_rgb16 {
	uint16_t           red;
	uint16_t           green;
	uint16_t           blue;
	uint16_t           __unused;
};

struct libaxl_str8 {
	uint8_t            length;
	char              *name;
};

struct libaxl_host {
	uint8_t            family;               /* See libaxl-consts.h */
	uint8_t            __pad;
	uint16_t           length_of_address;
	uint8_t           *address;
};
