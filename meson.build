project('kurisuBot', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3',
                     'cpp_std=c++17'])

dpp = dependency('dpp')

commands = include_directories('src/commands')

src = [
  'src/kurisubot.cpp',
  'src/commands/commands.cpp'
  ]


executable('kurisubot', src,
  install : true, dependencies : [dpp],
  include_directories : [commands])

# test('basic', exe)
