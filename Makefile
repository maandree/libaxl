.POSIX:

LIB_MAJOR = 0
LIB_MINOR = 1
LIB_VERSION = $(LIB_MAJOR).$(LIB_MINOR)

CONFIGFILE = config.mk
OSCONFIGFILE = linux.mk

include $(CONFIGFILE)
include $(OSCONFIGFILE)

OBJ =\
	libaxl_context_create.o\
	libaxl_context_free.o\
	libaxl_fileno.o\
	libaxl_flush.o\
	libaxl_generate_id.o\
	libaxl_get_decnet_object.o\
	libaxl_get_tcp_port.o\
	libaxl_info.o\
	libaxl_next_depth.o\
	libaxl_next_screen.o\
	libaxl_parse_display.o\
	libaxl_protocol_version_major.o\
	libaxl_protocol_version_minor.o\
	libaxl_protocol_version.o\
	libaxl_receive.o\
	libaxl_receive_handshake.o\
	libaxl_send_handshake.o\
	libaxl_send_request.o

LIB_HDR =\
	libaxl.h\
	libaxl-atoms.h\
	libaxl-consts.h\
	libaxl-errors.h\
	libaxl-errors-structs.h\
	libaxl-events.h\
	libaxl-events-structs.h\
	libaxl-replies.h\
	libaxl-replies-structs.h\
	libaxl-requests.h\
	libaxl-requests-ptr-structs.h\
	libaxl-requests-structs.h\
	libaxl-types.h\
	libaxl-display-info.h

HDR =\
	common.h\
	internal-linux.h\
	internal-llmutex.h\
	$(LIB_HDR)

