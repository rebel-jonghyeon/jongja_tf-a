# Override the C standard used for compilation to C 2011.
# This is due to some apps using static_assert which is a 2011 feature.
set_property(GLOBAL PROPERTY CSTD c11)
