/* See LICENSE file for copyright and license details. */

#if !defined(LIBAXL_H) || (LIBAXL_H < 2)
# error Do not include <libaxl/requests.h> directly, include <libaxl.h> instead.
#endif

struct libaxl_request_create_window {
#define LIBAXL_REQUEST_CREATE_WINDOW 1
	uint8_t                         opcode;
	uint8_t                         depth;
	uint16_t                        _request_length;
	libaxl_window_t                 wid;
	libaxl_window_t                 parent;
	int16_t                         x;
	int16_t                         y;
	uint16_t                        width;
	uint16_t                        height;
	uint16_t                        border_width;
	uint16_t                        class;                 /* LIBAXL_{COPY_FROM_PARENT, INPUT_OUTPUT, or INPUT_ONLY} */
	libaxl_visual_t                 visual;                /* Can be LIBAXL_COPY_FROM_PARENT */
	uint32_t                        value_mask;            /* Determines which below are included, all are encoded as uint32_t */
#define LIBAXL_REQUEST_CREATE_WINDOW_BACKGROUND_PIXMAP     0x00000001UL
#define LIBAXL_REQUEST_CREATE_WINDOW_BACKGROUND_PIXEL      0x00000002UL
#define LIBAXL_REQUEST_CREATE_WINDOW_BORDER_PIXMAP         0x00000004UL
#define LIBAXL_REQUEST_CREATE_WINDOW_BORDER_PIXEL          0x00000008UL
#define LIBAXL_REQUEST_CREATE_WINDOW_BIT_GRAVITY           0x00000010UL
#define LIBAXL_REQUEST_CREATE_WINDOW_WIN_GRAVITY           0x00000020UL
#define LIBAXL_REQUEST_CREATE_WINDOW_BACKING_STORE         0x00000040UL
#define LIBAXL_REQUEST_CREATE_WINDOW_BACKING_PLANES        0x00000080UL
#define LIBAXL_REQUEST_CREATE_WINDOW_BACKING_PIXEL         0x00000100UL
#define LIBAXL_REQUEST_CREATE_WINDOW_OVERRIDE_REDIRECT     0x00000200UL
#define LIBAXL_REQUEST_CREATE_WINDOW_SAVE_UNDER            0x00000400UL
#define LIBAXL_REQUEST_CREATE_WINDOW_EVENT_MASK            0x00000800UL
#define LIBAXL_REQUEST_CREATE_WINDOW_DO_NOT_PROPAGATE_MASK 0x00001000UL
#define LIBAXL_REQUEST_CREATE_WINDOW_COLORMAP              0x00002000UL
#define LIBAXL_REQUEST_CREATE_WINDOW_CURSOR                0x00004000UL
	libaxl_pixmap_t                 background_pixmap;     /* Can be LIBAXL_{NONE or PARENT_RELATIVE} */
	uint32_t                        background_pixel;
	libaxl_pixmap_t                 border_pixmap;         /* Can be LIBAXL_COPY_FROM_PARENT */
	uint32_t                        border_pixel;
	uint8_t                         bit_gravity;
	uint8_t                         win_gravity;
	uint8_t                         backing_store;         /* LIBAXL_{NOT_USEFUL, WHEN_MAPPED, or ALWAYS} */
	uint8_t                         __omitted1;
	uint32_t                        backing_planes;
	uint32_t                        backing_pixel;
	libaxl_bool_t                   override_redirect;
	libaxl_bool_t                   save_under;
	uint16_t                        __omitted2;
	uint32_t                        event_mask;            /* See "window event mask" in "consts.h" */
	uint32_t                        do_not_propagate_mask; /* See SETofDEVICEEVENT in "consts.h" */
	libaxl_colormap_t               colormap;              /* Can be LIBAXL_COPY_FROM_PARENT */
	libaxl_cursor_t                 cursor;                /* Can be LIBAXL_NONE */
};

struct libaxl_request_change_window_attributes {
#define LIBAXL_REQUEST_CHANGE_WINDOW_ATTRIBUTES 2
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;
	libaxl_window_t                 window;
	uint32_t                        value_mask;            /* Determines which below are included, all are encoded as uint32_t */
#define LIBAXL_REQUEST_CHANGE_WINDOW_ATTRIBUTES_BACKGROUND_PIXMAP     0x00000001UL
#define LIBAXL_REQUEST_CHANGE_WINDOW_ATTRIBUTES_BACKGROUND_PIXEL      0x00000002UL
#define LIBAXL_REQUEST_CHANGE_WINDOW_ATTRIBUTES_BORDER_PIXMAP         0x00000004UL
#define LIBAXL_REQUEST_CHANGE_WINDOW_ATTRIBUTES_BORDER_PIXEL          0x00000008UL
#define LIBAXL_REQUEST_CHANGE_WINDOW_ATTRIBUTES_BIT_GRAVITY           0x00000010UL
#define LIBAXL_REQUEST_CHANGE_WINDOW_ATTRIBUTES_WIN_GRAVITY           0x00000020UL
#define LIBAXL_REQUEST_CHANGE_WINDOW_ATTRIBUTES_BACKING_STORE         0x00000040UL
#define LIBAXL_REQUEST_CHANGE_WINDOW_ATTRIBUTES_BACKING_PLANES        0x00000080UL
#define LIBAXL_REQUEST_CHANGE_WINDOW_ATTRIBUTES_BACKING_PIXEL         0x00000100UL
#define LIBAXL_REQUEST_CHANGE_WINDOW_ATTRIBUTES_OVERRIDE_REDIRECT     0x00000200UL
#define LIBAXL_REQUEST_CHANGE_WINDOW_ATTRIBUTES_SAVE_UNDER            0x00000400UL
#define LIBAXL_REQUEST_CHANGE_WINDOW_ATTRIBUTES_EVENT_MASK            0x00000800UL
#define LIBAXL_REQUEST_CHANGE_WINDOW_ATTRIBUTES_DO_NOT_PROPAGATE_MASK 0x00001000UL
#define LIBAXL_REQUEST_CHANGE_WINDOW_ATTRIBUTES_COLORMAP              0x00002000UL
#define LIBAXL_REQUEST_CHANGE_WINDOW_ATTRIBUTES_CURSOR                0x00004000UL
	libaxl_pixmap_t                 background_pixmap;     /* Can be LIBAXL_{NONE or PARENT_RELATIVE} */
	uint32_t                        background_pixel;
	libaxl_pixmap_t                 border_pixmap;         /* Can be LIBAXL_COPY_FROM_PARENT */
	uint32_t                        border_pixel;
	uint8_t                         bit_gravity;
	uint8_t                         win_gravity;
	uint8_t                         backing_store;         /* LIBAXL_{NOT_USEFUL, WHEN_MAPPED, or ALWAYS} */
	uint8_t                         __omitted1;
	uint32_t                        backing_planes;
	uint32_t                        backing_pixel;
	libaxl_bool_t                   override_redirect;
	libaxl_bool_t                   save_under;
	uint16_t                        __omitted2;
	uint32_t                        event_mask;            /* See "window event mask" in "consts.h" */
	uint32_t                        do_not_propagate_mask; /* See SETofDEVICEEVENT in "consts.h" */
	libaxl_colormap_t               colormap;              /* Can be LIBAXL_COPY_FROM_PARENT */
	libaxl_cursor_t                 cursor;                /* Can be LIBAXL_NONE */
};

struct libaxl_request_get_window_attributes {
#define LIBAXL_REQUEST_GET_WINDOW_ATTRIBUTES 3
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;       /* = 2 */
	libaxl_window_t                 window;
};