MAN3 =\
	LIBAXL_ATOM_ARC.3\
	LIBAXL_ATOM_ATOM.3\
	LIBAXL_ATOM_BITMAP.3\
	LIBAXL_ATOM_CAP_HEIGHT.3\
	LIBAXL_ATOM_CARDINAL.3\
	LIBAXL_ATOM_COLORMAP.3\
	LIBAXL_ATOM_COPYRIGHT.3\
	LIBAXL_ATOM_CURSOR.3\
	LIBAXL_ATOM_CUT_BUFFER0.3\
	LIBAXL_ATOM_CUT_BUFFER1.3\
	LIBAXL_ATOM_CUT_BUFFER2.3\
	LIBAXL_ATOM_CUT_BUFFER3.3\
	LIBAXL_ATOM_CUT_BUFFER4.3\
	LIBAXL_ATOM_CUT_BUFFER5.3\
	LIBAXL_ATOM_CUT_BUFFER6.3\
	LIBAXL_ATOM_CUT_BUFFER7.3\
	LIBAXL_ATOM_DRAWABLE.3\
	LIBAXL_ATOM_END_SPACE.3\
	LIBAXL_ATOM_FAMILY_NAME.3\
	LIBAXL_ATOM_FONT.3\
	LIBAXL_ATOM_FONT_NAME.3\
	LIBAXL_ATOM_FULL_NAME.3\
	LIBAXL_ATOM_INTEGER.3\
	LIBAXL_ATOM_ITALIC_ANGLE.3\
	LIBAXL_ATOM_MAX_SPACE.3\
	LIBAXL_ATOM_MIN_SPACE.3\
	LIBAXL_ATOM_NORM_SPACE.3\
	LIBAXL_ATOM_NOTICE.3\
	LIBAXL_ATOM_PIXMAP.3\
	LIBAXL_ATOM_POINT.3\
	LIBAXL_ATOM_POINT_SIZE.3\
	LIBAXL_ATOM_PRIMARY.3\
	LIBAXL_ATOM_QUAD_WIDTH.3\
	LIBAXL_ATOM_RECTANGLE.3\
	LIBAXL_ATOM_RESOLUTION.3\
	LIBAXL_ATOM_RESOURCE_MANAGER.3\
	LIBAXL_ATOM_RGB_BEST_MAP.3\
	LIBAXL_ATOM_RGB_BLUE_MAP.3\
	LIBAXL_ATOM_RGB_COLOR_MAP.3\
	LIBAXL_ATOM_RGB_DEFAULT_MAP.3\
	LIBAXL_ATOM_RGB_GRAY_MAP.3\
	LIBAXL_ATOM_RGB_GREEN_MAP.3\
	LIBAXL_ATOM_RGB_RED_MAP.3\
	LIBAXL_ATOM_SECONDARY.3\
	LIBAXL_ATOM_STRIKEOUT_ASCENT.3\
	LIBAXL_ATOM_STRIKEOUT_DESCENT.3\
	LIBAXL_ATOM_STRING.3\
	LIBAXL_ATOM_SUBSCRIPT_X.3\
	LIBAXL_ATOM_SUBSCRIPT_Y.3\
	LIBAXL_ATOM_SUPERSCRIPT_X.3\
	LIBAXL_ATOM_SUPERSCRIPT_Y.3\
	LIBAXL_ATOM_UNDERLINE_POSITION.3\
	LIBAXL_ATOM_UNDERLINE_THICKNESS.3\
	LIBAXL_ATOM_VISUALID.3\
	LIBAXL_ATOM_WEIGHT.3\
	LIBAXL_ATOM_WINDOW.3\
	LIBAXL_ATOM_WM_CLASS.3\
	LIBAXL_ATOM_WM_CLIENT_MACHINE.3\
	LIBAXL_ATOM_WM_COMMAND.3\
	LIBAXL_ATOM_WM_HINTS.3\
	LIBAXL_ATOM_WM_ICON_NAME.3\
	LIBAXL_ATOM_WM_ICON_SIZE.3\
	LIBAXL_ATOM_WM_NAME.3\
	LIBAXL_ATOM_WM_NORMAL_HINTS.3\
	LIBAXL_ATOM_WM_SIZE_HINTS.3\
	LIBAXL_ATOM_WM_TRANSIENT_FOR.3\
	LIBAXL_ATOM_WM_ZOOM_HINTS.3\
	LIBAXL_ATOM_X_HEIGHT.3\
	LIBAXL_ERROR.3\
	LIBAXL_ERROR_REQUEST.3\
	LIBAXL_ERROR_VALUE.3\
	LIBAXL_ERROR_WINDOW.3\
	LIBAXL_ERROR_PIXMAP.3\
	LIBAXL_ERROR_ATOM.3\
	LIBAXL_ERROR_CURSOR.3\
	LIBAXL_ERROR_FONT.3\
	LIBAXL_ERROR_MATCH.3\
	LIBAXL_ERROR_DRAWABLE.3\
	LIBAXL_ERROR_ACCESS.3\
	LIBAXL_ERROR_ALLOC.3\
	LIBAXL_ERROR_COLORMAP.3\
	LIBAXL_ERROR_GCONTEXT.3\
	LIBAXL_ERROR_ID_CHOICE.3\
	LIBAXL_ERROR_NAME.3\
	LIBAXL_ERROR_LENGTH.3\
	LIBAXL_ERROR_IMPLEMENTATION.3\
	struct_libaxl_error_request.3\
	struct_libaxl_error_value.3\
	struct_libaxl_error_window.3\
	struct_libaxl_error_pixmap.3\
	struct_libaxl_error_atom.3\
	struct_libaxl_error_cursor.3\
	struct_libaxl_error_font.3\
	struct_libaxl_error_match.3\
	struct_libaxl_error_drawable.3\
	struct_libaxl_error_access.3\
	struct_libaxl_error_alloc.3\
	struct_libaxl_error_colormap.3\
	struct_libaxl_error_gcontext.3\
	struct_libaxl_error_id_choice.3\
	struct_libaxl_error_name.3\
	struct_libaxl_error_length.3\
	struct_libaxl_error_implementation.3\
	union_libaxl_error.3\
	LIBAXL_REQUEST_CREATE_WINDOW.3\
	LIBAXL_REQUEST_CHANGE_WINDOW_ATTRIBUTES.3\
	LIBAXL_REQUEST_GET_WINDOW_ATTRIBUTES.3\
	LIBAXL_REQUEST_DESTROY_WINDOW.3\
	LIBAXL_REQUEST_DESTROY_SUBWINDOWS.3\
	LIBAXL_REQUEST_CHANGE_SAVE_SET.3\
	LIBAXL_REQUEST_REPARENT_WINDOW.3\
	LIBAXL_REQUEST_MAP_WINDOW.3\
	LIBAXL_REQUEST_MAP_SUBWINDOWS.3\
	LIBAXL_REQUEST_UNMAP_WINDOW.3\
	LIBAXL_REQUEST_UNMAP_SUBWINDOWS.3\
	LIBAXL_REQUEST_CONFIGURE_WINDOW.3\
	LIBAXL_REQUEST_CIRCULATE_WINDOW.3\
	LIBAXL_REQUEST_GET_GEOMETRY.3\
	LIBAXL_REQUEST_QUERY_TREE.3\
	LIBAXL_REQUEST_INTERN_ATOM.3\
	LIBAXL_REQUEST_GET_ATOM_NAME.3\
	LIBAXL_REQUEST_CHANGE_PROPERTY.3\
	LIBAXL_REQUEST_DELETE_PROPERTY.3\
	LIBAXL_REQUEST_GET_PROPERTY.3\
	LIBAXL_REQUEST_LIST_PROPERTIES.3\
	LIBAXL_REQUEST_SET_SELECTION_OWNER.3\
	LIBAXL_REQUEST_GET_SELECTION_OWNER.3\
	LIBAXL_REQUEST_CONVERT_SELECTION.3\
	LIBAXL_REQUEST_SEND_EVENT.3\
	LIBAXL_REQUEST_GRAB_POINTER.3\
	LIBAXL_REQUEST_UNGRAB_POINTER.3\
	LIBAXL_REQUEST_GRAB_BUTTON.3\
	LIBAXL_REQUEST_UNGRAB_BUTTON.3\
	LIBAXL_REQUEST_CHANGE_ACTIVE_POINTER_GRAB.3\
	LIBAXL_REQUEST_GRAB_KEYBOARD.3\
	LIBAXL_REQUEST_UNGRAB_KEYBOARD.3\
	LIBAXL_REQUEST_GRAB_KEY.3\
	LIBAXL_REQUEST_UNGRAB_KEY.3\
	LIBAXL_REQUEST_ALLOW_EVENTS.3\
	LIBAXL_REQUEST_GRAB_SERVER.3\
	LIBAXL_REQUEST_UNGRAB_SERVER.3\
	LIBAXL_REQUEST_QUERY_POINTER.3\
	LIBAXL_REQUEST_GET_MOTION_EVENTS.3\
	LIBAXL_REQUEST_TRANSLATE_COORDINATES.3\
	LIBAXL_REQUEST_WARP_POINTER.3\
	LIBAXL_REQUEST_SET_INPUT_FOCUS.3\
	LIBAXL_REQUEST_GET_INPUT_FOCUS.3\
	LIBAXL_REQUEST_QUERY_KEYMAP.3\
	LIBAXL_REQUEST_OPEN_FONT.3\
	LIBAXL_REQUEST_CLOSE_FONT.3\
	LIBAXL_REQUEST_QUERY_FONT.3\
	LIBAXL_REQUEST_QUERY_TEXT_EXTENTS.3\
	LIBAXL_REQUEST_LIST_FONTS.3\
	LIBAXL_REQUEST_LIST_FONTS_WITH_INFO.3\
	LIBAXL_REQUEST_SET_FONT_PATH.3\
	LIBAXL_REQUEST_GET_FONT_PATH.3\
	LIBAXL_REQUEST_CREATE_PIXMAP.3\
	LIBAXL_REQUEST_FREE_PIXMAP.3\
	LIBAXL_REQUEST_CREATE_GC.3\
	LIBAXL_REQUEST_CHANGE_GC.3\
	LIBAXL_REQUEST_COPY_GC.3\
	LIBAXL_REQUEST_SET_DASHES.3\
	LIBAXL_REQUEST_SET_CLIP_RECTANGLES.3\
	LIBAXL_REQUEST_FREE_GC.3\
	LIBAXL_REQUEST_CLEAR_AREA.3\
	LIBAXL_REQUEST_COPY_AREA.3\
	LIBAXL_REQUEST_COPY_PLANE.3\
	LIBAXL_REQUEST_POLY_POINT.3\
	LIBAXL_REQUEST_POLY_LINE.3\
	LIBAXL_REQUEST_POLY_SEGMENT.3\
	LIBAXL_REQUEST_POLY_RECTANGLE.3\
	LIBAXL_REQUEST_POLY_ARC.3\
	LIBAXL_REQUEST_FILL_POLY.3\
	LIBAXL_REQUEST_POLY_FILL_RECTANGLE.3\
	LIBAXL_REQUEST_POLY_FILL_ARC.3\
	LIBAXL_REQUEST_PUT_IMAGE.3\
	LIBAXL_REQUEST_GET_IMAGE.3\
	LIBAXL_REQUEST_POLY_TEXT.3\
	LIBAXL_REQUEST_POLY_TEXT.3\
	LIBAXL_REQUEST_IMAGE_TEXT.3\
	LIBAXL_REQUEST_IMAGE_TEXT.3\
	LIBAXL_REQUEST_CREATE_COLORMAP.3\
	LIBAXL_REQUEST_FREE_COLORMAP.3\
	LIBAXL_REQUEST_COPY_COLORMAP_AND_FREE.3\
	LIBAXL_REQUEST_INSTALL_COLORMAP.3\
	LIBAXL_REQUEST_UNINSTALL_COLORMAP.3\
	LIBAXL_REQUEST_LIST_INSTALLED_COLORMAPS.3\
	LIBAXL_REQUEST_ALLOC_COLOR.3\
	LIBAXL_REQUEST_ALLOC_NAMED_COLOR.3\
	LIBAXL_REQUEST_ALLOC_COLOR_CELLS.3\
	LIBAXL_REQUEST_ALLOC_COLOR_PLANES.3\
	LIBAXL_REQUEST_FREE_COLORS.3\
	LIBAXL_REQUEST_STORE_COLORS.3\
	LIBAXL_REQUEST_STORE_NAMED_COLOR.3\
	LIBAXL_REQUEST_QUERY_COLORS.3\
	LIBAXL_REQUEST_LOOKUP_COLOR.3\
	LIBAXL_REQUEST_CREATE_CURSOR.3\
	LIBAXL_REQUEST_CREATE_GLYPH_CURSOR.3\
	LIBAXL_REQUEST_FREE_CURSOR.3\
	LIBAXL_REQUEST_RECOLOR_CURSOR.3\
	LIBAXL_REQUEST_QUERY_BEST_SIZE.3\
	LIBAXL_REQUEST_QUERY_EXTENSION.3\
	LIBAXL_REQUEST_LIST_EXTENSIONS.3\
	LIBAXL_REQUEST_CHANGE_KEYBOARD_MAPPING.3\
	LIBAXL_REQUEST_GET_KEYBOARD_MAPPING.3\
	LIBAXL_REQUEST_CHANGE_KEYBOARD_CONTROL.3\
	LIBAXL_REQUEST_GET_KEYBOARD_CONTROL.3\
	LIBAXL_REQUEST_BELL.3\
	LIBAXL_REQUEST_CHANGE_POINTER_CONTROL.3\
	LIBAXL_REQUEST_GET_POINTER_CONTROL.3\
	LIBAXL_REQUEST_SET_SCREEN_SAVER.3\
	LIBAXL_REQUEST_GET_SCREEN_SAVER.3\
	LIBAXL_REQUEST_CHANGE_HOSTS.3\
	LIBAXL_REQUEST_LIST_HOSTS.3\
	LIBAXL_REQUEST_SET_ACCESS_CONTROL.3\
	LIBAXL_REQUEST_SET_CLOSE_DOWN_MODE.3\
	LIBAXL_REQUEST_KILL_CLIENT.3\
	LIBAXL_REQUEST_ROTATE_PROPERTIES.3\
	LIBAXL_REQUEST_FORCE_SCREEN_SAVER.3\
	LIBAXL_REQUEST_SET_POINTER_MAPPING.3\
	LIBAXL_REQUEST_GET_POINTER_MAPPING.3\
	LIBAXL_REQUEST_SET_MODIFIER_MAPPING.3\
	LIBAXL_REQUEST_GET_MODIFIER_MAPPING.3\
	LIBAXL_REQUEST_NO_OPERATION.3\
	struct_libaxl_reply_alloc_color.3\
	struct_libaxl_reply_alloc_color_cells.3\
	struct_libaxl_reply_alloc_color_planes.3\
	struct_libaxl_reply_alloc_named_color.3\
	struct_libaxl_reply_get_atom_name.3\
	struct_libaxl_reply_get_font_path.3\
	struct_libaxl_reply_get_geometry.3\
	struct_libaxl_reply_get_image.3\
	struct_libaxl_reply_get_input_focus.3\
	struct_libaxl_reply_get_keyboard_control.3\
	struct_libaxl_reply_get_keyboard_mapping.3\
	struct_libaxl_reply_get_modifier_mapping.3\
	struct_libaxl_reply_get_motion_events.3\
	struct_libaxl_reply_get_pointer_control.3\
	struct_libaxl_reply_get_pointer_mapping.3\
	struct_libaxl_reply_get_property.3\
	struct_libaxl_reply_get_screen_saver.3\
	struct_libaxl_reply_get_selection_owner.3\
	struct_libaxl_reply_get_window_attributes.3\
	struct_libaxl_reply_grab_keyboard.3\
	struct_libaxl_reply_grab_pointer.3\
	struct_libaxl_reply_intern_atom.3\
	struct_libaxl_reply_list_extensions.3\
	struct_libaxl_reply_list_fonts.3\
	struct_libaxl_reply_list_fonts_with_info.3\
	struct_libaxl_reply_list_hosts.3\
	struct_libaxl_reply_list_installed_colormaps.3\
	struct_libaxl_reply_list_properties.3\
	struct_libaxl_reply_lookup_color.3\
	struct_libaxl_reply_query_best_size.3\
	struct_libaxl_reply_query_colors.3\
	struct_libaxl_reply_query_extension.3\
	struct_libaxl_reply_query_font.3\
	struct_libaxl_reply_query_keymap.3\
	struct_libaxl_reply_query_pointer.3\
	struct_libaxl_reply_query_text_extents.3\
	struct_libaxl_reply_query_tree.3\
	struct_libaxl_reply_set_modifier_mapping.3\
	struct_libaxl_reply_set_pointer_mapping.3\
	struct_libaxl_reply_translate_coordinates.3\
	struct_libaxl_request_create_window.3\
	struct_libaxl_request_change_window_attributes.3\
	struct_libaxl_request_get_window_attributes.3\
	struct_libaxl_request_destroy_window.3\
	struct_libaxl_request_destroy_subwindows.3\
	struct_libaxl_request_change_save_set.3\
	struct_libaxl_request_reparent_window.3\
	struct_libaxl_request_map_window.3\
	struct_libaxl_request_map_subwindows.3\
	struct_libaxl_request_unmap_window.3\
	struct_libaxl_request_unmap_subwindows.3\
	struct_libaxl_request_configure_window.3\
	struct_libaxl_request_circulate_window.3\
	struct_libaxl_request_get_geometry.3\
	struct_libaxl_request_query_tree.3\
	struct_libaxl_request_intern_atom.3\
	struct_libaxl_request_get_atom_name.3\
	struct_libaxl_request_change_property.3\
	struct_libaxl_request_delete_property.3\
	struct_libaxl_request_get_property.3\
	struct_libaxl_request_list_properties.3\
	struct_libaxl_request_set_selection_owner.3\
	struct_libaxl_request_get_selection_owner.3\
	struct_libaxl_request_convert_selection.3\
	struct_libaxl_request_send_event.3\
	struct_libaxl_request_grab_pointer.3\
	struct_libaxl_request_ungrab_pointer.3\
	struct_libaxl_request_grab_button.3\
	struct_libaxl_request_ungrab_button.3\
	struct_libaxl_request_change_active_pointer_grab.3\
	struct_libaxl_request_grab_keyboard.3\
	struct_libaxl_request_ungrab_keyboard.3\
	struct_libaxl_request_grab_key.3\
	struct_libaxl_request_ungrab_key.3\
	struct_libaxl_request_allow_events.3\
	struct_libaxl_request_grab_server.3\
	struct_libaxl_request_ungrab_server.3\
	struct_libaxl_request_query_pointer.3\
	struct_libaxl_request_get_motion_events.3\
	struct_libaxl_request_translate_coordinates.3\
	struct_libaxl_request_warp_pointer.3\
	struct_libaxl_request_set_input_focus.3\
	struct_libaxl_request_get_input_focus.3\
	struct_libaxl_request_query_keymap.3\
	struct_libaxl_request_open_font.3\
	struct_libaxl_request_close_font.3\
	struct_libaxl_request_query_font.3\
	struct_libaxl_request_query_text_extents.3\
	struct_libaxl_request_list_fonts.3\
	struct_libaxl_request_list_fonts_with_info.3\
	struct_libaxl_request_set_font_path.3\
	struct_libaxl_request_get_font_path.3\
	struct_libaxl_request_create_pixmap.3\
	struct_libaxl_request_free_pixmap.3\
	struct_libaxl_request_create_gc.3\
	struct_libaxl_request_change_gc.3\
	struct_libaxl_request_copy_gc.3\
	struct_libaxl_request_set_dashes.3\
	struct_libaxl_request_set_clip_rectangles.3\
	struct_libaxl_request_free_gc.3\
	struct_libaxl_request_clear_area.3\
	struct_libaxl_request_copy_area.3\
	struct_libaxl_request_copy_plane.3\
	struct_libaxl_request_poly_point.3\
	struct_libaxl_request_poly_line.3\
	struct_libaxl_request_poly_segment.3\
	struct_libaxl_request_poly_rectangle.3\
	struct_libaxl_request_poly_arc.3\
	struct_libaxl_request_fill_poly.3\
	struct_libaxl_request_poly_fill_rectangle.3\
	struct_libaxl_request_poly_fill_arc.3\
	struct_libaxl_request_put_image.3\
	struct_libaxl_request_get_image.3\
	struct_libaxl_request_poly_text.3\
	struct_libaxl_request_poly_text.3\
	struct_libaxl_request_image_text.3\
	struct_libaxl_request_image_text.3\
	struct_libaxl_request_create_colormap.3\
	struct_libaxl_request_free_colormap.3\
	struct_libaxl_request_copy_colormap_and_free.3\
	struct_libaxl_request_install_colormap.3\
	struct_libaxl_request_uninstall_colormap.3\
	struct_libaxl_request_list_installed_colormaps.3\
	struct_libaxl_request_alloc_color.3\
	struct_libaxl_request_alloc_named_color.3\
	struct_libaxl_request_alloc_color_cells.3\
	struct_libaxl_request_alloc_color_planes.3\
	struct_libaxl_request_free_colors.3\
	struct_libaxl_request_store_colors.3\
	struct_libaxl_request_store_named_color.3\
	struct_libaxl_request_query_colors.3\
	struct_libaxl_request_lookup_color.3\
	struct_libaxl_request_create_cursor.3\
	struct_libaxl_request_create_glyph_cursor.3\
	struct_libaxl_request_free_cursor.3\
	struct_libaxl_request_recolor_cursor.3\
	struct_libaxl_request_query_best_size.3\
	struct_libaxl_request_query_extension.3\
	struct_libaxl_request_list_extensions.3\
	struct_libaxl_request_change_keyboard_mapping.3\
	struct_libaxl_request_get_keyboard_mapping.3\
	struct_libaxl_request_change_keyboard_control.3\
	struct_libaxl_request_get_keyboard_control.3\
	struct_libaxl_request_bell.3\
	struct_libaxl_request_change_pointer_control.3\
	struct_libaxl_request_get_pointer_control.3\
	struct_libaxl_request_set_screen_saver.3\
	struct_libaxl_request_get_screen_saver.3\
	struct_libaxl_request_change_hosts.3\
	struct_libaxl_request_list_hosts.3\
	struct_libaxl_request_set_access_control.3\
	struct_libaxl_request_set_close_down_mode.3\
	struct_libaxl_request_kill_client.3\
	struct_libaxl_request_rotate_properties.3\
	struct_libaxl_request_force_screen_saver.3\
	struct_libaxl_request_set_pointer_mapping.3\
	struct_libaxl_request_get_pointer_mapping.3\
	struct_libaxl_request_set_modifier_mapping.3\
	struct_libaxl_request_get_modifier_mapping.3\
	struct_libaxl_request_no_operation.3


