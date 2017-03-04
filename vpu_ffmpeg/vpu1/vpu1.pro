TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
#CONFIG -= qt

SOURCES += \
    utils.c \
    loopback.c \
    fb.c \
    enc.c \
    display.c \
    dec.c \
    capture.c \
    transcode.c \
    ffmpeg.c \
    main.c \
    librtmp_sendh264.c \
    sps_decode.c

OTHER_FILES += \
    vpu1.pro.user

HEADERS += \
    vpu_test.h \
    vpu_jpegtable.h \
    dut_probes_vts.h \
    dut_api_vts.h \
    sps_decode.h \
    librtmp_send264.h

INCLUDEPATH += /usr/local/vpu/include
LIBS += /usr/local/vpu/lib/*

INCLUDEPATH += /usr/local/arm/sdl/include
INCLUDEPATH += /usr/local/arm/lame/include/lame
INCLUDEPATH += /usr/local/arm/xvid/include
LIBS += -L/usr/local/arm/sdl/lib -lSDL
LIBS += -L/usr/local/arm/lame/lib -lmp3lame
LIBS += -L/usr/local/arm/xvid/lib -lxvidcore -lpostproc

INCLUDEPATH += /usr/local/arm/1/ffmpeg/include
INCLUDEPATH += /usr/local/arm/1/h264/include
LIBS += -L/usr/local/arm/1/ffmpeg/lib -lavfilter -lavcodec -lavdevice\
        -lavformat -lavutil -lswresample -lswscale
LIBS += -L/usr/local/arm/1/h264/lib -lx264

INCLUDEPATH += /usr/local/opencv-arm/include
INCLUDEPATH += /usr/local/opencv-arm/include/opencv
INCLUDEPATH += /usr/local/opencv-arm/include/opencv2

LIBS += /usr/local/opencv-arm/lib/libopencv_highgui.so
LIBS += /usr/local/opencv-arm/lib/libopencv_core.so
LIBS += /usr/local/opencv-arm/lib/libopencv_imgproc.so
LIBS += /usr/local/opencv-arm/lib/libopencv*.so

#rtmp
INCLUDEPATH += /usr/local/arm/rtmp/include
LIBS += /usr/local/arm/rtmp/lib/librtmp.so

DESTDIR = /home/vincent/nfsroot/
