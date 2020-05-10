/* See LICENSE file for copyright and license details. */

struct libaxl_event_key_press {
#define LIBAXL_EVENT_KEY_PRESS 2
	uint8_t                   code;
	libaxl_keycode_t          detail;
	uint16_t                  sequence_number;
	libaxl_timestamp_t        time;
	libaxl_window_t           root;
	libaxl_window_t           event;
	libaxl_window_t           child;                 /* Can be LIBAXL_NONE */
	int16_t                   root_x;
	int16_t                   root_y;
	int16_t                   event_x;
	int16_t                   event_y;
	libaxl_keybutmask_t       state;
	libaxl_bool_t             same_screen;
	uint8_t                   __unused[1];
};

struct libaxl_event_key_release {
#define LIBAXL_EVENT_KEY_RELEASE 3
	uint8_t                   code;
	libaxl_keycode_t          detail;
	uint16_t                  sequence_number;
	libaxl_timestamp_t        time;
	libaxl_window_t           root;
	libaxl_window_t           event;
	libaxl_window_t           child;                 /* Can be LIBAXL_NONE */
	int16_t                   root_x;
	int16_t                   root_y;
	int16_t                   event_x;
	int16_t                   event_y;
	libaxl_keybutmask_t       state;
	libaxl_bool_t             same_screen;
	uint8_t                   __unused[1];
};

struct libaxl_event_key_press_release {
	/* key_{press,release} */
	uint8_t                   code;
	libaxl_keycode_t          detail;
	uint16_t                  sequence_number;
	libaxl_timestamp_t        time;
	libaxl_window_t           root;
	libaxl_window_t           event;
	libaxl_window_t           child;                 /* Can be LIBAXL_NONE */
	int16_t                   root_x;
	int16_t                   root_y;
	int16_t                   event_x;
	int16_t                   event_y;
	libaxl_keybutmask_t       state;
	libaxl_bool_t             same_screen;
	uint8_t                   __unused[1];
};

struct libaxl_event_button_press {
#define LIBAXL_EVENT_BUTTON_PRESS 4
	uint8_t                   code;
	libaxl_button_t           detail;
	uint16_t                  sequence_number;
	libaxl_timestamp_t        time;
	libaxl_window_t           root;
	libaxl_window_t           event;
	libaxl_window_t           child;                 /* Can be LIBAXL_NONE */
	int16_t                   root_x;
	int16_t                   root_y;
	int16_t                   event_x;
	int16_t                   event_y;
	libaxl_keybutmask_t       state;
	libaxl_bool_t             same_screen;
	uint8_t                   __unused[1];
};

struct libaxl_event_button_release {
#define LIBAXL_EVENT_BUTTON_RELEASE 5
	uint8_t                   code;
	libaxl_button_t           detail;
	uint16_t                  sequence_number;
	libaxl_timestamp_t        time;
	libaxl_window_t           root;
	libaxl_window_t           event;
	libaxl_window_t           child;                 /* Can be LIBAXL_NONE */
	int16_t                   root_x;
	int16_t                   root_y;
	int16_t                   event_x;
	int16_t                   event_y;
	libaxl_keybutmask_t       state;
	libaxl_bool_t             same_screen;
	uint8_t                   __unused[1];
};

struct libaxl_event_button_press_release {
	/* button_{press,release} */
	uint8_t                   code;
	libaxl_button_t           detail;
	uint16_t                  sequence_number;
	libaxl_timestamp_t        time;
	libaxl_window_t           root;
	libaxl_window_t           event;
	libaxl_window_t           child;                 /* Can be LIBAXL_NONE */
	int16_t                   root_x;
	int16_t                   root_y;
	int16_t                   event_x;
	int16_t                   event_y;
	libaxl_keybutmask_t       state;
	libaxl_bool_t             same_screen;
	uint8_t                   __unused[1];
};

