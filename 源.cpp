#define _CRT_SECURE_NO_WARNINGS
/*China(�й�)
Japan(�ձ�)
Korea(����)
Iran(����)
Saudi(ɳ��)
Iraq(������)
Katar(������)
UAE(������)
Uzbekistan(���ȱ��˹̹)
Thailand(̩��)
Vietnam(Խ��)
Oman(����)
Bahrain(����)
North_Korea(����)
Indonesia(ӡ��)*/

#include<stdio.h>//�ṩ���⺯��
#include<math.h>//�ṩ��ѧ����
#include<stdlib.h>
#include<string.h>

#define Data_Max 16//���ݸ������ֵ
#define Name_Max 500//��������
#define Data_xyz 3//��������
#define Seed 3//��׼����

char Country[Data_Max][Name_Max] ;
double Data[Data_Max][Data_xyz];//����������ҽ�����ı������
double flag[Seed][Data_xyz];//�����׼����
double Distance[Seed] = { 0 }, sum = 0;
int key_1 = 0, key_2 = 0, key_3 = 0;
int type_1[Data_Max] = { 0 }, type_2[Data_Max] = { 0 }, type_3[Data_Max] = { 0 };
int sort_1[Data_Max] = { 0 }, sort_2[Data_Max] = { 0 }, sort_3[Data_Max] = { 0 };
int s = 0, ReTemp;

void Read_Data();//�������뺯��
void Read_Name();//�������뺯��
void Normalization();//��һ��������
void Standard();//ѡ���׼����
void K_Means_Arithmetic();//�㷨
void Output();//�������

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
		printf("��Data.txt�ļ�ʧ��!\n");
		system("pause");
		exit(0);
	}
	for (i = 0; i < Data_Max; i++)
	{
		fscanf_s(fp, "%lf%lf%lf", &Data[i][0], &Data[i][1], &Data[i][2]);
	}
	fclose(fp);//�ر��ļ�
}

void Read_Name()
{
	int i;
	char* name,names[Name_Max];
	if ((err1 = fopen_s(&fp1, "Name.txt", "r")) != 0)
	{
		printf("��Name.txt�ļ�ʧ��!\n");
		system("pause");
		exit(0);
	}
	for (int i = 0; i < Data_Max; i++) {
		fgets(names, Name_Max, fp1);
		name = strtok(names, "\n");
		strcpy_s(Country[i], name);
		/*printf("%s\n", signal_s[i].name);*/
	}
	fclose(fp1);//�ر��ļ�
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
		}//�ҳ����е������Сֵ
		for (int k = 0; k < 15; k++)
		{
			Data[k][i] = (float)(Data[k][i] - Min) / (Max - Min);//��һ������
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
	}//�ֳ�����,���й�\Խ��\������Ϊһ��������
	for (int i = 0; i < 3; i++)
	{
		printf("����%d:  ", i);
		for (int j = 0; j < 3; j++)
		{
			printf("%lf    ", flag[i][j]);
		}
		printf("\n");
	}//���������Ϣ,����۲����˽�
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
	printf("��һ�ݶӣ�");
	while (sort_1[s] != 0)
	{
		ReTemp = sort_1[s];
		printf("%s  ", Country[ReTemp]);
		s++;
	}
	printf("\n");
	s = 0;
	printf("�ڶ��ݶӣ�");
	while (sort_2[s] != 0)
	{
		ReTemp = sort_2[s];
		printf("%s  ", Country[ReTemp]);
		s++;
	}
	printf("\n");
	s = 0;
	printf("�����ݶӣ�");
	while (sort_3[s] != 0)
	{
		ReTemp = sort_3[s];
		printf("%s  ", Country[ReTemp]);
		s++;
	}
}
