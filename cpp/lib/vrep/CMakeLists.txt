if(DEFINED ENV{VREP_PATH})
    MESSAGE(STATUS "VRep path found at $ENV{VREP_PATH}")
else()
    MESSAGE(FATAL_ERROR "VREP_PATH environment variable is not set. ")
endif()

# the following is required for windows (backslash issue..)
file(TO_CMAKE_PATH "$ENV{VREP_PATH}" ENV_VREP_PATH)

include_directories(include
                    ${ENV_VREP_PATH}/programming/remoteApi/
                    ${ENV_VREP_PATH}/programming/include/)

add_definitions(
  -DNON_MATLAB_PARSING 
  -DMAX_EXT_API_CONNECTIONS=255
  -DDO_NOT_USE_SHARED_MEMORY
)

add_library (vrep STATIC
    src/VRep.cpp
    ${ENV_VREP_PATH}/programming/remoteApi/extApi.c
    ${ENV_VREP_PATH}/programming/remoteApi/extApiPlatform.c)

target_link_libraries(vrep pthread)
