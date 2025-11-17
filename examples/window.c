// This file is part of WDL, for license see README.md


#include <stdio.h>
#define WDL_IMPLEMENTATION
#include "../WDL.h"



#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>


uint32_t width = 800;
uint32_t height = 600;

uint8_t color;
uint32_t* pixels;

bool cls;


struct wl_shm* shm;
struct wl_buffer* buffer;
struct wl_surface* surface;
struct wl_compositor* compositor;


struct xdg_toplevel* top;
struct xdg_wm_base* base;

struct wl_callback_listener callback_listener;

void resize() {
    char name[8];
    name[0] = '/';
    name[7] = '\0';
    for (int i = 1; i < 6; i++) {
        name[i] = 97 + rand() % 26; // random letter from a-z
    }

    int32_t fd = shm_open(name, O_RDWR | O_CREAT | O_EXCL, S_IWUSR | S_IRUSR | S_IWOTH | S_IROTH);
    shm_unlink(name);
    ftruncate(fd, width * height * 4);

    pixels = mmap(0, width * height * 4, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    struct wl_shm_pool* pool = wl_shm_create_pool(shm, fd, width * height * 4);
    buffer = wl_shm_pool_create_buffer(pool, 0, width, height, width * 4, WL_SHM_FORMAT_ARGB8888);
    wl_shm_pool_destroy(pool);
    close(fd);

    printf("resized to %ux%u\n", width, height);
}

uint32_t getARGB(uint8_t a, uint8_t r, uint8_t g, uint8_t b) {
    return ((uint32_t)a << 24) | ((uint32_t)r << 16) | ((uint32_t)g << 8) | (uint32_t)b;
}

void draw() {
    for (int i = 0; i < width * height; i++) {
        pixels[i] = getARGB(255, 255, 0, 0);
    }

    wl_surface_attach(surface, buffer, 0, 0);
    wl_surface_damage_buffer(surface, 0, 0, width, height);
    wl_surface_commit(surface);
}

void new_frame(void* data, struct wl_callback* callback, uint32_t callback_data) {
        wl_callback_destroy(callback);
        callback = wl_surface_frame(surface);
        wl_callback_add_listener(callback, &callback_listener, 0);

        color++;
        draw();
}

struct wl_callback_listener callback_listener = {
    .done = new_frame
};


void xdgsurface_conf(void* data, struct xdg_surface* xdgsurface, uint32_t serial) {
    xdg_surface_ack_configure(xdgsurface, serial);

    if (!pixels) {
        resize();
    }

    draw();
}

struct xdg_surface_listener xdgsurface_listener = {
    .configure = xdgsurface_conf
};

void top_conf(void* data, struct xdg_toplevel* top, int32_t w, int32_t h, struct wl_array* states) {
    if (!w && !h) {
        return;
    }

    if (width != w || height != h) {
        munmap(pixels, width * height * 4);
        width = w;
        height = h;
        resize();
    }
}


void top_close(void* data, struct xdg_toplevel* top) {
    cls = true;
}

struct xdg_toplevel_listener top_listener = {
    .configure = top_conf,
    .close = top_close
};


void base_ping(void* data, struct xdg_wm_base* base, uint32_t serial) {
    xdg_wm_base_pong(base, serial);
}

struct xdg_wm_base_listener base_listener = {
    .ping = base_ping
};



void registry_global(void* data, struct wl_registry* registry, uint32_t name, const char* interface, uint32_t version) {
	if (strcmp(interface, wl_compositor_interface.name) == 0) {
		compositor = wl_registry_bind(registry, name, &wl_compositor_interface, 4);
	}
	else if (strcmp(interface, wl_shm_interface.name) == 0) {
		shm = wl_registry_bind(registry, name, &wl_shm_interface, 1);
	}
	else if (strcmp(interface, xdg_wm_base_interface.name) == 0) {
		base = wl_registry_bind(registry, name, &xdg_wm_base_interface, 1);
		xdg_wm_base_add_listener(base, &base_listener, 0);
	}
}

void registry_global_remove(void* data, struct wl_registry* registry, uint32_t name) {}


struct wl_registry_listener registry_listener = {
    .global = registry_global,
    .global_remove = registry_global_remove
};

int main() {
    WDL_init();

    struct wl_display* display = wl_display_connect(NULL);
    struct wl_registry* registry = wl_display_get_registry(display);

    wl_registry_add_listener(registry, &registry_listener, NULL);
    wl_display_roundtrip(display);


    surface = wl_compositor_create_surface(compositor);
    struct wl_callback* callback = wl_surface_frame(surface);
    wl_callback_add_listener(callback, &callback_listener, NULL);

    struct xdg_surface* xsurface = xdg_wm_base_get_xdg_surface(base, surface);
    xdg_surface_add_listener(xsurface, &xdgsurface_listener, NULL);

    top = xdg_surface_get_toplevel(xsurface);
    xdg_toplevel_add_listener(top, &top_listener, NULL);
    xdg_toplevel_set_title(top, "WDL Example client");

    wl_surface_commit(surface);

    while (wl_display_dispatch(display)) { if (cls) break; } // keep open

    if (buffer) {
        wl_buffer_destroy(buffer);
    }

    xdg_toplevel_destroy(top);
    xdg_surface_destroy(xsurface);
    wl_surface_destroy(surface);
    wl_display_disconnect(display);

    WDL_deinit();

    return 0;
}