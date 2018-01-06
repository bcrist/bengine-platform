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
         'core', 'gfx'
      },
      toolchain 'vc_win' {
         link 'Setupapi.lib'
      }
   },

   app '-test' {
      icon 'icon/bengine-test-perf.ico',
      link_project {
         'testing',
         'platform',
         'gfx',
         'gfx-tex',
         'util-string',
         'core'
      }
   }
}
