include 'common/enum'

profile_type = make_enum_class('be::platform::ContextProfileType', 'U8', {
   'any',
   'core',
   'compatibility',
})

include('common/enum_std_begin', profile_type)
include('common/enum_std_end', profile_type)
