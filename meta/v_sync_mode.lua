include 'common/enum'

v_sync = make_enum_class('be::platform::VSyncMode', 'U8', {
   'none',
   'wait_always',
   'wait_if_early',
})

include('common/enum_std_begin', v_sync)
include('common/enum_std_end', v_sync)
