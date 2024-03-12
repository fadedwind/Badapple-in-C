#include<stdio.h>                   // 引入标准输入输出库
#include<stdlib.h>                  // 引入标准库
#include<windows.h>                 // 引入Windows API
#include<string.h>                  // 引入字符串处理库
#include<time.h>                    // 引入时间处理库

#include <mmsystem.h>               // 引入多媒体系统库
#pragma comment(lib, "WINMM.LIB")   // 链接到winmm.lib库

//cmd编译命令：-gcc badapple.c -o badapple -lwinmm

void recursur() // 重置控制台光标位置的函数
{
    HANDLE hout; // 控制台输出句柄
    COORD coord; // 光标
    coord.X = 0; // 光标的X坐标
    coord.Y = 0; // 光标的Y坐标
    hout = GetStdHandle(STD_OUTPUT_HANDLE); // 获取控制台输出句柄
    SetConsoleCursorPosition(hout,coord);   // 设置控制台光标位置
}

char F_filename(char* filename, char* f_index, int f_count){                                    //举例 此时f_count = 1                                                                    
    strcpy(filename, "out\\BA (");    // 构造文件名,将"out\\BA ("复制到filename中；               // filename: "out\\BA(      
    sprintf(f_index, "%d", f_count);  // 将帧计数f_count 的值转换为字符串，并将结果存储在f_index 中 //f_index变成字符串“1”，由f_count转化而来
    strcat(filename, f_index);        // 将帧编号添加到文件名(strcat: 将帧编号字符串放到seat末尾)   // filename: "out\\BA(1"
    strcat(filename, ").txt");        // 完成文件名的构造                                        // filename:"out\\BA(1).txt"
}

int main()
{
    void recursur(); // 声明一个函数，用于重置控制台光标位置

    clock_t stime = 0, ftime = 0;                // 初始化开始时间和结束时间
    int f_count = 0, interval = 33;              // 初始化目前的播放帧数(帧计数）  初始化帧间隔
    FILE *fp = NULL;                             // 文件指针，用于打开ASCII艺术帧文件
    char buffer[1920];                           // 初始化缓冲区

    char filename[]="out\\BA (0000).txt";        // 存放文件名的字符串
    char f_index[5];                             // 初始化帧编号字符串，用于辅助构建文件名filename
    
    printf("--Bad Apple ASCII art player--\nPress Enter to play.\n"); 
    getchar();      // 等待用户按键
    system("cls");  // 清除控制台

    PlaySound("BadApple.wav", NULL, SND_FILENAME | SND_ASYNC); // 播放背景音乐

    stime = clock();       // 记录开始时间
    while(f_count <= 6570) // 循环播放所有的ASCII艺术帧，共6570帧
    {	

        F_filename(filename,f_index,f_count);       // 函数：完成文件名的构造

        ftime = clock();                            // 记录当前时间

        interval = (f_count % 30 == 0) ?  43 : 33;  // 每30帧改变一次帧间隔

        if((ftime - stime) >= interval)             // 如果已经到了播放下一帧的时间
        {
            f_count++;                              // 帧数加1

            fp = fopen(filename, "r");            // 打开filename相应的文件 第二个参数为打开方式："r"只读
            fread(buffer, sizeof(buffer), 1, fp); // 读取ASCII艺术帧到缓冲区
            buffer[1920] = '\0';                  // 添加字符串结束符，确保buffer字符串在1920个字符后结束
            fclose(fp);                           // 关闭文件

            fprintf(stdout, "%s", buffer);        // 将帧打印到控制台
            fprintf(stdout, "Frame:%d", f_count); // 打印当前帧数

            stime += interval;                    // 更新开始时间
            recursur();                           // 重置控制台光标位置	
        }
    }

    system("cls"); // 清除控制台

    printf("~~Bad Apple ASCII art player~~\nThanks for watching!\nPress Enter to Exit.\n"); // 打印结束信息
    getchar(); 
    return 0; 
}










// FILE *fopen(const char *filename, const char *mode);
// 该函数接受两个参数：filename 和 mode。filename 是一个字符串，表示要打开的文件的路径和名称。mode 是一个字符串，表示打开文件的模式，可以是以下几种之一：
// "r"：只读方式打开文件。如果文件不存在，打开操作将失败。
// "w"：写入方式打开文件。如果文件存在，文件内容将被清空；如果文件不存在，将创建一个新文件。
// "a"：追加方式打开文件。如果文件存在，写入操作将从文件末尾开始；如果文件不存在，将创建一个新文件。
// "r+"：读写方式打开文件。文件必须存在，读写操作可以在任意位置进行。
// "w+"：读写方式打开文件。如果文件存在，文件内容将被清空；如果文件不存在，将创建一个新文件。
// "a+"：读写方式打开文件。如果文件存在，写入操作将从文件末尾开始；如果文件不存在，将创建一个新文件。


// int fprintf(FILE *stream, const char *format, ...);
// 该函数接受多个参数，其中最重要的是 stream 和 format。stream 是一个指向流对象的指针，用于指定数据的输出目标。
// format 是一个格式化字符串，用于指定数据的输出格式。
//... 表示可变参数，可以传入多个值，用于替换 format 字符串中的占位符。

