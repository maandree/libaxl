.POSIX:

LIB_MAJOR = 0
LIB_MINOR = 1
LIB_VERSION = $(LIB_MAJOR).$(LIB_MINOR)

CONFIGFILE = config.mk
OSCONFIGFILE = linux.mk

include $(CONFIGFILE)
include $(OSCONFIGFILE)

OBJ =\
	libaxl_attach.o\
	libaxl_close.o\
	libaxl_connect.o\
	libaxl_connect_without_handshake.o\
	libaxl_context_create.o\
	libaxl_context_free.o\
	libaxl_create.o\
	libaxl_deallocate_id.o\
	libaxl_detach.o\
	libaxl_fileno.o\
	libaxl_flush.o\
	libaxl_generate_id.o\
	libaxl_get_decnet_object.o\
	libaxl_get_tcp_port.o\
	libaxl_info.o\
	libaxl_next_depth.o\
	libaxl_next_screen.o\
	libaxl_parse_display.o\
	libaxl_protocol_version.o\
	libaxl_protocol_version_major.o\
	libaxl_protocol_version_minor.o\
	libaxl_receive.o\
	libaxl_receive_handshake.o\
	libaxl_send_handshake.o\
	libaxl_send_request.o

LIB_SUBHDR_GEN =\
	libaxl/errors-structs.h\
	libaxl/events-structs.h\
	libaxl/replies-structs.h\
	libaxl/requests-ptr-structs.h\
	libaxl/requests-structs.h

LIB_SUBHDR =\
	libaxl/advanced.h\
	libaxl/atoms.h\
	libaxl/consts.h\
	libaxl/display-info.h\
	libaxl/errors.h\
	libaxl/events.h\
	libaxl/low-level.h\
	libaxl/replies.h\
	libaxl/requests.h\
	libaxl/types.h\
	$(LIB_SUBHDR_GEN)

LIB_HDR =\
	libaxl.h\
	$(LIB_SUBHDR)

HDR =\
	common.h\
	internal-linux.h\
	internal-llmutex.h\
	$(LIB_HDR)

