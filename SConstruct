from os import environ

VariantDir('build/src', 'src', duplicate=0)
VariantDir('build/lib', 'lib', duplicate=0)

flags = []

env = Environment(ENV       = environ,
                  CXX       = 'clang++',
                  CPPFLAGS  = ['-Wno-unused-value'],
                  CXXFLAGS  = flags,
                  LINKFLAGS = flags,
                  CPPPATH   = ['#lib/include', '#src/include'],
                  LIBS      = [])

env.Program('ultrasnes', Glob('build/*/*.c') + Glob('build/*/*/*.c'))