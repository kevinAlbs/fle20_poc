cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(openssl_aes_ctr LANGUAGES C)
find_package(OpenSSL COMPONENTS Crypto REQUIRED) # Looks for FindOpenSSL.cmake
add_executable (main.out main.c)
target_link_libraries (main.out OpenSSL::Crypto)
