# Install script for directory: /home/conmed/Documents/GitHub_Nebs/pw-design/design/software/pw-controller-sw/hal/pw-hal-flux-v1/lib/core/hf-core-drivers/external/hf-pf1550-driver

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/conmed/Documents/GitHub_Nebs/pw-design/design/software/pw-controller-sw/hal/pw-hal-flux-v1/lib/core/hf-core-drivers/external/hf-pf1550-driver/inc/" FILES_MATCHING REGEX "/[^/]*\\.hpp$" REGEX "/[^/]*\\.h$" REGEX "/[^/]*\\.h\\.in$" EXCLUDE)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES "/home/conmed/Documents/GitHub_Nebs/pw-design/design/software/pw-controller-sw/hal/pw-hal-flux-v1/lib/core/hf-core-drivers/external/hf-pf1550-driver/build-verify/hf_pf1550_generated/pf1550_version.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/hf_pf1550/hf_pf1550Targets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/hf_pf1550/hf_pf1550Targets.cmake"
         "/home/conmed/Documents/GitHub_Nebs/pw-design/design/software/pw-controller-sw/hal/pw-hal-flux-v1/lib/core/hf-core-drivers/external/hf-pf1550-driver/build-verify/CMakeFiles/Export/lib/cmake/hf_pf1550/hf_pf1550Targets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/hf_pf1550/hf_pf1550Targets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/hf_pf1550/hf_pf1550Targets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/hf_pf1550" TYPE FILE FILES "/home/conmed/Documents/GitHub_Nebs/pw-design/design/software/pw-controller-sw/hal/pw-hal-flux-v1/lib/core/hf-core-drivers/external/hf-pf1550-driver/build-verify/CMakeFiles/Export/lib/cmake/hf_pf1550/hf_pf1550Targets.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/hf_pf1550" TYPE FILE FILES
    "/home/conmed/Documents/GitHub_Nebs/pw-design/design/software/pw-controller-sw/hal/pw-hal-flux-v1/lib/core/hf-core-drivers/external/hf-pf1550-driver/build-verify/hf_pf1550Config.cmake"
    "/home/conmed/Documents/GitHub_Nebs/pw-design/design/software/pw-controller-sw/hal/pw-hal-flux-v1/lib/core/hf-core-drivers/external/hf-pf1550-driver/build-verify/hf_pf1550ConfigVersion.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/conmed/Documents/GitHub_Nebs/pw-design/design/software/pw-controller-sw/hal/pw-hal-flux-v1/lib/core/hf-core-drivers/external/hf-pf1550-driver/build-verify/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
