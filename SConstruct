import os

env = Environment(CPPPATH = ['include'], CXXFLAGS = ["-std=c++11"])

for vendor in os.listdir('vendor'):
    Repository("vendor/" + vendor)

env.Program('app',
            Glob('src/*.cpp'),
            LIBS=['glfw3', 'GLEW'],
            LIBPATH=['lib'])

env.Append(LINKFLAGS=['-framework', 'Cocoa',
                      '-framework', 'OpenGL',
                      '-framework', 'IOKit',
                      '-framework', 'CoreVideo'])
