/* See LICENSE file for copyright and license details. */

#if !defined(LIBAXL_H) || (LIBAXL_H < 2)
# error Do not include <libaxl/replies.h> directly, include <libaxl.h> instead.
#endif

#define LIBAXL_REPLY 1 /* TODO man */

struct libaxl_reply_get_window_attributes {
	uint8_t                   __one;
	uint8_t                   backing_store;         /* LIBAXL_NOT_USEFUL, LIBAXL_WHEN_MAPPED, or LIBAXL_ALWAYS */
	uint16_t                  sequence_number;
	uint32_t                  _reply_length;         /* = 3 */
	libaxl_visual_t           visual;
	uint16_t                  class;                 /* LIBAXL_INPUT_OUTPUT (= 1) or LIBAXL_INPUT_ONLY (= 2) */
	uint8_t                   bit_gravity;
	uint8_t                   win_gravity;
	uint32_t                  backing_planes;
	uint32_t                  backing_pixel;
	libaxl_bool_t             save_under;
	libaxl_bool_t             map_is_installed;
	uint8_t                   map_state;             /* LIBAXL_UNMAPPED, LIBAXL_UNVIEWABLE, or LIBAXL_VIEWABLE */
	libaxl_bool_t             override_redirect;
	libaxl_colormap_t         colormap;              /* Can be LIBAXL_NONE */
	uint32_t                  all_event_masks;       /* TODO SETofEVENT */
	uint32_t                  your_event_mask;       /* TODO SETofEVENT */
	uint16_t                  do_not_propagate_mask; /* TODO SETofDEVICEEVENT */
	uint16_t                  __pad;
};

struct libaxl_reply_get_geometry {
	uint8_t                   __one;
	uint8_t                   depth;
	uint16_t                  sequence_number;
	uint32_t                  _reply_length;         /* = 0 */
	libaxl_window_t           root;
	int16_t                   x;
	int16_t                   y;
	uint16_t                  width;
	uint16_t                  height;
	uint16_t                  border_width;
	uint8_t                   __unused[10];
};

struct libaxl_reply_query_tree {
	uint8_t                   __one;
	uint8_t                   __pad;
	uint16_t                  sequence_number;
	uint32_t                  _reply_length;         /* = .number_of_children */
	libaxl_window_t           root;
	libaxl_window_t           parent;                /* Can be LIBAXL_NONE */
	uint16_t                  number_of_children;
	uint8_t                   __unused[14];
	libaxl_window_t          *children;
};

struct libaxl_reply_intern_atom {
	uint8_t                   __one;
	uint8_t                   __pad;
	uint16_t                  sequence_number;
	uint32_t                  _reply_length;         /* = 0 */
	libaxl_atom_t             atom;                  /* Can be LIBAXL_NONE */
	uint8_t                   __unused[20];
};

struct libaxl_reply_get_atom_name {
	uint8_t                   __one;
	uint8_t                   __pad;
	uint16_t                  sequence_number;
	uint32_t                  _reply_length;
	uint16_t                  length_of_name;
	uint8_t                   __unused[22];
	char                     *name;
};

struct libaxl_reply_get_property {
	uint8_t                   __one;
	uint8_t                   format;                /* {0 = 0, 8 = 8, 16 = 16, 32 = 32}*/
	uint16_t                  sequence_number;
	uint32_t                  _reply_length;
	libaxl_atom_t             type;                  /* Can be LIBAXL_NONE */
	uint32_t                  bytes_after;
	uint32_t                  length_of_value;       /* in format units */
	uint8_t                   __unused[12];
	union {
		char             *value;
		uint8_t          *value8;
		uint16_t         *value16;
		uint32_t         *value32;
	};
};

struct libaxl_reply_list_properties {
	uint8_t                   __one;
	uint8_t                   __pad;
	uint16_t                  sequence_number;
	uint32_t                  _reply_length;
	uint16_t                  number_of_atoms;
	uint8_t                   __unused[22];
	libaxl_atom_t            *atoms;
};

struct libaxl_reply_get_selection_owner {
	uint8_t                   __one;
	uint8_t                   __pad;
	uint16_t                  sequence_number;
	uint32_t                  _reply_length;         /* = 0 */
	libaxl_window_t           owner;                 /* Can be LIBAXL_NONE */
	uint8_t                   __unused[20];
};

struct libaxl_reply_grab_pointer {
	uint8_t                   __one;
	uint8_t                   status;                /* See "grab status" in libaxl-consts.h */
	uint16_t                  sequence_number;
	uint32_t                  _reply_length;         /* = 0 */
	uint8_t                   __unused[24];
};

