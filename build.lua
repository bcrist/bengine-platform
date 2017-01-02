module { name = 'platform',
   projects = {
      lib {
         src = {
            'src/*.cpp',
            'src/native/*.cpp',
            'src/native/' .. toolchain .. '/*.cpp',
            pch = 'src/pch.cpp'
         },
         preprocessor = {
            'BE_PLATFORM_IMPL'
         }
      }
   }
}
