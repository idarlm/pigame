project('pigame', 'c',
  default_options: 'default_library=static')

sdl2_dep = dependency('sdl2')
opengl_dep = dependency('OpenGL', method: 'cmake')

executable('pigame', 'pigame.c',
  win_subsystem: 'windows',
  dependencies: [sdl2_dep, opengl_dep])