struct libaxl_request_destroy_window {
#define LIBAXL_REQUEST_DESTROY_WINDOW 4
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;       /* = 2 */
	libaxl_window_t                 window;
};

struct libaxl_request_destroy_subwindows {
#define LIBAXL_REQUEST_DESTROY_SUBWINDOWS 5
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;       /* = 2 */
	libaxl_window_t                 window;
};

struct libaxl_request_change_save_set {
#define LIBAXL_REQUEST_CHANGE_SAVE_SET 6
	uint8_t                         opcode;
	uint8_t                         mode;                  /* LIBAXL_{INSERT or DELETE} */
	uint16_t                        _request_length;       /* = 2 */
	libaxl_window_t                 window;
};

struct libaxl_request_reparent_window {
#define LIBAXL_REQUEST_REPARENT_WINDOW 7
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;       /* = 4 */
	libaxl_window_t                 window;
	libaxl_window_t                 parent;
	int16_t                         x;
	int16_t                         y;
};

struct libaxl_request_map_window {
#define LIBAXL_REQUEST_MAP_WINDOW 8
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;       /* = 2 */
	libaxl_window_t                 window;
};

struct libaxl_request_map_subwindows {
#define LIBAXL_REQUEST_MAP_SUBWINDOWS 9
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;       /* = 2 */
	libaxl_window_t                 window;
};

struct libaxl_request_unmap_window {
#define LIBAXL_REQUEST_UNMAP_WINDOW 10
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;       /* = 2 */
	libaxl_window_t                 window;
};

struct libaxl_request_unmap_subwindows {
#define LIBAXL_REQUEST_UNMAP_SUBWINDOWS 11
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;       /* = 2 */
	libaxl_window_t                 window;
};

struct libaxl_request_configure_window {
#define LIBAXL_REQUEST_CONFIGURE_WINDOW 12
	uint8_t                         opcode;
	uint8_t                         __pad1;
	uint16_t                        _request_length;
	libaxl_window_t                 window;
	uint16_t                        value_mask;            /* Determines which below are included, all are encoded as uint32_t */
#define LIBAXL_REQUEST_CONFIGURE_WINDOW_X            0x0001U
#define LIBAXL_REQUEST_CONFIGURE_WINDOW_Y            0x0002U
#define LIBAXL_REQUEST_CONFIGURE_WINDOW_WIDTH        0x0004U
#define LIBAXL_REQUEST_CONFIGURE_WINDOW_HEIGHT       0x0008U
#define LIBAXL_REQUEST_CONFIGURE_WINDOW_BORDER_WIDTH 0x0010U
#define LIBAXL_REQUEST_CONFIGURE_WINDOW_SIBLING      0x0020U
#define LIBAXL_REQUEST_CONFIGURE_WINDOW_STACK_MODE   0x0040U
	uint16_t                        __pad2;
	int16_t                         x;
	int16_t                         y;
	uint16_t                        width;
	uint16_t                        height;
	uint16_t                        border_width;
	uint16_t                        __omitted1;
	libaxl_window_t                 sibling;
	uint8_t                         stack_mode;            /* See "stack mode" in "consts.h" */
	uint8_t                         __omitted2[3];
};

struct libaxl_request_circulate_window {
#define LIBAXL_REQUEST_CIRCULATE_WINDOW 13
	uint8_t                         opcode;
	uint8_t                         direction;             /* LIBAXL_{RAISE_LOWEST or LOWER_HIGHEST} */
	uint16_t                        _request_length;       /* = 2 */
	libaxl_window_t                 window;
};

struct libaxl_request_get_geometry {
#define LIBAXL_REQUEST_GET_GEOMETRY 14
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;       /* = 2 */
	libaxl_drawable_t               drawable;
};

struct libaxl_request_query_tree {
#define LIBAXL_REQUEST_QUERY_TREE 15
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;       /* = 2 */
	libaxl_window_t                 window;
};

struct libaxl_request_intern_atom {
#define LIBAXL_REQUEST_INTERN_ATOM 16
	uint8_t                         opcode;
	libaxl_bool_t                   only_if_exists;
	uint16_t                        _request_length;
	uint16_t                        length_of_name;
	uint16_t                        __pad;
	const char                     *name;
};

struct libaxl_request_get_atom_name {
#define LIBAXL_REQUEST_GET_ATOM_NAME 17
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;       /* = 2 */
	libaxl_atom_t                   atom;
};

struct libaxl_request_change_property {
#define LIBAXL_REQUEST_CHANGE_PROPERTY 18
	uint8_t                         opcode;
	uint8_t                         mode;                  /* See "consts.h" */
	uint16_t                        _request_length;
	libaxl_window_t                 window;
	libaxl_atom_t                   property;
	libaxl_atom_t                   type;
	uint8_t                         format;                /* {8, 16, 32} */
	uint8_t                         __pad[3];
	uint32_t                        length_of_data;        /* in format units */
	union {
		const char             *data;
		const uint8_t          *data8;
		const uint16_t         *data16;
		const uint32_t         *data32;
	};
};

struct libaxl_request_delete_property {
#define LIBAXL_REQUEST_DELETE_PROPERTY 19
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;       /* = 3 */
	libaxl_window_t                 window;
	libaxl_atom_t                   property;
};

struct libaxl_request_get_property {
#define LIBAXL_REQUEST_GET_PROPERTY 20
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;       /* = 6 */
	libaxl_window_t                 window;
	libaxl_atom_t                   property;
	libaxl_atom_t                   type;                  /* Can be LIBAXL_ANY_PROPERTY_TYPE */
	uint32_t                        offset;
	uint32_t                        length;
};

struct libaxl_request_list_properties {
#define LIBAXL_REQUEST_LIST_PROPERTIES 21
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length; /* = 2 */
	libaxl_window_t                 window;
};

struct libaxl_request_set_selection_owner {
#define LIBAXL_REQUEST_SET_SELECTION_OWNER 22
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;       /* = 4 */
	libaxl_window_t                 owner;                 /* Can be LIBAXL_NONE */
	libaxl_atom_t                   selection;
	libaxl_timestamp_t              time;                  /* Can be LIBAXL_CURRENT_TIME */
};

struct libaxl_request_get_selection_owner {
#define LIBAXL_REQUEST_GET_SELECTION_OWNER 23
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;       /* = 2 */
	libaxl_atom_t                   selection;
};

struct libaxl_request_convert_selection {
#define LIBAXL_REQUEST_CONVERT_SELECTION 24
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;       /* = 5 */
	libaxl_atom_t                   selection;
	libaxl_atom_t                   target;
	libaxl_atom_t                   property;              /* Can be LIBAXL_NONE */
	libaxl_timestamp_t              time;                  /* Can be LIBAXL_CURRENT_TIME */
};

struct libaxl_request_send_event {
#define LIBAXL_REQUEST_SEND_EVENT 25
	uint8_t                         opcode;
	libaxl_bool_t                   propagate;
	uint16_t                        _request_length;       /* = 11 */
	libaxl_window_t                 destination;           /* Can be LIBAXL_{POINTER_WINDOW or INPUT_FOCUS} */
	uint32_t                        event_mask;            /* See "window event mask" in "consts.h" */
	union libaxl_event              event;
};

