/* See LICENSE file for copyright and license details. */

#if !defined(LIBAXL_H) || (LIBAXL_H < 2)
# error Do not include <libaxl/consts.h> directly, include <libaxl.h> instead.
#endif

/* libaxl_keycode_t */
#define LIBAXL_ANY_KEY              0

/* libaxl_bool_t */
#define LIBAXL_FALSE                0
#define LIBAXL_TRUE                 1

/* libaxl_timestamp_t */
#define LIBAXL_CURRENT_TIME         0

/* struct libaxl_host.family
   struct libaxl_request_change_hosts.family */
#define LIBAXL_INTERNET             0    /* IPv4 */
#define LIBAXL_DECNET               1    /* DECnet */
#define LIBAXL_CHAOS                2    /* Chaos */
#define LIBAXL_SERVER_INTERPRETED   5    /* Server Interpreted */
#define LIBAXL_INTERNET_V6          6    /* IPv6 */

/* union libaxl_text_item8
   union libaxl_text_item16 */
#define LIBAXL_FONT_SHIFT_INDICATOR 255

/* struct libaxl_coloritem.flags
   struct libaxl_request_store_named_color.flags */
#define LIBAXL_RED                  0x01
#define LIBAXL_GREEN                0x02
#define LIBAXL_BLUE                 0x04

/* struct libaxl_request_set_clip_rectangles.ordering */
#define LIBAXL_UNSORTED             0
#define LIBAXL_YSORTED              1
#define LIBAXL_YXSORTED             2
#define LIBAXL_YXBANDED             3

/* struct libaxl_request_force_screen_saver.mode */
#define LIBAXL_RESET                0
#define LIBAXL_ACTIVATE             1

/* struct libaxl_request_query_best_size.class */
#define LIBAXL_CURSOR               0
#define LIBAXL_TILE                 1
#define LIBAXL_STIPPLE              2

/* struct libaxl_request_circulate_windo.direction */
#define LIBAXL_RAISE_LOWEST         0
#define LIBAXL_LOWER_HIGHEST        1

/* struct libaxl_request_allow_events.mode */
#define LIBAXL_ASYNC_POINTER        0
#define LIBAXL_SYNC_POINTER         1
#define LIBAXL_REPLAY_POINTER       2
#define LIBAXL_ASYNC_KEYBOARD       3
#define LIBAXL_SYNC_KEYBOARD        4
#define LIBAXL_REPLAY_KEYBOARD      5
#define LIBAXL_ASYNC_BOTH           6
#define LIBAXL_SYNC_BOTH            7

/* struct libaxl_request_change_property.mode */
#define LIBAXL_REPLACE              0
#define LIBAXL_PREPEND              1
#define LIBAXL_APPEND               2

/* struct libaxl_request_send_event.destination */
#define LIBAXL_POINTER_WINDOW       0
#define LIBAXL_INPUT_FOCUS          1

/* struct libaxl_event_property_notify.state */
#define LIBAXL_NEW_VALUE            0
#define LIBAXL_DELETED              1

/* struct libaxl_event_colormap_notify.state */
#define LIBAXL_UNINSTALLED          0
#define LIBAXL_INSTALLED            1

/* struct libaxl_event_mapping_notify.request */
#define LIBAXL_MODIFIER             0
#define LIBAXL_KEYBOARD             1
#define LIBAXL_POINTER              2

/* struct libaxl_visual_type.class */
#define LIBAXL_STATIC_GRAY          0
#define LIBAXL_GRAY_SCALE           1
#define LIBAXL_STATIC_COLOR         2
#define LIBAXL_PSEUDO_COLOR         3
#define LIBAXL_TRUE_COLOR           4
#define LIBAXL_DIRECT_COLOR         5

/* circatulation place */
#define LIBAXL_TOP                  0
#define LIBAXL_BOTTOM               1

/* cap style */
#define LIBAXL_CAP_NOT_LAST         0
#define LIBAXL_CAP_BUTT             1
#define LIBAXL_CAP_ROUND            2
#define LIBAXL_CAP_PROJECTING       3

/* join style */
#define LIBAXL_JOIN_MITER           0
#define LIBAXL_JOIN_ROUND           1
#define LIBAXL_JOIN_BEVEL           2

/* map state */
#define LIBAXL_UNMAPPED             0
#define LIBAXL_UNVIEWABLE           1
#define LIBAXL_VIEWABLE             2

/* gcontext function */
#define LIBAXL_CLEAR                0
#define LIBAXL_AND                  1
#define LIBAXL_AND_REVERSE          2
#define LIBAXL_COPY                 3
#define LIBAXL_AND_INVERTED         4
#define LIBAXL_NO_OP                5
#define LIBAXL_XOR                  6
#define LIBAXL_OR                   7
#define LIBAXL_NOR                  8
#define LIBAXL_EQUIV                9
#define LIBAXL_INVERT               10
#define LIBAXL_OR_REVERSE           11
#define LIBAXL_COPY_INVERTED        12
#define LIBAXL_OR_INVERTED          13
#define LIBAXL_NAND                 14
#define LIBAXL_SET                  15

