include 'common/enum'

window_flag = make_enum_class('be::platform::WindowFlag', 'U8', {
   'resizable',
   'undecorated',
   'transparent',
   'fullscreen',
   'monitor_exclusive',
   'system_positioned',
   'centered',
   'srgb_capable',
   'custom_gamma',
   'debug_context',
   'forward_compatible_context',
})

include('common/enum_std_begin', window_flag)
include('common/enum_std_end', window_flag)