struct libaxl_request_grab_pointer {
#define LIBAXL_REQUEST_GRAB_POINTER 26
	uint8_t                         opcode;
	libaxl_bool_t                   owner_events;
	uint16_t                        _request_length;       /* = 6 */
	libaxl_window_t                 grab_window;
	uint16_t                        event_mask;            /* See SETofPOINTEREVENT in "consts.h" */
	uint8_t                         pointer_mode;          /* LIBAXL_{SYNCHRONOUS or ASYNCHRONOUS} */
	uint8_t                         keyboard_mode;         /* LIBAXL_{SYNCHRONOUS or ASYNCHRONOUS} */
	libaxl_window_t                 confine_to;            /* Can be LIBAXL_NONE */
	libaxl_cursor_t                 cursor;                /* Can be LIBAXL_NONE */
	libaxl_timestamp_t              time;                  /* Can be LIBAXL_CURRENT_TIME */
};

struct libaxl_request_ungrab_pointer {
#define LIBAXL_REQUEST_UNGRAB_POINTER 27
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;       /* = 2 */
	libaxl_timestamp_t              time;                  /* Can be LIBAXL_CURRENT_TIME */
};

struct libaxl_request_grab_button {
#define LIBAXL_REQUEST_GRAB_BUTTON 28
	uint8_t                         opcode;
	uint8_t                         __pad1;
	uint16_t                        _request_length;       /* = 6 */
	libaxl_window_t                 grab_window;
	uint16_t                        event_mask;            /* See SETofPOINTEREVENT in "consts.h" */
	uint8_t                         pointer_mode;          /* LIBAXL_{SYNCHRONOUS or ASYNCHRONOUS} */
	uint8_t                         keyboard_mode;         /* LIBAXL_{SYNCHRONOUS or ASYNCHRONOUS} */
	libaxl_window_t                 confine_to;            /* Can be LIBAXL_NONE */
	libaxl_cursor_t                 cursor;                /* Can be LIBAXL_NONE */
	uint8_t                         button;                /* Can be LIBAXL_ANY_BUTTON */
	uint8_t                         __pad2;
	uint16_t                        modifiers;             /* See "key mask" in "consts.h", also LIBAXL_ANY_MODIFIER */
};

struct libaxl_request_ungrab_button {
#define LIBAXL_REQUEST_UNGRAB_BUTTON 29
	uint8_t                         opcode;
	uint8_t                         button;                /* Can be LIBAXL_ANY_BUTTON */
	uint16_t                        _request_length;       /* = 3 */
	libaxl_window_t                 grab_window;
	uint16_t                        modifiers;             /* See "key mask" in "consts.h", also LIBAXL_ANY_MODIFIER */
	uint16_t                        __pad;
};

struct libaxl_request_change_active_pointer_grab {
#define LIBAXL_REQUEST_CHANGE_ACTIVE_POINTER_GRAB 30
	uint8_t                         opcode;
	uint8_t                         __pad1;
	uint16_t                        _request_length;       /* = 4 */
	libaxl_cursor_t                 cursor;                /* Can be LIBAXL_NONE */
	libaxl_timestamp_t              time;                  /* Can be LIBAXL_CURRENT_TIME */
	uint16_t                        event_mask;            /* See SETofPOINTEREVENT in "consts.h" */
	uint16_t                        __pad2;
};

struct libaxl_request_grab_keyboard {
#define LIBAXL_REQUEST_GRAB_KEYBOARD 31
	uint8_t                         opcode;
	libaxl_bool_t                   owner_events;
	uint16_t                        _request_length;       /* = 4 */
	libaxl_window_t                 grab_window;
	libaxl_timestamp_t              time;                  /* Can be LIBAXL_CURRENT_TIME */
	uint8_t                         pointer_mode;          /* LIBAXL_{SYNCHRONOUS or ASYNCHRONOUS} */
	uint8_t                         keyboard_mode;         /* LIBAXL_{SYNCHRONOUS or ASYNCHRONOUS} */
	uint16_t                        __pad;
};

struct libaxl_request_ungrab_keyboard {
#define LIBAXL_REQUEST_UNGRAB_KEYBOARD 32
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;       /* = 2 */
	libaxl_timestamp_t              time;                  /* Can be LIBAXL_CURRENT_TIME */
};

struct libaxl_request_grab_key {
#define LIBAXL_REQUEST_GRAB_KEY 33
	uint8_t                         opcode;
	libaxl_bool_t                   owner_events;
	uint16_t                        _request_length;       /* = 4 */
	libaxl_window_t                 grab_window;
	uint16_t                        modifiers;             /* See "key mask" in "consts.h", also LIBAXL_ANY_MODIFIER */
	libaxl_keycode_t                key;                   /* Can be LIBAXL_ANY_KEY */
	uint8_t                         pointer_mode;          /* LIBAXL_{SYNCHRONOUS or ASYNCHRONOUS} */
	uint8_t                         keyboard_mode;         /* LIBAXL_{SYNCHRONOUS or ASYNCHRONOUS} */
	uint8_t                         __pad[3];
};

struct libaxl_request_ungrab_key {
#define LIBAXL_REQUEST_UNGRAB_KEY 34
	uint8_t                         opcode;
	libaxl_keycode_t                key;                   /* Can be LIBAXL_ANY_KEY */
	uint16_t                        _request_length;       /* = 3 */
	libaxl_window_t                 grab_window;
	uint16_t                        modifiers;             /* See "key mask" in "consts.h", also LIBAXL_ANY_MODIFIER */
	uint16_t                        __pad;
};

struct libaxl_request_allow_events {
#define LIBAXL_REQUEST_ALLOW_EVENTS 35
	uint8_t                         opcode;
	uint8_t                         mode;                  /* See "consts.h" */
	uint16_t                        _request_length;       /* = 2 */
	libaxl_timestamp_t              time;                  /* Can be LIBAXL_CURRENT_TIME */
};

struct libaxl_request_grab_server {
#define LIBAXL_REQUEST_GRAB_SERVER 36
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;       /* = 1 */
};

struct libaxl_request_ungrab_server {
#define LIBAXL_REQUEST_UNGRAB_SERVER 37
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;       /* = 1 */
};

struct libaxl_request_query_pointer {
#define LIBAXL_REQUEST_QUERY_POINTER 38
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;       /* = 2 */
	libaxl_window_t                 window;
};

struct libaxl_request_get_motion_events {
#define LIBAXL_REQUEST_GET_MOTION_EVENTS 39
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;       /* = 4 */
	libaxl_window_t                 window;
	libaxl_timestamp_t              start;                 /* Can be LIBAXL_CURRENT_TIME */
	libaxl_timestamp_t              end;                   /* Can be LIBAXL_CURRENT_TIME */
};

struct libaxl_request_translate_coordinates {
#define LIBAXL_REQUEST_TRANSLATE_COORDINATES 40
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;       /* = 4 */
	libaxl_window_t                 src_window;
	libaxl_window_t                 dest_window;
	int16_t                         src_x;
	int16_t                         src_y;
};

struct libaxl_request_warp_pointer {
#define LIBAXL_REQUEST_WARP_POINTER 41
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;       /* = 6 */
	libaxl_window_t                 src_window;            /* Can be LIBAXL_NONE */
	libaxl_window_t                 dest_window;           /* Can be LIBAXL_NONE */
	int16_t                         src_x;
	int16_t                         src_y;
	uint16_t                        src_width;
	uint16_t                        src_height;
	int16_t                         dest_x;
	int16_t                         dest_y;
};

