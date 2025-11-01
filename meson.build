project('wayback', 'c',
  version: '0.2',
  license: 'MIT',
  meson_version: '>= 1.4.0',
  default_options: [
    'c_std=gnu23',
    'warning_level=3',
  ])

cc = meson.get_compiler('c')
add_project_arguments(cc.get_supported_arguments(['-Wno-unused-parameter']), language: 'c')

add_project_arguments('-DWLR_USE_UNSTABLE', language: 'c')

add_global_arguments('-DWAYBACK_COMPOSITOR_EXEC_PATH="@0@/wayback-compositor"'.format(get_option('prefix') /get_option('libexecdir')), language : 'c')
add_global_arguments('-DWAYBACK_VERSION="@0@"'.format(meson.project_version()), language : 'c')

wayland_server = dependency('wayland-server')
wayland_client = dependency('wayland-client')
wayland_cursor = dependency('wayland-cursor')
wayland_egl    = dependency('wayland-egl')
wayland_protos = dependency('wayland-protocols', version: '>=1.14')
xcb            = [dependency('xcb'), dependency('xcb-composite')]
xkbcommon      = dependency('xkbcommon')
xwayland       = dependency('xwayland', version: '>=24.1')
wlroots        = dependency('wlroots-0.19', version: '>=0.19', required: false)

if not wlroots.found()
  wlroots = dependency('wlroots-0.18', version: '>=0.18')
endif

xwayland_executable_path = xwayland.get_variable(pkgconfig: 'xwayland')
add_global_arguments('-DXWAYLAND_EXEC_PATH="@0@"'.format(xwayland_executable_path), language : 'c')

subdir('common')
subdir('protocol')
subdir('wayback-compositor')
subdir('wayback-session')
subdir('xwayback')
subdir('doc')
