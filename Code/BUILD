load("//tools/build_rules:qt.bzl", "qt_cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "opencv",
    linkopts = [
        "-lopencv_core",
        "-lopencv_calib3d",
        "-lopencv_features2d",
        "-lopencv_highgui",
        "-lopencv_imgcodecs",
        "-lopencv_imgproc",
        "-lopencv_video",
        "-lopencv_videoio",
        ],
)

cc_library(
    name = "Type",
    srcs = ["Type.h"],
    hdrs = ["local.h"],
)

cc_library(
    name = "GPSType",
    srcs = ["GPSType.h"], 
    deps = ["Type"],
)

cc_library(
    name = "DoubleType",
    srcs = ["DoubleType.h"], 
    deps = ["Type"],
)

cc_library(
    name = "ImageType",
    srcs = ["ImageType.h"], 
    deps = [":opencv", "Type"],
)

cc_library(
    name = "DataStore",
    srcs = ["DataStore.cpp"],
    hdrs = ["DataStore.h"],
    deps = ["Type"],
)

cc_library(
    name = "ClockManager",
    srcs = ["ClockManager.cpp"],
    hdrs = ["ClockManager.h"],
    deps = ["DataStore"],
)

cc_library(
    name = "Reader",
    srcs = ["Reader.h"],
    deps = ["ClockManager"],
)

cc_library(
    name = "ImageReader",
    srcs = ["ImageReader.cpp"],
    hdrs = ["ImageReader.h"],
    deps = ["Reader", "ImageType"],
)

cc_library(
    name = "GPSReader",
    srcs = ["GPSReader.cpp"],
    hdrs = ["GPSReader.h"],
    deps = ["Reader", "GPSType"],
)

cc_library(
    name = "DoubleReader",
    srcs = ["DoubleReader.cpp"],
    hdrs = ["DoubleReader.h"],
    deps = ["Reader", "DoubleType"],
)

cc_library(
    name = "Driver",
    srcs = ["Driver.cpp"],
    hdrs = ["Driver.h"],
    deps = ["ImageReader", "GPSReader", "DoubleReader", "mainwindow"],
)

qt_cc_library(
    name = "mainwindow",
    src = "mainwindow.cpp",
    hdr = "mainwindow.h",
    copts = [
        '-fpic',
    ],
    deps = [ "DataStore", 
        "ImageType",
        "GPSType",
        "DoubleType",
        ":opencv",
        "@qt//:qt_core",
        "@qt//:qt_widgets",
        "@qt//:qt_gui",
    ],
    ui = "mainwindow.ui",
    ui_deps = [
        "@qt//:qt_widgets",
    ],
)



cc_binary(
    name = "main",
    srcs = ["main.cpp"],
    deps = ["Driver"],
)