LOBJ = $(OBJ:.o=.lo)

all: libaxl.a libaxl.$(LIBEXT) $(LIB_HDR)
$(OBJ): $(@:.o=.c) $(HDR)
$(LOBJ): $(@:.lo=.c) $(HDR)

.c.o:
	$(CC) -c -o $@ $< $(CFLAGS) $(CPPFLAGS)

.c.lo:
	$(CC) -fPIC -c -o $@ $< $(CFLAGS) $(CPPFLAGS)

libaxl-errors-structs.h: libaxl-errors.h
	sed -n 's/^struct libaxl_error_\([^ \t]*\).*$$/\tstruct libaxl_error_\1 \1;/p' < libaxl-errors.h > $@

libaxl-events-structs.h: libaxl-events.h
	sed -n 's/^struct libaxl_event_\([^ \t]*\).*$$/\tstruct libaxl_event_\1 \1;/p' < libaxl-events.h > $@

libaxl-replies-structs.h: libaxl-replies.h
	sed -n 's/^struct libaxl_reply_\([^ \t]*\).*$$/\tstruct libaxl_reply_\1 \1;/p' < libaxl-replies.h > $@

libaxl-requests-ptr-structs.h: libaxl-requests.h
	sed -n 's/^struct libaxl_request_\([^ \t]*\).*$$/\tconst struct libaxl_request_\1 \*\1;/p' < libaxl-requests.h > $@

