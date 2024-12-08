
set(LibraryName "amutex")
add_library(${LibraryName})

target_sources(${LibraryName}  PUBLIC  impl/amutex.cpp)

target_include_directories(${LibraryName} PUBLIC
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
#$<INSTALL_INTERFACE:include/amutex>  # <prefix>/include/mylib TODO: explore installing the lib and using from another executable installing an exporting
)