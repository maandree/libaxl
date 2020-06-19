/* See LICENSE file for copyright and license details. */

#if !defined(LIBAXL_H) || (LIBAXL_H < 2)
# error Do not include <libaxl/display-info.h> directly, include <libaxl.h> instead.
#endif

/**
 * The highest number of the `struct_version` field in
 * `struct libaxl_display_info` that this header file
 * supports
 */
#define LIBAXL_DISPLAY_INFO_VERSION 0

/**
 * Standard byte orders
 */
enum libaxl_byte_order {
	/**
	 * Least significant byte first
	 */
	LIBAXL_LSB_FIRST,

	/**
	 * Most significant byte first
	 */
	LIBAXL_MSB_FIRST
};

/**
 * Standard bit orders
 */
enum libaxl_bit_order {
	/**
	 * Least significant bit leftmost
	 */
	LIBAXL_LSB_LEFTMOST,

	/**
	 * Most significant bit leftmost
	 */
	LIBAXL_MSB_LEFTMOST
};

struct libaxl_format {
	uint8_t depth;
	uint8_t bits_per_pixel;
	uint8_t scanline_pad;
	uint8_t __unused[5];
};

struct libaxl_visual_type {
	libaxl_visual_t visual_id;
	uint8_t class;                /* LIBAXL_{STATIC_GRAY, GRAY_SCALE, STATIC_COLOR, PSEUDO_COLOR, TRUE_COLOR, DIRECT_COLOR} */
	uint8_t bits_per_rgb_value;
	uint16_t colormap_entries;
	uint32_t red_mask;
	uint32_t green_mask;
	uint32_t blue_mask;
	uint32_t __unused;
};

struct libaxl_depth {
	uint8_t depth;
	uint8_t __pad;
	uint16_t number_of_visuals;
	uint32_t __unused;
	struct libaxl_visual_type visuals[];
};

/**
 * Screen information
 */
struct libaxl_screen {
	/**
	 * The root window of the screen
	 * 
	 * This is always an LIBAXL_INPUT_OUTPUT window
	 */
	libaxl_window_t root;

	/**
	 * The map initially associated with the root window
	 * 
	 * Windows with minimal colour requires may want to
	 * use this colormap if they use the same depth as
	 * the root window.
	 */
	libaxl_colormap_t default_colormap;

	/**
	 * Bright colour usable for implementing monochrome
	 * applications using `.default_colormap`
	 * 
	 * This colour is permanently allocated
	 * 
	 * May be set to a dark colour on some screens
	 * (that what the colours to be inverted); the
	 * actual RGB value is unspecified and may any
	 * colour and not necessarily black or white
	 */
	uint32_t white_pixel;

	/**
	 * Dark colour usable for implementing monochrome
	 * applications using `.default_colormap`
	 * 
	 * This colour is permanently allocated
	 * 
	 * May be set to a bright colour on some screens
	 * (that what the colours to be inverted); the
	 * actual RGB value is unspecified and may any
	 * colour and not necessarily black or white
	 */
	uint32_t black_pixel;

	uint32_t current_input_masks; /* TODO SETofEVENTS */

	/**
	 * The width, in pixels, of the root window;
	 * which cannot be changed in the core protocol
	 * 
	 * This value will not update when root window
	 * is resized, but new connections may get an
	 * update value
	 */
	uint16_t width_in_pixels;

	/**
	 * The height, in pixels, of the root window;
	 * which cannot be changed in the core protocol
	 * 
	 * This value will not update when root window
	 * is resized, but new connections may get an
	 * update value
	 */
	uint16_t height_in_pixels;

	/**
	 * The width, in millimeters, of the root window;
	 * which cannot be changed in the core protocol
	 * 
	 * This value will not update when root window
	 * is resized or the monitor is changed
	 * 
	 * Note that the horizontal and vertical DPI
	 * (dots per inch) of a monitor are not
	 * necessarily equal to each other
	 */
	uint16_t width_in_millimeters;

	/**
	 * The height, in millimeters, of the root window;
	 * which cannot be changed in the core protocol
	 * 
	 * This value will not update when root window
	 * is resized or the monitor is changed
	 * 
	 * Note that the horizontal and vertical DPI
	 * (dots per inch) of a monitor are not
	 * necessarily equal to each other
	 */
	uint16_t height_in_millimeters;

