set(swift_private_libc_extras_flags)
if(SWIFT_STDLIB_HAS_ENVIRON)
  set(swift_private_libc_extras_flags "-D" "SWIFT_STDLIB_HAS_ENVIRON")
endif()

if(SWIFT_STDLIB_STATIC_PRINT)
  list(APPEND swift_private_libc_extras_flags "-D" "SWIFT_STDLIB_STATIC_PRINT")
endif()

set(swift_private_libc_extras_incorporate_object_libraries)
if(SWIFT_STDLIB_HAS_COMMANDLINE)
  list(APPEND swift_private_libc_extras_flags "-D" "SWIFT_STDLIB_HAS_COMMANDLINE")
else()
  set(swift_private_libc_extras_incorporate_object_libraries "swiftCommandLineSupport")
endif()

set(swift_private_libc_extras_darwin_dependencies)

if((SWIFT_BUILD_CLANG_OVERLAYS
    OR SWIFT_BUILD_TEST_SUPPORT_MODULES)
   AND (NOT DEFINED SWIFT_BUILD_CLANG_OVERLAYS_SKIP_BUILTIN_FLOAT
        OR NOT SWIFT_BUILD_CLANG_OVERLAYS_SKIP_BUILTIN_FLOAT))
  # This library imports Darwin from the SDK, which re-exports
  # _Builtin_float which is part of this build.
  list(APPEND swift_private_libc_extras_darwin_dependencies _Builtin_float)
endif()

add_swift_target_library(swiftSwiftPrivateLibcExtras ${SWIFT_STDLIB_LIBRARY_BUILD_TYPES} IS_STDLIB
  # This file should be listed the first.  Module name is inferred from the
  # filename.
  SwiftPrivateLibcExtras.swift
  Subprocess.c
  Subprocess.swift

  "${SWIFT_SOURCE_DIR}/stdlib/linker-support/magic-symbols-for-install-name.c"

  SWIFT_MODULE_DEPENDS SwiftPrivate
  SWIFT_COMPILE_FLAGS ${SWIFT_STANDARD_LIBRARY_SWIFT_FLAGS} ${swift_private_libc_extras_flags}
  SWIFT_MODULE_DEPENDS_OSX ${swift_private_libc_extras_darwin_dependencies}
  SWIFT_MODULE_DEPENDS_IOS ${swift_private_libc_extras_darwin_dependencies}
  SWIFT_MODULE_DEPENDS_TVOS ${swift_private_libc_extras_darwin_dependencies}
  SWIFT_MODULE_DEPENDS_WATCHOS ${swift_private_libc_extras_darwin_dependencies}
  SWIFT_MODULE_DEPENDS_XROS ${swift_private_libc_extras_darwin_dependencies}
  SWIFT_MODULE_DEPENDS_MACCATALYST ${swift_private_libc_extras_darwin_dependencies}
  SWIFT_MODULE_DEPENDS_FREESTANDING "${SWIFT_FREESTANDING_TEST_DEPENDENCIES}"
  SWIFT_MODULE_DEPENDS_ANDROID Android
  SWIFT_MODULE_DEPENDS_LINUX Glibc
  SWIFT_MODULE_DEPENDS_LINUX_STATIC Musl
  SWIFT_MODULE_DEPENDS_FREEBSD Glibc
  SWIFT_MODULE_DEPENDS_OPENBSD Glibc
  SWIFT_MODULE_DEPENDS_CYGWIN Glibc
  SWIFT_MODULE_DEPENDS_HAIKU Glibc
  SWIFT_MODULE_DEPENDS_WASI WASILibc
  SWIFT_MODULE_DEPENDS_WINDOWS CRT WinSDK
  INCORPORATE_OBJECT_LIBRARIES ${swift_private_libc_extras_incorporate_object_libraries}
  INSTALL_IN_COMPONENT stdlib-experimental
  DARWIN_INSTALL_NAME_DIR "${SWIFT_DARWIN_STDLIB_PRIVATE_INSTALL_NAME_DIR}"
  MACCATALYST_BUILD_FLAVOR "zippered")
