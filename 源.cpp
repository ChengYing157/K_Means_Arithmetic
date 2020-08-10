#define _CRT_SECURE_NO_WARNINGS
/*China(中国)
Japan(日本)
Korea(韩国)
Iran(伊朗)
Saudi(沙特)
Iraq(伊拉克)
Katar(卡塔尔)
UAE(阿联酋)
Uzbekistan(乌兹别克斯坦)
Thailand(泰国)
Vietnam(越南)
Oman(安曼)
Bahrain(巴林)
North_Korea(朝鲜)
Indonesia(印尼)*/

#include<stdio.h>//提供特殊函数
#include<math.h>//提供数学函数
#include<stdlib.h>
#include<string.h>

#define Data_Max 16//数据个数最大值
#define Name_Max 500//国家名字
#define Data_xyz 3//数据类型
#define Seed 3//标准种子

char Country[Data_Max][Name_Max] ;
double Data[Data_Max][Data_xyz];//输入各个国家近几年的比赛情况
double flag[Seed][Data_xyz];//分类标准数组
double Distance[Seed] = { 0 }, sum = 0;
int key_1 = 0, key_2 = 0, key_3 = 0;
int type_1[Data_Max] = { 0 }, type_2[Data_Max] = { 0 }, type_3[Data_Max] = { 0 };
int sort_1[Data_Max] = { 0 }, sort_2[Data_Max] = { 0 }, sort_3[Data_Max] = { 0 };
int s = 0, ReTemp;

void Read_Data();//数据输入函数
void Read_Name();//名字输入函数
void Normalization();//归一化处理函数
void Standard();//选择标准种子
void K_Means_Arithmetic();//算法
void Output();//输出函数

FILE* fp,*fp1;
errno_t err = 0,err1=0;

int main()
{
	Read_Name();
	Read_Data();
	Normalization();
	Standard();
	K_Means_Arithmetic();
	Output();
	return 0;
}

void Read_Data()
{
	int i;
	if ((err = fopen_s(&fp, "Data.txt", "r")) != 0)
	{
		printf("打开Data.txt文件失败!\n");
		system("pause");
		exit(0);
	}
	for (i = 0; i < Data_Max; i++)
	{
		fscanf_s(fp, "%lf%lf%lf", &Data[i][0], &Data[i][1], &Data[i][2]);
	}
	fclose(fp);//关闭文件
}

void Read_Name()
{
	int i;
	char* name,names[Name_Max];
	if ((err1 = fopen_s(&fp1, "Name.txt", "r")) != 0)
	{
		printf("打开Name.txt文件失败!\n");
		system("pause");
		exit(0);
	}
	for (int i = 0; i < Data_Max; i++) {
		fgets(names, Name_Max, fp1);
		name = strtok(names, "\n");
		strcpy_s(Country[i], name);
		/*printf("%s\n", signal_s[i].name);*/
	}
	fclose(fp1);//关闭文件
}

void Normalization()
{
	double Min, Max;
	for (int i = 0; i < 3; i++)
	{
		Min = Data[0][i], Max = Data[0][i];
		for (int j = 1; j < 15; j++)
		{
			if (Data[j][i] < Min)
			{
				Min = Data[j][i];
			}
			if (Data[j][i] > Max)
			{
				Max = Data[j][i];
			}
		}//找出单行的最大最小值
		for (int k = 0; k < 15; k++)
		{
			Data[k][i] = (float)(Data[k][i] - Min) / (Max - Min);//归一化处理
		}
	}
}

void Standard()
{
	int i, j;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (i == 0)
			{
				flag[i][j] = Data[1][j];
			}
			if (i == 1)
			{
				flag[i][j] = Data[12][j];
			}
			if (i == 2)
			{
				flag[i][j] = Data[9][j];
			}
		}
	}//分成三类,以中国\越南\阿联酋为一二三种子
	for (int i = 0; i < 3; i++)
	{
		printf("种子%d:  ", i);
		for (int j = 0; j < 3; j++)
		{
			printf("%lf    ", flag[i][j]);
		}
		printf("\n");
	}//输出种子信息,方便观察者了解
}

void K_Means_Arithmetic()
{
	while (key_1 == 0 && key_2 == 0 && key_3 == 0)
	{
		int q = 0, w = 0, e = 0, p = 0, temp = 0;
		int key_1 = 1, key_2 = 1, key_3 = 1;
		for (int m = 0; m < 15; m++)
		{
			double MinDis = 65536;
			Distance[0] = sqrt(pow((Data[m][0] - flag[0][0]), 2) + pow((Data[m][1] - flag[0][1]), 2) + pow((Data[m][2] - flag[0][2]), 2));
			Distance[1] = sqrt(pow((Data[m][0] - flag[1][0]), 2) + pow((Data[m][1] - flag[1][1]), 2) + pow((Data[m][2] - flag[1][2]), 2));
			Distance[2] = sqrt(pow((Data[m][0] - flag[2][0]), 2) + pow((Data[m][1] - flag[2][1]), 2) + pow((Data[m][2] - flag[2][2]), 2));
			for (int n = 0; n < 3; n++)
			{
				if (Distance[n] < MinDis)
				{
					MinDis = Distance[n];
				}
			}
			if (MinDis == Distance[0])
			{
				if (key_1 == 1 && type_1[q] == m + 1)
				{
					key_1 = 1;
				}
				else
				{
					key_1 = 0;
				}
				sort_1[q] = m + 1;
				type_1[q] = m + 1;
				q++;
			}
			if (MinDis == Distance[1])
			{
				if (key_2 == 1 && type_2[w] == m + 1)
				{
					key_2 = 1;
				}
				else
				{
					key_2 = 0;
				}
				sort_2[w] = m + 1;
				type_2[w] = m + 1;
				w++;
			}
			if (MinDis == Distance[2])
			{
				if (key_3 == 1 && type_3[e] == m + 1)
				{
					key_3 = 1;
				}
				else
				{
					key_3 = 0;
				}
				sort_3[e] = m + 1;
				type_3[e] = m + 1;
				e++;
			}
		}
		for (int j = 0; j < 3; j++)
		{
			while (sort_1[p] != 0)
			{
				temp = sort_1[p] - 1;
				sum = sum + Data[temp][j];
				p++;
			}
			flag[0][j] = (float)sum / p;
			sum = 0;
			p = 0;
			while (sort_2[p] != 0)
			{
				temp = sort_2[p] - 1;
				sum = sum + Data[temp][j];
				p++;
			}
			flag[1][j] = (float)sum / p;
			sum = 0;
			p = 0;
			while (sort_3[p] != 0)
			{
				temp = sort_3[p] - 1;
				sum = sum + Data[temp][j];
				p++;
			}
			flag[2][j] = (float)sum / p;
			sum = 0;
			p = 0;
		}
		if (key_1 == 1 && key_2 == 1 && key_3 == 1)
		{
			break;
		}
		int sort_1[15] = { 0 }, sort_2[15] = { 0 }, sort_3[15] = { 0 };
	}
}

void Output()
{
	printf("第一梯队：");
	while (sort_1[s] != 0)
	{
		ReTemp = sort_1[s];
		printf("%s  ", Country[ReTemp]);
		s++;
	}
	printf("\n");
	s = 0;
	printf("第二梯队：");
	while (sort_2[s] != 0)
	{
		ReTemp = sort_2[s];
		printf("%s  ", Country[ReTemp]);
		s++;
	}
	printf("\n");
	s = 0;
	printf("第三梯队：");
	while (sort_3[s] != 0)
	{
		ReTemp = sort_3[s];
		printf("%s  ", Country[ReTemp]);
		s++;
	}
}
