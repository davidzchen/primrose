package(default_visibility = ["//visibility:public"])

cc_library(
    name = "bcd",
    srcs = ["bcd.cc"],
    hdrs = ["bcd.h"],
    deps = [
        "@abseil-cpp//absl/types:span",
    ],
)

cc_test(
    name = "bcd_test",
    srcs = ["bcd_test.cc"],
    deps = [
        ":bcd",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)
