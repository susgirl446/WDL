/*
 *  WDL - The Wayland Dynamic Loader
 *  Version 0.1 for wayland-1.24
 *
 *  Options/defines:
 *  #define WDL_IMPLEMENTATION  - needed in 1 source file to include definitions
 *  #define WDL_NO_XDG          - do not include xdg related code
 *
 *
 *  Support:
 *  For support either open a github issue or ask in the #wdl-support channel in
 *  https://discord.gg/k4kNahe5Tq (in the Programming category)
 *
 *  Notes:
 *  This library is not a place to learn programming with wayland, it does not include documentation on the wayland structs and functions provided by this header
 *
 * LICENSE
 *
 * Copyright 2025 susgirl446 (Hannah S.)
 * You can copy, modify and share this software under the following conditions:
 * 1. Any modifications to this software must be published under the same
 * license and must be properly marked as modified versions
 * 2. You are not allowed to use the name of this software or its
 * developers/contributors to endorse a derived product without explicit
 * permission by the copyright holder
 * 3. You must include this copyright notice alongside binary distributions of
 * this software
 *
 * This software is provided as-is, i (the copyright holder) am not responsible
 * for any damage caused by it
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>

void WDL_init();
void WDL_deinit();

// start core wayland

// wayland-util
#if defined(__GNUC__) && __GNUC__ >= 4
#define WL_PRINTF(x, y) __attribute__((__format__(__printf__, x, y)))
#else
#define WL_PRINTF(x, y)
#endif

typedef int32_t wl_fixed_t;

union wl_argument {
	int32_t i;
	uint32_t u;
	wl_fixed_t f;
	const char *s;
	struct wl_object *o;
	uint32_t n;
	struct wl_array *a;
	int32_t h;
};

struct wl_message {
	const char *name;
	const char *signature;
	const struct wl_interface **types;
};


typedef int (*wl_dispatcher_func_t)(const void *user_data, void *target, uint32_t opcode, const struct wl_message *msg, union wl_argument *args);
typedef void (*wl_log_func_t)(const char *fmt, va_list args) WL_PRINTF(1, 0);




struct wl_interface {
	const char *name;
	int version;
	int method_count;
	const struct wl_message *methods;
	int event_count;
	const struct wl_message *events;
};


// wayland-client-core
#define WL_MARSHAL_FLAG_DESTROY (1 << 0)

struct timespec;

struct wl_proxy;
struct wl_display;
struct wl_event_queue;


typedef void                        (*PFN_wl_event_queue_destroy)(struct wl_event_queue*);
typedef struct wl_proxy*            (*PFN_wl_proxy_marshal_flags)(struct wl_proxy*, uint32_t, const struct wl_interface*, uint32_t, uint32_t, ...);
typedef struct wl_proxy*            (*PFN_wl_proxy_marshal_array_flags)(struct wl_proxy*, uint32_t, const struct wl_interface*, uint32_t, uint32_t, union wl_argument*);
typedef void                        (*PFN_wl_proxy_marshal)(struct wl_proxy*, uint32_t, ...);
typedef void                        (*PFN_wl_proxy_marshal_array)(struct wl_proxy*, uint32_t, union wl_argument*);
typedef struct wl_proxy*            (*PFN_wl_proxy_create)(struct wl_proxy*, const struct wl_interface*);
typedef void*                       (*PFN_wl_proxy_create_wrapper)(void*);
typedef void                        (*PFN_wl_proxy_wrapper_destroy)(void*);
typedef struct wl_proxy*            (*PFN_wl_proxy_marshal_constructor_versioned)(struct wl_proxy*, uint32_t, const struct wl_interface*, uint32_t, ...);
typedef struct wl_proxy*            (*PFN_wl_proxy_marshal_array_constructor)(struct wl_proxy*, uint32_t, union wl_argument*, const struct wl_interface*);
typedef struct wl_proxy*            (*PFN_wl_proxy_marshal_array_constructor_versioned)(struct wl_proxy*, uint32_t, union wl_argument*, const struct wl_interface*, uint32_t);
typedef void                        (*PFN_wl_proxy_destroy)(struct wl_proxy*);
typedef int                         (*PFN_wl_proxy_add_listener)(struct wl_proxy*, void (**)(void), void *);
typedef const void*                 (*PFN_wl_proxy_get_listener)(struct wl_proxy*);
typedef int                         (*PFN_wl_proxy_add_dispatcher)(struct wl_proxy*, wl_dispatcher_func_t, const void*, void *);
typedef void                        (*PFN_wl_proxy_set_user_data)(struct wl_proxy*, void*);
typedef void*                       (*PFN_wl_proxy_get_user_data)(struct wl_proxy*);
typedef uint32_t                    (*PFN_wl_proxy_get_version)(struct wl_proxy*);
typedef uint32_t                    (*PFN_wl_proxy_get_id)(struct wl_proxy*);
typedef void                        (*PFN_wl_proxy_set_tag)(struct wl_proxy*, const char* const*);
typedef const char* const*          (*PFN_wl_proxy_get_tag)(struct wl_proxy*);
typedef const char*                 (*PFN_wl_proxy_get_class)(struct wl_proxy*);
typedef const struct wl_interface*  (*PFN_wl_proxy_get_interface)(struct wl_proxy*);
typedef struct wl_display*          (*PFN_wl_proxy_get_display)(struct wl_proxy*);
typedef void                        (*PFN_wl_proxy_set_queue)(struct wl_proxy*, struct wl_event_queue*);
typedef struct wl_event_queue*      (*PFN_wl_proxy_get_queue)(const struct wl_proxy*);
typedef const char*                 (*PFN_wl_event_queue_get_name)(const struct wl_event_queue*);
typedef struct wl_display*          (*PFN_wl_display_connect)(const char*);
typedef struct wl_display*          (*PFN_wl_display_connect_to_fd)(int);
typedef void                        (*PFN_wl_display_disconnect)(struct wl_display*);
typedef int                         (*PFN_wl_display_get_fd)(struct wl_display*);
typedef int                         (*PFN_wl_display_dispatch)(struct wl_display*);
typedef int                         (*PFN_wl_display_dispatch_queue)(struct wl_display*, struct wl_event_queue*);
typedef int                         (*PFN_wl_display_dispatch_timeout)(struct wl_display*, const struct timespec*);
typedef int                         (*PFN_wl_display_dispatch_queue_timeout)(struct wl_display*, struct wl_event_queue*, const struct timespec*);
typedef int                         (*PFN_wl_display_dispatch_queue_pending)(struct wl_display*, struct wl_event_queue*);
typedef int                         (*PFN_wl_display_dispatch_pending)(struct wl_display*);
typedef int                         (*PFN_wl_display_get_error)(struct wl_display*);
typedef uint32_t                    (*PFN_wl_display_get_protocol_error)(struct wl_display*, const struct wl_interface**, uint32_t*);
typedef int                         (*PFN_wl_display_flush)(struct wl_display*);
typedef int                         (*PFN_wl_display_roundtrip_queue)(struct wl_display*, struct wl_event_queue*);
typedef int                         (*PFN_wl_display_roundtrip)(struct wl_display*);
typedef struct wl_event_queue*      (*PFN_wl_display_create_queue)(struct wl_display*);
typedef struct wl_event_queue*      (*PFN_wl_display_create_queue_with_name)(struct wl_display*, const char*);
typedef int                         (*PFN_wl_display_prepare_read_queue)(struct wl_display*, struct wl_event_queue*);
typedef int                         (*PFN_wl_display_prepare_read)(struct wl_display*);
typedef void                        (*PFN_wl_display_cancel_read)(struct wl_display*);
typedef int                         (*PFN_wl_display_read_events)(struct wl_display*);
typedef void                        (*PFN_wl_log_set_handler_client)(wl_log_func_t handler);
typedef void                        (*PFN_wl_display_set_max_buffer_size)(struct wl_display*, size_t);

 
PFN_wl_event_queue_destroy                            wl_event_queue_destroy;
PFN_wl_proxy_marshal_flags                            wl_proxy_marshal_flags;
PFN_wl_proxy_marshal_array_flags                      wl_proxy_marshal_array_flags;
PFN_wl_proxy_marshal                                  wl_proxy_marshal;
PFN_wl_proxy_marshal_array                            wl_proxy_marshal_array;
PFN_wl_proxy_create                                   wl_proxy_create;
PFN_wl_proxy_create_wrapper                           wl_proxy_create_wrapper;
PFN_wl_proxy_wrapper_destroy                          wl_proxy_wrapper_destroy;
PFN_wl_proxy_marshal_constructor_versioned            wl_proxy_marshal_constructor_versioned;
PFN_wl_proxy_marshal_array_constructor                wl_proxy_marshal_array_constructor;
PFN_wl_proxy_marshal_array_constructor_versioned      wl_proxy_marshal_array_constructor_versioned;
PFN_wl_proxy_destroy                                  wl_proxy_destroy;
PFN_wl_proxy_add_listener                             wl_proxy_add_listener;
PFN_wl_proxy_get_listener                             wl_proxy_get_listener;
PFN_wl_proxy_add_dispatcher                           wl_proxy_add_dispatcher;
PFN_wl_proxy_set_user_data                            wl_proxy_set_user_data;
PFN_wl_proxy_get_user_data                            wl_proxy_get_user_data;
PFN_wl_proxy_get_version                              wl_proxy_get_version;
PFN_wl_proxy_get_id                                   wl_proxy_get_id;
PFN_wl_proxy_set_tag                                  wl_proxy_set_tag;
PFN_wl_proxy_get_tag                                  wl_proxy_get_tag;
PFN_wl_proxy_get_class                                wl_proxy_get_class;
PFN_wl_proxy_get_interface                            wl_proxy_get_interface;
PFN_wl_proxy_get_display                              wl_proxy_get_display;
PFN_wl_proxy_set_queue                                wl_proxy_set_queue;
PFN_wl_proxy_get_queue                                wl_proxy_get_queue;
PFN_wl_event_queue_get_name                           wl_event_queue_get_name;
PFN_wl_display_connect                                wl_display_connect;
PFN_wl_display_connect_to_fd                          wl_display_connect_to_fd;
PFN_wl_display_disconnect                             wl_display_disconnect;
PFN_wl_display_get_fd                                 wl_display_get_fd;
PFN_wl_display_dispatch                               wl_display_dispatch;
PFN_wl_display_dispatch_queue                         wl_display_dispatch_queue;
PFN_wl_display_dispatch_timeout                       wl_display_dispatch_timeout;
PFN_wl_display_dispatch_queue_timeout                 wl_display_dispatch_queue_timeout;
PFN_wl_display_dispatch_queue_pending                 wl_display_dispatch_queue_pending;
PFN_wl_display_dispatch_pending                       wl_display_dispatch_pending;
PFN_wl_display_get_error                              wl_display_get_error;
PFN_wl_display_get_protocol_error                     wl_display_get_protocol_error;
PFN_wl_display_flush                                  wl_display_flush;
PFN_wl_display_roundtrip_queue                        wl_display_roundtrip_queue;
PFN_wl_display_roundtrip                              wl_display_roundtrip;
PFN_wl_display_create_queue                           wl_display_create_queue;
PFN_wl_display_create_queue_with_name                 wl_display_create_queue_with_name; 
PFN_wl_display_prepare_read_queue                     wl_display_prepare_read_queue;
PFN_wl_display_prepare_read                           wl_display_prepare_read;
PFN_wl_display_cancel_read                            wl_display_cancel_read;
PFN_wl_display_read_events                            wl_display_read_events;
PFN_wl_log_set_handler_client                         wl_log_set_handler_client;
PFN_wl_display_set_max_buffer_size                    wl_display_set_max_buffer_size;


// wayland-client-protocol
struct wl_buffer;
struct wl_callback;
struct wl_compositor;
struct wl_data_device;
struct wl_data_device_manager;
struct wl_data_offer;
struct wl_data_source;
struct wl_display;
struct wl_fixes;
struct wl_keyboard;
struct wl_output;
struct wl_pointer;
struct wl_region;
struct wl_registry;
struct wl_seat;
struct wl_shell;
struct wl_shell_surface;
struct wl_shm;
struct wl_shm_pool;
struct wl_subcompositor;
struct wl_subsurface;
struct wl_surface;
struct wl_touch;

#ifndef WL_DISPLAY_INTERFACE
#define WL_DISPLAY_INTERFACE
struct wl_interface wl_display_interface = {};
#endif
#ifndef WL_REGISTRY_INTERFACE
#define WL_REGISTRY_INTERFACE
struct wl_interface wl_registry_interface = {};
#endif
#ifndef WL_CALLBACK_INTERFACE
#define WL_CALLBACK_INTERFACE
struct wl_interface wl_callback_interface = {};
#endif
#ifndef WL_COMPOSITOR_INTERFACE
#define WL_COMPOSITOR_INTERFACE
struct wl_interface wl_compositor_interface = {};
#endif
#ifndef WL_SHM_POOL_INTERFACE
#define WL_SHM_POOL_INTERFACE
struct wl_interface wl_shm_pool_interface = {};
#endif
#ifndef WL_SHM_INTERFACE
#define WL_SHM_INTERFACE
struct wl_interface wl_shm_interface = {};
#endif
#ifndef WL_BUFFER_INTERFACE
#define WL_BUFFER_INTERFACE
struct wl_interface wl_buffer_interface = {};
#endif
#ifndef WL_DATA_OFFER_INTERFACE
#define WL_DATA_OFFER_INTERFACE
struct wl_interface wl_data_offer_interface = {};
#endif
#ifndef WL_DATA_SOURCE_INTERFACE
#define WL_DATA_SOURCE_INTERFACE
struct wl_interface wl_data_source_interface = {};
#endif
#ifndef WL_DATA_DEVICE_INTERFACE
#define WL_DATA_DEVICE_INTERFACE
struct wl_interface wl_data_device_interface = {};
#endif
#ifndef WL_DATA_DEVICE_MANAGER_INTERFACE
#define WL_DATA_DEVICE_MANAGER_INTERFACE
struct wl_interface wl_data_device_manager_interface = {};
#endif
#ifndef WL_SHELL_INTERFACE
#define WL_SHELL_INTERFACE
struct wl_interface wl_shell_interface = {};
#endif
#ifndef WL_SHELL_SURFACE_INTERFACE
#define WL_SHELL_SURFACE_INTERFACE
struct wl_interface wl_shell_surface_interface = {};
#endif
#ifndef WL_SURFACE_INTERFACE
#define WL_SURFACE_INTERFACE
struct wl_interface wl_surface_interface = {};
#endif
#ifndef WL_SEAT_INTERFACE
#define WL_SEAT_INTERFACE
struct wl_interface wl_seat_interface = {};
#endif
#ifndef WL_POINTER_INTERFACE
#define WL_POINTER_INTERFACE
struct wl_interface wl_pointer_interface = {};
#endif
#ifndef WL_KEYBOARD_INTERFACE
#define WL_KEYBOARD_INTERFACE
struct wl_interface wl_keyboard_interface = {};
#endif
#ifndef WL_TOUCH_INTERFACE
#define WL_TOUCH_INTERFACE
struct wl_interface wl_touch_interface = {};
#endif
#ifndef WL_OUTPUT_INTERFACE
#define WL_OUTPUT_INTERFACE
struct wl_interface wl_output_interface = {};
#endif
#ifndef WL_REGION_INTERFACE
#define WL_REGION_INTERFACE
struct wl_interface wl_region_interface = {};
#endif
#ifndef WL_SUBCOMPOSITOR_INTERFACE
#define WL_SUBCOMPOSITOR_INTERFACE
struct wl_interface wl_subcompositor_interface = {};
#endif
#ifndef WL_SUBSURFACE_INTERFACE
#define WL_SUBSURFACE_INTERFACE
struct wl_interface wl_subsurface_interface = {};
#endif
#ifndef WL_FIXES_INTERFACE
#define WL_FIXES_INTERFACE
struct wl_interface wl_fixes_interface = {};
#endif



#ifndef WL_DISPLAY_ERROR_ENUM
#define WL_DISPLAY_ERROR_ENUM
enum wl_display_error {
	WL_DISPLAY_ERROR_INVALID_OBJECT = 0,
	WL_DISPLAY_ERROR_INVALID_METHOD = 1,
	WL_DISPLAY_ERROR_NO_MEMORY = 2,
	WL_DISPLAY_ERROR_IMPLEMENTATION = 3,
};
#endif

struct wl_display_listener {
	void (*error)(void *data,
		      struct wl_display *wl_display,
		      void *object_id,
		      uint32_t code,
		      const char *message);

	void (*delete_id)(void *data,
			  struct wl_display *wl_display,
			  uint32_t id);
};


static inline int wl_display_add_listener(struct wl_display *wl_display, const struct wl_display_listener *listener, void *data) {
	return wl_proxy_add_listener((struct wl_proxy *) wl_display, (void (**)(void)) listener, data);
}

#define WL_DISPLAY_SYNC 0
#define WL_DISPLAY_GET_REGISTRY 1
#define WL_DISPLAY_ERROR_SINCE_VERSION 1
#define WL_DISPLAY_DELETE_ID_SINCE_VERSION 1
#define WL_DISPLAY_SYNC_SINCE_VERSION 1
#define WL_DISPLAY_GET_REGISTRY_SINCE_VERSION 1


static inline void wl_display_set_user_data(struct wl_display* wl_display, void* user_data) {
	wl_proxy_set_user_data((struct wl_proxy *) wl_display, user_data);
}

static inline void* wl_display_get_user_data(struct wl_display* wl_display) {
	return wl_proxy_get_user_data((struct wl_proxy *) wl_display);
}

static inline uint32_t wl_display_get_version(struct wl_display* wl_display) {
	return wl_proxy_get_version((struct wl_proxy *) wl_display);
}


static inline struct wl_callback* wl_display_sync(struct wl_display *wl_display) {
	struct wl_proxy *callback;

	callback = wl_proxy_marshal_flags((struct wl_proxy *) wl_display, WL_DISPLAY_SYNC, &wl_callback_interface, wl_proxy_get_version((struct wl_proxy *) wl_display), 0, NULL);

	return (struct wl_callback *) callback;
}

static inline struct wl_registry* wl_display_get_registry(struct wl_display *wl_display) {
	struct wl_proxy *registry;

	registry = wl_proxy_marshal_flags((struct wl_proxy *) wl_display, WL_DISPLAY_GET_REGISTRY, &wl_registry_interface, wl_proxy_get_version((struct wl_proxy *) wl_display), 0, NULL);

	return (struct wl_registry *) registry;
}

struct wl_registry_listener {
	void (*global)(void *data,
		       struct wl_registry *wl_registry,
		       uint32_t name,
		       const char *interface,
		       uint32_t version);

	void (*global_remove)(void *data,
			      struct wl_registry *wl_registry,
			      uint32_t name);
};

static inline int wl_registry_add_listener(struct wl_registry *wl_registry, const struct wl_registry_listener *listener, void *data) {
	return wl_proxy_add_listener((struct wl_proxy *) wl_registry, (void (**)(void)) listener, data);
}

#define WL_REGISTRY_BIND 0
#define WL_REGISTRY_GLOBAL_SINCE_VERSION 1
#define WL_REGISTRY_GLOBAL_REMOVE_SINCE_VERSION 1
#define WL_REGISTRY_BIND_SINCE_VERSION 1


static inline void wl_registry_set_user_data(struct wl_registry *wl_registry, void *user_data) {
	wl_proxy_set_user_data((struct wl_proxy *) wl_registry, user_data);
}


static inline void* wl_registry_get_user_data(struct wl_registry *wl_registry) {
	return wl_proxy_get_user_data((struct wl_proxy *) wl_registry);
}

static inline uint32_t wl_registry_get_version(struct wl_registry *wl_registry) {
	return wl_proxy_get_version((struct wl_proxy *) wl_registry);
}


static inline void wl_registry_destroy(struct wl_registry *wl_registry) {
	wl_proxy_destroy((struct wl_proxy *) wl_registry);
}

static inline void* wl_registry_bind(struct wl_registry *wl_registry, uint32_t name, const struct wl_interface *interface, uint32_t version) {
	struct wl_proxy *id;

	id = wl_proxy_marshal_flags((struct wl_proxy *) wl_registry,
			 WL_REGISTRY_BIND, interface, version, 0, name, interface->name, version, NULL);

	return (void *) id;
}

struct wl_callback_listener {
	void (*done)(void *data,
		     struct wl_callback *wl_callback,
		     uint32_t callback_data);
};


static inline int wl_callback_add_listener(struct wl_callback *wl_callback, const struct wl_callback_listener *listener, void *data) {
	return wl_proxy_add_listener((struct wl_proxy *) wl_callback, (void (**)(void)) listener, data);
}

#define WL_CALLBACK_DONE_SINCE_VERSION 1



static inline void wl_callback_set_user_data(struct wl_callback *wl_callback, void *user_data) {
	wl_proxy_set_user_data((struct wl_proxy *) wl_callback, user_data);
}


static inline void* wl_callback_get_user_data(struct wl_callback *wl_callback) {
	return wl_proxy_get_user_data((struct wl_proxy *) wl_callback);
}

static inline uint32_t wl_callback_get_version(struct wl_callback *wl_callback) {
	return wl_proxy_get_version((struct wl_proxy *) wl_callback);
}


static inline void wl_callback_destroy(struct wl_callback *wl_callback) {
	wl_proxy_destroy((struct wl_proxy *) wl_callback);
}

#define WL_COMPOSITOR_CREATE_SURFACE 0
#define WL_COMPOSITOR_CREATE_REGION 1



#define WL_COMPOSITOR_CREATE_SURFACE_SINCE_VERSION 1
#define WL_COMPOSITOR_CREATE_REGION_SINCE_VERSION 1

static inline void wl_compositor_set_user_data(struct wl_compositor *wl_compositor, void *user_data) {
	wl_proxy_set_user_data((struct wl_proxy *) wl_compositor, user_data);
}


static inline void* wl_compositor_get_user_data(struct wl_compositor *wl_compositor) {
	return wl_proxy_get_user_data((struct wl_proxy *) wl_compositor);
}

static inline uint32_t wl_compositor_get_version(struct wl_compositor *wl_compositor) {
	return wl_proxy_get_version((struct wl_proxy *) wl_compositor);
}


static inline void wl_compositor_destroy(struct wl_compositor *wl_compositor) {
	wl_proxy_destroy((struct wl_proxy *) wl_compositor);
}


static inline struct wl_surface* wl_compositor_create_surface(struct wl_compositor *wl_compositor) {
	struct wl_proxy *id;

	id = wl_proxy_marshal_flags((struct wl_proxy *) wl_compositor,
			 WL_COMPOSITOR_CREATE_SURFACE, &wl_surface_interface, wl_proxy_get_version((struct wl_proxy *) wl_compositor), 0, NULL);

	return (struct wl_surface *) id;
}


static inline struct wl_region * wl_compositor_create_region(struct wl_compositor *wl_compositor) {
	struct wl_proxy *id;

	id = wl_proxy_marshal_flags((struct wl_proxy *) wl_compositor,
			 WL_COMPOSITOR_CREATE_REGION, &wl_region_interface, wl_proxy_get_version((struct wl_proxy *) wl_compositor), 0, NULL);

	return (struct wl_region *) id;
}

#define WL_SHM_POOL_CREATE_BUFFER 0
#define WL_SHM_POOL_DESTROY 1
#define WL_SHM_POOL_RESIZE 2
#define WL_SHM_POOL_CREATE_BUFFER_SINCE_VERSION 1
#define WL_SHM_POOL_DESTROY_SINCE_VERSION 1
#define WL_SHM_POOL_RESIZE_SINCE_VERSION 1


static inline void wl_shm_pool_set_user_data(struct wl_shm_pool *wl_shm_pool, void *user_data) {
	wl_proxy_set_user_data((struct wl_proxy *) wl_shm_pool, user_data);
}

static inline void* wl_shm_pool_get_user_data(struct wl_shm_pool *wl_shm_pool) {
	return wl_proxy_get_user_data((struct wl_proxy *) wl_shm_pool);
}

static inline uint32_t wl_shm_pool_get_version(struct wl_shm_pool *wl_shm_pool) {
	return wl_proxy_get_version((struct wl_proxy *) wl_shm_pool);
}


static inline struct wl_buffer* wl_shm_pool_create_buffer(struct wl_shm_pool *wl_shm_pool, int32_t offset, int32_t width, int32_t height, int32_t stride, uint32_t format) {
	struct wl_proxy *id;

	id = wl_proxy_marshal_flags((struct wl_proxy *) wl_shm_pool,
			 WL_SHM_POOL_CREATE_BUFFER, &wl_buffer_interface, wl_proxy_get_version((struct wl_proxy *) wl_shm_pool), 0, NULL, offset, width, height, stride, format);

	return (struct wl_buffer *) id;
}


static inline void wl_shm_pool_destroy(struct wl_shm_pool *wl_shm_pool) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_shm_pool,
			 WL_SHM_POOL_DESTROY, NULL, wl_proxy_get_version((struct wl_proxy *) wl_shm_pool), WL_MARSHAL_FLAG_DESTROY);
}


static inline void wl_shm_pool_resize(struct wl_shm_pool *wl_shm_pool, int32_t size) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_shm_pool,
			 WL_SHM_POOL_RESIZE, NULL, wl_proxy_get_version((struct wl_proxy *) wl_shm_pool), 0, size);
}

#ifndef WL_SHM_ERROR_ENUM
#define WL_SHM_ERROR_ENUM

enum wl_shm_error {
	WL_SHM_ERROR_INVALID_FORMAT = 0,
	WL_SHM_ERROR_INVALID_STRIDE = 1,
	WL_SHM_ERROR_INVALID_FD = 2,
};
#endif

#ifndef WL_SHM_FORMAT_ENUM
#define WL_SHM_FORMAT_ENUM
enum wl_shm_format {
	WL_SHM_FORMAT_ARGB8888 = 0,
	WL_SHM_FORMAT_XRGB8888 = 1,
	WL_SHM_FORMAT_C8 = 0x20203843,
	WL_SHM_FORMAT_RGB332 = 0x38424752,
	WL_SHM_FORMAT_BGR233 = 0x38524742,
	WL_SHM_FORMAT_XRGB4444 = 0x32315258,
	WL_SHM_FORMAT_XBGR4444 = 0x32314258,
	WL_SHM_FORMAT_RGBX4444 = 0x32315852,
	WL_SHM_FORMAT_BGRX4444 = 0x32315842,
	WL_SHM_FORMAT_ARGB4444 = 0x32315241,
	WL_SHM_FORMAT_ABGR4444 = 0x32314241,
	WL_SHM_FORMAT_RGBA4444 = 0x32314152,
	WL_SHM_FORMAT_BGRA4444 = 0x32314142,
	WL_SHM_FORMAT_XRGB1555 = 0x35315258,
	WL_SHM_FORMAT_XBGR1555 = 0x35314258,
	WL_SHM_FORMAT_RGBX5551 = 0x35315852,
	WL_SHM_FORMAT_BGRX5551 = 0x35315842,
	WL_SHM_FORMAT_ARGB1555 = 0x35315241,
	WL_SHM_FORMAT_ABGR1555 = 0x35314241,
	WL_SHM_FORMAT_RGBA5551 = 0x35314152,
	WL_SHM_FORMAT_BGRA5551 = 0x35314142,
	WL_SHM_FORMAT_RGB565 = 0x36314752,
	WL_SHM_FORMAT_BGR565 = 0x36314742,
	WL_SHM_FORMAT_RGB888 = 0x34324752,
	WL_SHM_FORMAT_BGR888 = 0x34324742,
	WL_SHM_FORMAT_XBGR8888 = 0x34324258,
	WL_SHM_FORMAT_RGBX8888 = 0x34325852,
	WL_SHM_FORMAT_BGRX8888 = 0x34325842,
	WL_SHM_FORMAT_ABGR8888 = 0x34324241,
	WL_SHM_FORMAT_RGBA8888 = 0x34324152,
	WL_SHM_FORMAT_BGRA8888 = 0x34324142,
	WL_SHM_FORMAT_XRGB2101010 = 0x30335258,
	WL_SHM_FORMAT_XBGR2101010 = 0x30334258,
	WL_SHM_FORMAT_RGBX1010102 = 0x30335852,
	WL_SHM_FORMAT_BGRX1010102 = 0x30335842,
	WL_SHM_FORMAT_ARGB2101010 = 0x30335241,
	WL_SHM_FORMAT_ABGR2101010 = 0x30334241,
	WL_SHM_FORMAT_RGBA1010102 = 0x30334152,
	WL_SHM_FORMAT_BGRA1010102 = 0x30334142,
	WL_SHM_FORMAT_YUYV = 0x56595559,
	WL_SHM_FORMAT_YVYU = 0x55595659,
	WL_SHM_FORMAT_UYVY = 0x59565955,
	WL_SHM_FORMAT_VYUY = 0x59555956,
	WL_SHM_FORMAT_AYUV = 0x56555941,
	WL_SHM_FORMAT_NV12 = 0x3231564e,
	WL_SHM_FORMAT_NV21 = 0x3132564e,
	WL_SHM_FORMAT_NV16 = 0x3631564e,
	WL_SHM_FORMAT_NV61 = 0x3136564e,
	WL_SHM_FORMAT_YUV410 = 0x39565559,
	WL_SHM_FORMAT_YVU410 = 0x39555659,
	WL_SHM_FORMAT_YUV411 = 0x31315559,
	WL_SHM_FORMAT_YVU411 = 0x31315659,
	WL_SHM_FORMAT_YUV420 = 0x32315559,
	WL_SHM_FORMAT_YVU420 = 0x32315659,
	WL_SHM_FORMAT_YUV422 = 0x36315559,
	WL_SHM_FORMAT_YVU422 = 0x36315659,
	WL_SHM_FORMAT_YUV444 = 0x34325559,
	WL_SHM_FORMAT_YVU444 = 0x34325659,
	WL_SHM_FORMAT_R8 = 0x20203852,
	WL_SHM_FORMAT_R16 = 0x20363152,
	WL_SHM_FORMAT_RG88 = 0x38384752,
	WL_SHM_FORMAT_GR88 = 0x38385247,
	WL_SHM_FORMAT_RG1616 = 0x32334752,
	WL_SHM_FORMAT_GR1616 = 0x32335247,
	WL_SHM_FORMAT_XRGB16161616F = 0x48345258,
	WL_SHM_FORMAT_XBGR16161616F = 0x48344258,
	WL_SHM_FORMAT_ARGB16161616F = 0x48345241,
	WL_SHM_FORMAT_ABGR16161616F = 0x48344241,
	WL_SHM_FORMAT_XYUV8888 = 0x56555958,
	WL_SHM_FORMAT_VUY888 = 0x34325556,
	WL_SHM_FORMAT_VUY101010 = 0x30335556,
	WL_SHM_FORMAT_Y210 = 0x30313259,
	WL_SHM_FORMAT_Y212 = 0x32313259,
	WL_SHM_FORMAT_Y216 = 0x36313259,
	WL_SHM_FORMAT_Y410 = 0x30313459,
	WL_SHM_FORMAT_Y412 = 0x32313459,
	WL_SHM_FORMAT_Y416 = 0x36313459,
	WL_SHM_FORMAT_XVYU2101010 = 0x30335658,
	WL_SHM_FORMAT_XVYU12_16161616 = 0x36335658,
	WL_SHM_FORMAT_XVYU16161616 = 0x38345658,
	WL_SHM_FORMAT_Y0L0 = 0x304c3059,
	WL_SHM_FORMAT_X0L0 = 0x304c3058,
	WL_SHM_FORMAT_Y0L2 = 0x324c3059,
	WL_SHM_FORMAT_X0L2 = 0x324c3058,
	WL_SHM_FORMAT_YUV420_8BIT = 0x38305559,
	WL_SHM_FORMAT_YUV420_10BIT = 0x30315559,
	WL_SHM_FORMAT_XRGB8888_A8 = 0x38415258,
	WL_SHM_FORMAT_XBGR8888_A8 = 0x38414258,
	WL_SHM_FORMAT_RGBX8888_A8 = 0x38415852,
	WL_SHM_FORMAT_BGRX8888_A8 = 0x38415842,
	WL_SHM_FORMAT_RGB888_A8 = 0x38413852,
	WL_SHM_FORMAT_BGR888_A8 = 0x38413842,
	WL_SHM_FORMAT_RGB565_A8 = 0x38413552,
	WL_SHM_FORMAT_BGR565_A8 = 0x38413542,
	WL_SHM_FORMAT_NV24 = 0x3432564e,
	WL_SHM_FORMAT_NV42 = 0x3234564e,
	WL_SHM_FORMAT_P210 = 0x30313250,
	WL_SHM_FORMAT_P010 = 0x30313050,
	WL_SHM_FORMAT_P012 = 0x32313050,
	WL_SHM_FORMAT_P016 = 0x36313050,
	WL_SHM_FORMAT_AXBXGXRX106106106106 = 0x30314241,
	WL_SHM_FORMAT_NV15 = 0x3531564e,
	WL_SHM_FORMAT_Q410 = 0x30313451,
	WL_SHM_FORMAT_Q401 = 0x31303451,
	WL_SHM_FORMAT_XRGB16161616 = 0x38345258,
	WL_SHM_FORMAT_XBGR16161616 = 0x38344258,
	WL_SHM_FORMAT_ARGB16161616 = 0x38345241,
	WL_SHM_FORMAT_ABGR16161616 = 0x38344241,
	WL_SHM_FORMAT_C1 = 0x20203143,
	WL_SHM_FORMAT_C2 = 0x20203243,
	WL_SHM_FORMAT_C4 = 0x20203443,
	WL_SHM_FORMAT_D1 = 0x20203144,
	WL_SHM_FORMAT_D2 = 0x20203244,
	WL_SHM_FORMAT_D4 = 0x20203444,
	WL_SHM_FORMAT_D8 = 0x20203844,
	WL_SHM_FORMAT_R1 = 0x20203152,
	WL_SHM_FORMAT_R2 = 0x20203252,
	WL_SHM_FORMAT_R4 = 0x20203452,
	WL_SHM_FORMAT_R10 = 0x20303152,
	WL_SHM_FORMAT_R12 = 0x20323152,
	WL_SHM_FORMAT_AVUY8888 = 0x59555641,
	WL_SHM_FORMAT_XVUY8888 = 0x59555658,
	WL_SHM_FORMAT_P030 = 0x30333050,
};
#endif

struct wl_shm_listener {
	void (*format)(void *data,
		       struct wl_shm *wl_shm,
		       uint32_t format);
};

static inline int wl_shm_add_listener(struct wl_shm *wl_shm, const struct wl_shm_listener *listener, void *data) {
	return wl_proxy_add_listener((struct wl_proxy *) wl_shm, (void (**)(void)) listener, data);
}

#define WL_SHM_CREATE_POOL 0
#define WL_SHM_RELEASE 1
#define WL_SHM_FORMAT_SINCE_VERSION 1
#define WL_SHM_CREATE_POOL_SINCE_VERSION 1
#define WL_SHM_RELEASE_SINCE_VERSION 2


static inline void wl_shm_set_user_data(struct wl_shm *wl_shm, void *user_data) {
	wl_proxy_set_user_data((struct wl_proxy *) wl_shm, user_data);
}


static inline void* wl_shm_get_user_data(struct wl_shm *wl_shm) {
	return wl_proxy_get_user_data((struct wl_proxy *) wl_shm);
}

static inline uint32_t wl_shm_get_version(struct wl_shm *wl_shm) {
	return wl_proxy_get_version((struct wl_proxy *) wl_shm);
}


static inline void wl_shm_destroy(struct wl_shm *wl_shm) {
	wl_proxy_destroy((struct wl_proxy *) wl_shm);
}

static inline struct wl_shm_pool* wl_shm_create_pool(struct wl_shm *wl_shm, int32_t fd, int32_t size) {
	struct wl_proxy *id;

	id = wl_proxy_marshal_flags((struct wl_proxy *) wl_shm,
			 WL_SHM_CREATE_POOL, &wl_shm_pool_interface, wl_proxy_get_version((struct wl_proxy *) wl_shm), 0, NULL, fd, size);

	return (struct wl_shm_pool *) id;
}

static inline void wl_shm_release(struct wl_shm *wl_shm) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_shm,
			 WL_SHM_RELEASE, NULL, wl_proxy_get_version((struct wl_proxy *) wl_shm), WL_MARSHAL_FLAG_DESTROY);
}


struct wl_buffer_listener {
	void (*release)(void *data,
			struct wl_buffer *wl_buffer);
};

static inline int wl_buffer_add_listener(struct wl_buffer *wl_buffer, const struct wl_buffer_listener *listener, void *data) {
	return wl_proxy_add_listener((struct wl_proxy *) wl_buffer,
				     (void (**)(void)) listener, data);
}

#define WL_BUFFER_DESTROY 0
#define WL_BUFFER_RELEASE_SINCE_VERSION 1
#define WL_BUFFER_DESTROY_SINCE_VERSION 1


static inline void wl_buffer_set_user_data(struct wl_buffer *wl_buffer, void *user_data) {
	wl_proxy_set_user_data((struct wl_proxy *) wl_buffer, user_data);
}


static inline void * wl_buffer_get_user_data(struct wl_buffer *wl_buffer) {
	return wl_proxy_get_user_data((struct wl_proxy *) wl_buffer);
}

static inline uint32_t wl_buffer_get_version(struct wl_buffer *wl_buffer) {
	return wl_proxy_get_version((struct wl_proxy *) wl_buffer);
}

static inline void wl_buffer_destroy(struct wl_buffer *wl_buffer) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_buffer,
			 WL_BUFFER_DESTROY, NULL, wl_proxy_get_version((struct wl_proxy *) wl_buffer), WL_MARSHAL_FLAG_DESTROY);
}

#ifndef WL_DATA_OFFER_ERROR_ENUM
#define WL_DATA_OFFER_ERROR_ENUM
enum wl_data_offer_error {
	WL_DATA_OFFER_ERROR_INVALID_FINISH = 0,
	WL_DATA_OFFER_ERROR_INVALID_ACTION_MASK = 1,
	WL_DATA_OFFER_ERROR_INVALID_ACTION = 2,
	WL_DATA_OFFER_ERROR_INVALID_OFFER = 3,
};
#endif

struct wl_data_offer_listener {
	void (*offer)(void *data,
		      struct wl_data_offer *wl_data_offer,
		      const char *mime_type);

	void (*source_actions)(void *data,
			       struct wl_data_offer *wl_data_offer,
			       uint32_t source_actions);

	void (*action)(void *data,
		       struct wl_data_offer *wl_data_offer,
		       uint32_t dnd_action);
};

static inline int wl_data_offer_add_listener(struct wl_data_offer *wl_data_offer, const struct wl_data_offer_listener *listener, void *data) {
	return wl_proxy_add_listener((struct wl_proxy *) wl_data_offer,
				     (void (**)(void)) listener, data);
}

#define WL_DATA_OFFER_ACCEPT 0
#define WL_DATA_OFFER_RECEIVE 1
#define WL_DATA_OFFER_DESTROY 2
#define WL_DATA_OFFER_FINISH 3
#define WL_DATA_OFFER_SET_ACTIONS 4
#define WL_DATA_OFFER_OFFER_SINCE_VERSION 1
#define WL_DATA_OFFER_SOURCE_ACTIONS_SINCE_VERSION 3
#define WL_DATA_OFFER_ACTION_SINCE_VERSION 3
#define WL_DATA_OFFER_ACCEPT_SINCE_VERSION 1
#define WL_DATA_OFFER_RECEIVE_SINCE_VERSION 1
#define WL_DATA_OFFER_DESTROY_SINCE_VERSION 1
#define WL_DATA_OFFER_FINISH_SINCE_VERSION 3
#define WL_DATA_OFFER_SET_ACTIONS_SINCE_VERSION 3

static inline void wl_data_offer_set_user_data(struct wl_data_offer *wl_data_offer, void *user_data) {
	wl_proxy_set_user_data((struct wl_proxy *) wl_data_offer, user_data);
}


static inline void* wl_data_offer_get_user_data(struct wl_data_offer *wl_data_offer) {
	return wl_proxy_get_user_data((struct wl_proxy *) wl_data_offer);
}

static inline uint32_t wl_data_offer_get_version(struct wl_data_offer *wl_data_offer) {
	return wl_proxy_get_version((struct wl_proxy *) wl_data_offer);
}


static inline void wl_data_offer_accept(struct wl_data_offer *wl_data_offer, uint32_t serial, const char *mime_type) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_data_offer,
			 WL_DATA_OFFER_ACCEPT, NULL, wl_proxy_get_version((struct wl_proxy *) wl_data_offer), 0, serial, mime_type);
}

static inline void wl_data_offer_receive(struct wl_data_offer *wl_data_offer, const char *mime_type, int32_t fd) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_data_offer,
			 WL_DATA_OFFER_RECEIVE, NULL, wl_proxy_get_version((struct wl_proxy *) wl_data_offer), 0, mime_type, fd);
}

static inline void wl_data_offer_destroy(struct wl_data_offer *wl_data_offer) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_data_offer,
			 WL_DATA_OFFER_DESTROY, NULL, wl_proxy_get_version((struct wl_proxy *) wl_data_offer), WL_MARSHAL_FLAG_DESTROY);
}

static inline void wl_data_offer_finish(struct wl_data_offer *wl_data_offer) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_data_offer,
			 WL_DATA_OFFER_FINISH, NULL, wl_proxy_get_version((struct wl_proxy *) wl_data_offer), 0);
}

static inline void wl_data_offer_set_actions(struct wl_data_offer *wl_data_offer, uint32_t dnd_actions, uint32_t preferred_action) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_data_offer,
			 WL_DATA_OFFER_SET_ACTIONS, NULL, wl_proxy_get_version((struct wl_proxy *) wl_data_offer), 0, dnd_actions, preferred_action);
}

#ifndef WL_DATA_SOURCE_ERROR_ENUM
#define WL_DATA_SOURCE_ERROR_ENUM
enum wl_data_source_error {
	WL_DATA_SOURCE_ERROR_INVALID_ACTION_MASK = 0,
	WL_DATA_SOURCE_ERROR_INVALID_SOURCE = 1,
};
#endif

struct wl_data_source_listener {
	void (*target)(void *data,
		       struct wl_data_source *wl_data_source,
		       const char *mime_type);

	void (*send)(void *data,
		     struct wl_data_source *wl_data_source,
		     const char *mime_type,
		     int32_t fd);

	void (*cancelled)(void *data,
			  struct wl_data_source *wl_data_source);

	void (*dnd_drop_performed)(void *data,
				   struct wl_data_source *wl_data_source);

	void (*dnd_finished)(void *data,
			     struct wl_data_source *wl_data_source);

	void (*action)(void *data,
		       struct wl_data_source *wl_data_source,
		       uint32_t dnd_action);
};


static inline int wl_data_source_add_listener(struct wl_data_source *wl_data_source, const struct wl_data_source_listener *listener, void *data) {
	return wl_proxy_add_listener((struct wl_proxy *) wl_data_source,
				     (void (**)(void)) listener, data);
}

#define WL_DATA_SOURCE_OFFER 0
#define WL_DATA_SOURCE_DESTROY 1
#define WL_DATA_SOURCE_SET_ACTIONS 2
#define WL_DATA_SOURCE_TARGET_SINCE_VERSION 1
#define WL_DATA_SOURCE_SEND_SINCE_VERSION 1
#define WL_DATA_SOURCE_CANCELLED_SINCE_VERSION 1
#define WL_DATA_SOURCE_DND_DROP_PERFORMED_SINCE_VERSION 3
#define WL_DATA_SOURCE_DND_FINISHED_SINCE_VERSION 3
#define WL_DATA_SOURCE_ACTION_SINCE_VERSION 3
#define WL_DATA_SOURCE_OFFER_SINCE_VERSION 1
#define WL_DATA_SOURCE_DESTROY_SINCE_VERSION 1
#define WL_DATA_SOURCE_SET_ACTIONS_SINCE_VERSION 3


static inline void wl_data_source_set_user_data(struct wl_data_source *wl_data_source, void *user_data) {
	wl_proxy_set_user_data((struct wl_proxy *) wl_data_source, user_data);
}

static inline void* wl_data_source_get_user_data(struct wl_data_source *wl_data_source) {
	return wl_proxy_get_user_data((struct wl_proxy *) wl_data_source);
}

static inline uint32_t wl_data_source_get_version(struct wl_data_source *wl_data_source) {
	return wl_proxy_get_version((struct wl_proxy *) wl_data_source);
}


static inline void wl_data_source_offer(struct wl_data_source *wl_data_source, const char *mime_type) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_data_source,
			 WL_DATA_SOURCE_OFFER, NULL, wl_proxy_get_version((struct wl_proxy *) wl_data_source), 0, mime_type);
}


static inline void wl_data_source_destroy(struct wl_data_source *wl_data_source) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_data_source,
			 WL_DATA_SOURCE_DESTROY, NULL, wl_proxy_get_version((struct wl_proxy *) wl_data_source), WL_MARSHAL_FLAG_DESTROY);
}


static inline void wl_data_source_set_actions(struct wl_data_source *wl_data_source, uint32_t dnd_actions) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_data_source,
			 WL_DATA_SOURCE_SET_ACTIONS, NULL, wl_proxy_get_version((struct wl_proxy *) wl_data_source), 0, dnd_actions);
}

#ifndef WL_DATA_DEVICE_ERROR_ENUM
#define WL_DATA_DEVICE_ERROR_ENUM
enum wl_data_device_error {
	WL_DATA_DEVICE_ERROR_ROLE = 0,
	WL_DATA_DEVICE_ERROR_USED_SOURCE = 1,
};
#endif

struct wl_data_device_listener {
	void (*data_offer)(void *data,
			   struct wl_data_device *wl_data_device,
			   struct wl_data_offer *id);

	void (*enter)(void *data,
		      struct wl_data_device *wl_data_device,
		      uint32_t serial,
		      struct wl_surface *surface,
		      wl_fixed_t x,
		      wl_fixed_t y,
		      struct wl_data_offer *id);

	void (*leave)(void *data,
		      struct wl_data_device *wl_data_device);

	void (*motion)(void *data,
		       struct wl_data_device *wl_data_device,
		       uint32_t time,
		       wl_fixed_t x,
		       wl_fixed_t y);

	void (*drop)(void *data,
		     struct wl_data_device *wl_data_device);

	void (*selection)(void *data,
			  struct wl_data_device *wl_data_device,
			  struct wl_data_offer *id);
};


static inline int wl_data_device_add_listener(struct wl_data_device *wl_data_device, const struct wl_data_device_listener *listener, void *data) {
	return wl_proxy_add_listener((struct wl_proxy *) wl_data_device,
				     (void (**)(void)) listener, data);
}

#define WL_DATA_DEVICE_START_DRAG 0
#define WL_DATA_DEVICE_SET_SELECTION 1
#define WL_DATA_DEVICE_RELEASE 2
#define WL_DATA_DEVICE_DATA_OFFER_SINCE_VERSION 1
#define WL_DATA_DEVICE_ENTER_SINCE_VERSION 1
#define WL_DATA_DEVICE_LEAVE_SINCE_VERSION 1
#define WL_DATA_DEVICE_MOTION_SINCE_VERSION 1
#define WL_DATA_DEVICE_DROP_SINCE_VERSION 1
#define WL_DATA_DEVICE_SELECTION_SINCE_VERSION 1
#define WL_DATA_DEVICE_START_DRAG_SINCE_VERSION 1
#define WL_DATA_DEVICE_SET_SELECTION_SINCE_VERSION 1
#define WL_DATA_DEVICE_RELEASE_SINCE_VERSION 2


static inline void wl_data_device_set_user_data(struct wl_data_device *wl_data_device, void *user_data) {
	wl_proxy_set_user_data((struct wl_proxy *) wl_data_device, user_data);
}


static inline void* wl_data_device_get_user_data(struct wl_data_device *wl_data_device) {
	return wl_proxy_get_user_data((struct wl_proxy *) wl_data_device);
}

static inline uint32_t wl_data_device_get_version(struct wl_data_device *wl_data_device) {
	return wl_proxy_get_version((struct wl_proxy *) wl_data_device);
}


static inline void wl_data_device_destroy(struct wl_data_device *wl_data_device) {
	wl_proxy_destroy((struct wl_proxy *) wl_data_device);
}

static inline void wl_data_device_start_drag(struct wl_data_device *wl_data_device, struct wl_data_source *source, struct wl_surface *origin, struct wl_surface *icon, uint32_t serial) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_data_device,
			 WL_DATA_DEVICE_START_DRAG, NULL, wl_proxy_get_version((struct wl_proxy *) wl_data_device), 0, source, origin, icon, serial);
}


static inline void wl_data_device_set_selection(struct wl_data_device *wl_data_device, struct wl_data_source *source, uint32_t serial) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_data_device,
			 WL_DATA_DEVICE_SET_SELECTION, NULL, wl_proxy_get_version((struct wl_proxy *) wl_data_device), 0, source, serial);
}


static inline void wl_data_device_release(struct wl_data_device *wl_data_device) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_data_device,
			 WL_DATA_DEVICE_RELEASE, NULL, wl_proxy_get_version((struct wl_proxy *) wl_data_device), WL_MARSHAL_FLAG_DESTROY);
}

#ifndef WL_DATA_DEVICE_MANAGER_DND_ACTION_ENUM
#define WL_DATA_DEVICE_MANAGER_DND_ACTION_ENUM
enum wl_data_device_manager_dnd_action {
	WL_DATA_DEVICE_MANAGER_DND_ACTION_NONE = 0,
	WL_DATA_DEVICE_MANAGER_DND_ACTION_COPY = 1,
	WL_DATA_DEVICE_MANAGER_DND_ACTION_MOVE = 2,
	WL_DATA_DEVICE_MANAGER_DND_ACTION_ASK = 4,
};
#endif

#define WL_DATA_DEVICE_MANAGER_CREATE_DATA_SOURCE 0
#define WL_DATA_DEVICE_MANAGER_GET_DATA_DEVICE 1
#define WL_DATA_DEVICE_MANAGER_CREATE_DATA_SOURCE_SINCE_VERSION 1
#define WL_DATA_DEVICE_MANAGER_GET_DATA_DEVICE_SINCE_VERSION 1


static inline void wl_data_device_manager_set_user_data(struct wl_data_device_manager *wl_data_device_manager, void *user_data) {
	wl_proxy_set_user_data((struct wl_proxy *) wl_data_device_manager, user_data);
}


static inline void* wl_data_device_manager_get_user_data(struct wl_data_device_manager *wl_data_device_manager) {
	return wl_proxy_get_user_data((struct wl_proxy *) wl_data_device_manager);
}

static inline uint32_t wl_data_device_manager_get_version(struct wl_data_device_manager *wl_data_device_manager) {
	return wl_proxy_get_version((struct wl_proxy *) wl_data_device_manager);
}

static inline void wl_data_device_manager_destroy(struct wl_data_device_manager *wl_data_device_manager) {
	wl_proxy_destroy((struct wl_proxy *) wl_data_device_manager);
}


static inline struct wl_data_source* wl_data_device_manager_create_data_source(struct wl_data_device_manager *wl_data_device_manager) {
	struct wl_proxy *id;

	id = wl_proxy_marshal_flags((struct wl_proxy *) wl_data_device_manager,
			 WL_DATA_DEVICE_MANAGER_CREATE_DATA_SOURCE, &wl_data_source_interface, wl_proxy_get_version((struct wl_proxy *) wl_data_device_manager), 0, NULL);

	return (struct wl_data_source *) id;
}

static inline struct wl_data_device* wl_data_device_manager_get_data_device(struct wl_data_device_manager *wl_data_device_manager, struct wl_seat *seat) {
	struct wl_proxy *id;

	id = wl_proxy_marshal_flags((struct wl_proxy *) wl_data_device_manager,
			 WL_DATA_DEVICE_MANAGER_GET_DATA_DEVICE, &wl_data_device_interface, wl_proxy_get_version((struct wl_proxy *) wl_data_device_manager), 0, NULL, seat);

	return (struct wl_data_device *) id;
}

#ifndef WL_SHELL_ERROR_ENUM
#define WL_SHELL_ERROR_ENUM
enum wl_shell_error {
	WL_SHELL_ERROR_ROLE = 0,
};
#endif

#define WL_SHELL_GET_SHELL_SURFACE 0
#define WL_SHELL_GET_SHELL_SURFACE_SINCE_VERSION 1

static inline void wl_shell_set_user_data(struct wl_shell *wl_shell, void *user_data) {
	wl_proxy_set_user_data((struct wl_proxy *) wl_shell, user_data);
}


static inline void* wl_shell_get_user_data(struct wl_shell *wl_shell) {
	return wl_proxy_get_user_data((struct wl_proxy *) wl_shell);
}

static inline uint32_t wl_shell_get_version(struct wl_shell *wl_shell) {
	return wl_proxy_get_version((struct wl_proxy *) wl_shell);
}


static inline void wl_shell_destroy(struct wl_shell *wl_shell) {
	wl_proxy_destroy((struct wl_proxy *) wl_shell);
}


static inline struct wl_shell_surface* wl_shell_get_shell_surface(struct wl_shell *wl_shell, struct wl_surface *surface) {
	struct wl_proxy *id;

	id = wl_proxy_marshal_flags((struct wl_proxy *) wl_shell,
			 WL_SHELL_GET_SHELL_SURFACE, &wl_shell_surface_interface, wl_proxy_get_version((struct wl_proxy *) wl_shell), 0, NULL, surface);

	return (struct wl_shell_surface *) id;
}

#ifndef WL_SHELL_SURFACE_RESIZE_ENUM
#define WL_SHELL_SURFACE_RESIZE_ENUM
enum wl_shell_surface_resize {
	WL_SHELL_SURFACE_RESIZE_NONE = 0,
	WL_SHELL_SURFACE_RESIZE_TOP = 1,
	WL_SHELL_SURFACE_RESIZE_BOTTOM = 2,
	WL_SHELL_SURFACE_RESIZE_LEFT = 4,
	WL_SHELL_SURFACE_RESIZE_TOP_LEFT = 5,
	WL_SHELL_SURFACE_RESIZE_BOTTOM_LEFT = 6,
	WL_SHELL_SURFACE_RESIZE_RIGHT = 8,
	WL_SHELL_SURFACE_RESIZE_TOP_RIGHT = 9,
	WL_SHELL_SURFACE_RESIZE_BOTTOM_RIGHT = 10,
};
#endif

#ifndef WL_SHELL_SURFACE_TRANSIENT_ENUM
#define WL_SHELL_SURFACE_TRANSIENT_ENUM
enum wl_shell_surface_transient {
	WL_SHELL_SURFACE_TRANSIENT_INACTIVE = 0x1,
};
#endif

#ifndef WL_SHELL_SURFACE_FULLSCREEN_METHOD_ENUM
#define WL_SHELL_SURFACE_FULLSCREEN_METHOD_ENUM
enum wl_shell_surface_fullscreen_method {
	WL_SHELL_SURFACE_FULLSCREEN_METHOD_DEFAULT = 0,
	WL_SHELL_SURFACE_FULLSCREEN_METHOD_SCALE = 1,
	WL_SHELL_SURFACE_FULLSCREEN_METHOD_DRIVER = 2,
	WL_SHELL_SURFACE_FULLSCREEN_METHOD_FILL = 3,
};
#endif

struct wl_shell_surface_listener {
	void (*ping)(void *data,
		     struct wl_shell_surface *wl_shell_surface,
		     uint32_t serial);

	void (*configure)(void *data,
			  struct wl_shell_surface *wl_shell_surface,
			  uint32_t edges,
			  int32_t width,
			  int32_t height);

	void (*popup_done)(void *data,
			   struct wl_shell_surface *wl_shell_surface);
};


static inline int wl_shell_surface_add_listener(struct wl_shell_surface *wl_shell_surface, const struct wl_shell_surface_listener *listener, void *data) {
	return wl_proxy_add_listener((struct wl_proxy *) wl_shell_surface,
				     (void (**)(void)) listener, data);
}

#define WL_SHELL_SURFACE_PONG 0
#define WL_SHELL_SURFACE_MOVE 1
#define WL_SHELL_SURFACE_RESIZE 2
#define WL_SHELL_SURFACE_SET_TOPLEVEL 3
#define WL_SHELL_SURFACE_SET_TRANSIENT 4
#define WL_SHELL_SURFACE_SET_FULLSCREEN 5
#define WL_SHELL_SURFACE_SET_POPUP 6
#define WL_SHELL_SURFACE_SET_MAXIMIZED 7
#define WL_SHELL_SURFACE_SET_TITLE 8
#define WL_SHELL_SURFACE_SET_CLASS 9
#define WL_SHELL_SURFACE_PING_SINCE_VERSION 1
#define WL_SHELL_SURFACE_CONFIGURE_SINCE_VERSION 1
#define WL_SHELL_SURFACE_POPUP_DONE_SINCE_VERSION 1
#define WL_SHELL_SURFACE_PONG_SINCE_VERSION 1
#define WL_SHELL_SURFACE_MOVE_SINCE_VERSION 1
#define WL_SHELL_SURFACE_RESIZE_SINCE_VERSION 1
#define WL_SHELL_SURFACE_SET_TOPLEVEL_SINCE_VERSION 1
#define WL_SHELL_SURFACE_SET_TRANSIENT_SINCE_VERSION 1
#define WL_SHELL_SURFACE_SET_FULLSCREEN_SINCE_VERSION 1
#define WL_SHELL_SURFACE_SET_POPUP_SINCE_VERSION 1
#define WL_SHELL_SURFACE_SET_MAXIMIZED_SINCE_VERSION 1
#define WL_SHELL_SURFACE_SET_TITLE_SINCE_VERSION 1
#define WL_SHELL_SURFACE_SET_CLASS_SINCE_VERSION 1


static inline void wl_shell_surface_set_user_data(struct wl_shell_surface *wl_shell_surface, void *user_data) {
	wl_proxy_set_user_data((struct wl_proxy *) wl_shell_surface, user_data);
}


static inline void* wl_shell_surface_get_user_data(struct wl_shell_surface *wl_shell_surface) {
	return wl_proxy_get_user_data((struct wl_proxy *) wl_shell_surface);
}

static inline uint32_t wl_shell_surface_get_version(struct wl_shell_surface *wl_shell_surface) {
	return wl_proxy_get_version((struct wl_proxy *) wl_shell_surface);
}


static inline void wl_shell_surface_destroy(struct wl_shell_surface *wl_shell_surface) {
	wl_proxy_destroy((struct wl_proxy *) wl_shell_surface);
}


static inline void wl_shell_surface_pong(struct wl_shell_surface *wl_shell_surface, uint32_t serial) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_shell_surface,
			 WL_SHELL_SURFACE_PONG, NULL, wl_proxy_get_version((struct wl_proxy *) wl_shell_surface), 0, serial);
}


static inline void wl_shell_surface_move(struct wl_shell_surface *wl_shell_surface, struct wl_seat *seat, uint32_t serial) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_shell_surface,
			 WL_SHELL_SURFACE_MOVE, NULL, wl_proxy_get_version((struct wl_proxy *) wl_shell_surface), 0, seat, serial);
}


static inline void wl_shell_surface_resize(struct wl_shell_surface *wl_shell_surface, struct wl_seat *seat, uint32_t serial, uint32_t edges) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_shell_surface,
			 WL_SHELL_SURFACE_RESIZE, NULL, wl_proxy_get_version((struct wl_proxy *) wl_shell_surface), 0, seat, serial, edges);
}


static inline void wl_shell_surface_set_toplevel(struct wl_shell_surface *wl_shell_surface) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_shell_surface,
			 WL_SHELL_SURFACE_SET_TOPLEVEL, NULL, wl_proxy_get_version((struct wl_proxy *) wl_shell_surface), 0);
}


static inline void wl_shell_surface_set_transient(struct wl_shell_surface *wl_shell_surface, struct wl_surface *parent, int32_t x, int32_t y, uint32_t flags) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_shell_surface,
			 WL_SHELL_SURFACE_SET_TRANSIENT, NULL, wl_proxy_get_version((struct wl_proxy *) wl_shell_surface), 0, parent, x, y, flags);
}

static inline void wl_shell_surface_set_fullscreen(struct wl_shell_surface *wl_shell_surface, uint32_t method, uint32_t framerate, struct wl_output *output) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_shell_surface,
			 WL_SHELL_SURFACE_SET_FULLSCREEN, NULL, wl_proxy_get_version((struct wl_proxy *) wl_shell_surface), 0, method, framerate, output);
}


static inline void wl_shell_surface_set_popup(struct wl_shell_surface *wl_shell_surface, struct wl_seat *seat, uint32_t serial, struct wl_surface *parent, int32_t x, int32_t y, uint32_t flags) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_shell_surface,
			 WL_SHELL_SURFACE_SET_POPUP, NULL, wl_proxy_get_version((struct wl_proxy *) wl_shell_surface), 0, seat, serial, parent, x, y, flags);
}


static inline void wl_shell_surface_set_maximized(struct wl_shell_surface *wl_shell_surface, struct wl_output *output) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_shell_surface,
			 WL_SHELL_SURFACE_SET_MAXIMIZED, NULL, wl_proxy_get_version((struct wl_proxy *) wl_shell_surface), 0, output);
}

static inline void wl_shell_surface_set_title(struct wl_shell_surface *wl_shell_surface, const char *title) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_shell_surface,
			 WL_SHELL_SURFACE_SET_TITLE, NULL, wl_proxy_get_version((struct wl_proxy *) wl_shell_surface), 0, title);
}


static inline void wl_shell_surface_set_class(struct wl_shell_surface *wl_shell_surface, const char *class_) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_shell_surface,
			 WL_SHELL_SURFACE_SET_CLASS, NULL, wl_proxy_get_version((struct wl_proxy *) wl_shell_surface), 0, class_);
}

#ifndef WL_SURFACE_ERROR_ENUM
#define WL_SURFACE_ERROR_ENUM
enum wl_surface_error {
	WL_SURFACE_ERROR_INVALID_SCALE = 0,
	WL_SURFACE_ERROR_INVALID_TRANSFORM = 1,
	WL_SURFACE_ERROR_INVALID_SIZE = 2,
	WL_SURFACE_ERROR_INVALID_OFFSET = 3,
	WL_SURFACE_ERROR_DEFUNCT_ROLE_OBJECT = 4,
};
#endif


struct wl_surface_listener {
	void (*enter)(void *data,
		      struct wl_surface *wl_surface,
		      struct wl_output *output);

	void (*leave)(void *data,
		      struct wl_surface *wl_surface,
		      struct wl_output *output);

	void (*preferred_buffer_scale)(void *data,
				       struct wl_surface *wl_surface,
				       int32_t factor);

	void (*preferred_buffer_transform)(void *data,
					   struct wl_surface *wl_surface,
					   uint32_t transform);
};


static inline int wl_surface_add_listener(struct wl_surface *wl_surface, const struct wl_surface_listener *listener, void *data) {
	return wl_proxy_add_listener((struct wl_proxy *) wl_surface,
				     (void (**)(void)) listener, data);
}

#define WL_SURFACE_DESTROY 0
#define WL_SURFACE_ATTACH 1
#define WL_SURFACE_DAMAGE 2
#define WL_SURFACE_FRAME 3
#define WL_SURFACE_SET_OPAQUE_REGION 4
#define WL_SURFACE_SET_INPUT_REGION 5
#define WL_SURFACE_COMMIT 6
#define WL_SURFACE_SET_BUFFER_TRANSFORM 7
#define WL_SURFACE_SET_BUFFER_SCALE 8
#define WL_SURFACE_DAMAGE_BUFFER 9
#define WL_SURFACE_OFFSET 10
#define WL_SURFACE_ENTER_SINCE_VERSION 1
#define WL_SURFACE_LEAVE_SINCE_VERSION 1
#define WL_SURFACE_PREFERRED_BUFFER_SCALE_SINCE_VERSION 6
#define WL_SURFACE_PREFERRED_BUFFER_TRANSFORM_SINCE_VERSION 6
#define WL_SURFACE_DESTROY_SINCE_VERSION 1
#define WL_SURFACE_ATTACH_SINCE_VERSION 1
#define WL_SURFACE_DAMAGE_SINCE_VERSION 1
#define WL_SURFACE_FRAME_SINCE_VERSION 1
#define WL_SURFACE_SET_OPAQUE_REGION_SINCE_VERSION 1
#define WL_SURFACE_SET_INPUT_REGION_SINCE_VERSION 1
#define WL_SURFACE_COMMIT_SINCE_VERSION 1
#define WL_SURFACE_SET_BUFFER_TRANSFORM_SINCE_VERSION 2
#define WL_SURFACE_SET_BUFFER_SCALE_SINCE_VERSION 3
#define WL_SURFACE_DAMAGE_BUFFER_SINCE_VERSION 4
#define WL_SURFACE_OFFSET_SINCE_VERSION 5

static inline void wl_surface_set_user_data(struct wl_surface *wl_surface, void *user_data) {
	wl_proxy_set_user_data((struct wl_proxy *) wl_surface, user_data);
}


static inline void* wl_surface_get_user_data(struct wl_surface *wl_surface) {
	return wl_proxy_get_user_data((struct wl_proxy *) wl_surface);
}

static inline uint32_t wl_surface_get_version(struct wl_surface *wl_surface) {
	return wl_proxy_get_version((struct wl_proxy *) wl_surface);
}

static inline void wl_surface_destroy(struct wl_surface *wl_surface) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_surface,
			 WL_SURFACE_DESTROY, NULL, wl_proxy_get_version((struct wl_proxy *) wl_surface), WL_MARSHAL_FLAG_DESTROY);
}


static inline void wl_surface_attach(struct wl_surface *wl_surface, struct wl_buffer *buffer, int32_t x, int32_t y) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_surface,
			 WL_SURFACE_ATTACH, NULL, wl_proxy_get_version((struct wl_proxy *) wl_surface), 0, buffer, x, y);
}

static inline void wl_surface_damage(struct wl_surface *wl_surface, int32_t x, int32_t y, int32_t width, int32_t height) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_surface,
			 WL_SURFACE_DAMAGE, NULL, wl_proxy_get_version((struct wl_proxy *) wl_surface), 0, x, y, width, height);
}

static inline struct wl_callback* wl_surface_frame(struct wl_surface *wl_surface) {
	struct wl_proxy *callback;

	callback = wl_proxy_marshal_flags((struct wl_proxy *) wl_surface,
			 WL_SURFACE_FRAME, &wl_callback_interface, wl_proxy_get_version((struct wl_proxy *) wl_surface), 0, NULL);

	return (struct wl_callback *) callback;
}

static inline void wl_surface_set_opaque_region(struct wl_surface *wl_surface, struct wl_region *region) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_surface,
			 WL_SURFACE_SET_OPAQUE_REGION, NULL, wl_proxy_get_version((struct wl_proxy *) wl_surface), 0, region);
}

static inline void wl_surface_set_input_region(struct wl_surface *wl_surface, struct wl_region *region) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_surface,
			 WL_SURFACE_SET_INPUT_REGION, NULL, wl_proxy_get_version((struct wl_proxy *) wl_surface), 0, region);
}

static inline void wl_surface_commit(struct wl_surface *wl_surface) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_surface,
			 WL_SURFACE_COMMIT, NULL, wl_proxy_get_version((struct wl_proxy *) wl_surface), 0);
}

static inline void wl_surface_set_buffer_transform(struct wl_surface *wl_surface, int32_t transform) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_surface,
			 WL_SURFACE_SET_BUFFER_TRANSFORM, NULL, wl_proxy_get_version((struct wl_proxy *) wl_surface), 0, transform);
}

static inline void wl_surface_set_buffer_scale(struct wl_surface *wl_surface, int32_t scale) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_surface,
			 WL_SURFACE_SET_BUFFER_SCALE, NULL, wl_proxy_get_version((struct wl_proxy *) wl_surface), 0, scale);
}

static inline void wl_surface_damage_buffer(struct wl_surface *wl_surface, int32_t x, int32_t y, int32_t width, int32_t height) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_surface,
			 WL_SURFACE_DAMAGE_BUFFER, NULL, wl_proxy_get_version((struct wl_proxy *) wl_surface), 0, x, y, width, height);
}

static inline void wl_surface_offset(struct wl_surface *wl_surface, int32_t x, int32_t y) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_surface,
			 WL_SURFACE_OFFSET, NULL, wl_proxy_get_version((struct wl_proxy *) wl_surface), 0, x, y);
}

#ifndef WL_SEAT_CAPABILITY_ENUM
#define WL_SEAT_CAPABILITY_ENUM
enum wl_seat_capability {
	WL_SEAT_CAPABILITY_POINTER = 1,
	WL_SEAT_CAPABILITY_KEYBOARD = 2,
	WL_SEAT_CAPABILITY_TOUCH = 4,
};
#endif

#ifndef WL_SEAT_ERROR_ENUM
#define WL_SEAT_ERROR_ENUM
enum wl_seat_error {
	WL_SEAT_ERROR_MISSING_CAPABILITY = 0,
};
#endif

struct wl_seat_listener {

	void (*capabilities)(void *data,
			     struct wl_seat *wl_seat,
			     uint32_t capabilities);

	void (*name)(void *data,
		     struct wl_seat *wl_seat,
		     const char *name);
};

static inline int wl_seat_add_listener(struct wl_seat *wl_seat,
		     const struct wl_seat_listener *listener, void *data) {
	return wl_proxy_add_listener((struct wl_proxy *) wl_seat,
				     (void (**)(void)) listener, data);
}

#define WL_SEAT_GET_POINTER 0
#define WL_SEAT_GET_KEYBOARD 1
#define WL_SEAT_GET_TOUCH 2
#define WL_SEAT_RELEASE 3
#define WL_SEAT_CAPABILITIES_SINCE_VERSION 1
#define WL_SEAT_NAME_SINCE_VERSION 2
#define WL_SEAT_GET_POINTER_SINCE_VERSION 1
#define WL_SEAT_GET_KEYBOARD_SINCE_VERSION 1
#define WL_SEAT_GET_TOUCH_SINCE_VERSION 1
#define WL_SEAT_RELEASE_SINCE_VERSION 5

static inline void wl_seat_set_user_data(struct wl_seat *wl_seat, void *user_data) {
	wl_proxy_set_user_data((struct wl_proxy *) wl_seat, user_data);
}

static inline void* wl_seat_get_user_data(struct wl_seat *wl_seat) {
	return wl_proxy_get_user_data((struct wl_proxy *) wl_seat);
}

static inline uint32_t wl_seat_get_version(struct wl_seat *wl_seat) {
	return wl_proxy_get_version((struct wl_proxy *) wl_seat);
}

static inline void wl_seat_destroy(struct wl_seat *wl_seat) {
	wl_proxy_destroy((struct wl_proxy *) wl_seat);
}

static inline struct wl_pointer* wl_seat_get_pointer(struct wl_seat *wl_seat) {
	struct wl_proxy *id;

	id = wl_proxy_marshal_flags((struct wl_proxy *) wl_seat,
			 WL_SEAT_GET_POINTER, &wl_pointer_interface, wl_proxy_get_version((struct wl_proxy *) wl_seat), 0, NULL);

	return (struct wl_pointer *) id;
}

static inline struct wl_keyboard* wl_seat_get_keyboard(struct wl_seat *wl_seat) {
	struct wl_proxy *id;

	id = wl_proxy_marshal_flags((struct wl_proxy *) wl_seat,
			 WL_SEAT_GET_KEYBOARD, &wl_keyboard_interface, wl_proxy_get_version((struct wl_proxy *) wl_seat), 0, NULL);

	return (struct wl_keyboard *) id;
}

static inline struct wl_touch* wl_seat_get_touch(struct wl_seat *wl_seat) {
	struct wl_proxy *id;

	id = wl_proxy_marshal_flags((struct wl_proxy *) wl_seat,
			 WL_SEAT_GET_TOUCH, &wl_touch_interface, wl_proxy_get_version((struct wl_proxy *) wl_seat), 0, NULL);

	return (struct wl_touch *) id;
}

static inline void wl_seat_release(struct wl_seat *wl_seat) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_seat,
			 WL_SEAT_RELEASE, NULL, wl_proxy_get_version((struct wl_proxy *) wl_seat), WL_MARSHAL_FLAG_DESTROY);
}

#ifndef WL_POINTER_ERROR_ENUM
#define WL_POINTER_ERROR_ENUM
enum wl_pointer_error {
	WL_POINTER_ERROR_ROLE = 0,
};
#endif

#ifndef WL_POINTER_BUTTON_STATE_ENUM
#define WL_POINTER_BUTTON_STATE_ENUM

enum wl_pointer_button_state {
	WL_POINTER_BUTTON_STATE_RELEASED = 0,
	WL_POINTER_BUTTON_STATE_PRESSED = 1,
};
#endif

#ifndef WL_POINTER_AXIS_ENUM
#define WL_POINTER_AXIS_ENUM

enum wl_pointer_axis {
	WL_POINTER_AXIS_VERTICAL_SCROLL = 0,
	WL_POINTER_AXIS_HORIZONTAL_SCROLL = 1,
};
#endif

#ifndef WL_POINTER_AXIS_SOURCE_ENUM
#define WL_POINTER_AXIS_SOURCE_ENUM

enum wl_pointer_axis_source {
	WL_POINTER_AXIS_SOURCE_WHEEL = 0,
	WL_POINTER_AXIS_SOURCE_FINGER = 1,
	WL_POINTER_AXIS_SOURCE_CONTINUOUS = 2,
	WL_POINTER_AXIS_SOURCE_WHEEL_TILT = 3,
};

#define WL_POINTER_AXIS_SOURCE_WHEEL_TILT_SINCE_VERSION 6
#endif

#ifndef WL_POINTER_AXIS_RELATIVE_DIRECTION_ENUM
#define WL_POINTER_AXIS_RELATIVE_DIRECTION_ENUM

enum wl_pointer_axis_relative_direction {
	WL_POINTER_AXIS_RELATIVE_DIRECTION_IDENTICAL = 0,
	WL_POINTER_AXIS_RELATIVE_DIRECTION_INVERTED = 1,
};
#endif

struct wl_pointer_listener {
	void (*enter)(void *data,
		      struct wl_pointer *wl_pointer,
		      uint32_t serial,
		      struct wl_surface *surface,
		      wl_fixed_t surface_x,
		      wl_fixed_t surface_y);

	void (*leave)(void *data,
		      struct wl_pointer *wl_pointer,
		      uint32_t serial,
		      struct wl_surface *surface);

	void (*motion)(void *data,
		       struct wl_pointer *wl_pointer,
		       uint32_t time,
		       wl_fixed_t surface_x,
		       wl_fixed_t surface_y);

	void (*button)(void *data,
		       struct wl_pointer *wl_pointer,
		       uint32_t serial,
		       uint32_t time,
		       uint32_t button,
		       uint32_t state);

	void (*axis)(void *data,
		     struct wl_pointer *wl_pointer,
		     uint32_t time,
		     uint32_t axis,
		     wl_fixed_t value);

	void (*frame)(void *data,
		      struct wl_pointer *wl_pointer);

	void (*axis_source)(void *data,
			    struct wl_pointer *wl_pointer,
			    uint32_t axis_source);

	void (*axis_stop)(void *data,
			  struct wl_pointer *wl_pointer,
			  uint32_t time,
			  uint32_t axis);

	void (*axis_discrete)(void *data,
			      struct wl_pointer *wl_pointer,
			      uint32_t axis,
			      int32_t discrete);

	void (*axis_value120)(void *data,
			      struct wl_pointer *wl_pointer,
			      uint32_t axis,
			      int32_t value120);

	void (*axis_relative_direction)(void *data,
					struct wl_pointer *wl_pointer,
					uint32_t axis,
					uint32_t direction);
};

static inline int
wl_pointer_add_listener(struct wl_pointer *wl_pointer,
			const struct wl_pointer_listener *listener, void *data)
{
	return wl_proxy_add_listener((struct wl_proxy *) wl_pointer,
				     (void (**)(void)) listener, data);
}

#define WL_POINTER_SET_CURSOR 0
#define WL_POINTER_RELEASE 1

#define WL_POINTER_ENTER_SINCE_VERSION 1
#define WL_POINTER_LEAVE_SINCE_VERSION 1
#define WL_POINTER_MOTION_SINCE_VERSION 1
#define WL_POINTER_BUTTON_SINCE_VERSION 1
#define WL_POINTER_AXIS_SINCE_VERSION 1
#define WL_POINTER_FRAME_SINCE_VERSION 5
#define WL_POINTER_AXIS_SOURCE_SINCE_VERSION 5
#define WL_POINTER_AXIS_STOP_SINCE_VERSION 5
#define WL_POINTER_AXIS_DISCRETE_SINCE_VERSION 5
#define WL_POINTER_AXIS_VALUE120_SINCE_VERSION 8
#define WL_POINTER_AXIS_RELATIVE_DIRECTION_SINCE_VERSION 9
#define WL_POINTER_SET_CURSOR_SINCE_VERSION 1
#define WL_POINTER_RELEASE_SINCE_VERSION 3


static inline void wl_pointer_set_user_data(struct wl_pointer *wl_pointer, void *user_data) {
	wl_proxy_set_user_data((struct wl_proxy *) wl_pointer, user_data);
}

static inline void* wl_pointer_get_user_data(struct wl_pointer *wl_pointer) {
	return wl_proxy_get_user_data((struct wl_proxy *) wl_pointer);
}

static inline uint32_t wl_pointer_get_version(struct wl_pointer *wl_pointer) {
	return wl_proxy_get_version((struct wl_proxy *) wl_pointer);
}

static inline void wl_pointer_destroy(struct wl_pointer *wl_pointer) {
	wl_proxy_destroy((struct wl_proxy *) wl_pointer);
}

static inline void wl_pointer_set_cursor(struct wl_pointer *wl_pointer, uint32_t serial, struct wl_surface *surface, int32_t hotspot_x, int32_t hotspot_y) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_pointer,
			 WL_POINTER_SET_CURSOR, NULL, wl_proxy_get_version((struct wl_proxy *) wl_pointer), 0, serial, surface, hotspot_x, hotspot_y);
}

static inline void wl_pointer_release(struct wl_pointer *wl_pointer) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_pointer,
			 WL_POINTER_RELEASE, NULL, wl_proxy_get_version((struct wl_proxy *) wl_pointer), WL_MARSHAL_FLAG_DESTROY);
}

#ifndef WL_KEYBOARD_KEYMAP_FORMAT_ENUM
#define WL_KEYBOARD_KEYMAP_FORMAT_ENUM
enum wl_keyboard_keymap_format {
	WL_KEYBOARD_KEYMAP_FORMAT_NO_KEYMAP = 0,
	WL_KEYBOARD_KEYMAP_FORMAT_XKB_V1 = 1,
};
#endif

#ifndef WL_KEYBOARD_KEY_STATE_ENUM
#define WL_KEYBOARD_KEY_STATE_ENUM
enum wl_keyboard_key_state {
	WL_KEYBOARD_KEY_STATE_RELEASED = 0,
	WL_KEYBOARD_KEY_STATE_PRESSED = 1,
	WL_KEYBOARD_KEY_STATE_REPEATED = 2,
};
#define WL_KEYBOARD_KEY_STATE_REPEATED_SINCE_VERSION 10
#endif

struct wl_keyboard_listener {
	void (*keymap)(void *data,
		       struct wl_keyboard *wl_keyboard,
		       uint32_t format,
		       int32_t fd,
		       uint32_t size);

	void (*enter)(void *data,
		      struct wl_keyboard *wl_keyboard,
		      uint32_t serial,
		      struct wl_surface *surface,
		      struct wl_array *keys);

	void (*leave)(void *data,
		      struct wl_keyboard *wl_keyboard,
		      uint32_t serial,
		      struct wl_surface *surface);

	void (*key)(void *data,
		    struct wl_keyboard *wl_keyboard,
		    uint32_t serial,
		    uint32_t time,
		    uint32_t key,
		    uint32_t state);

	void (*modifiers)(void *data,
			  struct wl_keyboard *wl_keyboard,
			  uint32_t serial,
			  uint32_t mods_depressed,
			  uint32_t mods_latched,
			  uint32_t mods_locked,
			  uint32_t group);

	void (*repeat_info)(void *data,
			    struct wl_keyboard *wl_keyboard,
			    int32_t rate,
			    int32_t delay);
};


static inline int wl_keyboard_add_listener(struct wl_keyboard *wl_keyboard,
			 const struct wl_keyboard_listener *listener, void *data) {
	return wl_proxy_add_listener((struct wl_proxy *) wl_keyboard,
				     (void (**)(void)) listener, data);
}

#define WL_KEYBOARD_RELEASE 0
#define WL_KEYBOARD_KEYMAP_SINCE_VERSION 1
#define WL_KEYBOARD_ENTER_SINCE_VERSION 1
#define WL_KEYBOARD_LEAVE_SINCE_VERSION 1
#define WL_KEYBOARD_KEY_SINCE_VERSION 1
#define WL_KEYBOARD_MODIFIERS_SINCE_VERSION 1
#define WL_KEYBOARD_REPEAT_INFO_SINCE_VERSION 4
#define WL_KEYBOARD_RELEASE_SINCE_VERSION 3

static inline void
wl_keyboard_set_user_data(struct wl_keyboard *wl_keyboard, void *user_data) {
	wl_proxy_set_user_data((struct wl_proxy *) wl_keyboard, user_data);
}

static inline void* wl_keyboard_get_user_data(struct wl_keyboard *wl_keyboard) {
	return wl_proxy_get_user_data((struct wl_proxy *) wl_keyboard);
}

static inline uint32_t wl_keyboard_get_version(struct wl_keyboard *wl_keyboard) {
	return wl_proxy_get_version((struct wl_proxy *) wl_keyboard);
}

static inline void wl_keyboard_destroy(struct wl_keyboard *wl_keyboard) {
	wl_proxy_destroy((struct wl_proxy *) wl_keyboard);
}

static inline void wl_keyboard_release(struct wl_keyboard *wl_keyboard) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_keyboard,
			 WL_KEYBOARD_RELEASE, NULL, wl_proxy_get_version((struct wl_proxy *) wl_keyboard), WL_MARSHAL_FLAG_DESTROY);
}

struct wl_touch_listener {
	void (*down)(void *data,
		     struct wl_touch *wl_touch,
		     uint32_t serial,
		     uint32_t time,
		     struct wl_surface *surface,
		     int32_t id,
		     wl_fixed_t x,
		     wl_fixed_t y);

	void (*up)(void *data,
		   struct wl_touch *wl_touch,
		   uint32_t serial,
		   uint32_t time,
		   int32_t id);

	void (*motion)(void *data,
		       struct wl_touch *wl_touch,
		       uint32_t time,
		       int32_t id,
		       wl_fixed_t x,
		       wl_fixed_t y);

	void (*frame)(void *data,
		      struct wl_touch *wl_touch);

	void (*cancel)(void *data,
		       struct wl_touch *wl_touch);

	void (*shape)(void *data,
		      struct wl_touch *wl_touch,
		      int32_t id,
		      wl_fixed_t major,
		      wl_fixed_t minor);

	void (*orientation)(void *data,
			    struct wl_touch *wl_touch,
			    int32_t id,
			    wl_fixed_t orientation);
};


static inline int wl_touch_add_listener(struct wl_touch *wl_touch,
		      const struct wl_touch_listener *listener, void *data) {
	return wl_proxy_add_listener((struct wl_proxy *) wl_touch,
				     (void (**)(void)) listener, data);
}

#define WL_TOUCH_RELEASE 0
#define WL_TOUCH_DOWN_SINCE_VERSION 1
#define WL_TOUCH_UP_SINCE_VERSION 1
#define WL_TOUCH_MOTION_SINCE_VERSION 1
#define WL_TOUCH_FRAME_SINCE_VERSION 1
#define WL_TOUCH_CANCEL_SINCE_VERSION 1
#define WL_TOUCH_SHAPE_SINCE_VERSION 6
#define WL_TOUCH_ORIENTATION_SINCE_VERSION 6
#define WL_TOUCH_RELEASE_SINCE_VERSION 3

static inline void wl_touch_set_user_data(struct wl_touch *wl_touch, void *user_data) {
	wl_proxy_set_user_data((struct wl_proxy *) wl_touch, user_data);
}

static inline void* wl_touch_get_user_data(struct wl_touch *wl_touch) {
	return wl_proxy_get_user_data((struct wl_proxy *) wl_touch);
}

static inline uint32_t wl_touch_get_version(struct wl_touch *wl_touch) {
	return wl_proxy_get_version((struct wl_proxy *) wl_touch);
}

static inline void wl_touch_destroy(struct wl_touch *wl_touch) {
	wl_proxy_destroy((struct wl_proxy *) wl_touch);
}

static inline void wl_touch_release(struct wl_touch *wl_touch) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_touch,
			 WL_TOUCH_RELEASE, NULL, wl_proxy_get_version((struct wl_proxy *) wl_touch), WL_MARSHAL_FLAG_DESTROY);
}

#ifndef WL_OUTPUT_SUBPIXEL_ENUM
#define WL_OUTPUT_SUBPIXEL_ENUM

enum wl_output_subpixel {
	WL_OUTPUT_SUBPIXEL_UNKNOWN = 0,
	WL_OUTPUT_SUBPIXEL_NONE = 1,
	WL_OUTPUT_SUBPIXEL_HORIZONTAL_RGB = 2,
	WL_OUTPUT_SUBPIXEL_HORIZONTAL_BGR = 3,
	WL_OUTPUT_SUBPIXEL_VERTICAL_RGB = 4,
	WL_OUTPUT_SUBPIXEL_VERTICAL_BGR = 5,
};
#endif

#ifndef WL_OUTPUT_TRANSFORM_ENUM
#define WL_OUTPUT_TRANSFORM_ENUM

enum wl_output_transform {
	WL_OUTPUT_TRANSFORM_NORMAL = 0,
	WL_OUTPUT_TRANSFORM_90 = 1,
	WL_OUTPUT_TRANSFORM_180 = 2,
	WL_OUTPUT_TRANSFORM_270 = 3,
	WL_OUTPUT_TRANSFORM_FLIPPED = 4,
	WL_OUTPUT_TRANSFORM_FLIPPED_90 = 5,
	WL_OUTPUT_TRANSFORM_FLIPPED_180 = 6,
	WL_OUTPUT_TRANSFORM_FLIPPED_270 = 7,
};
#endif

#ifndef WL_OUTPUT_MODE_ENUM
#define WL_OUTPUT_MODE_ENUM

enum wl_output_mode {
	WL_OUTPUT_MODE_CURRENT = 0x1,
	WL_OUTPUT_MODE_PREFERRED = 0x2,
};
#endif

struct wl_output_listener {
	void (*geometry)(void *data,
			 struct wl_output *wl_output,
			 int32_t x,
			 int32_t y,
			 int32_t physical_width,
			 int32_t physical_height,
			 int32_t subpixel,
			 const char *make,
			 const char *model,
			 int32_t transform);

	void (*mode)(void *data,
		     struct wl_output *wl_output,
		     uint32_t flags,
		     int32_t width,
		     int32_t height,
		     int32_t refresh);

	void (*done)(void *data,
		     struct wl_output *wl_output);

	void (*scale)(void *data,
		      struct wl_output *wl_output,
		      int32_t factor);

	void (*name)(void *data,
		     struct wl_output *wl_output,
		     const char *name);

	void (*description)(void *data,
			    struct wl_output *wl_output,
			    const char *description);
};

static inline int wl_output_add_listener(struct wl_output *wl_output,
		       const struct wl_output_listener *listener, void *data) {
	return wl_proxy_add_listener((struct wl_proxy *) wl_output,
				     (void (**)(void)) listener, data);
}

#define WL_OUTPUT_RELEASE 0
#define WL_OUTPUT_GEOMETRY_SINCE_VERSION 1
#define WL_OUTPUT_MODE_SINCE_VERSION 1
#define WL_OUTPUT_DONE_SINCE_VERSION 2
#define WL_OUTPUT_SCALE_SINCE_VERSION 2
#define WL_OUTPUT_NAME_SINCE_VERSION 4
#define WL_OUTPUT_DESCRIPTION_SINCE_VERSION 4
#define WL_OUTPUT_RELEASE_SINCE_VERSION 3


static inline void wl_output_set_user_data(struct wl_output *wl_output, void *user_data) {
	wl_proxy_set_user_data((struct wl_proxy *) wl_output, user_data);
}

static inline void* wl_output_get_user_data(struct wl_output *wl_output) {
	return wl_proxy_get_user_data((struct wl_proxy *) wl_output);
}

static inline uint32_t wl_output_get_version(struct wl_output *wl_output) {
	return wl_proxy_get_version((struct wl_proxy *) wl_output);
}

static inline void wl_output_destroy(struct wl_output *wl_output) {
	wl_proxy_destroy((struct wl_proxy *) wl_output);
}

static inline void wl_output_release(struct wl_output *wl_output) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_output,
			 WL_OUTPUT_RELEASE, NULL, wl_proxy_get_version((struct wl_proxy *) wl_output), WL_MARSHAL_FLAG_DESTROY);
}

#define WL_REGION_DESTROY 0
#define WL_REGION_ADD 1
#define WL_REGION_SUBTRACT 2
#define WL_REGION_DESTROY_SINCE_VERSION 1
#define WL_REGION_ADD_SINCE_VERSION 1
#define WL_REGION_SUBTRACT_SINCE_VERSION 1

static inline void wl_region_set_user_data(struct wl_region *wl_region, void *user_data) {
	wl_proxy_set_user_data((struct wl_proxy *) wl_region, user_data);
}

static inline void* wl_region_get_user_data(struct wl_region *wl_region) {
	return wl_proxy_get_user_data((struct wl_proxy *) wl_region);
}

static inline uint32_t wl_region_get_version(struct wl_region *wl_region) {
	return wl_proxy_get_version((struct wl_proxy *) wl_region);
}

static inline void wl_region_destroy(struct wl_region *wl_region) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_region,
			 WL_REGION_DESTROY, NULL, wl_proxy_get_version((struct wl_proxy *) wl_region), WL_MARSHAL_FLAG_DESTROY);
}

static inline void wl_region_add(struct wl_region *wl_region, int32_t x, int32_t y, int32_t width, int32_t height) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_region,
			 WL_REGION_ADD, NULL, wl_proxy_get_version((struct wl_proxy *) wl_region), 0, x, y, width, height);
}

static inline void wl_region_subtract(struct wl_region *wl_region, int32_t x, int32_t y, int32_t width, int32_t height) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_region,
			 WL_REGION_SUBTRACT, NULL, wl_proxy_get_version((struct wl_proxy *) wl_region), 0, x, y, width, height);
}

#ifndef WL_SUBCOMPOSITOR_ERROR_ENUM
#define WL_SUBCOMPOSITOR_ERROR_ENUM
enum wl_subcompositor_error {
	WL_SUBCOMPOSITOR_ERROR_BAD_SURFACE = 0,
	WL_SUBCOMPOSITOR_ERROR_BAD_PARENT = 1,
};
#endif
#define WL_SUBCOMPOSITOR_DESTROY 0
#define WL_SUBCOMPOSITOR_GET_SUBSURFACE 1
#define WL_SUBCOMPOSITOR_DESTROY_SINCE_VERSION 1
#define WL_SUBCOMPOSITOR_GET_SUBSURFACE_SINCE_VERSION 1

static inline void wl_subcompositor_set_user_data(struct wl_subcompositor *wl_subcompositor, void *user_data) {
	wl_proxy_set_user_data((struct wl_proxy *) wl_subcompositor, user_data);
}

static inline void* wl_subcompositor_get_user_data(struct wl_subcompositor *wl_subcompositor) {
	return wl_proxy_get_user_data((struct wl_proxy *) wl_subcompositor);
}

static inline uint32_t wl_subcompositor_get_version(struct wl_subcompositor *wl_subcompositor) {
	return wl_proxy_get_version((struct wl_proxy *) wl_subcompositor);
}

static inline void wl_subcompositor_destroy(struct wl_subcompositor *wl_subcompositor) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_subcompositor,
			 WL_SUBCOMPOSITOR_DESTROY, NULL, wl_proxy_get_version((struct wl_proxy *) wl_subcompositor), WL_MARSHAL_FLAG_DESTROY);
}

static inline struct wl_subsurface* wl_subcompositor_get_subsurface(struct wl_subcompositor *wl_subcompositor, struct wl_surface *surface, struct wl_surface *parent) {
	struct wl_proxy *id;

	id = wl_proxy_marshal_flags((struct wl_proxy *) wl_subcompositor,
			 WL_SUBCOMPOSITOR_GET_SUBSURFACE, &wl_subsurface_interface, wl_proxy_get_version((struct wl_proxy *) wl_subcompositor), 0, NULL, surface, parent);

	return (struct wl_subsurface *) id;
}

#ifndef WL_SUBSURFACE_ERROR_ENUM
#define WL_SUBSURFACE_ERROR_ENUM
enum wl_subsurface_error {
	WL_SUBSURFACE_ERROR_BAD_SURFACE = 0,
};
#endif

#define WL_SUBSURFACE_DESTROY 0
#define WL_SUBSURFACE_SET_POSITION 1
#define WL_SUBSURFACE_PLACE_ABOVE 2
#define WL_SUBSURFACE_PLACE_BELOW 3
#define WL_SUBSURFACE_SET_SYNC 4
#define WL_SUBSURFACE_SET_DESYNC 5
#define WL_SUBSURFACE_DESTROY_SINCE_VERSION 1
#define WL_SUBSURFACE_SET_POSITION_SINCE_VERSION 1
#define WL_SUBSURFACE_PLACE_ABOVE_SINCE_VERSION 1
#define WL_SUBSURFACE_PLACE_BELOW_SINCE_VERSION 1
#define WL_SUBSURFACE_SET_SYNC_SINCE_VERSION 1
#define WL_SUBSURFACE_SET_DESYNC_SINCE_VERSION 1

static inline void wl_subsurface_set_user_data(struct wl_subsurface *wl_subsurface, void *user_data) {
	wl_proxy_set_user_data((struct wl_proxy *) wl_subsurface, user_data);
}

static inline void* wl_subsurface_get_user_data(struct wl_subsurface *wl_subsurface)
{
	return wl_proxy_get_user_data((struct wl_proxy *) wl_subsurface);
}

static inline uint32_t wl_subsurface_get_version(struct wl_subsurface *wl_subsurface) {
	return wl_proxy_get_version((struct wl_proxy *) wl_subsurface);
}

static inline void wl_subsurface_destroy(struct wl_subsurface *wl_subsurface) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_subsurface,
			 WL_SUBSURFACE_DESTROY, NULL, wl_proxy_get_version((struct wl_proxy *) wl_subsurface), WL_MARSHAL_FLAG_DESTROY);
}

static inline void wl_subsurface_set_position(struct wl_subsurface *wl_subsurface, int32_t x, int32_t y) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_subsurface,
			 WL_SUBSURFACE_SET_POSITION, NULL, wl_proxy_get_version((struct wl_proxy *) wl_subsurface), 0, x, y);
}

static inline void wl_subsurface_place_above(struct wl_subsurface *wl_subsurface, struct wl_surface *sibling) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_subsurface,
			 WL_SUBSURFACE_PLACE_ABOVE, NULL, wl_proxy_get_version((struct wl_proxy *) wl_subsurface), 0, sibling);
}

static inline void wl_subsurface_place_below(struct wl_subsurface *wl_subsurface, struct wl_surface *sibling) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_subsurface,
			 WL_SUBSURFACE_PLACE_BELOW, NULL, wl_proxy_get_version((struct wl_proxy *) wl_subsurface), 0, sibling);
}

static inline void wl_subsurface_set_sync(struct wl_subsurface *wl_subsurface) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_subsurface,
			 WL_SUBSURFACE_SET_SYNC, NULL, wl_proxy_get_version((struct wl_proxy *) wl_subsurface), 0);
}

static inline void wl_subsurface_set_desync(struct wl_subsurface *wl_subsurface) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_subsurface,
			 WL_SUBSURFACE_SET_DESYNC, NULL, wl_proxy_get_version((struct wl_proxy *) wl_subsurface), 0);
}

#define WL_FIXES_DESTROY 0
#define WL_FIXES_DESTROY_REGISTRY 1
#define WL_FIXES_DESTROY_SINCE_VERSION 1
#define WL_FIXES_DESTROY_REGISTRY_SINCE_VERSION 1

static inline void wl_fixes_set_user_data(struct wl_fixes *wl_fixes, void *user_data) {
	wl_proxy_set_user_data((struct wl_proxy *) wl_fixes, user_data);
}

static inline void* wl_fixes_get_user_data(struct wl_fixes *wl_fixes)
{
	return wl_proxy_get_user_data((struct wl_proxy *) wl_fixes);
}

static inline uint32_t wl_fixes_get_version(struct wl_fixes *wl_fixes)
{
	return wl_proxy_get_version((struct wl_proxy *) wl_fixes);
}


static inline void wl_fixes_destroy(struct wl_fixes *wl_fixes) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_fixes,
			 WL_FIXES_DESTROY, NULL, wl_proxy_get_version((struct wl_proxy *) wl_fixes), WL_MARSHAL_FLAG_DESTROY);
}


static inline void wl_fixes_destroy_registry(struct wl_fixes *wl_fixes, struct wl_registry *registry) {
	wl_proxy_marshal_flags((struct wl_proxy *) wl_fixes,
			 WL_FIXES_DESTROY_REGISTRY, NULL, wl_proxy_get_version((struct wl_proxy *) wl_fixes), 0, registry);
}




// end core wayland

#ifndef WDL_NO_XDG
struct xdg_popup;
struct xdg_positioner;
struct xdg_surface;
struct xdg_toplevel;
struct xdg_wm_base;

extern const struct wl_interface xdg_wm_base_interface;
extern const struct wl_interface xdg_positioner_interface;
extern const struct wl_interface xdg_surface_interface;
extern const struct wl_interface xdg_toplevel_interface;
extern const struct wl_interface xdg_popup_interface;

enum xdg_wm_base_error {
  XDG_WM_BASE_ERROR_ROLE = 0,
  XDG_WM_BASE_ERROR_DEFUNCT_SURFACES = 1,
  XDG_WM_BASE_ERROR_NOT_THE_TOPMOST_POPUP = 2,
  XDG_WM_BASE_ERROR_INVALID_POPUP_PARENT = 3,
  XDG_WM_BASE_ERROR_INVALID_SURFACE_STATE = 4,
  XDG_WM_BASE_ERROR_INVALID_POSITIONER = 5,
  XDG_WM_BASE_ERROR_UNRESPONSIVE = 6,
};

struct xdg_wm_base_listener {
  void (*ping)(void *data, struct xdg_wm_base *xdg_wm_base, uint32_t serial);
};

static inline int xdg_wm_base_add_listener(struct xdg_wm_base *xdg_wm_base, const struct xdg_wm_base_listener *listener, void *data) {
  return wl_proxy_add_listener((struct wl_proxy *)xdg_wm_base,
                               (void (**)(void))listener, data);
}

#define XDG_WM_BASE_DESTROY 0
#define XDG_WM_BASE_CREATE_POSITIONER 1
#define XDG_WM_BASE_GET_XDG_SURFACE 2
#define XDG_WM_BASE_PONG 3
#define XDG_WM_BASE_PING_SINCE_VERSION 1
#define XDG_WM_BASE_DESTROY_SINCE_VERSION 1
#define XDG_WM_BASE_CREATE_POSITIONER_SINCE_VERSION 1
#define XDG_WM_BASE_GET_XDG_SURFACE_SINCE_VERSION 1
#define XDG_WM_BASE_PONG_SINCE_VERSION 1

static inline void xdg_wm_base_set_user_data(struct xdg_wm_base *xdg_wm_base,
                                             void *user_data) {
  wl_proxy_set_user_data((struct wl_proxy *)xdg_wm_base, user_data);
}

static inline void* xdg_wm_base_get_user_data(struct xdg_wm_base *xdg_wm_base) {
  return wl_proxy_get_user_data((struct wl_proxy *)xdg_wm_base);
}

static inline uint32_t xdg_wm_base_get_version(struct xdg_wm_base *xdg_wm_base) {
  return wl_proxy_get_version((struct wl_proxy *)xdg_wm_base);
}

static inline void xdg_wm_base_destroy(struct xdg_wm_base *xdg_wm_base) {
  wl_proxy_marshal_flags((struct wl_proxy *)xdg_wm_base, XDG_WM_BASE_DESTROY,
                         NULL,
                         wl_proxy_get_version((struct wl_proxy *)xdg_wm_base),
                         WL_MARSHAL_FLAG_DESTROY);
}

static inline struct xdg_positioner* xdg_wm_base_create_positioner(struct xdg_wm_base *xdg_wm_base) {
  struct wl_proxy *id;

  id = wl_proxy_marshal_flags(
      (struct wl_proxy *)xdg_wm_base, XDG_WM_BASE_CREATE_POSITIONER,
      &xdg_positioner_interface,
      wl_proxy_get_version((struct wl_proxy *)xdg_wm_base), 0, NULL);

  return (struct xdg_positioner *)id;
}

static inline struct xdg_surface* xdg_wm_base_get_xdg_surface(struct xdg_wm_base *xdg_wm_base,
                            struct wl_surface *surface) {
  struct wl_proxy *id;

  id = wl_proxy_marshal_flags(
      (struct wl_proxy *)xdg_wm_base, XDG_WM_BASE_GET_XDG_SURFACE,
      &xdg_surface_interface,
      wl_proxy_get_version((struct wl_proxy *)xdg_wm_base), 0, NULL, surface);

  return (struct xdg_surface *)id;
}

static inline void xdg_wm_base_pong(struct xdg_wm_base *xdg_wm_base,
                                    uint32_t serial) {
  wl_proxy_marshal_flags((struct wl_proxy *)xdg_wm_base, XDG_WM_BASE_PONG, NULL,
                         wl_proxy_get_version((struct wl_proxy *)xdg_wm_base),
                         0, serial);
}

enum xdg_positioner_anchor {
  XDG_POSITIONER_ANCHOR_NONE = 0,
  XDG_POSITIONER_ANCHOR_TOP = 1,
  XDG_POSITIONER_ANCHOR_BOTTOM = 2,
  XDG_POSITIONER_ANCHOR_LEFT = 3,
  XDG_POSITIONER_ANCHOR_RIGHT = 4,
  XDG_POSITIONER_ANCHOR_TOP_LEFT = 5,
  XDG_POSITIONER_ANCHOR_BOTTOM_LEFT = 6,
  XDG_POSITIONER_ANCHOR_TOP_RIGHT = 7,
  XDG_POSITIONER_ANCHOR_BOTTOM_RIGHT = 8,
};

enum xdg_positioner_gravity {
  XDG_POSITIONER_GRAVITY_NONE = 0,
  XDG_POSITIONER_GRAVITY_TOP = 1,
  XDG_POSITIONER_GRAVITY_BOTTOM = 2,
  XDG_POSITIONER_GRAVITY_LEFT = 3,
  XDG_POSITIONER_GRAVITY_RIGHT = 4,
  XDG_POSITIONER_GRAVITY_TOP_LEFT = 5,
  XDG_POSITIONER_GRAVITY_BOTTOM_LEFT = 6,
  XDG_POSITIONER_GRAVITY_TOP_RIGHT = 7,
  XDG_POSITIONER_GRAVITY_BOTTOM_RIGHT = 8,
};

enum xdg_positioner_constraint_adjustment {
  XDG_POSITIONER_CONSTRAINT_ADJUSTMENT_NONE = 0,
  XDG_POSITIONER_CONSTRAINT_ADJUSTMENT_SLIDE_X = 1,
  XDG_POSITIONER_CONSTRAINT_ADJUSTMENT_SLIDE_Y = 2,
  XDG_POSITIONER_CONSTRAINT_ADJUSTMENT_FLIP_X = 4,
  XDG_POSITIONER_CONSTRAINT_ADJUSTMENT_FLIP_Y = 8,
  XDG_POSITIONER_CONSTRAINT_ADJUSTMENT_RESIZE_X = 16,
  XDG_POSITIONER_CONSTRAINT_ADJUSTMENT_RESIZE_Y = 32,
};

#define XDG_POSITIONER_DESTROY 0
#define XDG_POSITIONER_SET_SIZE 1
#define XDG_POSITIONER_SET_ANCHOR_RECT 2
#define XDG_POSITIONER_SET_ANCHOR 3
#define XDG_POSITIONER_SET_GRAVITY 4
#define XDG_POSITIONER_SET_CONSTRAINT_ADJUSTMENT 5
#define XDG_POSITIONER_SET_OFFSET 6
#define XDG_POSITIONER_SET_REACTIVE 7
#define XDG_POSITIONER_SET_PARENT_SIZE 8
#define XDG_POSITIONER_SET_PARENT_CONFIGURE 9
#define XDG_POSITIONER_DESTROY_SINCE_VERSION 1
#define XDG_POSITIONER_SET_SIZE_SINCE_VERSION 1
#define XDG_POSITIONER_SET_ANCHOR_RECT_SINCE_VERSION 1
#define XDG_POSITIONER_SET_ANCHOR_SINCE_VERSION 1
#define XDG_POSITIONER_SET_GRAVITY_SINCE_VERSION 1
#define XDG_POSITIONER_SET_CONSTRAINT_ADJUSTMENT_SINCE_VERSION 1
#define XDG_POSITIONER_SET_OFFSET_SINCE_VERSION 1
#define XDG_POSITIONER_SET_REACTIVE_SINCE_VERSION 3
#define XDG_POSITIONER_SET_PARENT_SIZE_SINCE_VERSION 3
#define XDG_POSITIONER_SET_PARENT_CONFIGURE_SINCE_VERSION 3

static inline void xdg_positioner_set_user_data(struct xdg_positioner *xdg_positioner,
                             void *user_data) {
  wl_proxy_set_user_data((struct wl_proxy *)xdg_positioner, user_data);
}

static inline void* xdg_positioner_get_user_data(struct xdg_positioner *xdg_positioner) {
  return wl_proxy_get_user_data((struct wl_proxy *)xdg_positioner);
}

static inline uint32_t xdg_positioner_get_version(struct xdg_positioner *xdg_positioner) {
  return wl_proxy_get_version((struct wl_proxy *)xdg_positioner);
}

static inline void xdg_positioner_destroy(struct xdg_positioner *xdg_positioner) {
  wl_proxy_marshal_flags(
      (struct wl_proxy *)xdg_positioner, XDG_POSITIONER_DESTROY, NULL,
      wl_proxy_get_version((struct wl_proxy *)xdg_positioner),
      WL_MARSHAL_FLAG_DESTROY);
}

static inline void xdg_positioner_set_size(struct xdg_positioner *xdg_positioner, int32_t width,
                        int32_t height) {
  wl_proxy_marshal_flags(
      (struct wl_proxy *)xdg_positioner, XDG_POSITIONER_SET_SIZE, NULL,
      wl_proxy_get_version((struct wl_proxy *)xdg_positioner), 0, width,
      height);
}

static inline void xdg_positioner_set_anchor_rect(struct xdg_positioner *xdg_positioner, int32_t x,
                               int32_t y, int32_t width, int32_t height) {
  wl_proxy_marshal_flags(
      (struct wl_proxy *)xdg_positioner, XDG_POSITIONER_SET_ANCHOR_RECT, NULL,
      wl_proxy_get_version((struct wl_proxy *)xdg_positioner), 0, x, y, width,
      height);
}

static inline void xdg_positioner_set_anchor(struct xdg_positioner *xdg_positioner,
                          uint32_t anchor) {
  wl_proxy_marshal_flags(
      (struct wl_proxy *)xdg_positioner, XDG_POSITIONER_SET_ANCHOR, NULL,
      wl_proxy_get_version((struct wl_proxy *)xdg_positioner), 0, anchor);
}

static inline void xdg_positioner_set_gravity(struct xdg_positioner *xdg_positioner,
                           uint32_t gravity) {
  wl_proxy_marshal_flags(
      (struct wl_proxy *)xdg_positioner, XDG_POSITIONER_SET_GRAVITY, NULL,
      wl_proxy_get_version((struct wl_proxy *)xdg_positioner), 0, gravity);
}

static inline void xdg_positioner_set_constraint_adjustment(struct xdg_positioner *xdg_positioner,
                                         uint32_t constraint_adjustment) {
  wl_proxy_marshal_flags(
      (struct wl_proxy *)xdg_positioner,
      XDG_POSITIONER_SET_CONSTRAINT_ADJUSTMENT, NULL,
      wl_proxy_get_version((struct wl_proxy *)xdg_positioner), 0,
      constraint_adjustment);
}

static inline void xdg_positioner_set_offset(struct xdg_positioner *xdg_positioner, int32_t x,
                          int32_t y) {
  wl_proxy_marshal_flags(
      (struct wl_proxy *)xdg_positioner, XDG_POSITIONER_SET_OFFSET, NULL,
      wl_proxy_get_version((struct wl_proxy *)xdg_positioner), 0, x, y);
}

static inline void xdg_positioner_set_reactive(struct xdg_positioner *xdg_positioner) {
  wl_proxy_marshal_flags(
      (struct wl_proxy *)xdg_positioner, XDG_POSITIONER_SET_REACTIVE, NULL,
      wl_proxy_get_version((struct wl_proxy *)xdg_positioner), 0);
}

static inline void xdg_positioner_set_parent_size(struct xdg_positioner *xdg_positioner,
                               int32_t parent_width, int32_t parent_height) {
  wl_proxy_marshal_flags(
      (struct wl_proxy *)xdg_positioner, XDG_POSITIONER_SET_PARENT_SIZE, NULL,
      wl_proxy_get_version((struct wl_proxy *)xdg_positioner), 0, parent_width,
      parent_height);
}

static inline void xdg_positioner_set_parent_configure(struct xdg_positioner *xdg_positioner,
                                    uint32_t serial) {
  wl_proxy_marshal_flags(
      (struct wl_proxy *)xdg_positioner, XDG_POSITIONER_SET_PARENT_CONFIGURE,
      NULL, wl_proxy_get_version((struct wl_proxy *)xdg_positioner), 0, serial);
}

enum xdg_surface_error {
  XDG_SURFACE_ERROR_NOT_CONSTRUCTED = 1,
  XDG_SURFACE_ERROR_ALREADY_CONSTRUCTED = 2,
  XDG_SURFACE_ERROR_UNCONFIGURED_BUFFER = 3,
  XDG_SURFACE_ERROR_INVALID_SERIAL = 4,
  XDG_SURFACE_ERROR_INVALID_SIZE = 5,
  XDG_SURFACE_ERROR_DEFUNCT_ROLE_OBJECT = 6,
};

struct xdg_surface_listener {
  void (*configure)(void *data, struct xdg_surface *xdg_surface,
                    uint32_t serial);
};

static inline int xdg_surface_add_listener(struct xdg_surface *xdg_surface, const struct xdg_surface_listener *listener, void *data) {
  return wl_proxy_add_listener((struct wl_proxy *)xdg_surface, (void (**)(void))listener, data);
}

#define XDG_SURFACE_DESTROY 0
#define XDG_SURFACE_GET_TOPLEVEL 1
#define XDG_SURFACE_GET_POPUP 2
#define XDG_SURFACE_SET_WINDOW_GEOMETRY 3
#define XDG_SURFACE_ACK_CONFIGURE 4
#define XDG_SURFACE_CONFIGURE_SINCE_VERSION 1
#define XDG_SURFACE_DESTROY_SINCE_VERSION 1
#define XDG_SURFACE_GET_TOPLEVEL_SINCE_VERSION 1
#define XDG_SURFACE_GET_POPUP_SINCE_VERSION 1
#define XDG_SURFACE_SET_WINDOW_GEOMETRY_SINCE_VERSION 1
#define XDG_SURFACE_ACK_CONFIGURE_SINCE_VERSION 1

static inline void xdg_surface_set_user_data(struct xdg_surface *xdg_surface, void *user_data) {
  wl_proxy_set_user_data((struct wl_proxy *)xdg_surface, user_data);
}

static inline void *xdg_surface_get_user_data(struct xdg_surface *xdg_surface) {
  return wl_proxy_get_user_data((struct wl_proxy *)xdg_surface);
}

static inline uint32_t xdg_surface_get_version(struct xdg_surface *xdg_surface) {
  return wl_proxy_get_version((struct wl_proxy *)xdg_surface);
}

static inline void xdg_surface_destroy(struct xdg_surface *xdg_surface) {
  wl_proxy_marshal_flags((struct wl_proxy *)xdg_surface, XDG_SURFACE_DESTROY, NULL, wl_proxy_get_version((struct wl_proxy *)xdg_surface), WL_MARSHAL_FLAG_DESTROY);
}

static inline struct xdg_toplevel* xdg_surface_get_toplevel(struct xdg_surface *xdg_surface) {
  struct wl_proxy *id;

  id = wl_proxy_marshal_flags(
      (struct wl_proxy *)xdg_surface, XDG_SURFACE_GET_TOPLEVEL,
      &xdg_toplevel_interface,
      wl_proxy_get_version((struct wl_proxy *)xdg_surface), 0, NULL);

  return (struct xdg_toplevel *)id;
}

static inline struct xdg_popup* xdg_surface_get_popup(struct xdg_surface *xdg_surface,
                      struct xdg_surface *parent,
                      struct xdg_positioner *positioner) {
  struct wl_proxy *id;

  id = wl_proxy_marshal_flags(
      (struct wl_proxy *)xdg_surface, XDG_SURFACE_GET_POPUP,
      &xdg_popup_interface,
      wl_proxy_get_version((struct wl_proxy *)xdg_surface), 0, NULL, parent,
      positioner);

  return (struct xdg_popup *)id;
}

static inline void xdg_surface_set_window_geometry(struct xdg_surface *xdg_surface, int32_t x,
                                int32_t y, int32_t width, int32_t height) {
  wl_proxy_marshal_flags((struct wl_proxy *)xdg_surface,
                         XDG_SURFACE_SET_WINDOW_GEOMETRY, NULL,
                         wl_proxy_get_version((struct wl_proxy *)xdg_surface),
                         0, x, y, width, height);
}

static inline void xdg_surface_ack_configure(struct xdg_surface *xdg_surface,
                                             uint32_t serial) {
  wl_proxy_marshal_flags(
      (struct wl_proxy *)xdg_surface, XDG_SURFACE_ACK_CONFIGURE, NULL,
      wl_proxy_get_version((struct wl_proxy *)xdg_surface), 0, serial);
}

enum xdg_toplevel_error {
  XDG_TOPLEVEL_ERROR_INVALID_RESIZE_EDGE = 0,
  XDG_TOPLEVEL_ERROR_INVALID_PARENT = 1,
  XDG_TOPLEVEL_ERROR_INVALID_SIZE = 2,
};

enum xdg_toplevel_resize_edge {
  XDG_TOPLEVEL_RESIZE_EDGE_NONE = 0,
  XDG_TOPLEVEL_RESIZE_EDGE_TOP = 1,
  XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM = 2,
  XDG_TOPLEVEL_RESIZE_EDGE_LEFT = 4,
  XDG_TOPLEVEL_RESIZE_EDGE_TOP_LEFT = 5,
  XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM_LEFT = 6,
  XDG_TOPLEVEL_RESIZE_EDGE_RIGHT = 8,
  XDG_TOPLEVEL_RESIZE_EDGE_TOP_RIGHT = 9,
  XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM_RIGHT = 10,
};

enum xdg_toplevel_state {
  XDG_TOPLEVEL_STATE_MAXIMIZED = 1,
  XDG_TOPLEVEL_STATE_FULLSCREEN = 2,
  XDG_TOPLEVEL_STATE_RESIZING = 3,
  XDG_TOPLEVEL_STATE_ACTIVATED = 4,
  XDG_TOPLEVEL_STATE_TILED_LEFT = 5,
  XDG_TOPLEVEL_STATE_TILED_RIGHT = 6,
  XDG_TOPLEVEL_STATE_TILED_TOP = 7,
  XDG_TOPLEVEL_STATE_TILED_BOTTOM = 8,
  XDG_TOPLEVEL_STATE_SUSPENDED = 9,
  XDG_TOPLEVEL_STATE_CONSTRAINED_LEFT = 10,
  XDG_TOPLEVEL_STATE_CONSTRAINED_RIGHT = 11,
  XDG_TOPLEVEL_STATE_CONSTRAINED_TOP = 12,
  XDG_TOPLEVEL_STATE_CONSTRAINED_BOTTOM = 13,
};

#define XDG_TOPLEVEL_STATE_TILED_LEFT_SINCE_VERSION 2
#define XDG_TOPLEVEL_STATE_TILED_RIGHT_SINCE_VERSION 2
#define XDG_TOPLEVEL_STATE_TILED_TOP_SINCE_VERSION 2
#define XDG_TOPLEVEL_STATE_TILED_BOTTOM_SINCE_VERSION 2
#define XDG_TOPLEVEL_STATE_SUSPENDED_SINCE_VERSION 6
#define XDG_TOPLEVEL_STATE_CONSTRAINED_LEFT_SINCE_VERSION 7
#define XDG_TOPLEVEL_STATE_CONSTRAINED_RIGHT_SINCE_VERSION 7
#define XDG_TOPLEVEL_STATE_CONSTRAINED_TOP_SINCE_VERSION 7
#define XDG_TOPLEVEL_STATE_CONSTRAINED_BOTTOM_SINCE_VERSION 7

enum xdg_toplevel_wm_capabilities {
  XDG_TOPLEVEL_WM_CAPABILITIES_WINDOW_MENU = 1,
  XDG_TOPLEVEL_WM_CAPABILITIES_MAXIMIZE = 2,
  XDG_TOPLEVEL_WM_CAPABILITIES_FULLSCREEN = 3,
  XDG_TOPLEVEL_WM_CAPABILITIES_MINIMIZE = 4,
};

struct xdg_toplevel_listener {

  void (*configure)(void *data, struct xdg_toplevel *xdg_toplevel,
                    int32_t width, int32_t height, struct wl_array *states);

  void (*close)(void *data, struct xdg_toplevel *xdg_toplevel);

  void (*configure_bounds)(void *data, struct xdg_toplevel *xdg_toplevel,
                           int32_t width, int32_t height);

  void (*wm_capabilities)(void *data, struct xdg_toplevel *xdg_toplevel,
                          struct wl_array *capabilities);
};

static inline int xdg_toplevel_add_listener(struct xdg_toplevel *xdg_toplevel,
                          const struct xdg_toplevel_listener *listener,
                          void *data) {
  return wl_proxy_add_listener((struct wl_proxy *)xdg_toplevel,
                               (void (**)(void))listener, data);
}

#define XDG_TOPLEVEL_DESTROY 0
#define XDG_TOPLEVEL_SET_PARENT 1
#define XDG_TOPLEVEL_SET_TITLE 2
#define XDG_TOPLEVEL_SET_APP_ID 3
#define XDG_TOPLEVEL_SHOW_WINDOW_MENU 4
#define XDG_TOPLEVEL_MOVE 5
#define XDG_TOPLEVEL_RESIZE 6
#define XDG_TOPLEVEL_SET_MAX_SIZE 7
#define XDG_TOPLEVEL_SET_MIN_SIZE 8
#define XDG_TOPLEVEL_SET_MAXIMIZED 9
#define XDG_TOPLEVEL_UNSET_MAXIMIZED 10
#define XDG_TOPLEVEL_SET_FULLSCREEN 11
#define XDG_TOPLEVEL_UNSET_FULLSCREEN 12
#define XDG_TOPLEVEL_SET_MINIMIZED 13
#define XDG_TOPLEVEL_CONFIGURE_SINCE_VERSION 1
#define XDG_TOPLEVEL_CLOSE_SINCE_VERSION 1
#define XDG_TOPLEVEL_CONFIGURE_BOUNDS_SINCE_VERSION 4
#define XDG_TOPLEVEL_WM_CAPABILITIES_SINCE_VERSION 5
#define XDG_TOPLEVEL_DESTROY_SINCE_VERSION 1
#define XDG_TOPLEVEL_SET_PARENT_SINCE_VERSION 1
#define XDG_TOPLEVEL_SET_TITLE_SINCE_VERSION 1
#define XDG_TOPLEVEL_SET_APP_ID_SINCE_VERSION 1
#define XDG_TOPLEVEL_SHOW_WINDOW_MENU_SINCE_VERSION 1
#define XDG_TOPLEVEL_MOVE_SINCE_VERSION 1
#define XDG_TOPLEVEL_RESIZE_SINCE_VERSION 1
#define XDG_TOPLEVEL_SET_MAX_SIZE_SINCE_VERSION 1
#define XDG_TOPLEVEL_SET_MIN_SIZE_SINCE_VERSION 1
#define XDG_TOPLEVEL_SET_MAXIMIZED_SINCE_VERSION 1
#define XDG_TOPLEVEL_UNSET_MAXIMIZED_SINCE_VERSION 1
#define XDG_TOPLEVEL_SET_FULLSCREEN_SINCE_VERSION 1
#define XDG_TOPLEVEL_UNSET_FULLSCREEN_SINCE_VERSION 1
#define XDG_TOPLEVEL_SET_MINIMIZED_SINCE_VERSION 1

static inline void xdg_toplevel_set_user_data(struct xdg_toplevel *xdg_toplevel,
                                              void *user_data) {
  wl_proxy_set_user_data((struct wl_proxy *)xdg_toplevel, user_data);
}

static inline void* xdg_toplevel_get_user_data(struct xdg_toplevel *xdg_toplevel) {
  return wl_proxy_get_user_data((struct wl_proxy *)xdg_toplevel);
}

static inline uint32_t xdg_toplevel_get_version(struct xdg_toplevel *xdg_toplevel) {
  return wl_proxy_get_version((struct wl_proxy *)xdg_toplevel);
}

static inline void xdg_toplevel_destroy(struct xdg_toplevel *xdg_toplevel) {
  wl_proxy_marshal_flags((struct wl_proxy *)xdg_toplevel, XDG_TOPLEVEL_DESTROY,
                         NULL,
                         wl_proxy_get_version((struct wl_proxy *)xdg_toplevel),
                         WL_MARSHAL_FLAG_DESTROY);
}

static inline void xdg_toplevel_set_parent(struct xdg_toplevel *xdg_toplevel,
                                           struct xdg_toplevel *parent) {
  wl_proxy_marshal_flags(
      (struct wl_proxy *)xdg_toplevel, XDG_TOPLEVEL_SET_PARENT, NULL,
      wl_proxy_get_version((struct wl_proxy *)xdg_toplevel), 0, parent);
}

static inline void xdg_toplevel_set_title(struct xdg_toplevel *xdg_toplevel,
                                          const char *title) {
  wl_proxy_marshal_flags(
      (struct wl_proxy *)xdg_toplevel, XDG_TOPLEVEL_SET_TITLE, NULL,
      wl_proxy_get_version((struct wl_proxy *)xdg_toplevel), 0, title);
}

static inline void xdg_toplevel_set_app_id(struct xdg_toplevel *xdg_toplevel,
                                           const char *app_id) {
  wl_proxy_marshal_flags(
      (struct wl_proxy *)xdg_toplevel, XDG_TOPLEVEL_SET_APP_ID, NULL,
      wl_proxy_get_version((struct wl_proxy *)xdg_toplevel), 0, app_id);
}

static inline void
xdg_toplevel_show_window_menu(struct xdg_toplevel *xdg_toplevel,
                              struct wl_seat *seat, uint32_t serial, int32_t x,
                              int32_t y) {
  wl_proxy_marshal_flags((struct wl_proxy *)xdg_toplevel,
                         XDG_TOPLEVEL_SHOW_WINDOW_MENU, NULL,
                         wl_proxy_get_version((struct wl_proxy *)xdg_toplevel),
                         0, seat, serial, x, y);
}

static inline void xdg_toplevel_move(struct xdg_toplevel *xdg_toplevel,
                                     struct wl_seat *seat, uint32_t serial) {
  wl_proxy_marshal_flags(
      (struct wl_proxy *)xdg_toplevel, XDG_TOPLEVEL_MOVE, NULL,
      wl_proxy_get_version((struct wl_proxy *)xdg_toplevel), 0, seat, serial);
}

static inline void xdg_toplevel_resize(struct xdg_toplevel *xdg_toplevel,
                                       struct wl_seat *seat, uint32_t serial,
                                       uint32_t edges) {
  wl_proxy_marshal_flags((struct wl_proxy *)xdg_toplevel, XDG_TOPLEVEL_RESIZE,
                         NULL,
                         wl_proxy_get_version((struct wl_proxy *)xdg_toplevel),
                         0, seat, serial, edges);
}

static inline void xdg_toplevel_set_max_size(struct xdg_toplevel *xdg_toplevel,
                                             int32_t width, int32_t height) {
  wl_proxy_marshal_flags(
      (struct wl_proxy *)xdg_toplevel, XDG_TOPLEVEL_SET_MAX_SIZE, NULL,
      wl_proxy_get_version((struct wl_proxy *)xdg_toplevel), 0, width, height);
}

static inline void xdg_toplevel_set_min_size(struct xdg_toplevel *xdg_toplevel,
                                             int32_t width, int32_t height) {
  wl_proxy_marshal_flags(
      (struct wl_proxy *)xdg_toplevel, XDG_TOPLEVEL_SET_MIN_SIZE, NULL,
      wl_proxy_get_version((struct wl_proxy *)xdg_toplevel), 0, width, height);
}

static inline void xdg_toplevel_set_maximized(struct xdg_toplevel *xdg_toplevel) {
  wl_proxy_marshal_flags(
      (struct wl_proxy *)xdg_toplevel, XDG_TOPLEVEL_SET_MAXIMIZED, NULL,
      wl_proxy_get_version((struct wl_proxy *)xdg_toplevel), 0);
}

static inline void xdg_toplevel_unset_maximized(struct xdg_toplevel *xdg_toplevel) {
  wl_proxy_marshal_flags(
      (struct wl_proxy *)xdg_toplevel, XDG_TOPLEVEL_UNSET_MAXIMIZED, NULL,
      wl_proxy_get_version((struct wl_proxy *)xdg_toplevel), 0);
}

static inline void xdg_toplevel_set_fullscreen(struct xdg_toplevel *xdg_toplevel,
                            struct wl_output *output) {
  wl_proxy_marshal_flags(
      (struct wl_proxy *)xdg_toplevel, XDG_TOPLEVEL_SET_FULLSCREEN, NULL,
      wl_proxy_get_version((struct wl_proxy *)xdg_toplevel), 0, output);
}

static inline void xdg_toplevel_unset_fullscreen(struct xdg_toplevel *xdg_toplevel) {
  wl_proxy_marshal_flags(
      (struct wl_proxy *)xdg_toplevel, XDG_TOPLEVEL_UNSET_FULLSCREEN, NULL,
      wl_proxy_get_version((struct wl_proxy *)xdg_toplevel), 0);
}

static inline void xdg_toplevel_set_minimized(struct xdg_toplevel *xdg_toplevel) {
  wl_proxy_marshal_flags(
      (struct wl_proxy *)xdg_toplevel, XDG_TOPLEVEL_SET_MINIMIZED, NULL,
      wl_proxy_get_version((struct wl_proxy *)xdg_toplevel), 0);
}

enum xdg_popup_error {
  XDG_POPUP_ERROR_INVALID_GRAB = 0,
};

struct xdg_popup_listener {

  void (*configure)(void *data, struct xdg_popup *xdg_popup, int32_t x,
                    int32_t y, int32_t width, int32_t height);

  void (*popup_done)(void *data, struct xdg_popup *xdg_popup);

  void (*repositioned)(void *data, struct xdg_popup *xdg_popup, uint32_t token);
};

static inline int
xdg_popup_add_listener(struct xdg_popup *xdg_popup,
                       const struct xdg_popup_listener *listener, void *data) {
  return wl_proxy_add_listener((struct wl_proxy *)xdg_popup,
                               (void (**)(void))listener, data);
}

#define XDG_POPUP_DESTROY 0
#define XDG_POPUP_GRAB 1
#define XDG_POPUP_REPOSITION 2
#define XDG_POPUP_CONFIGURE_SINCE_VERSION 1
#define XDG_POPUP_POPUP_DONE_SINCE_VERSION 1
#define XDG_POPUP_REPOSITIONED_SINCE_VERSION 3
#define XDG_POPUP_DESTROY_SINCE_VERSION 1
#define XDG_POPUP_GRAB_SINCE_VERSION 1
#define XDG_POPUP_REPOSITION_SINCE_VERSION 3

static inline void xdg_popup_set_user_data(struct xdg_popup *xdg_popup,
                                           void *user_data) {
  wl_proxy_set_user_data((struct wl_proxy *)xdg_popup, user_data);
}

static inline void *xdg_popup_get_user_data(struct xdg_popup *xdg_popup) {
  return wl_proxy_get_user_data((struct wl_proxy *)xdg_popup);
}

static inline uint32_t xdg_popup_get_version(struct xdg_popup *xdg_popup) {
  return wl_proxy_get_version((struct wl_proxy *)xdg_popup);
}

static inline void xdg_popup_destroy(struct xdg_popup *xdg_popup) {
  wl_proxy_marshal_flags((struct wl_proxy *)xdg_popup, XDG_POPUP_DESTROY, NULL,
                         wl_proxy_get_version((struct wl_proxy *)xdg_popup),
                         WL_MARSHAL_FLAG_DESTROY);
}

static inline void xdg_popup_grab(struct xdg_popup *xdg_popup,
                                  struct wl_seat *seat, uint32_t serial) {
  wl_proxy_marshal_flags((struct wl_proxy *)xdg_popup, XDG_POPUP_GRAB, NULL,
                         wl_proxy_get_version((struct wl_proxy *)xdg_popup), 0,
                         seat, serial);
}

static inline void xdg_popup_reposition(struct xdg_popup *xdg_popup,
                                        struct xdg_positioner *positioner,
                                        uint32_t token) {
  wl_proxy_marshal_flags(
      (struct wl_proxy *)xdg_popup, XDG_POPUP_REPOSITION, NULL,
      wl_proxy_get_version((struct wl_proxy *)xdg_popup), 0, positioner, token);
}

extern const struct wl_interface
    xdg_popup_interface; // arent really external but it works in the
                         // wayland-scanner code so why shouldnt it here
extern const struct wl_interface xdg_positioner_interface;
extern const struct wl_interface xdg_surface_interface;
extern const struct wl_interface xdg_toplevel_interface;

const struct wl_interface *xdg_shell_types[26];

static const struct wl_message xdg_wm_base_requests[] = {
    {"destroy", "", xdg_shell_types + 0},
    {"create_positioner", "n", xdg_shell_types + 4},
    {"get_xdg_surface", "no", xdg_shell_types + 5},
    {"pong", "u", xdg_shell_types + 0},
};

static const struct wl_message xdg_wm_base_events[] = {
    {"ping", "u", xdg_shell_types + 0},
};

const struct wl_interface xdg_wm_base_interface = {
    "xdg_wm_base", 7, 4, xdg_wm_base_requests, 1, xdg_wm_base_events,
};

static const struct wl_message xdg_positioner_requests[] = {
    {"destroy", "", xdg_shell_types + 0},
    {"set_size", "ii", xdg_shell_types + 0},
    {"set_anchor_rect", "iiii", xdg_shell_types + 0},
    {"set_anchor", "u", xdg_shell_types + 0},
    {"set_gravity", "u", xdg_shell_types + 0},
    {"set_constraint_adjustment", "u", xdg_shell_types + 0},
    {"set_offset", "ii", xdg_shell_types + 0},
    {"set_reactive", "3", xdg_shell_types + 0},
    {"set_parent_size", "3ii", xdg_shell_types + 0},
    {"set_parent_configure", "3u", xdg_shell_types + 0},
};

const struct wl_interface xdg_positioner_interface = {
    "xdg_positioner", 7, 10, xdg_positioner_requests, 0, NULL,
};

static const struct wl_message xdg_surface_requests[] = {
    {"destroy", "", xdg_shell_types + 0},
    {"get_toplevel", "n", xdg_shell_types + 7},
    {"get_popup", "n?oo", xdg_shell_types + 8},
    {"set_window_geometry", "iiii", xdg_shell_types + 0},
    {"ack_configure", "u", xdg_shell_types + 0},
};

static const struct wl_message xdg_surface_events[] = {
    {"configure", "u", xdg_shell_types + 0},
};

const struct wl_interface xdg_surface_interface = {
    "xdg_surface", 7, 5, xdg_surface_requests, 1, xdg_surface_events,
};

static const struct wl_message xdg_toplevel_requests[] = {
    {"destroy", "", xdg_shell_types + 0},
    {"set_parent", "?o", xdg_shell_types + 11},
    {"set_title", "s", xdg_shell_types + 0},
    {"set_app_id", "s", xdg_shell_types + 0},
    {"show_window_menu", "ouii", xdg_shell_types + 12},
    {"move", "ou", xdg_shell_types + 16},
    {"resize", "ouu", xdg_shell_types + 18},
    {"set_max_size", "ii", xdg_shell_types + 0},
    {"set_min_size", "ii", xdg_shell_types + 0},
    {"set_maximized", "", xdg_shell_types + 0},
    {"unset_maximized", "", xdg_shell_types + 0},
    {"set_fullscreen", "?o", xdg_shell_types + 21},
    {"unset_fullscreen", "", xdg_shell_types + 0},
    {"set_minimized", "", xdg_shell_types + 0},
};

static const struct wl_message xdg_toplevel_events[] = {
    {"configure", "iia", xdg_shell_types + 0},
    {"close", "", xdg_shell_types + 0},
    {"configure_bounds", "4ii", xdg_shell_types + 0},
    {"wm_capabilities", "5a", xdg_shell_types + 0},
};

const struct wl_interface xdg_toplevel_interface = {
    "xdg_toplevel", 7, 14, xdg_toplevel_requests, 4, xdg_toplevel_events,
};

static const struct wl_message xdg_popup_requests[] = {
    {"destroy", "", xdg_shell_types + 0},
    {"grab", "ou", xdg_shell_types + 22},
    {"reposition", "3ou", xdg_shell_types + 24},
};

static const struct wl_message xdg_popup_events[] = {
    {"configure", "iiii", xdg_shell_types + 0},
    {"popup_done", "", xdg_shell_types + 0},
    {"repositioned", "3u", xdg_shell_types + 0},
};

const struct wl_interface xdg_popup_interface = {
    "xdg_popup", 7, 3, xdg_popup_requests, 3, xdg_popup_events,
};
#endif

		// start definitions
#ifdef WDL_IMPLEMENTATION

#include <dlfcn.h>

void *WDL_DL_HANDLE = NULL;


#define WDL_LOAD_SYM(name) name = (PFN_##name)dlsym(WDL_DL_HANDLE, #name);
#define WDL_LOAD_SYM_STRUCT(name, struct_name) name = *(struct struct_name*)dlsym(WDL_DL_HANDLE, #name)

void WDL_init() {
  WDL_DL_HANDLE = dlopen("libwayland-client.so", RTLD_LAZY | RTLD_GLOBAL);

  if (!WDL_DL_HANDLE) {
    fprintf(stderr, "dlopen on libwayland-client.so failed with: %s %s",
            dlerror(), "\n");
    return;
  }




wl_display_interface = WDL_LOAD_SYM_STRUCT(wl_display_interface, wl_interface);
wl_registry_interface = WDL_LOAD_SYM_STRUCT(wl_registry_interface, wl_interface);
wl_callback_interface = WDL_LOAD_SYM_STRUCT(wl_callback_interface, wl_interface);
wl_compositor_interface = WDL_LOAD_SYM_STRUCT(wl_compositor_interface, wl_interface);
wl_shm_pool_interface = WDL_LOAD_SYM_STRUCT(wl_shm_pool_interface, wl_interface);
wl_shm_interface = WDL_LOAD_SYM_STRUCT(wl_shm_interface, wl_interface);
wl_buffer_interface = WDL_LOAD_SYM_STRUCT(wl_buffer_interface, wl_interface);
wl_data_offer_interface = WDL_LOAD_SYM_STRUCT(wl_data_offer_interface, wl_interface);
wl_data_source_interface = WDL_LOAD_SYM_STRUCT(wl_data_source_interface, wl_interface);
wl_data_device_interface = WDL_LOAD_SYM_STRUCT(wl_data_device_interface, wl_interface);
wl_data_device_manager_interface = WDL_LOAD_SYM_STRUCT(wl_data_device_manager_interface, wl_interface);
wl_shell_interface = WDL_LOAD_SYM_STRUCT(wl_shell_interface, wl_interface);
wl_shell_surface_interface = WDL_LOAD_SYM_STRUCT(wl_shell_surface_interface, wl_interface);
wl_surface_interface = WDL_LOAD_SYM_STRUCT(wl_surface_interface, wl_interface);
wl_seat_interface = WDL_LOAD_SYM_STRUCT(wl_seat_interface, wl_interface);
wl_pointer_interface = WDL_LOAD_SYM_STRUCT(wl_pointer_interface, wl_interface);
wl_keyboard_interface = WDL_LOAD_SYM_STRUCT(wl_keyboard_interface, wl_interface);
wl_touch_interface = WDL_LOAD_SYM_STRUCT(wl_touch_interface, wl_interface);
wl_output_interface = WDL_LOAD_SYM_STRUCT(wl_output_interface, wl_interface);
wl_region_interface = WDL_LOAD_SYM_STRUCT(wl_region_interface, wl_interface);
wl_subcompositor_interface = WDL_LOAD_SYM_STRUCT(wl_subcompositor_interface, wl_interface);
wl_subsurface_interface = WDL_LOAD_SYM_STRUCT(wl_subsurface_interface, wl_interface);
wl_fixes_interface = WDL_LOAD_SYM_STRUCT(wl_fixes_interface, wl_interface);


WDL_LOAD_SYM(wl_event_queue_destroy)
WDL_LOAD_SYM(wl_proxy_marshal_flags)
WDL_LOAD_SYM(wl_proxy_marshal_array_flags)
WDL_LOAD_SYM(wl_proxy_marshal)
WDL_LOAD_SYM(wl_proxy_marshal_array)
WDL_LOAD_SYM(wl_proxy_create)
WDL_LOAD_SYM(wl_proxy_create_wrapper)
WDL_LOAD_SYM(wl_proxy_wrapper_destroy)
WDL_LOAD_SYM(wl_proxy_marshal_constructor_versioned)
WDL_LOAD_SYM(wl_proxy_marshal_array_constructor)
WDL_LOAD_SYM(wl_proxy_marshal_array_constructor_versioned)
WDL_LOAD_SYM(wl_proxy_destroy)
WDL_LOAD_SYM(wl_proxy_add_listener)
WDL_LOAD_SYM(wl_proxy_get_listener)
WDL_LOAD_SYM(wl_proxy_add_dispatcher)
WDL_LOAD_SYM(wl_proxy_set_user_data)
WDL_LOAD_SYM(wl_proxy_get_user_data)
WDL_LOAD_SYM(wl_proxy_get_version)
WDL_LOAD_SYM(wl_proxy_get_id)
WDL_LOAD_SYM(wl_proxy_set_tag)
WDL_LOAD_SYM(wl_proxy_get_tag)
WDL_LOAD_SYM(wl_proxy_get_class)
WDL_LOAD_SYM(wl_proxy_get_interface)
WDL_LOAD_SYM(wl_proxy_get_display)
WDL_LOAD_SYM(wl_proxy_set_queue)
WDL_LOAD_SYM(wl_proxy_get_queue)
WDL_LOAD_SYM(wl_event_queue_get_name)
WDL_LOAD_SYM(wl_display_connect)
WDL_LOAD_SYM(wl_display_connect_to_fd)
WDL_LOAD_SYM(wl_display_disconnect)
WDL_LOAD_SYM(wl_display_get_fd)
WDL_LOAD_SYM(wl_display_dispatch)
WDL_LOAD_SYM(wl_display_dispatch_queue)
WDL_LOAD_SYM(wl_display_dispatch_timeout)
WDL_LOAD_SYM(wl_display_dispatch_queue_timeout)
WDL_LOAD_SYM(wl_display_dispatch_queue_pending)
WDL_LOAD_SYM(wl_display_dispatch_pending)
WDL_LOAD_SYM(wl_display_get_error)
WDL_LOAD_SYM(wl_display_get_protocol_error)
WDL_LOAD_SYM(wl_display_flush)
WDL_LOAD_SYM(wl_display_roundtrip_queue)
WDL_LOAD_SYM(wl_display_roundtrip)
WDL_LOAD_SYM(wl_display_create_queue)
WDL_LOAD_SYM(wl_display_create_queue_with_name) 
WDL_LOAD_SYM(wl_display_prepare_read_queue)
WDL_LOAD_SYM(wl_display_prepare_read)
WDL_LOAD_SYM(wl_display_cancel_read)
WDL_LOAD_SYM(wl_display_read_events)
WDL_LOAD_SYM(wl_log_set_handler_client)
WDL_LOAD_SYM(wl_display_set_max_buffer_size)





#ifndef WDL_NO_XDG
  xdg_shell_types[0] = NULL;
  xdg_shell_types[1] = NULL;
  xdg_shell_types[2] = NULL;
  xdg_shell_types[3] = NULL;
  xdg_shell_types[4] = &xdg_positioner_interface;
  xdg_shell_types[5] = &xdg_surface_interface;
  xdg_shell_types[6] = &wl_surface_interface;
  xdg_shell_types[7] = &xdg_toplevel_interface;
  xdg_shell_types[8] = &xdg_popup_interface;
  xdg_shell_types[9] = &xdg_surface_interface;
  xdg_shell_types[10] = &xdg_positioner_interface;
  xdg_shell_types[11] = &xdg_toplevel_interface;
  xdg_shell_types[12] = &wl_seat_interface;
  xdg_shell_types[13] = NULL;
  xdg_shell_types[14] = NULL;
  xdg_shell_types[15] = NULL;
  xdg_shell_types[16] = &wl_seat_interface;
  xdg_shell_types[17] = NULL;
  xdg_shell_types[18] = &wl_seat_interface;
  xdg_shell_types[19] = NULL;
  xdg_shell_types[20] = NULL;
  xdg_shell_types[21] = &wl_output_interface;
  xdg_shell_types[22] = &wl_seat_interface;
  xdg_shell_types[23] = NULL;
  xdg_shell_types[24] = &xdg_positioner_interface;
  xdg_shell_types[25] = NULL;

#endif
}

void WDL_deinit() { dlclose(WDL_DL_HANDLE); }

#endif

// end definitions

#ifdef __cplusplus
}
#endif