struct libaxl_request_set_input_focus {
#define LIBAXL_REQUEST_SET_INPUT_FOCUS 42
	uint8_t                         opcode;
	uint8_t                         revert_to;             /* LIBAXL_{NONE, POINTER_ROOT, or PARENT} */
	uint16_t                        _request_length;       /* = 3 */
	libaxl_window_t                 focus;                 /* Can be LIBAXL_{NONE or POINTER_ROOT} */
	libaxl_timestamp_t              time;                  /* Can be LIBAXL_CURRENT_TIME */
};

struct libaxl_request_get_input_focus {
#define LIBAXL_REQUEST_GET_INPUT_FOCUS 43
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;       /* = 1 */
};

struct libaxl_request_query_keymap {
#define LIBAXL_REQUEST_QUERY_KEYMAP 44
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;       /* = 1 */
};

struct libaxl_request_open_font {
#define LIBAXL_REQUEST_OPEN_FONT 45
	uint8_t                         opcode;
	uint8_t                         __pad1;
	uint16_t                        _request_length;
	libaxl_font_t                   fid;
	uint16_t                        length_of_name;
	uint16_t                        __pad2;
	const char                     *name;
};

struct libaxl_request_close_font {
#define LIBAXL_REQUEST_CLOSE_FONT 46
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;
	libaxl_font_t                   font;
};

struct libaxl_request_query_font {
#define LIBAXL_REQUEST_QUERY_FONT 47
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;
	libaxl_fontable_t               font;
};

struct libaxl_request_query_text_extents {
#define LIBAXL_REQUEST_QUERY_TEXT_EXTENTS 48
	uint8_t                         opcode;
	libaxl_bool_t                   _odd_length;
	uint16_t                        _request_length;
	libaxl_fontable_t               font;
	size_t                          length_of_string;
	const uint16_t                  *string;
};

struct libaxl_request_list_fonts {
#define LIBAXL_REQUEST_LIST_FONTS 49
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;
	uint16_t                        max_names;
	uint16_t                        length_of_pattern;
	const char                     *pattern;
};

struct libaxl_request_list_fonts_with_info {
#define LIBAXL_REQUEST_LIST_FONTS_WITH_INFO 50
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;
	uint16_t                        max_names;
	uint16_t                        length_of_pattern;
	const char                     *pattern;
};

struct libaxl_request_set_font_path {
#define LIBAXL_REQUEST_SET_FONT_PATH 51
	uint8_t                         opcode;
	uint8_t                         __pad1;
	uint16_t                        _request_length;
	uint16_t                        number_of_strs;        /* in path */
	uint16_t                        __pad2;
	const struct libaxl_str8       *path;
};

struct libaxl_request_get_font_path {
#define LIBAXL_REQUEST_GET_FONT_PATH 52
	uint8_t                         opcode;
	uint8_t                         __pad1;
	uint16_t                        _request_length;       /* = 1 */
};

struct libaxl_request_create_pixmap {
#define LIBAXL_REQUEST_CREATE_PIXMAP 53
	uint8_t                         opcode;
	uint8_t                         depth;
	uint16_t                        _request_length;       /* = 4 */
	libaxl_pixmap_t                 pid;
	libaxl_drawable_t               drawable;
	uint16_t                        width;
	uint16_t                        height;
};

struct libaxl_request_free_pixmap {
#define LIBAXL_REQUEST_FREE_PIXMAP 54
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;       /* = 2 */
	libaxl_pixmap_t                 pixmap;
};

struct libaxl_request_create_gc {
#define LIBAXL_REQUEST_CREATE_GC 55
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;
	libaxl_gcontext_t               cid;
	libaxl_drawable_t               drawable;
	uint32_t                        value_mask;            /* Determines which below are included, all are encoded as uint32_t */
#define LIBAXL_REQUEST_CREATE_GC_FUNCTION              0x00000001UL
#define LIBAXL_REQUEST_CREATE_GC_PLANE_MASK            0x00000002UL
#define LIBAXL_REQUEST_CREATE_GC_FOREGROUND            0x00000004UL
#define LIBAXL_REQUEST_CREATE_GC_BACKGROUND            0x00000008UL
#define LIBAXL_REQUEST_CREATE_GC_LINE_WIDTH            0x00000010UL
#define LIBAXL_REQUEST_CREATE_GC_LINE_STYLE            0x00000020UL
#define LIBAXL_REQUEST_CREATE_GC_CAP_STYLE             0x00000040UL
#define LIBAXL_REQUEST_CREATE_GC_JOIN_STYLE            0x00000080UL
#define LIBAXL_REQUEST_CREATE_GC_FILL_STYLE            0x00000100UL
#define LIBAXL_REQUEST_CREATE_GC_FILL_RULE             0x00000200UL
#define LIBAXL_REQUEST_CREATE_GC_TILE                  0x00000400UL
#define LIBAXL_REQUEST_CREATE_GC_STIPPLE               0x00000800UL
#define LIBAXL_REQUEST_CREATE_GC_TILE_STIPPLE_X_ORIGIN 0x00001000UL
#define LIBAXL_REQUEST_CREATE_GC_TILE_STIPPLE_Y_ORIGIN 0x00002000UL
#define LIBAXL_REQUEST_CREATE_GC_FONT                  0x00004000UL
#define LIBAXL_REQUEST_CREATE_GC_SUBWINDOW_MODE        0x00008000UL
#define LIBAXL_REQUEST_CREATE_GC_GRAPHICS_EXPOSURES    0x00010000UL
#define LIBAXL_REQUEST_CREATE_GC_CLIP_X_ORIGIN         0x00020000UL
#define LIBAXL_REQUEST_CREATE_GC_CLIP_Y_ORIGIN         0x00040000UL
#define LIBAXL_REQUEST_CREATE_GC_CLIP_MASK             0x00080000UL
#define LIBAXL_REQUEST_CREATE_GC_DASH_OFFSET           0x00100000UL
#define LIBAXL_REQUEST_CREATE_GC_DASHES                0x00200000UL
#define LIBAXL_REQUEST_CREATE_GC_ARC_MODE              0x00400000UL
	uint8_t                         function;              /* See "gcontext function" in "consts.h" */
	uint8_t                         __omitted1[3];
	uint32_t                        plane_mask;
	uint32_t                        foreground;
	uint32_t                        background;
	uint16_t                        line_width;
	uint8_t                         line_style;            /* LIBAXL_{SOLID, ON_OFF_DASH, or DOUBLE_DASH} */
	uint8_t                         cap_style;             /* See "cap style" in "consts.h" (Beware of namespacing) */
	uint8_t                         join_style;            /* See "join style" in "consts.h" (Beware of namespacing) */
	uint8_t                         fill_style;            /* LIBAXL_{SOLID, TILED, STIPPLED, or OPAQUE_STIPPLED} */
	uint8_t                         fill_rule;             /* LIBAXL_{EVEN_ODD or WINDING} */
	uint8_t                         __omitted2;
	libaxl_pixmap_t                 tile;
	libaxl_pixmap_t                 stipple;
	int16_t                         tile_stipple_x_origin;
	int16_t                         tile_stipple_y_origin;
	libaxl_font_t                   font;
	uint8_t                         subwindow_mode;        /* LIBAXL_{CLIP_BY_CHILDREN or INCLUDE_INFERIORS} */
	libaxl_bool_t                   graphics_exposures;
	uint16_t                        __omitted3;
	int16_t                         clip_x_origin;
	int16_t                         clip_y_origin;
	libaxl_pixmap_t                 clip_mask;             /* Can be LIBAXL_NONE */
	uint16_t                        dash_offset;
	uint8_t                         dashes;
	uint8_t                         arc_mode;              /* LIBAXL_{CHORD or PIE_SLICE} */
};