MAN3 =\
	man3/LIBAXL_ATOM_ARC.3\
	man3/LIBAXL_ATOM_ATOM.3\
	man3/LIBAXL_ATOM_BITMAP.3\
	man3/LIBAXL_ATOM_CAP_HEIGHT.3\
	man3/LIBAXL_ATOM_CARDINAL.3\
	man3/LIBAXL_ATOM_COLORMAP.3\
	man3/LIBAXL_ATOM_COPYRIGHT.3\
	man3/LIBAXL_ATOM_CURSOR.3\
	man3/LIBAXL_ATOM_CUT_BUFFER0.3\
	man3/LIBAXL_ATOM_CUT_BUFFER1.3\
	man3/LIBAXL_ATOM_CUT_BUFFER2.3\
	man3/LIBAXL_ATOM_CUT_BUFFER3.3\
	man3/LIBAXL_ATOM_CUT_BUFFER4.3\
	man3/LIBAXL_ATOM_CUT_BUFFER5.3\
	man3/LIBAXL_ATOM_CUT_BUFFER6.3\
	man3/LIBAXL_ATOM_CUT_BUFFER7.3\
	man3/LIBAXL_ATOM_DRAWABLE.3\
	man3/LIBAXL_ATOM_END_SPACE.3\
	man3/LIBAXL_ATOM_FAMILY_NAME.3\
	man3/LIBAXL_ATOM_FONT.3\
	man3/LIBAXL_ATOM_FONT_NAME.3\
	man3/LIBAXL_ATOM_FULL_NAME.3\
	man3/LIBAXL_ATOM_INTEGER.3\
	man3/LIBAXL_ATOM_ITALIC_ANGLE.3\
	man3/LIBAXL_ATOM_MAX_SPACE.3\
	man3/LIBAXL_ATOM_MIN_SPACE.3\
	man3/LIBAXL_ATOM_NORM_SPACE.3\
	man3/LIBAXL_ATOM_NOTICE.3\
	man3/LIBAXL_ATOM_PIXMAP.3\
	man3/LIBAXL_ATOM_POINT.3\
	man3/LIBAXL_ATOM_POINT_SIZE.3\
	man3/LIBAXL_ATOM_PRIMARY.3\
	man3/LIBAXL_ATOM_QUAD_WIDTH.3\
	man3/LIBAXL_ATOM_RECTANGLE.3\
	man3/LIBAXL_ATOM_RESOLUTION.3\
	man3/LIBAXL_ATOM_RESOURCE_MANAGER.3\
	man3/LIBAXL_ATOM_RGB_BEST_MAP.3\
	man3/LIBAXL_ATOM_RGB_BLUE_MAP.3\
	man3/LIBAXL_ATOM_RGB_COLOR_MAP.3\
	man3/LIBAXL_ATOM_RGB_DEFAULT_MAP.3\
	man3/LIBAXL_ATOM_RGB_GRAY_MAP.3\
	man3/LIBAXL_ATOM_RGB_GREEN_MAP.3\
	man3/LIBAXL_ATOM_RGB_RED_MAP.3\
	man3/LIBAXL_ATOM_SECONDARY.3\
	man3/LIBAXL_ATOM_STRIKEOUT_ASCENT.3\
	man3/LIBAXL_ATOM_STRIKEOUT_DESCENT.3\
	man3/LIBAXL_ATOM_STRING.3\
	man3/LIBAXL_ATOM_SUBSCRIPT_X.3\
	man3/LIBAXL_ATOM_SUBSCRIPT_Y.3\
	man3/LIBAXL_ATOM_SUPERSCRIPT_X.3\
	man3/LIBAXL_ATOM_SUPERSCRIPT_Y.3\
	man3/LIBAXL_ATOM_UNDERLINE_POSITION.3\
	man3/LIBAXL_ATOM_UNDERLINE_THICKNESS.3\
	man3/LIBAXL_ATOM_VISUALID.3\
	man3/LIBAXL_ATOM_WEIGHT.3\
	man3/LIBAXL_ATOM_WINDOW.3\
	man3/LIBAXL_ATOM_WM_CLASS.3\
	man3/LIBAXL_ATOM_WM_CLIENT_MACHINE.3\
	man3/LIBAXL_ATOM_WM_COMMAND.3\
	man3/LIBAXL_ATOM_WM_HINTS.3\
	man3/LIBAXL_ATOM_WM_ICON_NAME.3\
	man3/LIBAXL_ATOM_WM_ICON_SIZE.3\
	man3/LIBAXL_ATOM_WM_NAME.3\
	man3/LIBAXL_ATOM_WM_NORMAL_HINTS.3\
	man3/LIBAXL_ATOM_WM_SIZE_HINTS.3\
	man3/LIBAXL_ATOM_WM_TRANSIENT_FOR.3\
	man3/LIBAXL_ATOM_WM_ZOOM_HINTS.3\
	man3/LIBAXL_ATOM_X_HEIGHT.3\
	man3/LIBAXL_CONNECTION.3\
	man3/LIBAXL_CONTEXT.3\
	man3/LIBAXL_DECNET_OBJECT_MAX.3\
	man3/LIBAXL_ERROR.3\
	man3/LIBAXL_ERROR_ACCESS.3\
	man3/LIBAXL_ERROR_ALLOC.3\
	man3/LIBAXL_ERROR_ATOM.3\
	man3/LIBAXL_ERROR_COLORMAP.3\
	man3/LIBAXL_ERROR_CURSOR.3\
	man3/LIBAXL_ERROR_DRAWABLE.3\
	man3/LIBAXL_ERROR_FONT.3\
	man3/LIBAXL_ERROR_GCONTEXT.3\
	man3/LIBAXL_ERROR_ID_CHOICE.3\
	man3/LIBAXL_ERROR_IMPLEMENTATION.3\
	man3/LIBAXL_ERROR_LENGTH.3\
	man3/LIBAXL_ERROR_MATCH.3\
	man3/LIBAXL_ERROR_NAME.3\
	man3/LIBAXL_ERROR_PIXMAP.3\
	man3/LIBAXL_ERROR_REQUEST.3\
	man3/LIBAXL_ERROR_VALUE.3\
	man3/LIBAXL_ERROR_WINDOW.3\
	man3/LIBAXL_HANDSHAKE_AUTHENTICATE.3\
	man3/LIBAXL_HANDSHAKE_FAILED.3\
	man3/LIBAXL_HANDSHAKE_SUCCESS.3\
	man3/LIBAXL_PROTOCOL_VERSION.3\
	man3/LIBAXL_PROTOCOL_VERSION_MAJOR.3\
	man3/LIBAXL_PROTOCOL_VERSION_MINOR.3\
	man3/LIBAXL_REQUEST_ALLOC_COLOR.3\
	man3/LIBAXL_REQUEST_ALLOC_COLOR_CELLS.3\
	man3/LIBAXL_REQUEST_ALLOC_COLOR_PLANES.3\
	man3/LIBAXL_REQUEST_ALLOC_NAMED_COLOR.3\
	man3/LIBAXL_REQUEST_ALLOW_EVENTS.3\
	man3/LIBAXL_REQUEST_BELL.3\
	man3/LIBAXL_REQUEST_CHANGE_ACTIVE_POINTER_GRAB.3\
	man3/LIBAXL_REQUEST_CHANGE_GC.3\
	man3/LIBAXL_REQUEST_CHANGE_GC_FUNCTION.3\
	man3/LIBAXL_REQUEST_CHANGE_GC_PLANE_MASK.3\
	man3/LIBAXL_REQUEST_CHANGE_GC_FOREGROUND.3\
	man3/LIBAXL_REQUEST_CHANGE_GC_BACKGROUND.3\
	man3/LIBAXL_REQUEST_CHANGE_GC_LINE_WIDTH.3\
	man3/LIBAXL_REQUEST_CHANGE_GC_LINE_STYLE.3\
	man3/LIBAXL_REQUEST_CHANGE_GC_CAP_STYLE.3\
	man3/LIBAXL_REQUEST_CHANGE_GC_JOIN_STYLE.3\
	man3/LIBAXL_REQUEST_CHANGE_GC_FILL_STYLE.3\
	man3/LIBAXL_REQUEST_CHANGE_GC_FILL_RULE.3\
	man3/LIBAXL_REQUEST_CHANGE_GC_TILE.3\
	man3/LIBAXL_REQUEST_CHANGE_GC_STIPPLE.3\
	man3/LIBAXL_REQUEST_CHANGE_GC_TILE_STIPPLE_X_ORIGIN.3\
	man3/LIBAXL_REQUEST_CHANGE_GC_TILE_STIPPLE_Y_ORIGIN.3\
	man3/LIBAXL_REQUEST_CHANGE_GC_FONT.3\
	man3/LIBAXL_REQUEST_CHANGE_GC_SUBWINDOW_MODE.3\
	man3/LIBAXL_REQUEST_CHANGE_GC_GRAPHICS_EXPOSURES.3\
	man3/LIBAXL_REQUEST_CHANGE_GC_CLIP_X_ORIGIN.3\
	man3/LIBAXL_REQUEST_CHANGE_GC_CLIP_Y_ORIGIN.3\
	man3/LIBAXL_REQUEST_CHANGE_GC_CLIP_MASK.3\
	man3/LIBAXL_REQUEST_CHANGE_GC_DASH_OFFSET.3\
	man3/LIBAXL_REQUEST_CHANGE_GC_DASHES.3\
	man3/LIBAXL_REQUEST_CHANGE_GC_ARC_MODE.3\
	man3/LIBAXL_REQUEST_CHANGE_HOSTS.3\
	man3/LIBAXL_REQUEST_CHANGE_KEYBOARD_CONTROL.3\
	man3/LIBAXL_REQUEST_CHANGE_KEYBOARD_CONTROL_KEY_CLICK_PERCENT.3\
	man3/LIBAXL_REQUEST_CHANGE_KEYBOARD_CONTROL_BELL_PERCENT.3\
	man3/LIBAXL_REQUEST_CHANGE_KEYBOARD_CONTROL_BELL_PITCH.3\
	man3/LIBAXL_REQUEST_CHANGE_KEYBOARD_CONTROL_BELL_DURATION.3\
	man3/LIBAXL_REQUEST_CHANGE_KEYBOARD_CONTROL_LED.3\
	man3/LIBAXL_REQUEST_CHANGE_KEYBOARD_CONTROL_LED_MODE.3\
	man3/LIBAXL_REQUEST_CHANGE_KEYBOARD_CONTROL_KEY.3\
	man3/LIBAXL_REQUEST_CHANGE_KEYBOARD_CONTROL_AUTO_REPEAT_MODE.3\
	man3/LIBAXL_REQUEST_CHANGE_KEYBOARD_MAPPING.3\
	man3/LIBAXL_REQUEST_CHANGE_POINTER_CONTROL.3\
	man3/LIBAXL_REQUEST_CHANGE_PROPERTY.3\
	man3/LIBAXL_REQUEST_CHANGE_SAVE_SET.3\
	man3/LIBAXL_REQUEST_CHANGE_WINDOW_ATTRIBUTES.3\
	man3/LIBAXL_REQUEST_CHANGE_WINDOW_ATTRIBUTES_BACKGROUND_PIXMAP.3\
	man3/LIBAXL_REQUEST_CHANGE_WINDOW_ATTRIBUTES_BACKGROUND_PIXEL.3\
	man3/LIBAXL_REQUEST_CHANGE_WINDOW_ATTRIBUTES_BORDER_PIXMAP.3\
	man3/LIBAXL_REQUEST_CHANGE_WINDOW_ATTRIBUTES_BORDER_PIXEL.3\
	man3/LIBAXL_REQUEST_CHANGE_WINDOW_ATTRIBUTES_BIT_GRAVITY.3\
	man3/LIBAXL_REQUEST_CHANGE_WINDOW_ATTRIBUTES_WIN_GRAVITY.3\
	man3/LIBAXL_REQUEST_CHANGE_WINDOW_ATTRIBUTES_BACKING_STORE.3\
	man3/LIBAXL_REQUEST_CHANGE_WINDOW_ATTRIBUTES_BACKING_PLANES.3\
	man3/LIBAXL_REQUEST_CHANGE_WINDOW_ATTRIBUTES_BACKING_PIXEL.3\
	man3/LIBAXL_REQUEST_CHANGE_WINDOW_ATTRIBUTES_OVERRIDE_REDIRECT.3\
	man3/LIBAXL_REQUEST_CHANGE_WINDOW_ATTRIBUTES_SAVE_UNDER.3\
	man3/LIBAXL_REQUEST_CHANGE_WINDOW_ATTRIBUTES_EVENT_MASK.3\
	man3/LIBAXL_REQUEST_CHANGE_WINDOW_ATTRIBUTES_DO_NOT_PROPAGATE_MASK.3\
	man3/LIBAXL_REQUEST_CHANGE_WINDOW_ATTRIBUTES_COLORMAP.3\
	man3/LIBAXL_REQUEST_CHANGE_WINDOW_ATTRIBUTES_CURSOR.3\
	man3/LIBAXL_REQUEST_CIRCULATE_WINDOW.3\
	man3/LIBAXL_REQUEST_CLEAR_AREA.3\
	man3/LIBAXL_REQUEST_CLOSE_FONT.3\
	man3/LIBAXL_REQUEST_CONFIGURE_WINDOW.3\
	man3/LIBAXL_REQUEST_CONFIGURE_WINDOW_X.3\
	man3/LIBAXL_REQUEST_CONFIGURE_WINDOW_Y.3\
	man3/LIBAXL_REQUEST_CONFIGURE_WINDOW_WIDTH.3\
	man3/LIBAXL_REQUEST_CONFIGURE_WINDOW_HEIGHT.3\
	man3/LIBAXL_REQUEST_CONFIGURE_WINDOW_BORDER_WIDTH.3\
	man3/LIBAXL_REQUEST_CONFIGURE_WINDOW_SIBLING.3\
	man3/LIBAXL_REQUEST_CONFIGURE_WINDOW_STACK_MODE.3\
	man3/LIBAXL_REQUEST_CONVERT_SELECTION.3\
	man3/LIBAXL_REQUEST_COPY_AREA.3\
	man3/LIBAXL_REQUEST_COPY_COLORMAP_AND_FREE.3\
	man3/LIBAXL_REQUEST_COPY_GC.3\
	man3/LIBAXL_REQUEST_COPY_GC_FUNCTION.3\
	man3/LIBAXL_REQUEST_COPY_GC_PLANE_MASK.3\
	man3/LIBAXL_REQUEST_COPY_GC_FOREGROUND.3\
	man3/LIBAXL_REQUEST_COPY_GC_BACKGROUND.3\
	man3/LIBAXL_REQUEST_COPY_GC_LINE_WIDTH.3\
	man3/LIBAXL_REQUEST_COPY_GC_LINE_STYLE.3\
	man3/LIBAXL_REQUEST_COPY_GC_CAP_STYLE.3\
	man3/LIBAXL_REQUEST_COPY_GC_JOIN_STYLE.3\
	man3/LIBAXL_REQUEST_COPY_GC_FILL_STYLE.3\
	man3/LIBAXL_REQUEST_COPY_GC_FILL_RULE.3\
	man3/LIBAXL_REQUEST_COPY_GC_TILE.3\
	man3/LIBAXL_REQUEST_COPY_GC_STIPPLE.3\
	man3/LIBAXL_REQUEST_COPY_GC_TILE_STIPPLE_X_ORIGIN.3\
	man3/LIBAXL_REQUEST_COPY_GC_TILE_STIPPLE_Y_ORIGIN.3\
	man3/LIBAXL_REQUEST_COPY_GC_FONT.3\
	man3/LIBAXL_REQUEST_COPY_GC_SUBWINDOW_MODE.3\
	man3/LIBAXL_REQUEST_COPY_GC_GRAPHICS_EXPOSURES.3\
	man3/LIBAXL_REQUEST_COPY_GC_CLIP_X_ORIGIN.3\
	man3/LIBAXL_REQUEST_COPY_GC_CLIP_Y_ORIGIN.3\
	man3/LIBAXL_REQUEST_COPY_GC_CLIP_MASK.3\
	man3/LIBAXL_REQUEST_COPY_GC_DASH_OFFSET.3\
	man3/LIBAXL_REQUEST_COPY_GC_DASHES.3\
	man3/LIBAXL_REQUEST_COPY_GC_ARC_MODE.3\
	man3/LIBAXL_REQUEST_COPY_PLANE.3\
	man3/LIBAXL_REQUEST_CREATE_COLORMAP.3\
	man3/LIBAXL_REQUEST_CREATE_CURSOR.3\
	man3/LIBAXL_REQUEST_CREATE_GC.3\
	man3/LIBAXL_REQUEST_CREATE_GC_FUNCTION.3\
	man3/LIBAXL_REQUEST_CREATE_GC_PLANE_MASK.3\
	man3/LIBAXL_REQUEST_CREATE_GC_FOREGROUND.3\
	man3/LIBAXL_REQUEST_CREATE_GC_BACKGROUND.3\
	man3/LIBAXL_REQUEST_CREATE_GC_LINE_WIDTH.3\
	man3/LIBAXL_REQUEST_CREATE_GC_LINE_STYLE.3\
	man3/LIBAXL_REQUEST_CREATE_GC_CAP_STYLE.3\
	man3/LIBAXL_REQUEST_CREATE_GC_JOIN_STYLE.3\
	man3/LIBAXL_REQUEST_CREATE_GC_FILL_STYLE.3\
	man3/LIBAXL_REQUEST_CREATE_GC_FILL_RULE.3\
	man3/LIBAXL_REQUEST_CREATE_GC_TILE.3\
	man3/LIBAXL_REQUEST_CREATE_GC_STIPPLE.3\
	man3/LIBAXL_REQUEST_CREATE_GC_TILE_STIPPLE_X_ORIGIN.3\
	man3/LIBAXL_REQUEST_CREATE_GC_TILE_STIPPLE_Y_ORIGIN.3\
	man3/LIBAXL_REQUEST_CREATE_GC_FONT.3\
	man3/LIBAXL_REQUEST_CREATE_GC_SUBWINDOW_MODE.3\
	man3/LIBAXL_REQUEST_CREATE_GC_GRAPHICS_EXPOSURES.3\
	man3/LIBAXL_REQUEST_CREATE_GC_CLIP_X_ORIGIN.3\
	man3/LIBAXL_REQUEST_CREATE_GC_CLIP_Y_ORIGIN.3\
	man3/LIBAXL_REQUEST_CREATE_GC_CLIP_MASK.3\
	man3/LIBAXL_REQUEST_CREATE_GC_DASH_OFFSET.3\
	man3/LIBAXL_REQUEST_CREATE_GC_DASHES.3\
	man3/LIBAXL_REQUEST_CREATE_GC_ARC_MODE.3\
	man3/LIBAXL_REQUEST_CREATE_GLYPH_CURSOR.3\
	man3/LIBAXL_REQUEST_CREATE_PIXMAP.3\
	man3/LIBAXL_REQUEST_CREATE_WINDOW.3\
	man3/LIBAXL_REQUEST_CREATE_WINDOW_BACKGROUND_PIXMAP.3\
	man3/LIBAXL_REQUEST_CREATE_WINDOW_BACKGROUND_PIXEL.3\
	man3/LIBAXL_REQUEST_CREATE_WINDOW_BORDER_PIXMAP.3\
	man3/LIBAXL_REQUEST_CREATE_WINDOW_BORDER_PIXEL.3\
	man3/LIBAXL_REQUEST_CREATE_WINDOW_BIT_GRAVITY.3\
	man3/LIBAXL_REQUEST_CREATE_WINDOW_WIN_GRAVITY.3\
	man3/LIBAXL_REQUEST_CREATE_WINDOW_BACKING_STORE.3\
	man3/LIBAXL_REQUEST_CREATE_WINDOW_BACKING_PLANES.3\
	man3/LIBAXL_REQUEST_CREATE_WINDOW_BACKING_PIXEL.3\
	man3/LIBAXL_REQUEST_CREATE_WINDOW_OVERRIDE_REDIRECT.3\
	man3/LIBAXL_REQUEST_CREATE_WINDOW_SAVE_UNDER.3\
	man3/LIBAXL_REQUEST_CREATE_WINDOW_EVENT_MASK.3\
	man3/LIBAXL_REQUEST_CREATE_WINDOW_DO_NOT_PROPAGATE_MASK.3\
	man3/LIBAXL_REQUEST_CREATE_WINDOW_COLORMAP.3\
	man3/LIBAXL_REQUEST_CREATE_WINDOW_CURSOR.3\
	man3/LIBAXL_REQUEST_DELETE_PROPERTY.3\
	man3/LIBAXL_REQUEST_DESTROY_SUBWINDOWS.3\
	man3/LIBAXL_REQUEST_DESTROY_WINDOW.3\
	man3/LIBAXL_REQUEST_FILL_POLY.3\
	man3/LIBAXL_REQUEST_FORCE_SCREEN_SAVER.3\
	man3/LIBAXL_REQUEST_FREE_COLORMAP.3\
	man3/LIBAXL_REQUEST_FREE_COLORS.3\
	man3/LIBAXL_REQUEST_FREE_CURSOR.3\
	man3/LIBAXL_REQUEST_FREE_GC.3\
	man3/LIBAXL_REQUEST_FREE_PIXMAP.3\
	man3/LIBAXL_REQUEST_GET_ATOM_NAME.3\
	man3/LIBAXL_REQUEST_GET_FONT_PATH.3\
	man3/LIBAXL_REQUEST_GET_GEOMETRY.3\
	man3/LIBAXL_REQUEST_GET_IMAGE.3\
	man3/LIBAXL_REQUEST_GET_INPUT_FOCUS.3\
	man3/LIBAXL_REQUEST_GET_KEYBOARD_CONTROL.3\
	man3/LIBAXL_REQUEST_GET_KEYBOARD_MAPPING.3\
	man3/LIBAXL_REQUEST_GET_MODIFIER_MAPPING.3\
	man3/LIBAXL_REQUEST_GET_MOTION_EVENTS.3\
	man3/LIBAXL_REQUEST_GET_POINTER_CONTROL.3\
	man3/LIBAXL_REQUEST_GET_POINTER_MAPPING.3\
	man3/LIBAXL_REQUEST_GET_PROPERTY.3\
	man3/LIBAXL_REQUEST_GET_SCREEN_SAVER.3\
	man3/LIBAXL_REQUEST_GET_SELECTION_OWNER.3\
	man3/LIBAXL_REQUEST_GET_WINDOW_ATTRIBUTES.3\
	man3/LIBAXL_REQUEST_GRAB_BUTTON.3\
	man3/LIBAXL_REQUEST_GRAB_KEY.3\
	man3/LIBAXL_REQUEST_GRAB_KEYBOARD.3\
	man3/LIBAXL_REQUEST_GRAB_POINTER.3\
	man3/LIBAXL_REQUEST_GRAB_SERVER.3\
	man3/LIBAXL_REQUEST_IMAGE_TEXT16.3\
	man3/LIBAXL_REQUEST_IMAGE_TEXT8.3\
	man3/LIBAXL_REQUEST_INSTALL_COLORMAP.3\
	man3/LIBAXL_REQUEST_INTERN_ATOM.3\
	man3/LIBAXL_REQUEST_KILL_CLIENT.3\
	man3/LIBAXL_REQUEST_LIST_EXTENSIONS.3\
	man3/LIBAXL_REQUEST_LIST_FONTS.3\
	man3/LIBAXL_REQUEST_LIST_FONTS_WITH_INFO.3\
	man3/LIBAXL_REQUEST_LIST_HOSTS.3\
	man3/LIBAXL_REQUEST_LIST_INSTALLED_COLORMAPS.3\
	man3/LIBAXL_REQUEST_LIST_PROPERTIES.3\
	man3/LIBAXL_REQUEST_LOOKUP_COLOR.3\
	man3/LIBAXL_REQUEST_MAP_SUBWINDOWS.3\
	man3/LIBAXL_REQUEST_MAP_WINDOW.3\
	man3/LIBAXL_REQUEST_NO_OPERATION.3\
	man3/LIBAXL_REQUEST_OPEN_FONT.3\
	man3/LIBAXL_REQUEST_POLY_ARC.3\
	man3/LIBAXL_REQUEST_POLY_FILL_ARC.3\
	man3/LIBAXL_REQUEST_POLY_FILL_RECTANGLE.3\
	man3/LIBAXL_REQUEST_POLY_LINE.3\
	man3/LIBAXL_REQUEST_POLY_POINT.3\
	man3/LIBAXL_REQUEST_POLY_RECTANGLE.3\
	man3/LIBAXL_REQUEST_POLY_SEGMENT.3\
	man3/LIBAXL_REQUEST_POLY_TEXT16.3\
	man3/LIBAXL_REQUEST_POLY_TEXT8.3\
	man3/LIBAXL_REQUEST_PUT_IMAGE.3\
	man3/LIBAXL_REQUEST_QUERY_BEST_SIZE.3\
	man3/LIBAXL_REQUEST_QUERY_COLORS.3\
	man3/LIBAXL_REQUEST_QUERY_EXTENSION.3\
	man3/LIBAXL_REQUEST_QUERY_FONT.3\
	man3/LIBAXL_REQUEST_QUERY_KEYMAP.3\
	man3/LIBAXL_REQUEST_QUERY_POINTER.3\
	man3/LIBAXL_REQUEST_QUERY_TEXT_EXTENTS.3\
	man3/LIBAXL_REQUEST_QUERY_TREE.3\
	man3/LIBAXL_REQUEST_RECOLOR_CURSOR.3\
	man3/LIBAXL_REQUEST_REPARENT_WINDOW.3\
	man3/LIBAXL_REQUEST_ROTATE_PROPERTIES.3\
	man3/LIBAXL_REQUEST_SEND_EVENT.3\
	man3/LIBAXL_REQUEST_SET_ACCESS_CONTROL.3\
	man3/LIBAXL_REQUEST_SET_CLIP_RECTANGLES.3\
	man3/LIBAXL_REQUEST_SET_CLOSE_DOWN_MODE.3\
	man3/LIBAXL_REQUEST_SET_DASHES.3\
	man3/LIBAXL_REQUEST_SET_FONT_PATH.3\
	man3/LIBAXL_REQUEST_SET_INPUT_FOCUS.3\
	man3/LIBAXL_REQUEST_SET_MODIFIER_MAPPING.3\
	man3/LIBAXL_REQUEST_SET_POINTER_MAPPING.3\
	man3/LIBAXL_REQUEST_SET_SCREEN_SAVER.3\
	man3/LIBAXL_REQUEST_SET_SELECTION_OWNER.3\
	man3/LIBAXL_REQUEST_STORE_COLORS.3\
	man3/LIBAXL_REQUEST_STORE_NAMED_COLOR.3\
	man3/LIBAXL_REQUEST_TRANSLATE_COORDINATES.3\
	man3/LIBAXL_REQUEST_UNGRAB_BUTTON.3\
	man3/LIBAXL_REQUEST_UNGRAB_KEY.3\
	man3/LIBAXL_REQUEST_UNGRAB_KEYBOARD.3\
	man3/LIBAXL_REQUEST_UNGRAB_POINTER.3\
	man3/LIBAXL_REQUEST_UNGRAB_SERVER.3\
	man3/LIBAXL_REQUEST_UNINSTALL_COLORMAP.3\
	man3/LIBAXL_REQUEST_UNMAP_SUBWINDOWS.3\
	man3/LIBAXL_REQUEST_UNMAP_WINDOW.3\
	man3/LIBAXL_REQUEST_WARP_POINTER.3\
	man3/LIBAXL_SYNTHETIC_EVENT_BIT.3\
	man3/libaxl_attach.3\
	man3/libaxl_close.3\
	man3/libaxl_context_create.3\
	man3/libaxl_context_free.3\
	man3/libaxl_create.3\
	man3/libaxl_deallocate_id.3\
	man3/libaxl_detach.3\
	man3/libaxl_fileno.3\
	man3/libaxl_generate_id.3\
	man3/libaxl_get_decnet_object.3\
	man3/libaxl_get_tcp_port.3\
	man3/libaxl_parse_display.3\
	man3/libaxl_protocol_version.3\
	man3/libaxl_protocol_version_major.3\
	man3/libaxl_protocol_version_minor.3\
	man3/libaxl_receive_handshake.3\
	man3/libaxl_send_handshake.3\
	man3/struct_libaxl_connection.3\
	man3/struct_libaxl_context.3\
	man3/struct_libaxl_error_access.3\
	man3/struct_libaxl_error_alloc.3\
	man3/struct_libaxl_error_atom.3\
	man3/struct_libaxl_error_colormap.3\
	man3/struct_libaxl_error_cursor.3\
	man3/struct_libaxl_error_drawable.3\
	man3/struct_libaxl_error_font.3\
	man3/struct_libaxl_error_gcontext.3\
	man3/struct_libaxl_error_id_choice.3\
	man3/struct_libaxl_error_implementation.3\
	man3/struct_libaxl_error_length.3\
	man3/struct_libaxl_error_match.3\
	man3/struct_libaxl_error_name.3\
	man3/struct_libaxl_error_pixmap.3\
	man3/struct_libaxl_error_request.3\
	man3/struct_libaxl_error_value.3\
	man3/struct_libaxl_error_window.3\
	man3/struct_libaxl_reply_alloc_color.3\
	man3/struct_libaxl_reply_alloc_color_cells.3\
	man3/struct_libaxl_reply_alloc_color_planes.3\
	man3/struct_libaxl_reply_alloc_named_color.3\
	man3/struct_libaxl_reply_get_atom_name.3\
	man3/struct_libaxl_reply_get_font_path.3\
	man3/struct_libaxl_reply_get_geometry.3\
	man3/struct_libaxl_reply_get_image.3\
	man3/struct_libaxl_reply_get_input_focus.3\
	man3/struct_libaxl_reply_get_keyboard_control.3\
	man3/struct_libaxl_reply_get_keyboard_mapping.3\
	man3/struct_libaxl_reply_get_modifier_mapping.3\
	man3/struct_libaxl_reply_get_motion_events.3\
	man3/struct_libaxl_reply_get_pointer_control.3\
	man3/struct_libaxl_reply_get_pointer_mapping.3\
	man3/struct_libaxl_reply_get_property.3\
	man3/struct_libaxl_reply_get_screen_saver.3\
	man3/struct_libaxl_reply_get_selection_owner.3\
	man3/struct_libaxl_reply_get_window_attributes.3\
	man3/struct_libaxl_reply_grab_keyboard.3\
	man3/struct_libaxl_reply_grab_pointer.3\
	man3/struct_libaxl_reply_intern_atom.3\
	man3/struct_libaxl_reply_list_extensions.3\
	man3/struct_libaxl_reply_list_fonts.3\
	man3/struct_libaxl_reply_list_fonts_with_info.3\
	man3/struct_libaxl_reply_list_hosts.3\
	man3/struct_libaxl_reply_list_installed_colormaps.3\
	man3/struct_libaxl_reply_list_properties.3\
	man3/struct_libaxl_reply_lookup_color.3\
	man3/struct_libaxl_reply_query_best_size.3\
	man3/struct_libaxl_reply_query_colors.3\
	man3/struct_libaxl_reply_query_extension.3\
	man3/struct_libaxl_reply_query_font.3\
	man3/struct_libaxl_reply_query_keymap.3\
	man3/struct_libaxl_reply_query_pointer.3\
	man3/struct_libaxl_reply_query_text_extents.3\
	man3/struct_libaxl_reply_query_tree.3\
	man3/struct_libaxl_reply_set_modifier_mapping.3\
	man3/struct_libaxl_reply_set_pointer_mapping.3\
	man3/struct_libaxl_reply_translate_coordinates.3\
	man3/struct_libaxl_request_alloc_color.3\
	man3/struct_libaxl_request_alloc_color_cells.3\
	man3/struct_libaxl_request_alloc_color_planes.3\
	man3/struct_libaxl_request_alloc_named_color.3\
	man3/struct_libaxl_request_allow_events.3\
	man3/struct_libaxl_request_bell.3\
	man3/struct_libaxl_request_change_active_pointer_grab.3\
	man3/struct_libaxl_request_change_gc.3\
	man3/struct_libaxl_request_change_hosts.3\
	man3/struct_libaxl_request_change_keyboard_control.3\
	man3/struct_libaxl_request_change_keyboard_mapping.3\
	man3/struct_libaxl_request_change_pointer_control.3\
	man3/struct_libaxl_request_change_property.3\
	man3/struct_libaxl_request_change_save_set.3\
	man3/struct_libaxl_request_change_window_attributes.3\
	man3/struct_libaxl_request_circulate_window.3\
	man3/struct_libaxl_request_clear_area.3\
	man3/struct_libaxl_request_close_font.3\
	man3/struct_libaxl_request_configure_window.3\
	man3/struct_libaxl_request_convert_selection.3\
	man3/struct_libaxl_request_copy_area.3\
	man3/struct_libaxl_request_copy_colormap_and_free.3\
	man3/struct_libaxl_request_copy_gc.3\
	man3/struct_libaxl_request_copy_plane.3\
	man3/struct_libaxl_request_create_colormap.3\
	man3/struct_libaxl_request_create_cursor.3\
	man3/struct_libaxl_request_create_gc.3\
	man3/struct_libaxl_request_create_glyph_cursor.3\
	man3/struct_libaxl_request_create_pixmap.3\
	man3/struct_libaxl_request_create_window.3\
	man3/struct_libaxl_request_delete_property.3\
	man3/struct_libaxl_request_destroy_subwindows.3\
	man3/struct_libaxl_request_destroy_window.3\
	man3/struct_libaxl_request_fill_poly.3\
	man3/struct_libaxl_request_force_screen_saver.3\
	man3/struct_libaxl_request_free_colormap.3\
	man3/struct_libaxl_request_free_colors.3\
	man3/struct_libaxl_request_free_cursor.3\
	man3/struct_libaxl_request_free_gc.3\
	man3/struct_libaxl_request_free_pixmap.3\
	man3/struct_libaxl_request_get_atom_name.3\
	man3/struct_libaxl_request_get_font_path.3\
	man3/struct_libaxl_request_get_geometry.3\
	man3/struct_libaxl_request_get_image.3\
	man3/struct_libaxl_request_get_input_focus.3\
	man3/struct_libaxl_request_get_keyboard_control.3\
	man3/struct_libaxl_request_get_keyboard_mapping.3\
	man3/struct_libaxl_request_get_modifier_mapping.3\
	man3/struct_libaxl_request_get_motion_events.3\
	man3/struct_libaxl_request_get_pointer_control.3\
	man3/struct_libaxl_request_get_pointer_mapping.3\
	man3/struct_libaxl_request_get_property.3\
	man3/struct_libaxl_request_get_screen_saver.3\
	man3/struct_libaxl_request_get_selection_owner.3\
	man3/struct_libaxl_request_get_window_attributes.3\
	man3/struct_libaxl_request_grab_button.3\
	man3/struct_libaxl_request_grab_key.3\
	man3/struct_libaxl_request_grab_keyboard.3\
	man3/struct_libaxl_request_grab_pointer.3\
	man3/struct_libaxl_request_grab_server.3\
	man3/struct_libaxl_request_image_text16.3\
	man3/struct_libaxl_request_image_text8.3\
	man3/struct_libaxl_request_install_colormap.3\
	man3/struct_libaxl_request_intern_atom.3\
	man3/struct_libaxl_request_kill_client.3\
	man3/struct_libaxl_request_list_extensions.3\
	man3/struct_libaxl_request_list_fonts.3\
	man3/struct_libaxl_request_list_fonts_with_info.3\
	man3/struct_libaxl_request_list_hosts.3\
	man3/struct_libaxl_request_list_installed_colormaps.3\
	man3/struct_libaxl_request_list_properties.3\
	man3/struct_libaxl_request_lookup_color.3\
	man3/struct_libaxl_request_map_subwindows.3\
	man3/struct_libaxl_request_map_window.3\
	man3/struct_libaxl_request_no_operation.3\
	man3/struct_libaxl_request_open_font.3\
	man3/struct_libaxl_request_poly_arc.3\
	man3/struct_libaxl_request_poly_fill_arc.3\
	man3/struct_libaxl_request_poly_fill_rectangle.3\
	man3/struct_libaxl_request_poly_line.3\
	man3/struct_libaxl_request_poly_point.3\
	man3/struct_libaxl_request_poly_rectangle.3\
	man3/struct_libaxl_request_poly_segment.3\
	man3/struct_libaxl_request_poly_text16.3\
	man3/struct_libaxl_request_poly_text8.3\
	man3/struct_libaxl_request_put_image.3\
	man3/struct_libaxl_request_query_best_size.3\
	man3/struct_libaxl_request_query_colors.3\
	man3/struct_libaxl_request_query_extension.3\
	man3/struct_libaxl_request_query_font.3\
	man3/struct_libaxl_request_query_keymap.3\
	man3/struct_libaxl_request_query_pointer.3\
	man3/struct_libaxl_request_query_text_extents.3\
	man3/struct_libaxl_request_query_tree.3\
	man3/struct_libaxl_request_recolor_cursor.3\
	man3/struct_libaxl_request_reparent_window.3\
	man3/struct_libaxl_request_rotate_properties.3\
	man3/struct_libaxl_request_send_event.3\
	man3/struct_libaxl_request_set_access_control.3\
	man3/struct_libaxl_request_set_clip_rectangles.3\
	man3/struct_libaxl_request_set_close_down_mode.3\
	man3/struct_libaxl_request_set_dashes.3\
	man3/struct_libaxl_request_set_font_path.3\
	man3/struct_libaxl_request_set_input_focus.3\
	man3/struct_libaxl_request_set_modifier_mapping.3\
	man3/struct_libaxl_request_set_pointer_mapping.3\
	man3/struct_libaxl_request_set_screen_saver.3\
	man3/struct_libaxl_request_set_selection_owner.3\
	man3/struct_libaxl_request_store_colors.3\
	man3/struct_libaxl_request_store_named_color.3\
	man3/struct_libaxl_request_translate_coordinates.3\
	man3/struct_libaxl_request_ungrab_button.3\
	man3/struct_libaxl_request_ungrab_key.3\
	man3/struct_libaxl_request_ungrab_keyboard.3\
	man3/struct_libaxl_request_ungrab_pointer.3\
	man3/struct_libaxl_request_ungrab_server.3\
	man3/struct_libaxl_request_uninstall_colormap.3\
	man3/struct_libaxl_request_unmap_subwindows.3\
	man3/struct_libaxl_request_unmap_window.3\
	man3/struct_libaxl_request_warp_pointer.3\
	man3/union_libaxl_error.3\
	man3/union_libaxl_input.3