struct libaxl_event_motion_notify {
#define LIBAXL_EVENT_MOTION_NOTIFY 6
	uint8_t                   code;
	uint8_t                   detail;                /* LIBAXL_NORMAL or LIBAXL_HINT */
	uint16_t                  sequence_number;
	libaxl_timestamp_t        time;
	libaxl_window_t           root;
	libaxl_window_t           event;
	libaxl_window_t           child;                 /* Can be LIBAXL_NONE */
	int16_t                   root_x;
	int16_t                   root_y;
	int16_t                   event_x;
	int16_t                   event_y;
	libaxl_keybutmask_t       state;
	libaxl_bool_t             same_screen;
	uint8_t                   __unused[1];
};

struct libaxl_event_input_device_event {
	/* {key,button}_{press,release}, motion_notify */
	uint8_t                   code;
	uint8_t                   detail;
	uint16_t                  sequence_number;
	libaxl_timestamp_t        time;
	libaxl_window_t           root;
	libaxl_window_t           event;
	libaxl_window_t           child;                 /* Can be LIBAXL_NONE */
	int16_t                   root_x;
	int16_t                   root_y;
	int16_t                   event_x;
	int16_t                   event_y;
	libaxl_keybutmask_t       state;
	libaxl_bool_t             same_screen;
	uint8_t                   __unused[1];
};

struct libaxl_event_enter_notify {
#define LIBAXL_EVENT_ENTER_NOTIFY 7
	uint8_t                   code;
	uint8_t                   detail;                /* See "pointer window details" in libaxl-consts.h */
	uint16_t                  sequence_number;
	libaxl_timestamp_t        time;
	libaxl_window_t           root;
	libaxl_window_t           event;
	libaxl_window_t           child;                 /* Can be LIBAXL_NONE */
	int16_t                   root_x;
	int16_t                   root_y;
	int16_t                   event_x;
	int16_t                   event_y;
	libaxl_keybutmask_t       state;
	uint8_t                   mode;                  /* LIBAXL_NORMAL, LIBAXL_GRAB, or LIBAXL_UNGRAB */
	uint8_t                   flags;                 /* TODO #x01 = Focus, #x02 = Same-screen */
};

struct libaxl_event_leave_notify {
#define LIBAXL_EVENT_LEAVE_NOTIFY 8
	uint8_t                   code;
	uint8_t                   detail;                /* See "pointer window details" in libaxl-consts.h */
	uint16_t                  sequence_number;
	libaxl_timestamp_t        time;
	libaxl_window_t           root;
	libaxl_window_t           event;
	libaxl_window_t           child;                 /* Can be LIBAXL_NONE */
	int16_t                   root_x;
	int16_t                   root_y;
	int16_t                   event_x;
	int16_t                   event_y;
	libaxl_keybutmask_t       state;
	uint8_t                   mode;                  /* LIBAXL_NORMAL, LIBAXL_GRAB, or LIBAXL_UNGRAB */
	uint8_t                   flags;                 /* TODO #x01 = Focus, #x02 = Same-screen */
};

struct libaxl_event_pointer_window_event {
	/* {enter,leave}_notify */
	uint8_t                   code;
	uint8_t                   detail;                /* See "pointer window details" in libaxl-consts.h */
	uint16_t                  sequence_number;
	libaxl_timestamp_t        time;
	libaxl_window_t           root;
	libaxl_window_t           event;
	libaxl_window_t           child;                 /* Can be LIBAXL_NONE */
	int16_t                   root_x;
	int16_t                   root_y;
	int16_t                   event_x;
	int16_t                   event_y;
	libaxl_keybutmask_t       state;
	uint8_t                   mode;                  /* LIBAXL_NORMAL, LIBAXL_GRAB, or LIBAXL_UNGRAB */
	uint8_t                   flags;                 /* TODO #x01 = Focus, #x02 = Same-screen */
};

struct libaxl_event_focus_in {
#define LIBAXL_EVENT_FOCUS_IN 9
	uint8_t                   code;
	uint8_t                   detail;                /* See "window focus details" in libaxl-consts.h (Beware of namespacing!) */
	uint16_t                  sequence_number;
	libaxl_window_t           window;
	uint8_t                   mode;                  /* LIBAXL_NORMAL, LIBAXL_GRAB, LIBAXL_UNGRAB, or LIBAXL_WHILE_GRABBED */
	uint8_t                   __unused[23];
};

