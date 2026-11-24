project('camera2ndk-hybris', 'c',
  version: '0.0.0',
  license: 'TBD',
  default_options: ['c_std=gnu11', 'warning_level=2'],
)

cc = meson.get_compiler('c')
hybris_common = cc.find_library('hybris-common')
threads = dependency('threads')

ndk_inc = include_directories('include/ndk')

libcamera2ndk_hybris = shared_library('camera2ndk-hybris',
  'src/loader.c',
  'src/ndk_forward.c',
  include_directories: ndk_inc,
  dependencies: [hybris_common, threads],
  gnu_symbol_visibility: 'hidden',
  version: meson.project_version(),
  soversion: '0',
)

executable('probe', 'tools/probe.c',
  include_directories: ndk_inc,
  link_with: libcamera2ndk_hybris,
)
