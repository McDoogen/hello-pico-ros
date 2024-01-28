add_executable(hello
    hello.cpp
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(hello pico_stdlib)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(hello)