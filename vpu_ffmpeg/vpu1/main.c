#include <sys/stat.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <getopt.h>
#include "vpu_test.h"
#include "librtmp_send264.h"

#define ONE_FRAME_INTERV 100000 // 100 ms

struct input_argument {
	int mode;
	pthread_t tid;
	char line[256];
	struct cmd_line cmd;
};

int quitflag;

static struct input_argument input_arg[MAX_NUM_INSTANCE];
static int instance;
static int using_config_file;

int vpu_test_dbg_level;

int decode_test(void *arg);
int encode_test(void *arg);
int encdec_test(void *arg);
int transcode_test(void *arg);

//RTMP264
struct vpu_h264_out_buffer vpu_out_buffer;

unsigned char *raw_data;
unsigned char *current_ptr;

int main(int argc, char *argv[])
{

    vpu_out_buffer.index = 0;
    raw_data = (unsigned char *)malloc(1024 * 1024 * 30);
    current_ptr = raw_data;

    int err, nargc, i, ret = 0;
	vpu_versioninfo ver;
	//获取输入内容
	input_arg[0].mode = ENCODE;

	framebuf_init();//初始化framebuf

	err = vpu_Init(NULL);
	if (err) {
		err_msg("VPU Init Failure.\n");
		return -1;
	}

	err = vpu_GetVersionInfo(&ver);
	if (err) {
		err_msg("Cannot get version info, err:%d\n", err);
		vpu_UnInit();
		return -1;
	}

	info_msg("VPU firmware version: %d.%d.%d_r%d\n", ver.fw_major, ver.fw_minor,
						ver.fw_release, ver.fw_code);
	info_msg("VPU library version: %d.%d.%d\n", ver.lib_major, ver.lib_minor,
						ver.lib_release);

	input_arg[0].cmd.chromaInterleave = 1;
	if (cpu_is_mx6x())
		input_arg[0].cmd.bs_mode = 1;

	
    strncpy(input_arg[0].cmd.input, "/mnt/nfs/blue.nv12", MAX_PATH);//-i 输入文件名
    input_arg[0].cmd.src_scheme = PATH_FILE;//属于文件类型

//    input_arg[0].cmd.video_node_capture = 0;
//    input_arg[0].cmd.src_scheme = PATH_V4L2;//属于摄像头类型
	
    //live.tla001.cn/live/test1
//    strncpy(input_arg[0].cmd.output, "rtmp://219.216.87.28/myapp/test1", MAX_PATH);//-o 输出文件名
//    input_arg[0].cmd.dst_scheme = PATH_LIBRTMP;//librtmp tui liu

    strncpy(input_arg[0].cmd.output, "/mnt/nfs/myblue2.mp4", MAX_PATH);//-o 输出文件名
    input_arg[0].cmd.dst_scheme = PATH_MV;//输出为文件类型
	
	input_arg[0].cmd.format = 2;//-f  0 - MPEG4, 1 - H.263, 2 - H.264, 3 - VC1, 7 - MJPG

    input_arg[0].cmd.width = 1280;//-w 长

    input_arg[0].cmd.height = 720;//-h 高

    input_arg[0].cmd.count=700;//采集帧数
	input_arg[0].cmd.rot_angle=0;
	input_arg[0].cmd.mirror=0;
    input_arg[0].cmd.bitrate=4000; //0-32767
    input_arg[0].cmd.gop=12; //
    input_arg[0].cmd.fps = 25;
	

    //打开输入文件
    input_arg[0].cmd.src_fd = open(input_arg[0].cmd.input, O_RDONLY, 0);
    if (input_arg[0].cmd.src_fd < 0) {
        perror("file open");
        return -1;
    }
    info_msg("Input file \"%s\" opened.\n",input_arg[0].cmd.input);

	//打开输出文件
    input_arg[0].cmd.dst_fd = open(input_arg[0].cmd.output, O_CREAT | O_RDWR | O_TRUNC,
                S_IRWXU | S_IRWXG | S_IRWXO);
    if (input_arg[0].cmd.dst_fd < 0) {
        perror("file open");

        if (input_arg[0].cmd.src_scheme == PATH_FILE)
            close(input_arg[0].cmd.src_fd);

        return -1;
    }
    info_msg("Output file \"%s\" opened.\n", input_arg[0].cmd.output);


    ffmpeg_init();
    ffmpeg_parameters_set(&input_arg[0].cmd, "flv");
	

//    RTMP264_Connect("rtmp://219.216.87.28/myapp/test1");

	ret = encode_test(&input_arg[0].cmd);

//    RTMP264_Close();

    ffmpeg_clean(&input_arg[0].cmd);

	close_files(&input_arg[0].cmd);
	
	vpu_UnInit();
	return ret;
}