struct libaxl_request_change_gc {
#define LIBAXL_REQUEST_CHANGE_GC 56
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;
	libaxl_gcontext_t               gc;
	uint32_t                        value_mask;            /* Determines which below are included, all are encoded as uint32_t */
#define LIBAXL_REQUEST_CHANGE_GC_FUNCTION              0x00000001UL
#define LIBAXL_REQUEST_CHANGE_GC_PLANE_MASK            0x00000002UL
#define LIBAXL_REQUEST_CHANGE_GC_FOREGROUND            0x00000004UL
#define LIBAXL_REQUEST_CHANGE_GC_BACKGROUND            0x00000008UL
#define LIBAXL_REQUEST_CHANGE_GC_LINE_WIDTH            0x00000010UL
#define LIBAXL_REQUEST_CHANGE_GC_LINE_STYLE            0x00000020UL
#define LIBAXL_REQUEST_CHANGE_GC_CAP_STYLE             0x00000040UL
#define LIBAXL_REQUEST_CHANGE_GC_JOIN_STYLE            0x00000080UL
#define LIBAXL_REQUEST_CHANGE_GC_FILL_STYLE            0x00000100UL
#define LIBAXL_REQUEST_CHANGE_GC_FILL_RULE             0x00000200UL
#define LIBAXL_REQUEST_CHANGE_GC_TILE                  0x00000400UL
#define LIBAXL_REQUEST_CHANGE_GC_STIPPLE               0x00000800UL
#define LIBAXL_REQUEST_CHANGE_GC_TILE_STIPPLE_X_ORIGIN 0x00001000UL
#define LIBAXL_REQUEST_CHANGE_GC_TILE_STIPPLE_Y_ORIGIN 0x00002000UL
#define LIBAXL_REQUEST_CHANGE_GC_FONT                  0x00004000UL
#define LIBAXL_REQUEST_CHANGE_GC_SUBWINDOW_MODE        0x00008000UL
#define LIBAXL_REQUEST_CHANGE_GC_GRAPHICS_EXPOSURES    0x00010000UL
#define LIBAXL_REQUEST_CHANGE_GC_CLIP_X_ORIGIN         0x00020000UL
#define LIBAXL_REQUEST_CHANGE_GC_CLIP_Y_ORIGIN         0x00040000UL
#define LIBAXL_REQUEST_CHANGE_GC_CLIP_MASK             0x00080000UL
#define LIBAXL_REQUEST_CHANGE_GC_DASH_OFFSET           0x00100000UL
#define LIBAXL_REQUEST_CHANGE_GC_DASHES                0x00200000UL
#define LIBAXL_REQUEST_CHANGE_GC_ARC_MODE              0x00400000UL
	uint8_t                         function;              /* See "gcontext function" in "consts.h" */
	uint8_t                         __omitted1[3];
	uint32_t                        plane_mask;
	uint32_t                        foreground;
	uint32_t                        background;
	uint16_t                        line_width;
	uint8_t                         line_style;            /* LIBAXL_{SOLID, ON_OFF_DASH, or DOUBLE_DASH} */
	uint8_t                         cap_style;             /* See "cap style" in "consts.h" (Beware of namespacing) */
	uint8_t                         join_style;            /* See "join style" in "consts.h" (Beware of namespacing) */
	uint8_t                         fill_style;            /* LIBAXL_{SOLID, TILED, STIPPLED, or OPAQUE_STIPPLED} */
	uint8_t                         fill_rule;             /* LIBAXL_{EVEN_ODD or WINDING} */
	uint8_t                         __omitted2;
	libaxl_pixmap_t                 tile;
	libaxl_pixmap_t                 stipple;
	int16_t                         tile_stipple_x_origin;
	int16_t                         tile_stipple_y_origin;
	libaxl_font_t                   font;
	uint8_t                         subwindow_mode;        /* LIBAXL_{CLIP_BY_CHILDREN or INCLUDE_INFERIORS} */
	libaxl_bool_t                   graphics_exposures;
	uint16_t                        __omitted3;
	int16_t                         clip_x_origin;
	int16_t                         clip_y_origin;
	libaxl_pixmap_t                 clip_mask;             /* Can be LIBAXL_NONE */
	uint16_t                        dash_offset;
	uint8_t                         dashes;
	uint8_t                         arc_mode;              /* LIBAXL_{CHORD or PIE_SLICE} */
};

struct libaxl_request_copy_gc {
#define LIBAXL_REQUEST_COPY_GC 57
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;       /* = 4 */
	libaxl_gcontext_t               src_gc;
	libaxl_gcontext_t               dest_gc;
	uint32_t                        value_mask;
#define LIBAXL_REQUEST_COPY_GC_FUNCTION              0x00000001UL
#define LIBAXL_REQUEST_COPY_GC_PLANE_MASK            0x00000002UL
#define LIBAXL_REQUEST_COPY_GC_FOREGROUND            0x00000004UL
#define LIBAXL_REQUEST_COPY_GC_BACKGROUND            0x00000008UL
#define LIBAXL_REQUEST_COPY_GC_LINE_WIDTH            0x00000010UL
#define LIBAXL_REQUEST_COPY_GC_LINE_STYLE            0x00000020UL
#define LIBAXL_REQUEST_COPY_GC_CAP_STYLE             0x00000040UL
#define LIBAXL_REQUEST_COPY_GC_JOIN_STYLE            0x00000080UL
#define LIBAXL_REQUEST_COPY_GC_FILL_STYLE            0x00000100UL
#define LIBAXL_REQUEST_COPY_GC_FILL_RULE             0x00000200UL
#define LIBAXL_REQUEST_COPY_GC_TILE                  0x00000400UL
#define LIBAXL_REQUEST_COPY_GC_STIPPLE               0x00000800UL
#define LIBAXL_REQUEST_COPY_GC_TILE_STIPPLE_X_ORIGIN 0x00001000UL
#define LIBAXL_REQUEST_COPY_GC_TILE_STIPPLE_Y_ORIGIN 0x00002000UL
#define LIBAXL_REQUEST_COPY_GC_FONT                  0x00004000UL
#define LIBAXL_REQUEST_COPY_GC_SUBWINDOW_MODE        0x00008000UL
#define LIBAXL_REQUEST_COPY_GC_GRAPHICS_EXPOSURES    0x00010000UL
#define LIBAXL_REQUEST_COPY_GC_CLIP_X_ORIGIN         0x00020000UL
#define LIBAXL_REQUEST_COPY_GC_CLIP_Y_ORIGIN         0x00040000UL
#define LIBAXL_REQUEST_COPY_GC_CLIP_MASK             0x00080000UL
#define LIBAXL_REQUEST_COPY_GC_DASH_OFFSET           0x00100000UL
#define LIBAXL_REQUEST_COPY_GC_DASHES                0x00200000UL
#define LIBAXL_REQUEST_COPY_GC_ARC_MODE              0x00400000UL
};

struct libaxl_request_set_dashes {
#define LIBAXL_REQUEST_SET_DASHES 58
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;
	libaxl_gcontext_t               gc;
	uint16_t                        dash_offset;
	uint16_t                        length_of_dashes;
	const uint8_t                  *dashes;
};