LOBJ = $(OBJ:.o=.lo)

all: libaxl.a libaxl.$(LIBEXT) $(LIB_SUBHDR_GEN)
$(OBJ): $(@:.o=.c) $(HDR)
$(LOBJ): $(@:.lo=.c) $(HDR)

.c.o:
	$(CC) -c -o $@ $< $(CFLAGS) $(CPPFLAGS)

.c.lo:
	$(CC) -fPIC -c -o $@ $< $(CFLAGS) $(CPPFLAGS)

libaxl/errors-structs.h: libaxl/errors.h
	sed -n 's/^struct libaxl_error_\([^ \t]*\).*$$/\tstruct libaxl_error_\1 \1;/p' < libaxl/errors.h > $@

libaxl/events-structs.h: libaxl/events.h
	sed -n 's/^struct libaxl_event_\([^ \t]*\).*$$/\tstruct libaxl_event_\1 \1;/p' < libaxl/events.h > $@

libaxl/replies-structs.h: libaxl/replies.h
	sed -n 's/^struct libaxl_reply_\([^ \t]*\).*$$/\tstruct libaxl_reply_\1 \1;/p' < libaxl/replies.h > $@

libaxl/requests-ptr-structs.h: libaxl/requests.h
	sed -n 's/^struct libaxl_request_\([^ \t]*\).*$$/\tconst struct libaxl_request_\1 \*\1;/p' < libaxl/requests.h > $@

