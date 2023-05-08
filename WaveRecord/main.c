#include <stdio.h>

int main()
{
    struct SetConfig //录播参数结构体
    {
        char cmd_uid[10];   //编号
        char interval_steps[2]; //间隔步数
        char record_steps[10];  //记录步数
        char variables[100];   //需录播变量名数组
    };
    struct TaskStart   //任务参数结构体
    {
       char cmd_uid[10];    //编号
       char realtime_mode[2];   //模式选择
       char step_nsec[10];  //仿真时间长度
       char steps[10];  //仿真步数
       char warm_steps[10]; //警告步数
    };
    struct SetConfig RecordWaveDate = {0,0,0,0};
    struct TaskStart TaskStartDate = {0,0,0,0,0};

    char TaskStop_uid[10] = {0};//仿真停止编号存储
    char InputTemp[7] = {0};
    char Startcmd[7] = {"./csgd"};//开始指令
    int InputSize = 0;
    int StartFlag = 0;

    while(1)
    {
        scanf("%S",InputTemp);
        InputSize = sizeof(InputTemp);

        for (int i = 0; i < 6; i++)//比对判断是否是启动主框架指令
        {
            if (Startcmd[i] == InputTemp[i])
            {
                StartFlag++;
            }       
        }
        if (StartFlag == 6)    //是正确主框架启动指令，开始下面操作 && InputSize == 6
        {
            while(1)
            {
                char RcdWaveCmdTemp[100] = {0};//录波指令临时存储单元
                char Precmd[9] = {"csgacmd "};//前置指令符
                char SaveWaveConfigCmd[31] = {"task-record set-configuration "};//配置录波参数指令
                char TaskStartcmd[12] = {"task start "};//仿真开始指令
                char TaskStopCmd[11] = {"task stop "};//仿真停止指令
                char CmdRightFlag = 0;//判断指令是否正确标志位
                char ConfigErroFlag = 0;//定义报错标志位
                char StartErroFlag = 0;//仿真开始报错标志位
                char StopErroFlag = 0;//仿真结束报错标志位

                gets(RcdWaveCmdTemp);
                for (int i = 0; i < 8; i++) //对比判断是否是正确预指令Csgacmd
                {
                    if (Precmd[i] == RcdWaveCmdTemp[i])
                    {
                        CmdRightFlag++;
                    }
                }
                if (CmdRightFlag == 8)  //是正确预指令Csgacmd，执行下面操作
                {
                    CmdRightFlag = 0; //临时标志位
                    for (int i = 8, j = 0; i < 38 && j<30; i++, j++) //对比判断是否是正确操作指令task-record
                    {
                        if (SaveWaveConfigCmd[j] == RcdWaveCmdTemp[i])
                            CmdRightFlag++;
                    }
                    if (CmdRightFlag == 30)  //task-record操作
                    {
                        int SaveTemp = 0;
                        for (int i = 38, j = 0; RcdWaveCmdTemp[i] != ' '; i++, j++) //存入UID
                        {
                            RecordWaveDate.cmd_uid[j] = RcdWaveCmdTemp[i];
                            SaveTemp = i;
                        }
                        for (int i = SaveTemp + 2, j = 0; RcdWaveCmdTemp[i] != ' '; i++, j++)   //存入间隔步数interval_steps
                        {
                            RecordWaveDate.interval_steps[j] = RcdWaveCmdTemp[i];
                            SaveTemp = i;
                        }
                        for (int i = SaveTemp + 2, j = 0; RcdWaveCmdTemp[i] != ' '; i++, j++)   //存入记录步数record_steps
                        {
                            RecordWaveDate.record_steps[j] = RcdWaveCmdTemp[i];
                            SaveTemp = i;
                        }
                        for (int i = SaveTemp + 2, j = 0; RcdWaveCmdTemp[i] != ' '; i++, j++)   //存入要录播的变量名variables
                        {
                            RecordWaveDate.variables[j] = RcdWaveCmdTemp[i];
                            SaveTemp = 0;
                        }
                        ConfigErroFlag = 1;   //表示命令正确
                    } 

                    CmdRightFlag = 0; //临时标志位
                    for (int i = 8, j = 0; i < 19 && j<11; i++, j++) //对比判断是否是正确操作指令task start
                    {
                        if (TaskStartcmd[j] == RcdWaveCmdTemp[i])
                            CmdRightFlag++;
                    }
                    if (CmdRightFlag == 11)  //task start操作
                    {
                        int SaveTemp = 0;
                        for (int i = 19, j = 0; RcdWaveCmdTemp[i] != ' '; i++, j++) //存入UID
                        {
                            TaskStartDate.cmd_uid[j] = RcdWaveCmdTemp[i];
                            SaveTemp = i;
                        }
                        for (int i = SaveTemp + 2, j = 0; RcdWaveCmdTemp[i] != ' '; i++, j++)   //存入实时模式realtime_mode
                        {
                            TaskStartDate.realtime_mode[j] = RcdWaveCmdTemp[i];
                            SaveTemp = i;
                        }
                        for (int i = SaveTemp + 2, j = 0; RcdWaveCmdTemp[i] != ' '; i++, j++)   //存入仿真时间step_nsec
                        {
                            TaskStartDate.step_nsec[j] = RcdWaveCmdTemp[i];
                            SaveTemp = i;
                        }
                        for (int i = SaveTemp + 2, j = 0; RcdWaveCmdTemp[i] != ' '; i++, j++)   //存入仿真步数steps
                        {
                            TaskStartDate.steps[j] = RcdWaveCmdTemp[i];
                            SaveTemp = i;
                        }
                        for (int i = SaveTemp + 2, j = 0; RcdWaveCmdTemp[i] != ' '; i++, j++)   //存入警告步数warm_steps
                        {
                            TaskStartDate.warm_steps[j] = RcdWaveCmdTemp[i];
                            SaveTemp = 0;
                        }
                        StartErroFlag = 1;   //表示命令正确
                    }

                    CmdRightFlag = 0; //临时标志位
                    for (int i = 8, j = 0; i < 18 && j<10; i++, j++) //对比判断是否是正确操作指令task stop
                    {
                        if (TaskStopCmd[j] == RcdWaveCmdTemp[i])
                            CmdRightFlag++;
                    }
                    if (CmdRightFlag == 10)  //task stop操作
                    {
                        for (int i = 18, j = 0; RcdWaveCmdTemp[i] != '\n'; i++, j++) //存入UID
                        {
                            TaskStop_uid[j] = RcdWaveCmdTemp[i];
                        }
                        StopErroFlag = 1;   //表示命令正确
                    }
                    if (ConfigErroFlag == 0 && StartErroFlag == 0 && StopErroFlag == 0)
                    {
                        printf("command error");    //报错
                    }
                    else if (ConfigErroFlag == 1)
                    {
                        for (int i = 0; i < sizeof(RecordWaveDate.cmd_uid); i++)
                        {
                            printf("%d",RecordWaveDate.cmd_uid[i]);
                        }
                        printf("\t");
                        for (int i = 0; i < sizeof(RecordWaveDate.interval_steps); i++)
                        {
                            printf("%d",RecordWaveDate.interval_steps[i]);
                        }
                        printf("\t");
                        for (int i = 0; i < sizeof(RecordWaveDate.record_steps); i++)
                        {
                            printf("%d",RecordWaveDate.record_steps[i]);
                        }
                        printf("\t");
                        for (int i = 0; i < sizeof(RecordWaveDate.variables); i++)
                        {
                            printf("%d",RecordWaveDate.variables[i]);
                        }
                        printf("\n");
                    }
                    else if (StartErroFlag == 1)
                    {
                        for (int i = 0; i < sizeof(TaskStartDate.cmd_uid); i++)
                        {
                            printf("%d",TaskStartDate.cmd_uid[i]);
                        }
                        printf("\t");
                        for (int i = 0; i < sizeof(TaskStartDate.realtime_mode); i++)
                        {
                            printf("%d",TaskStartDate.realtime_mode[i]);
                        }
                        printf("\t");
                        for (int i = 0; i < sizeof(TaskStartDate.step_nsec); i++)
                        {
                            printf("%d",TaskStartDate.step_nsec[i]);
                        }
                        printf("\t");
                        for (int i = 0; i < sizeof(TaskStartDate.steps); i++)
                        {
                            printf("%d",TaskStartDate.steps[i]);
                        }
                        printf("\t");
                        for (int i = 0; i < sizeof(TaskStartDate.warm_steps); i++)
                        {
                            printf("%d",TaskStartDate.warm_steps[i]);
                        }
                        printf("\n");
                    }
                    else if (StopErroFlag == 1)
                    {
                        for (int i = 0; i < sizeof(TaskStop_uid); i++)
                        {
                            printf("%d",TaskStop_uid[i]);
                        }
                        printf("\n");
                    }
                    // CmdRightFlag = 0;
                    // RcdWaveCmdTemp[] = {"0"};
                }
                else
                {
                    printf("An error was entered in the operation command\n");
                }
            }
        }
        else
        {
            printf("Startup command error, please try again.\n");
        }
    }

    return 0;  
}