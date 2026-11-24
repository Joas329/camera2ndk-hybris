project('camera2ndk-hybris', 'c',
  version: '0.0.0',
  license: 'TBD',
  default_options: ['c_std=gnu11', 'warning_level=2'],
)

cc = meson.get_compiler('c')
hybris_common = cc.find_library('hybris-common')

executable('probe', 'tools/probe.c',
  include_directories: include_directories('include/ndk'),
  dependencies: hybris_common,
)
