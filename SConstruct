env = Environment(CPPPATH = ['include'], CXXFLAGS = ["-std=c++11"])

Repository('vendor/glew')
Repository('vendor/glfw')
Repository('vendor/stb_image')

env.Program('app',
            Glob('src/*.cpp'),
            LIBS=['glfw3', 'GLEW'],
            LIBPATH=['lib'])

env.Append(LINKFLAGS=['-framework', 'Cocoa',
                      '-framework', 'OpenGL',
                      '-framework', 'IOKit',
                      '-framework', 'CoreVideo'])
