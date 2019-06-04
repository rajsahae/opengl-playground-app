import os
import multiprocessing

num_cpu = multiprocessing.cpu_count()
SetOption('num_jobs', num_cpu)
print("Setting concurrent jobs to %s", num_cpu)

env = Environment(CPPPATH = ['.'], CXXFLAGS = ["-std=c++11", "-DIMGUI_IMPL_OPENGL_LOADER_GLEW"])

# Set global sconsign file so we don't rebuild objects every time
env.SConsignFile('.sconsign.dblite')

for vendor in os.listdir('vendor'):
    Repository("vendor/" + vendor)

for src in os.listdir('src'):
    Repository("src/" + src)

source_files = []
source_dirs = ['src/app/', 'src/test/', 'vendor/stb_image/', 'vendor/imgui/']
for source_dir in source_dirs:
    source_files.append(Glob(source_dir + '*.cpp'))

env.Program('app',
            source_files,
            LIBS=['glfw3', 'GLEW'],
            LIBPATH=['.'])

env.Append(LINKFLAGS=['-framework', 'Cocoa',
                      '-framework', 'OpenGL',
                      '-framework', 'IOKit',
                      '-framework', 'CoreVideo'])
