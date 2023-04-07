cmake_minimum_required(VERSION 3.24)
project(photopicker C)

set(CMAKE_C_STANDARD 23)

add_executable(photopicker main.c util/List.c util/List.h util/FolderFormatter.c util/FolderFormatter.h)
