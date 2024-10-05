package(default_visibility = ["//visibility:public"])

cc_library(
    name = "file",
    srcs = ["file.cc"],
    hdrs = ["file.h"],
    deps = [
        "@abseil-cpp//absl/base:nullability",
        "@abseil-cpp//absl/status",
        "@abseil-cpp//absl/strings",
        "@abxl//abxl/status:status_macros",
    ],
)

cc_test(
    name = "file_test",
    srcs = ["file_test.cc"],
    data = [
        "testdata/foo",
    ],
    deps = [
        ":file",
        "@abxl//abxl/file:path",
        "@abxl//abxl/status:status_matchers",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)