struct libaxl_event_focus_out {
#define LIBAXL_EVENT_FOCUS_OUT 10
	uint8_t                   code;
	uint8_t                   detail;                /* See "window focus details" in libaxl-consts.h (Beware of namespacing!) */
	uint16_t                  sequence_number;
	libaxl_window_t           window;
	uint8_t                   mode;                  /* LIBAXL_NORMAL, LIBAXL_GRAB, LIBAXL_UNGRAB, or LIBAXL_WHILE_GRABBED */
	uint8_t                   __unused[23];
};

struct libaxl_event_input_focus_event {
	/* focus_{in,out} */
	uint8_t                   code;
	uint8_t                   detail;                /* See "window focus details" in libaxl-consts.h (Beware of namespacing!) */
	uint16_t                  sequence_number;
	libaxl_window_t           window;
	uint8_t                   mode;                  /* LIBAXL_NORMAL, LIBAXL_GRAB, LIBAXL_UNGRAB, or LIBAXL_WHILE_GRABBED */
	uint8_t                   __unused[23];
};

struct libaxl_event_keymap_notify {
#define LIBAXL_EVENT_KEYMAP_NOTIFY 11
	uint8_t                   code;
	uint8_t                   keys[31];              /* Byte for keycodes 0-7, which are unused, is omitted */
};

struct libaxl_event_expose {
#define LIBAXL_EVENT_EXPOSE 12
	uint8_t                   code;
	uint8_t                   __pad;
	uint16_t                  sequence_number;
	libaxl_window_t           window;
	uint16_t                  x;
	uint16_t                  y;
	uint16_t                  width;
	uint16_t                  height;
	uint16_t                  count;
	uint8_t                   __unused[14];
};

struct libaxl_event_graphics_exposure {
#define LIBAXL_EVENT_GRAPHICS_EXPOSURE 13
	uint8_t                   code;
	uint8_t                   __pad;
	uint16_t                  sequence_number;
	libaxl_drawable_t         drawable;
	uint16_t                  x;
	uint16_t                  y;
	uint16_t                  width;
	uint16_t                  height;
	uint16_t                  minor_opcode;
	uint16_t                  count;
	uint8_t                   major_opcode;
	uint8_t                   __unused[11];
};

struct libaxl_event_no_exposure {
#define LIBAXL_EVENT_NO_EXPOSURE 14
	uint8_t                   code;
	uint8_t                   __pad;
	uint16_t                  sequence_number;
	libaxl_drawable_t         drawable;
	uint16_t                  minor_opcode;
	uint8_t                   major_opcode;
	uint8_t                   __unused[21];
};

struct libaxl_event_visibility_notify {
#define LIBAXL_EVENT_VISIBILITY_NOTIFY 15
	uint8_t                   code;
	uint8_t                   __pad;
	uint16_t                  sequence_number;
	libaxl_drawable_t         drawable;
	uint8_t                   state;                 /* LIBAXL_UNOBSCURED, LIBAXL_PARTIALLY_OBSCURED, or LIBAXL_FULLY_OBSCURED */
	uint8_t                   __unused[23];
};

struct libaxl_event_create_notify {
#define LIBAXL_EVENT_CREATE_NOTIFY 16
	uint8_t                   code;
	uint8_t                   __pad;
	uint16_t                  sequence_number;
	libaxl_window_t           parent;
	libaxl_window_t           window;
	int16_t                   x;
	int16_t                   y;
	int16_t                   width;
	int16_t                   height;
	int16_t                   border_width;
	libaxl_bool_t             override_redirect;
	uint8_t                   __unused[9];
};

struct libaxl_event_destroy_notify {
#define LIBAXL_EVENT_DESTROY_NOTIFY 17
	uint8_t                   code;
	uint8_t                   __pad;
	uint16_t                  sequence_number;
	libaxl_window_t           event;
	libaxl_window_t           window;
	uint8_t                   __unused[20];
};

struct libaxl_event_unmap_notify {
#define LIBAXL_EVENT_UNMAP_NOTIFY 18
	uint8_t                   code;
	uint8_t                   __pad;
	uint16_t                  sequence_number;
	libaxl_window_t           event;
	libaxl_window_t           window;
	libaxl_bool_t             from_configure;
	uint8_t                   __unused[19];
};