/* close down mode */
#define LIBAXL_DESTROY              0
#define LIBAXL_RETAIN_PERMANENT     1
#define LIBAXL_RETAIN_TEMPORARY     2

/* visibility state */
#define LIBAXL_UNOBSCURED           0
#define LIBAXL_PARTIALLY_OBSCURED   1
#define LIBAXL_FULLY_OBSCURED       2

/* bitgravity and wingravity */
#define LIBAXL_FORGET               0    /* bitgravity */
#define LIBAXL_UNMAP                0    /* wingravity */
#define LIBAXL_NORTH_WEST           1
#define LIBAXL_NORTH                2
#define LIBAXL_NORTH_EAST           3
#define LIBAXL_WEST                 4
#define LIBAXL_CENTER               5
#define LIBAXL_EAST                 6
#define LIBAXL_SOUTH_WEST           7
#define LIBAXL_SOUTH                8
#define LIBAXL_SOUTH_EAST           9
#define LIBAXL_STATIC               10

/* synchronicity */
#define LIBAXL_SYNCHRONOUS          0
#define LIBAXL_ASYNCHRONOUS         1

/* image formats */
#define LIBAXL_BITMAP               0
#define LIBAXL_XYPIXMAP             1
#define LIBAXL_ZPIXMAP              2

/* buttons */
#define LIBAXL_ANY_BUTTON           0

/* draw directions */
#define LIBAXL_LEFT_TO_RIGHT        0
#define LIBAXL_RIGHT_TO_LEFT        1

/* fill rule */
#define LIBAXL_EVEN_ODD             0
#define LIBAXL_WINDING              1

/* fill style and line style */
#define LIBAXL_SOLID                0
#define LIBAXL_TILED                1    /* fill style */
#define LIBAXL_STIPPLED             2    /* fill style */
#define LIBAXL_OPAQUE_STIPPLED      3    /* fill style */
#define LIBAXL_ON_OFF_DASH          1    /* line style */
#define LIBAXL_DOUBLE_DASH          2    /* line style */

/* polygon shape */
#define LIBAXL_COMPLEX              0
#define LIBAXL_NONCONVEX            1
#define LIBAXL_CONVEX               2

/* arc mode */
#define LIBAXL_CHORD                0
#define LIBAXL_PIE_SLICE            1

/* grab mode (includes LIBAXL_NORMAL) */
#define LIBAXL_GRAB                 1
#define LIBAXL_UNGRAB               2
#define LIBAXL_WHILE_GRABBED        3

/* grab status (includes LIBAXL_SUCCESS) */
#define LIBAXL_ALREADY_GRABBED      1
#define LIBAXL_INVALID_TIME         2
#define LIBAXL_NOT_VIEWABLE         3
#define LIBAXL_FROZEN               4

/* coordinate mode */
#define LIBAXL_ORIGIN               0
#define LIBAXL_PREVIOUS             1

/* enabled status */
#define LIBAXL_DISABLE              0
#define LIBAXL_DISABLED             0
#define LIBAXL_ENABLE               1
#define LIBAXL_ENABLED              1

/* window class */
#define LIBAXL_INPUT_OUTPUT         1
#define LIBAXL_INPUT_ONLY           2

/* subwindow mode */
#define LIBAXL_CLIP_BY_CHILDREN     0
#define LIBAXL_INCLUDE_INFERIORS    1

/* backing store */
#define LIBAXL_NOT_USEFUL           0 /* Not used in `struct libaxl_screen.backing_stores` */
#define LIBAXL_NEVER                0 /* Used in `struct libaxl_screen.backing_stores` */
#define LIBAXL_WHEN_MAPPED          1
#define LIBAXL_ALWAYS               2

/* change mode */
#define LIBAXL_INSERT               0
#define LIBAXL_DELETE               1

/* stack mode */
#define LIBAXL_ABOVE                0
#define LIBAXL_BELOW                1
#define LIBAXL_TOP_IF               2
#define LIBAXL_BOTTOM_IF            3
#define LIBAXL_OPPOSITE             4

/* pointer window detail and window focus details */
#define LIBAXL_ANCESTOR             0
#define LIBAXL_VIRTUAL              1
#define LIBAXL_INFERIOR             2
#define LIBAXL_NONLINEAR            3
#define LIBAXL_NONLINEAR_VIRTUAL    4
/* window focus details */
#define LIBAXL_FOCUS_POINTER        5 /* Just called Pointer in the specification */
#define LIBAXL_FOCUS_POINTER_ROOT   6 /* Just called PointerRoot in the specification */
#define LIBAXL_FOCUS_NONE           7 /* Just called None in the specification */

