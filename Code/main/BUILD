load("@rules_cc//cc:defs.bzl", "cc_library", "cc_binary")

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


cc_binary(
    name = "main",
    srcs = ["main.cpp"],
    deps = ["//Code/Driver:Driver"],
)