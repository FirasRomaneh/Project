load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])


cc_library(
    name = "ImageReader",
    srcs = ["ImageReader.cpp"],
    hdrs = ["ImageReader.h"],
    deps = ["//Code/Reader:Reader", "//Code/ImageType:ImageType"],
)
