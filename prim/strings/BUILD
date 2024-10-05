package(default_visibility = ["//visibility:public"])

cc_library(
    name = "color",
    hdrs = ["color.h"],
    deps = [
        "@abseil-cpp//absl/strings",
    ],
)

cc_test(
    name = "color_test",
    srcs = ["color_test.cc"],
    deps = [
        ":color",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)
