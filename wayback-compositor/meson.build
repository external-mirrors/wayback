executable(
	'wayback-compositor',
	['wayback-compositor.c'],
	dependencies: [wayland_server, wayland_client, wayland_cursor, wayland_egl, wayland_protos, wlroots, xcb, xkbcommon, server_protos, shared],
	install: true,
	install_dir: get_option('libexecdir'),
)