libaxl/requests-structs.h: libaxl/requests.h
	sed -n 's/^struct libaxl_request_\([^ \t]*\).*$$/\tstruct libaxl_request_\1 \1;/p' < libaxl/requests.h > $@

libaxl.a: $(OBJ)
	@rm -f -- $@
	$(AR) rc $@ $(OBJ)
	$(AR) ts $@ > /dev/null

libaxl.$(LIBEXT): $(LOBJ)
	$(CC) $(LIBFLAGS) -o $@ $(LOBJ) $(LDFLAGS)

install: libaxl.a libaxl.$(LIBEXT)
	mkdir -p -- "$(DESTDIR)$(PREFIX)/include/libaxl"
	mkdir -p -- "$(DESTDIR)$(PREFIX)/lib"
#	mkdir -p -- "$(DESTDIR)$(MANPREFIX)/man0"
#	mkdir -p -- "$(DESTDIR)$(MANPREFIX)/man3"
#	mkdir -p -- "$(DESTDIR)$(MANPREFIX)/man7"
	cp -- libaxl.h "$(DESTDIR)$(PREFIX)/include"
	cp -- $(LIB_SUBHDR) "$(DESTDIR)$(PREFIX)/include/libaxl"
	cp -- libaxl.a "$(DESTDIR)$(PREFIX)/lib"
	cp -- libaxl.$(LIBEXT) "$(DESTDIR)$(PREFIX)/lib/libaxl.$(LIBMINOREXT)"
	$(FIX_INSTALL_NAME) "$(DESTDIR)$(PREFIX)/lib/libaxl.$(LIBMINOREXT)"
	ln -sf -- libaxl.$(LIBMINOREXT) "$(DESTDIR)$(PREFIX)/lib/libaxl.$(LIBMAJOREXT)"
	ln -sf -- libaxl.$(LIBMINOREXT) "$(DESTDIR)$(PREFIX)/lib/libaxl.$(LIBEXT)"
