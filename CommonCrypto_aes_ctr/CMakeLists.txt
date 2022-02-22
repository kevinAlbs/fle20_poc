cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(CommonCrypto_aes_ctr LANGUAGES C)
add_executable (main.out main.c)
target_link_libraries (main.out PRIVATE "-framework CoreFoundation -framework Security")