libaxl-requests-structs.h: libaxl-requests.h
	sed -n 's/^struct libaxl_request_\([^ \t]*\).*$$/\tstruct libaxl_request_\1 \1;/p' < libaxl-requests.h > $@

libaxl.a: $(OBJ)
	$(AR) rc $@ $?
	$(AR) s $@

libaxl.$(LIBEXT): $(LOBJ)
	$(CC) $(LIBFLAGS) -o $@ $(LOBJ) $(LDFLAGS)

install: libaxl.a libaxl.$(LIBEXT)
	mkdir -p -- "$(DESTDIR)$(PREFIX)/include"
	mkdir -p -- "$(DESTDIR)$(PREFIX)/lib"
#	mkdir -p -- "$(DESTDIR)$(MANPREFIX)/man0"
#	mkdir -p -- "$(DESTDIR)$(MANPREFIX)/man3"
#	mkdir -p -- "$(DESTDIR)$(MANPREFIX)/man7"
	cp -- libaxl.h "$(DESTDIR)$(PREFIX)/include"
	cp -- libaxl.a "$(DESTDIR)$(PREFIX)/lib"
	cp -- libaxl.$(LIBEXT) "$(DESTDIR)$(PREFIX)/lib/libaxl.$(LIBMINOREXT)"
	ln -sf -- libaxl.$(LIBMINOREXT) "$(DESTDIR)$(PREFIX)/lib/libaxl.$(LIBMAJOREXT)"
	ln -sf -- libaxl.$(LIBMINOREXT) "$(DESTDIR)$(PREFIX)/lib/libaxl.$(LIBEXT)"
