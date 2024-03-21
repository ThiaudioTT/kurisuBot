project('kurisuBot', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3',
                     'cpp_std=c++17'])

dpp = dependency('dpp')

commands = include_directories('src/commands')

src = [
  'src/kurisubot.cpp',
  # Adds all source files for the commands here
  'src/commands/status.cpp'
]


executable('kurisubot', src,
  install : true, dependencies : [dpp],
  include_directories : [commands])

# test('basic', exe)