struct libaxl_event_map_notify {
#define LIBAXL_EVENT_MAP_NOTIFY 19
	uint8_t                   code;
	uint8_t                   __pad;
	uint16_t                  sequence_number;
	libaxl_window_t           event;
	libaxl_window_t           window;
	libaxl_bool_t             override_redirect;
	uint8_t                   __unused[19];
};

struct libaxl_event_map_request {
#define LIBAXL_EVENT_MAP_REQUEST 20
	uint8_t                   code;
	uint8_t                   __pad;
	uint16_t                  sequence_number;
	libaxl_window_t           parent;
	libaxl_window_t           window;
	uint8_t                   __unused[20];
};

struct libaxl_event_reparent_notify {
#define LIBAXL_EVENT_REPARENT_NOTIFY 21
	uint8_t                   code;
	uint8_t                   __pad;
	uint16_t                  sequence_number;
	libaxl_window_t           event;
	libaxl_window_t           window;
	libaxl_window_t           parent;
	int16_t                   x;
	int16_t                   y;
	libaxl_bool_t             override_redirect;
	uint8_t                   __unused[11];
};

struct libaxl_event_configure_notify {
#define LIBAXL_EVENT_CONFIGURE_NOTIFY 22
	uint8_t                   code;
	uint8_t                   __pad;
	uint16_t                  sequence_number;
	libaxl_window_t           event;
	libaxl_window_t           window;
	libaxl_window_t           above_sibling;         /* Can be LIBAXL_NONE */
	int16_t                   x;
	int16_t                   y;
	uint16_t                  width;
	uint16_t                  height;
	uint16_t                  border_width;
	libaxl_bool_t             override_redirect;
	uint8_t                   __unused[5];
};

struct libaxl_event_configure_request {
#define LIBAXL_EVENT_CONFIGURE_REQUEST 23
	uint8_t                   code;
	uint8_t                   stack_mode;            /* See "stack mode" in libaxl-consts.h */
	uint16_t                  sequence_number;
	libaxl_window_t           event;
	libaxl_window_t           window;
	libaxl_window_t           sibling;               /* Can be LIBAXL_NONE */
	int16_t                   x;
	int16_t                   y;
	uint16_t                  width;
	uint16_t                  height;
	uint16_t                  border_width;
	uint16_t                  value_mask;
#define LIBAXL_EVENT_CONFIGURE_REQUEST_X            0x0001U
#define LIBAXL_EVENT_CONFIGURE_REQUEST_Y            0x0002U
#define LIBAXL_EVENT_CONFIGURE_REQUEST_WIDTH        0x0004U
#define LIBAXL_EVENT_CONFIGURE_REQUEST_HEIGHT       0x0008U
#define LIBAXL_EVENT_CONFIGURE_REQUEST_BORDER_WIDTH 0x0010U
#define LIBAXL_EVENT_CONFIGURE_REQUEST_SIBLING      0x0020U
#define LIBAXL_EVENT_CONFIGURE_REQUEST_STACK_MODE   0x0040U
	uint8_t                   __unused[4];
};

struct libaxl_event_gravity_notify {
#define LIBAXL_EVENT_GRAVITY_NOTIFY 24
	uint8_t                   code;
	uint8_t                   __pad;
	uint16_t                  sequence_number;
	libaxl_window_t           event;
	libaxl_window_t           window;
	int16_t                   x;
	int16_t                   y;
	uint8_t                   __unused[16];
};

struct libaxl_event_resize_request {
#define LIBAXL_EVENT_RESIZE_REQUEST 25
	uint8_t                   code;
	uint8_t                   __pad;
	uint16_t                  sequence_number;
	libaxl_window_t           window;
	uint16_t                  width;
	uint16_t                  height;
	uint8_t                   __unused[20];
};

struct libaxl_event_circulate_notify {
#define LIBAXL_EVENT_CIRCULATE_NOTIFY 26
	uint8_t                   code;
	uint8_t                   __pad;
	uint16_t                  sequence_number;
	libaxl_window_t           event;
	libaxl_window_t           window;
	uint32_t                  __unused1;
	uint8_t                   place;                 /* LIBAXL_TOP or LIBAXL_BOTTOM */
	uint8_t                   __unused[15];
};