	uint16_t min_installed_maps;
	uint16_t max_installed_maps;
	libaxl_visual_t root_visual;
	uint8_t backing_stores;
	libaxl_bool_t save_under;
	uint8_t root_depth;
	uint8_t number_of_allowed_depths;
	struct libaxl_depth allowed_depths[];
};

/**
 * Information about the display, display server, and connection
 */
struct libaxl_display_info {
	/**
	 * The version number of this structure that this library uses.
	 * When using dynamic linking, is important use the version that
	 * is the lowest of the number stored in this field and the
	 * number stored in the LIBAXL_DISPLAY_INFO_VERSION constant.
	 */
	int struct_version;

	/* SINCE STRUCT VERSION 0: */

	/**
	 * The major number of version of the protocol negotiated
	 * between the client and the server. This is not necessarily
	 * the same number as returned in the second parameter of
	 * the libaxl_receive_handshake() function.
	 */
	int protocol_version_major;

	/**
	 * The minor number of version of the protocol negotiated
	 * between the client and the server. This is not necessarily
	 * the same number as returned in the third parameter of
	 * the libaxl_receive_handshake() function.
	 */
	int protocol_version_minor;

	/**
	 * The version of the protocol negotiated between the client
	 * and the server, encoded as the sum of the major number
	 * multipled by 10000 and the minor number.
	 */
	int protocol_version;

	/**
	 * The byte order generally used in communication with the
	 * display server
	 */
	enum libaxl_byte_order protocol_byte_order;

	/**
	 * The byte order used in images
	 */
	enum libaxl_byte_order image_byte_order;

	/**
	 * The smallest keycode transmitted by the server
	 * 
	 * Will never be less than 8
	 */
	unsigned int min_keycode;

	/**
	 * The greatest keycode transmitted by the server
	 * 
	 * This field has the `unsigned int` type rather than the
	 * `libaxl_keycode_t` type because the latter is restricted
	 * to 8-bits, and a future version of the protocol could
	 * theoretically use a larger value
	 */
	unsigned int max_keycode;

	/**
	 * Some identification of the owner of the server implementation
	 */
	const char *vendor;

	/**
	 * Release number for the implementation. The vendor controls
	 * the semantics of this number.
	 */
	uint32_t vendor_release;

	/**
	 * The bit order used in the units in the scanlines of bitmaps
	 */
	enum libaxl_bit_order bitmap_format_bit_order;

	/**
	 * Number of bits (will be a multiple of 8) that the scanlines
	 * in bitmaps are quantised into units of
	 * 
	 * Will never greater than `bitmap_format_scanline_pad`
	 */
	size_t bitmap_format_scanline_unit;

	/**
	 * Number of bits (will be a multiple of 8), that scanlines in
	 * bitmaps are padded to
	 */
	size_t bitmap_format_scanline_pad;

	/**
	 * The server may retain recent pointer motion history with
	 * finer granularity than is reported by LIBAXL_EVENT_MOTION_NOTIFY
	 * events, and which may be requested with
	 * LIBAXL_REQUEST_GET_MOTION_EVENTS requests
	 */
	size_t motion_buffer_size;

	/**
	 * The maximum value that can may appear in the length field
	 * in requests (that field is filled in by the library). Any
	 * requests larger than this (it is in byte-quads, meaning
	 * that it is multipled by 4 to get limit in bytes) generate
	 * a LIBAXL_ERROR_LENGTH error and the request is discarded.
	 * 
	 * This field will always be at least 4096 (meaning 16384 bytes)
	 */
	size_t maximum_request_length;

	/**
	 * The number of elements in `.formats`
	 */
	size_t nformats;

	const struct libaxl_format *formats; /* TODO doc */

	/**
	 * The number of elements in `.screens`
	 */
	size_t nscreens;

	/**
	 * List of all screens in the display
	 */
	const struct libaxl_screen *screens;

	/**
	 * The default screen
	 * 
	 * `NULL` if the specified default screen does not exist
	 */
	const struct libaxl_screen *default_screen;

	/**
	 * The default screen
	 */
	int default_screen_number;
};