struct libaxl_request_set_clip_rectangles {
#define LIBAXL_REQUEST_SET_CLIP_RECTANGLES 59
	uint8_t                         opcode;
	uint8_t                         ordering;              /* LIBAXL_{UNSORTED, YSORTED, YXSORTED, or YXBANDED} */
	uint16_t                        _request_length;
	libaxl_gcontext_t               gc;
	int16_t                         clip_x_origin;
	int16_t                         clip_y_origin;
	size_t                          number_of_rectangles;
	const struct libaxl_rectangle  *rectangles;
};

struct libaxl_request_free_gc {
#define LIBAXL_REQUEST_FREE_GC 60
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;       /* = 2 */
	libaxl_gcontext_t               gc;
};

struct libaxl_request_clear_area {
#define LIBAXL_REQUEST_CLEAR_AREA 61
	uint8_t                         opcode;
	libaxl_bool_t                   exposures;
	uint16_t                        _request_length;       /* = 4 */
	libaxl_window_t                 window;
	int16_t                         x;
	int16_t                         y;
	uint16_t                        width;
	uint16_t                        height;
};

struct libaxl_request_copy_area {
#define LIBAXL_REQUEST_COPY_AREA 62
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;       /* = 7 */
	libaxl_drawable_t               src_drawable;
	libaxl_drawable_t               dest_drawable;
	libaxl_gcontext_t               gc;
	int16_t                         src_x;
	int16_t                         src_y;
	int16_t                         dest_x;
	int16_t                         dest_y;
	uint16_t                        width;
	uint16_t                        height;
};

struct libaxl_request_copy_plane {
#define LIBAXL_REQUEST_COPY_PLANE 63
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;       /* = 8 */
	libaxl_drawable_t               src_drawable;
	libaxl_drawable_t               dest_drawable;
	libaxl_gcontext_t               gc;
	int16_t                         src_x;
	int16_t                         src_y;
	int16_t                         dest_x;
	int16_t                         dest_y;
	uint16_t                        width;
	uint16_t                        height;
	uint32_t                        bit_plane;
};

struct libaxl_request_poly_point {
#define LIBAXL_REQUEST_POLY_POINT 64
	uint8_t                         opcode;
	uint8_t                         coordinate_mode;       /* LIBAXL_{ORIGIN or PREVIOUS} */
	uint16_t                        _request_length;
	libaxl_drawable_t               drawable;
	libaxl_gcontext_t               gc;
	size_t                          number_of_points;
	const struct libaxl_point      *points;
};

struct libaxl_request_poly_line {
#define LIBAXL_REQUEST_POLY_LINE 65
	uint8_t                         opcode;
	uint8_t                         coordinate_mode;       /* LIBAXL_{ORIGIN or PREVIOUS} */
	uint16_t                        _request_length;
	libaxl_drawable_t               drawable;
	libaxl_gcontext_t               gc;
	const struct libaxl_point      *points;
};

struct libaxl_request_poly_segment {
#define LIBAXL_REQUEST_POLY_SEGMENT 66
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;
	libaxl_drawable_t               drawable;
	libaxl_gcontext_t               gc;
	size_t                          number_of_segments;
	const struct libaxl_segment    *segments;
};

struct libaxl_request_poly_rectangle {
#define LIBAXL_REQUEST_POLY_RECTANGLE 67
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;
	libaxl_drawable_t               drawable;
	libaxl_gcontext_t               gc;
	size_t                          number_of_rectangles;
	const struct libaxl_rectangle  *rectangle;
};

struct libaxl_request_poly_arc {
#define LIBAXL_REQUEST_POLY_ARC 68
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;
	libaxl_drawable_t               drawable;
	libaxl_gcontext_t               gc;
	size_t                          number_of_arcs;
	const struct libaxl_arc        *arc;
};

struct libaxl_request_fill_poly {
#define LIBAXL_REQUEST_FILL_POLY 69
	uint8_t                         opcode;
	uint8_t                         __pad1;
	uint16_t                        _request_length;
	libaxl_drawable_t               drawable;
	libaxl_gcontext_t               gc;
	uint8_t                         shape;                 /* LIBAXL_{COMPLEX, NONCONVEX, or CONVEX} */
	uint8_t                         coordinate_mode;       /* LIBAXL_{ORIGIN or PREVIOUS} */
	uint16_t                        __pad2;
	size_t                          number_of_pointss;
	const struct libaxl_point      *points;
};

struct libaxl_request_poly_fill_rectangle {
#define LIBAXL_REQUEST_POLY_FILL_RECTANGLE 70
	uint8_t                         opcode;
	uint8_t                         __pad1;
	uint16_t                        _request_length;
	libaxl_drawable_t               drawable;
	libaxl_gcontext_t               gc;
	size_t                          number_of_rectangles;
	struct libaxl_rectangle        *rectangles;
};

struct libaxl_request_poly_fill_arc {
#define LIBAXL_REQUEST_POLY_FILL_ARC 71
	uint8_t                         opcode;
	uint8_t                         __pad1;
	uint16_t                        _request_length;
	libaxl_drawable_t               drawable;
	libaxl_gcontext_t               gc;
	size_t                          number_of_arcs;
	const struct libaxl_arc        *arcs;
};

struct libaxl_request_put_image {
#define LIBAXL_REQUEST_PUT_IMAGE 72
	uint8_t                         opcode;
	uint8_t                         format;                /* LIBAXL_{BITMAP, XYPIXMAP, or ZPIXMAP} */
	uint16_t                        _request_length;
	libaxl_drawable_t               drawable;
	libaxl_gcontext_t               gc;
	uint16_t                        width;
	uint16_t                        height;
	int16_t                         dest_x;
	int16_t                         dest_y;
	uint8_t                         left_pad;
	uint8_t                         depth;
	uint16_t                        __pad;
	size_t                          data_size;
	const uint8_t                  *data;
};

struct libaxl_request_get_image {
#define LIBAXL_REQUEST_GET_IMAGE 73
	uint8_t                         opcode;
	uint8_t                         format;                /* LIBAXL_{XYPIXMAP (= 1) or ZPIXMAP (= 2)} */
	uint16_t                        _request_length;       /* = 5 */
	libaxl_drawable_t               drawable;
	int16_t                         x;
	int16_t                         y;
	uint16_t                        width;
	uint16_t                        height;
	uint32_t                        plane_mask;
};

struct libaxl_request_poly_text8 {
#define LIBAXL_REQUEST_POLY_TEXT8 74
	uint8_t                         opcode;
	uint8_t                         __unused;
	uint16_t                        _request_length;
	libaxl_drawable_t               drawable;
	libaxl_gcontext_t               gc;
	int16_t                         x;
	int16_t                         y;
	size_t                          number_of_items;
	const union libaxl_text_item8  *items;
};

struct libaxl_request_poly_text16 {
#define LIBAXL_REQUEST_POLY_TEXT16 75
	uint8_t                         opcode;
	uint8_t                         __unused;
	uint16_t                        _request_length;
	libaxl_drawable_t               drawable;
	libaxl_gcontext_t               gc;
	int16_t                         x;
	int16_t                         y;
	size_t                          number_of_items;
	const union libaxl_text_item16 *items;
};

struct libaxl_request_image_text8 {
#define LIBAXL_REQUEST_IMAGE_TEXT8 76
	uint8_t                         opcode;
	uint8_t                         length_of_string;
	uint16_t                        _request_length;
	libaxl_drawable_t               drawable;
	libaxl_gcontext_t               gc;
	int16_t                         x;
	int16_t                         y;
	const char                     *string;
};

