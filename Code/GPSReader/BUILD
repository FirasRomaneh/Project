load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])


cc_library(
    name = "GPSReader",
    srcs = ["GPSReader.cpp"],
    hdrs = ["GPSReader.h"],
    deps = ["//Code/Reader:Reader", "//Code/GPSType:GPSType"],
)