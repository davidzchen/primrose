package(default_visibility = ["//visibility:public"])

cc_library(
    name = "int24",
    srcs = ["int24.cc"],
    hdrs = ["int24.h"],
)

cc_test(
    name = "int24_test",
    srcs = ["int24_test.cc"],
    deps = [
        ":int24",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)