struct libaxl_reply_grab_keyboard {
	uint8_t                   __one;
	uint8_t                   status;                /* See "grab status" in libaxl-consts.h */
	uint16_t                  sequence_number;
	uint32_t                  _reply_length;         /* = 0 */
	uint8_t                   __unused[24];
};

struct libaxl_reply_query_pointer {
	uint8_t                   __one;
	libaxl_bool_t             same_screen;
	uint16_t                  sequence_number;
	uint32_t                  _reply_length;         /* = 0 */
	libaxl_window_t           root;
	libaxl_window_t           child;                 /* Can be LIBAXL_NONE */
	int16_t                   root_x;
	int16_t                   root_y;
	int16_t                   win_x;
	int16_t                   win_y;
	libaxl_keybutmask_t       mask;                  /* TODO ? SETofKEYBUTMASK shouldn't have its own type */
	uint8_t                   __unused[6];
};

struct libaxl_reply_get_motion_events {
	uint8_t                   __one;
	libaxl_bool_t             same_screen;
	uint16_t                  sequence_number;
	uint32_t                  _reply_length;         /* = 2 * .number_of_events */
	uint32_t                  number_of_events;
	uint8_t                   __unused[20];
	struct libaxl_timecoord  *events;
};

struct libaxl_reply_translate_coordinates {
	uint8_t                   __one;
	libaxl_bool_t             same_screen;
	uint16_t                  sequence_number;
	uint32_t                  _reply_length;         /* = 0 */
	libaxl_window_t           child;                 /* Can be LIBAXL_NONE */
	int16_t                   dest_x;
	int16_t                   dest_y;
	int8_t                    __unused[16];
};

struct libaxl_reply_get_input_focus {
	uint8_t                   __one;
	uint8_t                   revert_to;             /* LIBAXL_NONE, LIBAXL_POINTER_ROOT, or LIBAXL_PARENT */
	uint16_t                  sequence_number;
	uint32_t                  _reply_length;         /* = 0 */
	libaxl_window_t           focus;                 /* Can be LIBAXL_NONE or LIBAXL_POINTER_ROOT */
	int8_t                    __unused[20];
};

struct libaxl_reply_query_keymap {
	uint8_t                   __one;
	uint8_t                   __pad;
	uint16_t                  sequence_number;
	uint32_t                  _reply_length;         /* = 2 */
	uint8_t                   keys[32];
};

struct libaxl_reply_query_font {
	uint8_t                   __one;
	uint8_t                   __pad;
	uint16_t                  sequence_number;
	uint32_t                  _reply_length;
	struct libaxl_charinfo    min_bounds;
	uint32_t                  __unused1;
	struct libaxl_charinfo    max_bounds;
	uint32_t                  __unused2;
	uint16_t                  min_char_or_byte2;
	uint16_t                  max_char_or_byte2;
	uint16_t                  default_char;
	uint16_t                  number_of_properties;
	uint8_t                   draw_direction;        /* LIBAXL_LEFT_TO_RIGHT or LIBAXL_RIGHT_TO_LEFT */
	uint8_t                   min_byte1;
	uint8_t                   max_byte1;
	libaxl_bool_t             all_chars_exist;
	int16_t                   font_ascent;
	int16_t                   font_descent;
	uint32_t                  number_of_char_infos;
	struct libaxl_fontprop   *properties;
	struct libaxl_charinfo   *char_infos;
};

struct libaxl_reply_query_text_extents {
	uint8_t                   __one;
	uint8_t                   draw_direction;        /* LIBAXL_LEFT_TO_RIGHT or LIBAXL_RIGHT_TO_LEFT */
	uint16_t                  sequence_number;
	uint32_t                  _reply_length;         /* = 0 */
	int16_t                   font_ascent;
	int16_t                   font_descent;
	int16_t                   overall_ascent;
	int16_t                   overall_descent;
	int32_t                   overall_width;
	int32_t                   overall_left;
	int32_t                   overall_right;
	uint8_t                   __unused[4];
};

struct libaxl_reply_list_fonts {
	uint8_t                   __one;
	uint8_t                   __pad;
	uint16_t                  sequence_number;
	uint32_t                  _reply_length;
	uint16_t                  number_of_names;
	uint8_t                   __unused[22];
	struct libaxl_str8       *names;
};

struct libaxl_reply_list_fonts_with_info {
	uint8_t                   __one;
	uint8_t                   length_of_name;        /* 0 = end of series */
	uint16_t                  sequence_number;
	uint32_t                  _reply_length;         /* = 7 if .length_of_name = 0 */