struct libaxl_event_circulate_request {
#define LIBAXL_EVENT_CIRCULATE_REQUEST 27
	uint8_t                   code;
	uint8_t                   __pad;
	uint16_t                  sequence_number;
	libaxl_window_t           parent;
	libaxl_window_t           window;
	uint32_t                  __unused1;
	uint8_t                   place;                 /* LIBAXL_TOP or LIBAXL_BOTTOM */
	uint8_t                   __unused[15];
};

struct libaxl_event_property_notify {
#define LIBAXL_EVENT_PROPERTY_NOTIFY 28
	uint8_t                   code;
	uint8_t                   __pad;
	uint16_t                  sequence_number;
	libaxl_window_t           window;
	libaxl_atom_t             atom;
	uint8_t                   state;                 /* LIBAXL_NEW_VALUE or LIBAXL_DELETED */
	uint8_t                   __unused[15];
};

struct libaxl_event_selection_clear {
#define LIBAXL_EVENT_SELECTION_CLEAR 29
	uint8_t                   code;
	uint8_t                   __pad;
	uint16_t                  sequence_number;
	libaxl_timestamp_t        time;
	libaxl_window_t           owner;
	libaxl_atom_t             selection;
	uint8_t                   __unused[16];
};

struct libaxl_event_selection_request {
#define LIBAXL_EVENT_SELECTION_REQUEST 30
	uint8_t                   code;
	uint8_t                   __pad;
	uint16_t                  sequence_number;
	libaxl_timestamp_t        time;                  /* Can be LIBAXL_CURRENT_TIME */
	libaxl_window_t           owner;
	libaxl_window_t           requestor;
	libaxl_atom_t             selection;
	libaxl_atom_t             target;
	libaxl_atom_t             property;              /* Can be LIBAXL_NONE */
	uint8_t                   __unused[4];
};

struct libaxl_event_selection_notify {
#define LIBAXL_EVENT_SELECTION_NOTIFY 31
	uint8_t                   code;
	uint8_t                   __pad;
	uint16_t                  sequence_number;
	libaxl_timestamp_t        time;                  /* Can be LIBAXL_CURRENT_TIME */
	libaxl_window_t           requestor;
	libaxl_atom_t             selection;
	libaxl_atom_t             target;
	libaxl_atom_t             property;              /* Can be LIBAXL_NONE */
	uint8_t                   __unused[8];
};

struct libaxl_event_colormap_notify {
#define LIBAXL_EVENT_COLORMAP_NOTIFY 32
	uint8_t                   code;
	uint8_t                   __pad;
	uint16_t                  sequence_number;
	libaxl_window_t           requestor;
	libaxl_colormap_t         colormap;              /* Can be LIBAXL_NONE */
	libaxl_bool_t             new;
	uint8_t                   state;                 /* LIBAXL_UNINSTALLED or LIBAXL_INSTALLED */
	uint8_t                   __unused[18];
};

struct libaxl_event_client_message {
#define LIBAXL_EVENT_CLIENT_MESSAGE 33
	uint8_t                   code;
	uint8_t                   format;                /* {8, 16, 32} */
	uint16_t                  sequence_number;
	libaxl_window_t           window;
	libaxl_atom_t             type;
	union {
		uint8_t           u8[20];
		uint16_t          u16[10];
		uint32_t          u32[5];
	} data;
};

struct libaxl_event_mapping_notify {
#define LIBAXL_EVENT_MAPPING_NOTIFY 34
	uint8_t                   code;
	uint8_t                   __pad;
	uint16_t                  sequence_number;
	uint8_t                   request;               /* LIBAXL_MODIFIER, LIBAXL_KEYBOARD, or LIBAXL_POINTER */
	libaxl_keycode_t          first_keycode;
	uint8_t                   count;
	uint8_t                   __unused[25];
};

union libaxl_event {
	uint8_t                   code;                  /* Highest bit marks the event as sent with SendEvent */
	/* .keymap_notify does not have a sequence number */
#include "libaxl-events-structs.h"
};
