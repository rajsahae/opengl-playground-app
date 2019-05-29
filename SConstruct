env = Environment(CPPPATH = ['.'], CXXFLAGS = ["-std=c++11"])

Repository('glfw-3.3/include')
Repository('glew-2.1.0/include')

env.Program('app', 'Application.cpp', LIBS=['glfw3', 'GLEW'], LIBPATH=['glfw-3.3/src', 'glew-2.1.0/lib'])

env.Append(LINKFLAGS=['-framework'])
env.Append(LINKFLAGS=['Cocoa'])
env.Append(LINKFLAGS=['-framework'])
env.Append(LINKFLAGS=['OpenGL'])
env.Append(LINKFLAGS=['-framework'])
env.Append(LINKFLAGS=['IOKit'])
env.Append(LINKFLAGS=['-framework'])
env.Append(LINKFLAGS=['CoreVideo'])