	/* the rest (52 bytes) are unused if .length_of_name = 0 */
	struct libaxl_charinfo    min_bounds;
	uint32_t                  __unused1;
	struct libaxl_charinfo    max_bounds;
	uint32_t                  __unused2;
	uint16_t                  min_char_or_byte2;
	uint16_t                  max_char_or_byte2;
	uint16_t                  default_char;
	uint16_t                  number_of_properties;
	uint8_t                   draw_direction;        /* LIBAXL_LEFT_TO_RIGHT or LIBAXL_RIGHT_TO_LEFT */
	uint8_t                   min_byte1;
	uint8_t                   max_byte1;
	libaxl_bool_t             all_chars_exist;
	int16_t                   font_ascent;
	int16_t                   font_descent;
	uint32_t                  replies_hint;
	struct libaxl_fontprop   *properties;
	char                     *name;
};

struct libaxl_reply_get_font_path {
	uint8_t                   __one;
	uint8_t                   __pad;
	uint16_t                  sequence_number;
	uint32_t                  _reply_length;
	uint16_t                  number_of_strs;
	uint8_t                   __unused[22];
	struct libaxl_str8       *path;
};

struct libaxl_reply_get_image {
	uint8_t                   __one;
	uint8_t                   depth;
	uint16_t                  sequence_number;
	uint32_t                  _reply_length;
	libaxl_visual_t           visual;                /* Can be LIBAXL_NONE */
	uint8_t                   __unused[20];
	size_t                    size_of_data;
	uint8_t                  *data;
};

struct libaxl_reply_list_installed_colormaps {
	uint8_t                   __one;
	uint8_t                   __pad;
	uint16_t                  sequence_number;
	uint32_t                  _reply_length;         /* = .number_of_cmaps */
	uint16_t                  number_of_cmaps;
	uint8_t                   __unused[22];
	libaxl_colormap_t        *cmaps;
};

struct libaxl_reply_alloc_color {
	uint8_t                   __one;
	uint8_t                   __pad1;
	uint16_t                  sequence_number;
	uint32_t                  _reply_length;         /* = 0 */
	uint16_t                  red;
	uint16_t                  green;
	uint16_t                  blue;
	uint16_t                  __pad2;
	uint32_t                  pixel;
	uint8_t                   __unused[12];
};

struct libaxl_reply_alloc_named_color {
	uint8_t                   __one;
	uint8_t                   __pad1;
	uint16_t                  sequence_number;
	uint32_t                  _reply_length;         /* = 0 */
	uint32_t                  pixel;
	uint16_t                  exact_red;
	uint16_t                  exact_green;
	uint16_t                  exact_blue;
	uint16_t                  visual_red;
	uint16_t                  visual_green;
	uint16_t                  visual_blue;
	uint8_t                   __unused[8];
};

struct libaxl_reply_alloc_color_cells {
	uint8_t                   __one;
	uint8_t                   __pad;
	uint16_t                  sequence_number;
	uint32_t                  _reply_length;
	uint16_t                  number_of_pixels;
	uint16_t                  number_of_masks;
	uint8_t                   __used[20];
	uint32_t                 *pixels;
	uint32_t                 *mask;
};

struct libaxl_reply_alloc_color_planes {
	uint8_t                   __one;
	uint8_t                   __pad1;
	uint16_t                  sequence_number;
	uint32_t                  _reply_length;         /* = .number_of_pixels */
	uint16_t                  number_of_pixels;
	uint16_t                  __pad2;
	uint32_t                  red_mask;
	uint32_t                  green_mask;
	uint32_t                  blue_mask;
	uint8_t                   __unused[8];
	uint32_t                 *pixels;
};

struct libaxl_reply_query_colors {
	uint8_t                   __one;
	uint8_t                   __pad;
	uint16_t                  sequence_number;
	uint32_t                  _reply_length;         /* = 2 * .number_of_colors */
	uint16_t                  number_of_colors;
	uint8_t                   __unused[22];
	struct libaxl_rgb16      *colors;
};

struct libaxl_reply_lookup_color {
	uint8_t                   __one;
	uint8_t                   __pad;
	uint16_t                  sequence_number;
	uint32_t                  _reply_length;         /* = 0 */
	uint16_t                  exact_red;
	uint16_t                  exact_green;
	uint16_t                  exact_blue;
	uint16_t                  visual_red;
	uint16_t                  visual_green;
	uint16_t                  visual_blue;
	uint8_t                   __unused[12];
};