#	cp -P -- $(MAN0) "$(DESTDIR)$(MANPREFIX)/man0"
#	cp -P -- $(MAN3) "$(DESTDIR)$(MANPREFIX)/man3"
#	cp -P -- $(MAN7) "$(DESTDIR)$(MANPREFIX)/man7"

uninstall:
	-cd -- "$(DESTDIR)$(PREFIX)/include/" && rm -f -- $(LIB_HDR)
	-rm -f -- "$(DESTDIR)$(PREFIX)/lib/libaxl.a"
	-rm -f -- "$(DESTDIR)$(PREFIX)/lib/libaxl.$(LIBMINOREXT)"
	-rm -f -- "$(DESTDIR)$(PREFIX)/lib/libaxl.$(LIBMAJOREXT)"
	-rm -f -- "$(DESTDIR)$(PREFIX)/lib/libaxl.$(LIBEXT)"
#	-cd -- "$(DESTDIR)$(MANPREFIX)/man0/" && rm -f -- $(MAN0)
#	-cd -- "$(DESTDIR)$(MANPREFIX)/man3/" && rm -f -- $(MAN3)
#	-cd -- "$(DESTDIR)$(MANPREFIX)/man7/" && rm -f -- $(MAN7)

clean:
	-rm -f -- *.o *.lo *.a *.su *.$(LIBEXT) libaxl-*-structs.h

.SUFFIXES:
.SUFFIXES: .lo .o .c

.PHONY: all install uninstall clean
