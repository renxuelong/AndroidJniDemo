cmake_minimum_required(VERSION 3.4.1)

add_library(jni_test # 指定库的名称

    # 指定 library 的类型为共享库
    SHARED

    # 提供源文件的相对路径
    src/main/jni/jni_test_01.c
)