struct libaxl_reply_query_best_size {
	uint8_t                   __one;
	uint8_t                   __pad;
	uint16_t                  sequence_number;
	uint32_t                  _reply_length;         /* = 0 */
	uint16_t                  width;
	uint16_t                  height;
	uint8_t                   __unused[20];
};

struct libaxl_reply_query_extension {
	uint8_t                   __one;
	uint8_t                   __pad;
	uint16_t                  sequence_number;
	uint32_t                  _reply_length;         /* = 0 */
	libaxl_bool_t             present;
	uint8_t                   major_opcode;
	uint8_t                   first_event;
	uint8_t                   first_error;
	uint8_t                   __unused[20];
};

struct libaxl_reply_list_extensions {
	uint8_t                   __one;
	uint8_t                   number_of_names;
	uint16_t                  sequence_number;
	uint32_t                  _reply_length;
	uint8_t                   __unused[24];
	struct libaxl_str8       *names;
};

struct libaxl_reply_get_keyboard_mapping {
	uint8_t                   __one;
	uint8_t                   keysyms_per_keycode;
	uint16_t                  sequence_number;
	uint32_t                  _reply_length;         /* = count field from the request divided by .keysyms_per_keycode */
	uint8_t                   __unused[24];
	libaxl_keysym_t          *keysyms;
};

struct libaxl_reply_get_keyboard_control {
	uint8_t                   __one;
	uint8_t                   global_auto_repeat;    /* LIBAXL_OFF or LIBAXL_ON */
	uint16_t                  sequence_number;
	uint32_t                  _reply_length;         /* = 5 */
	uint32_t                  led_mask;
	uint8_t                   key_click_percent;
	uint8_t                   bell_percent;
	uint16_t                  bell_pitch;
	uint16_t                  bell_duration;
	uint16_t                  __unused;
	uint8_t                   auto_repeats[32];
};

struct libaxl_reply_get_pointer_control {
	uint8_t                   __one;
	uint8_t                   __pad;
	uint16_t                  sequence_number;
	uint32_t                  _reply_length;         /* = 0 */
	uint16_t                  acceleration_numerator;
	uint16_t                  acceleration_denominator;
	uint16_t                  threshold;
	uint8_t                   __unused[18];
};

struct libaxl_reply_get_screen_saver {
	uint8_t                   __one;
	uint8_t                   __pad;
	uint16_t                  sequence_number;
	uint32_t                  _reply_length;         /* = 0 */
	uint16_t                  timeout;
	uint16_t                  interval;
	uint8_t                   prefer_blanking;       /* LIBAXL_NO or LIBAXL_YES */
	uint8_t                   allow_exposures;       /* LIBAXL_NO or LIBAXL_YES */
	uint8_t                   __unused[18];
};

struct libaxl_reply_list_hosts {
	uint8_t                   __one;
	uint8_t                   mode;                  /* LIBAXL_DISABLED or LIBAXL_ENABLED */
	uint16_t                  sequence_number;
	uint32_t                  _reply_length;         /* = 0 */
	uint16_t                  number_of_hosts;
	uint8_t                   __unused[22];
	struct libaxl_host       *hosts;
};

struct libaxl_reply_set_pointer_mapping {
	uint8_t                   __one;
	uint8_t                   status;                /* LIBAXL_SUCCESS or LIBAXL_BUSY */
	uint16_t                  sequence_number;
	uint32_t                  _reply_length;         /* = 0 */
	uint8_t                   __unused[24];
};

struct libaxl_reply_get_pointer_mapping {
	uint8_t                   __one;
	uint8_t                   length_of_map;
	uint16_t                  sequence_number;
	uint32_t                  _reply_length;
	uint8_t                   __unused[24];
	uint8_t                  *map;
};

struct libaxl_reply_set_modifier_mapping {
	uint8_t                   __one;
	uint8_t                   status;                /* LIBAXL_SUCCESS, LIBAXL_BUSY, or LIBAXL_FAILED */
	uint16_t                  sequence_number;
	uint32_t                  _reply_length;         /* = 0 */
	uint8_t                   __unused[24];
};

struct libaxl_reply_get_modifier_mapping {
	uint8_t                   __one;
	uint8_t                   keycodes_per_modifier; /* pairs */
	uint16_t                  sequence_number;
	uint32_t                  _reply_length;         /* = 2 * .keycodes_per_modifier */
	uint8_t                   __unused[24];
	libaxl_keycode_t         *keycodes;
};

union libaxl_reply {
	struct {
		uint8_t           __one;
		uint8_t           __data;
		uint16_t          sequence_number;
		uint32_t          _reply_length;
	};
#include "replies-structs.h"
};
