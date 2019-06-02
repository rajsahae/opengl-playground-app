import os
import multiprocessing

num_cpu = multiprocessing.cpu_count()
SetOption('num_jobs', num_cpu)
print("Setting concurrent jobs to %s", num_cpu)

env = Environment(CPPPATH = ['include'], CXXFLAGS = ["-std=c++11"])

include_vendors = ['glew', 'glfw', 'glm', 'stb_image']
for vendor in include_vendors:
    Repository("vendor/" + vendor)

source_files = []
source_dirs = ['src/', 'vendor/stb_image/', 'vendor/imgui/']
for source_dir in source_dirs:
    source_files.append(Glob(source_dir + '*.cpp'))

env.Program('app',
            source_files,
            LIBS=['glfw3', 'GLEW'],
            LIBPATH=['lib'])

env.Append(LINKFLAGS=['-framework', 'Cocoa',
                      '-framework', 'OpenGL',
                      '-framework', 'IOKit',
                      '-framework', 'CoreVideo'])
