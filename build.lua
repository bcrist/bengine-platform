module 'platform' {
   lib {
      src {
         'src/*.cpp',
         pch_src 'src/pch.cpp'
      },
      src {
         'src/native/*.cpp',
         'src/native/$(toolchain)/*.cpp'
      },
      define 'BE_PLATFORM_IMPL',
      link_project {
         'core', 'glfw'
      }
   }
}
