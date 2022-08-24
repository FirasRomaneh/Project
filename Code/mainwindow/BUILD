load("//tools/build_rules:qt.bzl", "qt_cc_library")

package(default_visibility = ["//visibility:public"])


qt_cc_library(
    name = "mainwindow",
    src = "mainwindow.cpp",
    hdr = "mainwindow.h",
    copts = [
        '-fpic',
    ],
    deps = [ "//Code/DataStore:DataStore", 
        "//Code/ImageType:ImageType",
        "//Code/GPSType:GPSType",
        "//Code/DoubleType:DoubleType",
        "//Code/main:opencv",
        "@qt//:qt_core",
        "@qt//:qt_widgets",
        "@qt//:qt_gui",
    ],
    ui = "mainwindow.ui",
    ui_deps = [
        "@qt//:qt_widgets",
    ],
)