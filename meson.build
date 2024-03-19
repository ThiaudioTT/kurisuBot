project('kurisuBot', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3',
                     'cpp_std=c++17'])

dpp = dependency('dpp')

exe = executable('kurisubot', 'kurisubot.cpp',
  install : true, dependencies : [dpp])

test('basic', exe)