/* focus flags */
#define LIBAXL_FOCUS                0x01
#define LIBAXL_SAME_SCREEN          0x02

/* misc. */
#define LIBAXL_ANY_PROPERTY_TYPE    0
#define LIBAXL_ALL_TEMPORARY        0
#define LIBAXL_PARENT_RELATIVE      1
#define LIBAXL_HINT                 1
#define LIBAXL_ALL                  1

/* generic */
#define LIBAXL_NONE                 0
#define LIBAXL_NORMAL               0
#define LIBAXL_SUCCESS              0
#define LIBAXL_BUSY                 1
#define LIBAXL_FAILED               2
#define LIBAXL_NO                   0
#define LIBAXL_YES                  1
#define LIBAXL_DEFAULT              2
#define LIBAXL_OFF                  0
#define LIBAXL_ON                   1
#define LIBAXL_COPY_FROM_PARENT     0
#define LIBAXL_POINTER_ROOT         1
#define LIBAXL_PARENT               2

/* window event mask */
#define LIBAXL_EVENT_MASK_KEY_PRESS             UINT32_C(0x00000001) /* in SETofDEVICEEVENT                       */
#define LIBAXL_EVENT_MASK_KEY_RELEASE           UINT32_C(0x00000002) /* in SETofDEVICEEVENT                       */
#define LIBAXL_EVENT_MASK_BUTTON_PRESS          UINT32_C(0x00000004) /* in SETofDEVICEEVENT and SETofPOINTEREVENT */
#define LIBAXL_EVENT_MASK_BUTTON_RELEASE        UINT32_C(0x00000008) /* in SETofDEVICEEVENT and SETofPOINTEREVENT */
#define LIBAXL_EVENT_MASK_ENTER_WINDOW          UINT32_C(0x00000010) /* in                      SETofPOINTEREVENT */
#define LIBAXL_EVENT_MASK_LEAVE_WINDOW          UINT32_C(0x00000020) /* in                      SETofPOINTEREVENT */
#define LIBAXL_EVENT_MASK_POINTER_MOTION        UINT32_C(0x00000040) /* in SETofDEVICEEVENT and SETofPOINTEREVENT */
#define LIBAXL_EVENT_MASK_POINTER_MOTION_HINT   UINT32_C(0x00000080) /* in                      SETofPOINTEREVENT */
#define LIBAXL_EVENT_MASK_BUTTON_1_MOTION       UINT32_C(0x00000100) /* in SETofDEVICEEVENT and SETofPOINTEREVENT */
#define LIBAXL_EVENT_MASK_BUTTON_2_MOTION       UINT32_C(0x00000200) /* in SETofDEVICEEVENT and SETofPOINTEREVENT */
#define LIBAXL_EVENT_MASK_BUTTON_3_MOTION       UINT32_C(0x00000400) /* in SETofDEVICEEVENT and SETofPOINTEREVENT */
#define LIBAXL_EVENT_MASK_BUTTON_4_MOTION       UINT32_C(0x00000800) /* in SETofDEVICEEVENT and SETofPOINTEREVENT */
#define LIBAXL_EVENT_MASK_BUTTON_5_MOTION       UINT32_C(0x00001000) /* in SETofDEVICEEVENT and SETofPOINTEREVENT */
#define LIBAXL_EVENT_MASK_BUTTON_MOTION         UINT32_C(0x00002000) /* in SETofDEVICEEVENT and SETofPOINTEREVENT */
#define LIBAXL_EVENT_MASK_KEYMAP_STATE          UINT32_C(0x00004000) /* in                      SETofPOINTEREVENT */
#define LIBAXL_EVENT_MASK_EXPOSURE              UINT32_C(0x00008000)
#define LIBAXL_EVENT_MASK_VISIBILITY_CHANGE     UINT32_C(0x00010000)
#define LIBAXL_EVENT_MASK_STRUCTURE_NOTIFY      UINT32_C(0x00020000)
#define LIBAXL_EVENT_MASK_RESIZE_REDIRECT       UINT32_C(0x00040000)
#define LIBAXL_EVENT_MASK_SUBSTRUCTURE_NOTIFY   UINT32_C(0x00080000)
#define LIBAXL_EVENT_MASK_SUBSTRUCTURE_REDIRECT UINT32_C(0x00100000)
#define LIBAXL_EVENT_MASK_FOCUS_CHANGE          UINT32_C(0x00200000)
#define LIBAXL_EVENT_MASK_PROPERTY_CHANGE       UINT32_C(0x00400000)
#define LIBAXL_EVENT_MASK_COLOR_MAP_CHANGE      UINT32_C(0x00800000)
#define LIBAXL_EVENT_MASK_OWNER_GRAB_BUTTON     UINT32_C(0x01000000)
