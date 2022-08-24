load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])


cc_library(
    name = "Driver",
    srcs = ["Driver.cpp"],
    hdrs = ["Driver.h"],
    deps = ["//Code/ImageReader:ImageReader", "//Code/GPSReader:GPSReader", 
    "//Code/DoubleReader:DoubleReader", "//Code/mainwindow:mainwindow"],
)