struct libaxl_request_image_text16 {
#define LIBAXL_REQUEST_IMAGE_TEXT16 77
	uint8_t                         opcode;
	uint8_t                         length_of_string;
	uint16_t                        _request_length;
	libaxl_drawable_t               drawable;
	libaxl_gcontext_t               gc;
	int16_t                         x;
	int16_t                         y;
	const uint16_t                 *string;
};

struct libaxl_request_create_colormap {
#define LIBAXL_REQUEST_CREATE_COLORMAP 78
	uint8_t                         opcode;
	uint8_t                         alloc;                 /* LIBAXL_{NONE or ALL} */
	uint16_t                        _request_length;       /* = 4 */
	libaxl_colormap_t               mid;
	libaxl_window_t                 window;
	libaxl_visual_t                 visual;
};

struct libaxl_request_free_colormap {
#define LIBAXL_REQUEST_FREE_COLORMAP 79
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;       /* = 2 */
	libaxl_colormap_t               cmap;
};

struct libaxl_request_copy_colormap_and_free {
#define LIBAXL_REQUEST_COPY_COLORMAP_AND_FREE 80
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;       /* = 3 */
	libaxl_colormap_t               mid;
	libaxl_colormap_t               src_cmap;
};

struct libaxl_request_install_colormap {
#define LIBAXL_REQUEST_INSTALL_COLORMAP 81
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;       /* = 2 */
	libaxl_colormap_t               cmap;
};

struct libaxl_request_uninstall_colormap {
#define LIBAXL_REQUEST_UNINSTALL_COLORMAP 82
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;       /* = 2 */
	libaxl_colormap_t               cmap;
};

struct libaxl_request_list_installed_colormaps {
#define LIBAXL_REQUEST_LIST_INSTALLED_COLORMAPS 83
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;       /* = 2 */
	libaxl_window_t                 window;
};

struct libaxl_request_alloc_color {
#define LIBAXL_REQUEST_ALLOC_COLOR 84
	uint8_t                         opcode;
	uint8_t                         __pad1;
	uint16_t                        _request_length;       /* = 4 */
	libaxl_colormap_t               cmap;
	uint16_t                        red;
	uint16_t                        green;
	uint16_t                        blue;
	uint16_t                        __pad2;
};

struct libaxl_request_alloc_named_color {
#define LIBAXL_REQUEST_ALLOC_NAMED_COLOR 85
	uint8_t                         opcode;
	uint8_t                         __pad1;
	uint16_t                        _request_length;
	libaxl_colormap_t               cmap;
	uint16_t                        length_of_name;
	uint16_t                        __pad2;
	const char                     *name;
};

struct libaxl_request_alloc_color_cells {
#define LIBAXL_REQUEST_ALLOC_COLOR_CELLS 86
	uint8_t                         opcode;
	libaxl_bool_t                   contiguous;
	uint16_t                        _request_length;       /* = 3 */
	libaxl_colormap_t               cmap;
	uint16_t                        colors;
	uint16_t                        planes;
};

struct libaxl_request_alloc_color_planes {
#define LIBAXL_REQUEST_ALLOC_COLOR_PLANES 87
	uint8_t                         opcode;
	libaxl_bool_t                   contiguous;
	uint16_t                        _request_length;       /* = 4 */
	libaxl_colormap_t               cmap;
	uint16_t                        colors;
	uint16_t                        reds;
	uint16_t                        greens;
	uint16_t                        blues;
};

struct libaxl_request_free_colors {
#define LIBAXL_REQUEST_FREE_COLORS 88
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;
	libaxl_colormap_t               cmap;
	uint32_t                        plane_mask;
	size_t                          number_of_pixels;
	const uint32_t                 *pixels;
};

struct libaxl_request_store_colors {
#define LIBAXL_REQUEST_STORE_COLORS 89
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;
	libaxl_colormap_t               cmap;
	size_t                          number_of_items;
	const struct libaxl_coloritem  *items;
};

struct libaxl_request_store_named_color {
#define LIBAXL_REQUEST_STORE_NAMED_COLOR 90
	uint8_t                         opcode;
	uint8_t                         flags;                 /* See "consts.h" */
	uint16_t                        _request_length;
	libaxl_colormap_t               cmap;
	uint32_t                        pixel;
	uint16_t                        length_of_name;
	uint16_t                        __unused;
	const char                     *name;
};

struct libaxl_request_query_colors {
#define LIBAXL_REQUEST_QUERY_COLORS 91
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;
	libaxl_colormap_t               cmap;
	size_t                          number_of_pixels;
	const uint32_t                 *pixels;
};

struct libaxl_request_lookup_color {
#define LIBAXL_REQUEST_LOOKUP_COLOR 92
	uint8_t                         opcode;
	uint8_t                         __unused;
	uint16_t                        _request_length;
	libaxl_colormap_t               cmap;
	uint16_t                        length_of_name;
	uint16_t                        __pad;
	const char                     *name;
};

struct libaxl_request_create_cursor {
#define LIBAXL_REQUEST_CREATE_CURSOR 93
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;       /* = 8 */
	libaxl_cursor_t                 cid;
	libaxl_pixmap_t                 source;
	libaxl_pixmap_t                 mask;                  /* Can be LIBAXL_NONE */
	uint16_t                        fore_red;
	uint16_t                        fore_green;
	uint16_t                        fore_blue;
	uint16_t                        back_red;
	uint16_t                        back_green;
	uint16_t                        back_blue;
	uint16_t                        x;
	uint16_t                        y;
};

struct libaxl_request_create_glyph_cursor {
#define LIBAXL_REQUEST_CREATE_GLYPH_CURSOR 94
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;       /* = 8 */
	libaxl_cursor_t                 cid;
	libaxl_font_t                   source_font;
	libaxl_font_t                   mask_font;             /* Can be LIBAXL_NONE */
	uint16_t                        source_char;
	uint16_t                        mask_char;
	uint16_t                        fore_red;
	uint16_t                        fore_green;
	uint16_t                        fore_blue;
	uint16_t                        back_red;
	uint16_t                        back_green;
	uint16_t                        back_blue;
};

struct libaxl_request_free_cursor {
#define LIBAXL_REQUEST_FREE_CURSOR 95
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;       /* = 2 */
	libaxl_cursor_t                 cursor;
};

struct libaxl_request_recolor_cursor {
#define LIBAXL_REQUEST_RECOLOR_CURSOR 96
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;       /* = 5 */
	libaxl_cursor_t                 cursor;
	uint16_t                        fore_red;
	uint16_t                        fore_green;
	uint16_t                        fore_blue;
	uint16_t                        back_red;
	uint16_t                        back_green;
	uint16_t                        back_blue;
};

struct libaxl_request_query_best_size {
#define LIBAXL_REQUEST_QUERY_BEST_SIZE 97
	uint8_t                         opcode;
	uint8_t                         class;                 /* LIBAXL_{CURSOR, TILE, or STIPPLE} */
	uint16_t                        _request_length;       /* = 3 */
	libaxl_drawable_t               drawable;
	uint16_t                        width;
	uint16_t                        height;
};

struct libaxl_request_query_extension {
#define LIBAXL_REQUEST_QUERY_EXTENSION 98
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;
	uint16_t                        length_of_name;
	uint16_t                        __unused;
	const char                     *name;
};

struct libaxl_request_list_extensions {
#define LIBAXL_REQUEST_LIST_EXTENSIONS 99
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;       /* = 1 */
};

struct libaxl_request_change_keyboard_mapping {
#define LIBAXL_REQUEST_CHANGE_KEYBOARD_MAPPING 100
	uint8_t                         opcode;
	uint8_t                         keycode_count;
	uint16_t                        _request_length;
	libaxl_keycode_t                first_keycode;
	uint8_t                         keysyms_per_keycode;
	uint16_t                        __pad;
	const libaxl_keysym_t          *keysyms;
};

