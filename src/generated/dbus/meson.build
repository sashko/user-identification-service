gdbus_codegen = find_program('gdbus-codegen-glibmm3')

gdbus_codegen_deps = [
    giomm_dep,
    glibmm_dep
]

interfaces_dir = join_paths(meson.source_root(), 'data')
dbus_build_dir = meson.current_build_dir()

# com.luxoft.UserIdentification
tdbs_dbus_sources = custom_target('User Identification D-Bus source',
    command : [ gdbus_codegen, '--generate-cpp-code=' + join_paths(dbus_build_dir, 'user_identification'), '@INPUT@' ],
    input : join_paths(interfaces_dir, 'com.luxoft.UserIdentification.xml'),
    output : [
        'user_identification_common.cpp',
        'user_identification_common.h',
        'user_identification_proxy.cpp',
        'user_identification_proxy.h',
        'user_identification_stub.cpp',
        'user_identification_stub.h'
    ])

tdbs_dbus_headers = [ tdbs_dbus_sources[1], tdbs_dbus_sources[3], tdbs_dbus_sources[5] ]

tdbs_dbus_lib = static_library('user_identification_dbus_service_dbus',
    sources : tdbs_dbus_sources,
    dependencies : gdbus_codegen_deps)

tdbs_dbus_dep = declare_dependency(link_with : tdbs_dbus_lib, sources : tdbs_dbus_headers)
