#include <stdio.h>
#include <stdlib.h>
#include<time.h>   //用到clock()函数
#define n_infinite -100000
#define p_infinite -100000
#define MAX 1024*512+1

//void set_up_Binary(char *filename,int **array);
void set_up_Binary(char *filename,int *array);
void InsertSort(int max,int *array);
void Shellsort(int max, int *array);
void gen_random(int max, char *filename);
int menu();

int main()
{
    int *array = (int *)malloc(sizeof(int)*MAX);
    int begintime,endtime;
    char* filename[6] = {"1024_16.txt","1024_32.txt","1024_64.txt","1024_128.txt","1024_256.txt","1024_512.txt"};
    int max[6] = {1024*16+1,1024*32+1,1024*64+1,1024*128+1,1024*256+1,1024*512+1};
    int choice;
    int i;
    while(1)
    {
        choice = menu();
        switch(choice)
        {
        case 1:
            printf("插入排序时间性能分析\n");
            for(i=0;i<6;i++)
            {
                set_up_Binary(filename[i],array);
                begintime=clock();	//计时开始
                InsertSort(max[i],array);
                endtime = clock();	//计时结束
                printf("数据集大小为%d个整数,排序消耗时间%dms\n",max[i]-1,endtime-begintime);
            }
            break;
        case 2:
            printf("希尔排序时间性能分析\n");
            for(i=0;i<6;i++)
            {
                set_up_Binary(filename[i],array);
                begintime=clock();	//计时开始
                Shellsort(max[i],array);
                endtime = clock();	//计时结束
                printf("数据集大小为%d个整数,排序消耗时间%dms\n",max[i]-1,endtime-begintime);
            }
            break;
        case 3:
            free(array);
            exit(0);
        }


    }
    return 0;
}
int menu()
{
    int choice;
    printf("本程序实现的功能：\n");
    printf("1、分析插入排序时间性能\n");
    printf("2、分析希尔排序时间性能\n");
    printf("3、退出");
    printf("请输入你的选择：");
    scanf("%d",&choice);
    return choice;
}
void gen_random(int max, char *filename)
{
    FILE *fp = fopen(filename,"w");
    srand(time(NULL));
    int i=0;
    int target;
    while(i<max)
    {
        target = (int)(1+rand()%max*2);
        fprintf(fp,"%d\n",target);
        i++;
    }
}
void Shellsort(int max, int *array)
{
    int i, j, k, x;
    for(k = max/2; k >= 1; k /= 2)
    {
        //组内排序，将x直接插入到组内合适的位置
        for( i=k+1; i<max; i++ )
        {
            x = array[i];
            j = i-k;
            while((j>0)&&(x<array[j]))
            {
                array[j+k] = array[j];
                j -= k;
                array[j+k] = x;
            }
        }
    }
}
void set_up_Binary(char *filename,int *array)
{
    FILE *fp;
    fp = fopen(filename,"r");
    if(fp==NULL)
    {
        printf("打开文件失败\n");
        exit(1);
    }
    int num;
    int max = 1;
    while(!feof(fp))
    {
        fscanf(fp,"%d\n",&num);
        array[max] = num;
        max++;
    }
    fclose(fp);
}


void InsertSort(int max,int *array)
{
    int  i, j, temp;
    array[0] = n_infinite;//监视哨
    for(i=1; i<max; i++)
    {
        j=i;
        temp = array[j];
        while(temp<array[j-1])
        {
            array[j] = array[j-1];
            j--;
        }
        array[j] = temp;
    }
}