struct libaxl_request_get_keyboard_mapping {
#define LIBAXL_REQUEST_GET_KEYBOARD_MAPPING 101
	uint8_t                         opcode;
	uint8_t                         __pad1;
	uint16_t                        _request_length;       /* = 2 */
	libaxl_keycode_t                first_keycode;
	uint8_t                         count;
	uint16_t                        __pad2;
};

struct libaxl_request_change_keyboard_control {
#define LIBAXL_REQUEST_CHANGE_KEYBOARD_CONTROL 102
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;
	uint32_t                        value_mask;            /* Determines which below are included, all are encoded as uint32_t */
#define LIBAXL_REQUEST_CHANGE_KEYBOARD_CONTROL_KEY_CLICK_PERCENT 0x0001U
#define LIBAXL_REQUEST_CHANGE_KEYBOARD_CONTROL_BELL_PERCENT      0x0002U
#define LIBAXL_REQUEST_CHANGE_KEYBOARD_CONTROL_BELL_PITCH        0x0004U
#define LIBAXL_REQUEST_CHANGE_KEYBOARD_CONTROL_BELL_DURATION     0x0008U
#define LIBAXL_REQUEST_CHANGE_KEYBOARD_CONTROL_LED               0x0010U
#define LIBAXL_REQUEST_CHANGE_KEYBOARD_CONTROL_LED_MODE          0x0020U
#define LIBAXL_REQUEST_CHANGE_KEYBOARD_CONTROL_KEY               0x0040U
#define LIBAXL_REQUEST_CHANGE_KEYBOARD_CONTROL_AUTO_REPEAT_MODE  0x0080U
	int8_t                          key_click_percent;
	int8_t                          bell_percent;
	int16_t                         bell_pitch;
	int16_t                         bell_duration;
	uint8_t                         led;
	uint8_t                         led_mode;              /* LIBAXL_{OFF or ON} */
	libaxl_keycode_t                key;
	uint8_t                         auto_repeat_mode;      /* LIBAXL_{OFF, ON, or DEFAULT} */
	uint16_t                        __omitted;
};

struct libaxl_request_get_keyboard_control {
#define LIBAXL_REQUEST_GET_KEYBOARD_CONTROL 103
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;       /* = 1 */
};

struct libaxl_request_bell {
#define LIBAXL_REQUEST_BELL 104
	uint8_t                         opcode;
	int8_t                          percent;
	uint16_t                        _request_length;       /* = 1 */
};

struct libaxl_request_change_pointer_control {
#define LIBAXL_REQUEST_CHANGE_POINTER_CONTROL 105
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;       /* = 3 */
	int16_t                         acceleration_numerator;
	int16_t                         acceleration_denominator;
	int16_t                         threshold;
	libaxl_bool_t                   do_acceleration;
	libaxl_bool_t                   do_threshold;
};

struct libaxl_request_get_pointer_control {
#define LIBAXL_REQUEST_GET_POINTER_CONTROL 106
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;       /* = 1 */
};

struct libaxl_request_set_screen_saver {
#define LIBAXL_REQUEST_SET_SCREEN_SAVER 107
	uint8_t                         opcode;
	uint8_t                         __pad1;
	uint16_t                        _request_length;       /* = 3 */
	int16_t                         timeout;
	int16_t                         interval;
	uint8_t                         prefer_blanking;       /* LIBAXL_{NO, YES, or DEFAULT} */
	uint8_t                         allow_exposures;       /* LIBAXL_{NO, YES, or DEFAULT} */
	uint16_t                        __pad2;
};

struct libaxl_request_get_screen_saver {
#define LIBAXL_REQUEST_GET_SCREEN_SAVER 108
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;       /* = 1 */
};

struct libaxl_request_change_hosts {
#define LIBAXL_REQUEST_CHANGE_HOSTS 109
	uint8_t                         opcode;
	uint8_t                         mode;                  /* LIBAXL_{INSERT or DELETE} */
	uint16_t                        _request_length;
	uint8_t                         family;                /* See "consts.h" */
	uint8_t                         __pad;
	uint16_t                        length_of_address;
	const uint8_t                  *address;
};

struct libaxl_request_list_hosts {
#define LIBAXL_REQUEST_LIST_HOSTS 110
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;       /* = 1 */
};

struct libaxl_request_set_access_control {
#define LIBAXL_REQUEST_SET_ACCESS_CONTROL 111
	uint8_t                         opcode;
	uint8_t                         mode;                  /* LIBAXL_{DISABLE or ENABLE} */
	uint16_t                        _request_length;       /* = 1 */
};

struct libaxl_request_set_close_down_mode {
#define LIBAXL_REQUEST_SET_CLOSE_DOWN_MODE 112
	uint8_t                         opcode;
	uint8_t                         mode;                  /* LIBAXL_{DESTROY, RETAIN_PERMANENT, or RETAIN_TEMPORARY} */
	uint16_t                        _request_length;       /* = 1 */
};

struct libaxl_request_kill_client {
#define LIBAXL_REQUEST_KILL_CLIENT 113
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;       /* = 2 */
	libaxl_id_t                     resource;              /* Can be LIBAXL_ALL_TEMPORARY */
};

struct libaxl_request_rotate_properties {
#define LIBAXL_REQUEST_ROTATE_PROPERTIES 114
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;
	libaxl_window_t                 window;
	uint16_t                        number_of_properties;
	int16_t                         delta;
	const libaxl_atom_t            *properties;
};

struct libaxl_request_force_screen_saver {
#define LIBAXL_REQUEST_FORCE_SCREEN_SAVER 115
	uint8_t                         opcode;
	uint8_t                         mode;                  /* LIBAXL_{RESET or ACTIVATE} */
	uint16_t                        _request_length;       /* = 1 */
};

struct libaxl_request_set_pointer_mapping {
#define LIBAXL_REQUEST_SET_POINTER_MAPPING 116
	uint8_t                         opcode;
	uint8_t                         length_of_map;
	uint16_t                        _request_length;
	const uint8_t                  *map;
};

struct libaxl_request_get_pointer_mapping {
#define LIBAXL_REQUEST_GET_POINTER_MAPPING 117
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;       /* = 1 */
};

struct libaxl_request_set_modifier_mapping {
#define LIBAXL_REQUEST_SET_MODIFIER_MAPPING 118
	uint8_t                         opcode;
	uint8_t                         keycodes_per_modifier; /* number of pairs */
	uint16_t                        _request_length;
	const libaxl_keycode_t         *keycodes;
};

struct libaxl_request_get_modifier_mapping {
#define LIBAXL_REQUEST_GET_MODIFIER_MAPPING 119
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        _request_length;       /* = 1 */
};

struct libaxl_request_no_operation {
#define LIBAXL_REQUEST_NO_OPERATION 127
	uint8_t                         opcode;
	uint8_t                         __pad;
	uint16_t                        request_length;
};

union libaxl_request { /* TODO man page */
	struct {
		uint8_t                 opcode;
		uint8_t                 __data;
		uint16_t                _request_length;
	};
# include "requests-structs.h"
};

union libaxl_request_const_ptr { /* TODO man page */
	const void                     *as_voidptr;
	const union libaxl_request     *as_union;
# include "requests-ptr-structs.h"
} _LIBAXL_GCC_ONLY(__attribute__((__transparent_union__)));
