module 'platform' {
   lib {
      src {
         'src/*.cpp',
         'src/native/*.cpp',
         'src/native/$(toolchain)/*.cpp',
      },
      pch_src 'src/pch.cpp',
      define 'BE_PLATFORM_IMPL'
   }
}
