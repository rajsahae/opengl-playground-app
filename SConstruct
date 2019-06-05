import os
import multiprocessing

num_cpu = multiprocessing.cpu_count()
SetOption('num_jobs', num_cpu)
print("Setting concurrent jobs to %s", num_cpu)

compile_flags = ["-std=c++11", "-DIMGUI_IMPL_OPENGL_LOADER_GLEW"]
source_dirs = ['src/app', 'src/test', 'src/vendor/stb_image', 'src/vendor/imgui']
include_dirs = source_dirs + ['.', 'include']
source_files = map(lambda dir: Glob(os.path.join(dir, '*.cpp')), source_dirs)

env = Environment(CPPPATH = include_dirs, CXXFLAGS = compile_flags)

Repository("vendor")

env.Program('app',
            source_files,
            LIBS=['glfw3', 'GLEW'],
            LIBPATH=['lib'])

env.Append(LINKFLAGS=['-framework', 'Cocoa',
                      '-framework', 'OpenGL',
                      '-framework', 'IOKit',
                      '-framework', 'CoreVideo'])