#	cp -P -- $(MAN0) "$(DESTDIR)$(MANPREFIX)/man0"
#	cp -P -- $(MAN3) "$(DESTDIR)$(MANPREFIX)/man3"
#	cp -P -- $(MAN7) "$(DESTDIR)$(MANPREFIX)/man7"

uninstall:
	-cd -- "$(DESTDIR)$(PREFIX)/include/" && rm -f -- $(LIB_HDR)
	-rmdir -- "$(DESTDIR)$(PREFIX)/include/libaxl"
	-rm -f -- "$(DESTDIR)$(PREFIX)/lib/libaxl.a"
	-rm -f -- "$(DESTDIR)$(PREFIX)/lib/libaxl.$(LIBMINOREXT)"
	-rm -f -- "$(DESTDIR)$(PREFIX)/lib/libaxl.$(LIBMAJOREXT)"
	-rm -f -- "$(DESTDIR)$(PREFIX)/lib/libaxl.$(LIBEXT)"
#	-cd -- "$(DESTDIR)$(MANPREFIX)/" && rm -f -- $(MAN0)
#	-cd -- "$(DESTDIR)$(MANPREFIX)/" && rm -f -- $(MAN3)
#	-cd -- "$(DESTDIR)$(MANPREFIX)/" && rm -f -- $(MAN7)

clean:
	-rm -f -- *.o *.lo *.a *.su *.$(LIBEXT) libaxl/*-structs.h

.SUFFIXES:
.SUFFIXES: .lo .o .c

.PHONY: all install uninstall clean
