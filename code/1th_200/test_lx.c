#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>


#define N 20
#define LEN 20

typedef struct student
{
	long num;
	char name[LEN];
	float score[3];
}STUDENT;

void Welcome(void);
void Thanks(void);
void EN_LO(void);
void Enroll(void);
void LoginCheck(void);
void Manage(void);
void AboutAuthor(void);
void InputInfo(void);
void WritetoFile(STUDENT *p,int n);
void Show(void);
void Transcript(STUDENT *p,int n,float *sumstu,float *sumcou);
void LimitScore(STUDENT *p,int n,float *sumstu);
int Ascending(float a,float b);
int Descending(float a,float b);
void PrintScore(STUDENT *p,int n,float *sumstu);
void SelectSortSum(STUDENT *p,int n,float *sumstu,int (*compare)(float a,float b));
void Swap(STUDENT *p,int i,int k,float *sumstu);
void SelectSortNum(STUDENT *p,int n,float *sumstu);
int SearchbyNum(STUDENT *p,int n);
int SearchbyName(STUDENT *p,int n);
void ListGrade(STUDENT *p,int n,int count[][5]);
void ReadfromFile(STUDENT *p, int n);
int ReadN(void);
void SumStu(STUDENT *p,int n,float *sumstu);
void SumCou(STUDENT *p,int n,float *sumcou);
void SelectSortName(STUDENT *p,int n,float *sumstu);
void PasswordCorrect(void);
void Print(STUDENT *p,int n,float *sumstu,float *sumcou);

int main()
{
	Welcome();
	EN_LO();
	return 0;

}

void Welcome(void)
{
	int i;
	for (i=0;i <=100;i=i+30)
	{
		printf("\n\n\n\n\t\t\t\t********\n");
		printf("\t\t\t\tWelcome!\n");
		printf("\t\t\t\t********\n");
		printf("\n\t\t\t\t  %d%%\n\n\n",i);
		sleep(1);
		
	}
		//system("color 0");
		sleep(1);
		
		//system("color 1");
		sleep(1);

		//system("color 2");
		sleep(1);
}

void EN_LO(void)
{
	int choose;
	while(1)
	{
		printf("  **************µÇ Â¼ ×¢ ²á Ïµ Í³ ************  ");
		printf(" \n\n\n\n\t\t\t  1.  ×¢ ²á 2.   µÇ Â¼ 3. ¹Ø ÓÚ 4. ÍË ³ö");
		printf("\n\n\t\n\t\t Choose :");
		scanf("%d",&choose);
		switch (choose)
		{
			case 1:
				Enroll();
				break;

			case 2:
				LoginCheck();
				break;

			case 3:
				AboutAuthor();
				break;
			
			case 4:
			{
				Thanks();
				exit(0);
			}

			default:
				{
					printf("\n\t\t\t\tInput erro!\n");
					while((choose=getchar())!='\n');
				}
			
		}
	}
	
}


void Enroll(void)
{
	FILE *fp;
	int flag = 0;
	char ch;
	char name[20],password[20],repassword[20];

	do{
		//system("cls");
		printf("************zhucexitong*****************");
		printf("\n\n\n\n\t\t\t yonghuming :");
		scanf("%s",name);
		printf("\n\n\t\t\t\tmima: ");
		scanf("%s",password);
		if (strlen(password) != 6)
		{
			printf("\n\t\t\t mimazhinengwei 6wei !shifouchengshi?[Y\\y or n\\N]\n");
			printf("\n\t\t\t\tchoose");
			getchar();
			ch = getchar();
			if ((ch == 'Y') || (ch == 'y'))
			{
				continue;
			}else
				return;
		}

		printf("\n\n\t\t\tquerenmingma: ");
		scanf("%s",repassword);
		if (strcmp(password,repassword) != 0)
		{
			printf("\n\t\t\t\tmmabuyizhi!shifouchongshi?[Y\\y or N\\n]\n");
			printf("\n\t\t\tchoose: ");
			getchar();
			ch = getchar();
			if ((ch == 'Y') || (ch == 'y'))
			{
				continue;
			}else
				return;
			
		}
		
		if ((fp = fopen("login.bin","wb")) == NULL)
		{
			printf("\n\n\t\t\tlogin.bin cannot open to write!\n");
			exit(0);
		}
		fprintf(fp,"%s %s",name,password);
		fclose(fp);
		flag = 1;

	}while(flag !=1);
	

}


//dengluxitong 
void LoginCheck(void)
{

	FILE *fp;
	int flag1 = 0,flag2 =0;
	char ch;
	char name[20],password[20],rename[10],repassword[20];

	do
	{
		printf("*************dengluxitong *******************");
		printf("\n\n\t\t\tyonghuming: ");
		if ((fp=fopen("login.bin","rb")) == NULL)
		{
			printf("\n\n\t\t\tlogin.bin cannot open to read!\n");
			exit(0);
		}
		fscanf(fp,"%s",name);
		scanf("%s",rename);
		if (strcmp(rename,name) == 0)
			flag1 = 1;
		else
		{
			printf("\n\n\t\t\t\tyonghumingbucunzai!shifouchongshi[Y\\y or N\\n]\n");
			printf("\n\t\t\t\tchoose:");
			getchar();
			ch =getchar();
			if ((ch == 'Y') || (ch =='y'))
			{
				continue;
			}
			else
			{
				return ;
			}
		}
		
		printf("\n\t\t\tmima :");
		fscanf(fp,"%s",password);
		scanf("%s",repassword);
		if (strcmp(repassword,password) == 0)
			flag2 = 1;
		else
			{

				getchar();
				ch = getchar();
				if ((ch == 'Y') || (ch == 'y'))
					{
						continue;
					}
				else
					{
						return ;
					}
			}
	}while(flag1 != 1|| flag2 != 1);
		fclose(fp);
		system("pause");
		Manage();

}


//guanlidaoduxitong 
void Manage(void)
{
	int choose;
	system("color 3e");
	while (1)
	{
		printf("*************guanlidiaoduxitong*******************\n");
		printf("\n\t\t1. shurufenshu 2.tongjijieguo 3.xiugaimima \n\t\t4.guanyu \t 5.tuichu\n\n");
		printf("\t\tchoose:");
		scanf("%d",&choose);
		switch (choose)
		{
			case 1:
				InputInfo();
				break;
			
			case 2:
				Show();
				break;

			case 3:
				PasswordCorrect();
				break;

			case 4:
				AboutAuthor();
				break;
			
			case 5:
				{
					Thanks();
					exit(0);
				}
			
			default:
			{
				printf("input erro !\n");
				//system("pause");
				while((choose = getchar())!= '\n');
			}
			
		}
	}
}


void AboutAuthor(void)
{
	int i;
	for (i =0; i <= 100; i= i+10)
	{
		printf("\n\n\n\n\t\t\t%d%%\n",i);
		sleep(1);
	}
	printf("\n\n\t\t\tAbuout author :\n\n");
	printf("\n\n\t\t\tMade by wuhai :\n\n");
	
}


void Thanks(void)
{
	int i;
	for (i =0; i <=100 ;i= i + 10)
	{
		printf("\n\n\n\n\t\t********\n");
		printf("\t\t\t Thanks !\n");
		printf("\t\t\t\t********\n");
		printf("\n\t\t\t %d%%\n\n\n",i);
		sleep(1);
	}

}

void InputInfo(void)
{
	STUDENT *p = NULL;
	int i,j,n;
	printf("**********xinxiluruxitong********************\n");
	printf("Please enter the number of the students: ");
	scanf("%d",&n);
	p = (STUDENT *)malloc(n * sizeof(STUDENT));
	if (p == NULL)
	{
		printf("No enough memory!\n");
		exit(0);
	}
	printf("Please input this informations:\n");
	printf("num\\name\\MT\\EN\\PH\n");
	for (i=0;i <n; i++)
	{
		printf("\nthe %d student :\n",i + 1);
		scanf("%ld",&p[i].num);
		scanf("%s",  p[i].name);
		for (j =0; j <3;j ++)
			scanf("%f",&p[i].score[j]);
	}
	WritetoFile(p,n);
	free(p);
}

void WritetoFile(STUDENT *p,int n)
{
	FILE *fp1,*fp2;
	int i,j;
	if ((fp1 = fopen("info.txt","w")) == NULL)
	{
		printf("info.txt cannot open to write!\n");
		exit(0);
	}
	
	for (i =0;i <n; i++)
	{
		fprintf(fp1,"%ld %s",p[i].num,p[i].name);
		for (j = 0;j <3;j++)
			fprintf(fp1,"%f",p[i].score[j]);
	}
	fclose(fp1);
	
	if ((fp2 = fopen("n.txt","w")) == NULL)
	{
		printf("n.txt cannot open to write!\n");
		exit(0);
	}
	fprintf(fp2,"%d",n);
	fclose(fp2);
	
}


void Show(void)
{
	int i,j,n,choose,count[3][5] = {0};
	float sumstu[N],sumcou[3],averstu = 0.0f,avercou[3];
	STUDENT *p = NULL;
	n = ReadN();
	p = (STUDENT *)malloc(n*sizeof(STUDENT));
	ReadfromFile(p,n);
	SumStu(p,n,sumstu);
	SumCou(p,n,sumcou);

	while (1)
	{
		printf("**********************tongjiguanlixitong**********************\n");
		printf("\n\t\t 1.chakanchengjidan \t 2.xueshengzongfen \t 3.kechengzongfen\n \n\t\t4.xueshengpingjunfen\t5.kechengpingjunfen\t6.zuigaozuidifeng\n");
		printf(" \n\tt13.gekedengjitongji\t14.dayinchengji\t15.guanyu\n\t\t16.fanhuishangyiji\n ");
		scanf("%d",&choose);
		switch (choose)
		{
			case 1:
				Transcript(p,n,sumstu,sumcou);
				break;

			case 2:
				{
					printf("num\t\tname\tsumstu\n");
					for (i =0;i <n;i++)
					{
						printf("%-12ld\t%s\t%.1f\n",p[i].num,p[i].name,sumstu[i]);
					}
					printf("\n");
					break;
				}

			case 3:
				{
					printf("  sumMT\tsumEN\tsumPH\n ");
					for (j =0;j <3;j++)
					{
						printf("%1.f\t",sumcou[j]);
					}
					printf("\n\n");
					break;
				}

			  case 4:
			  	{

					for (i=0;i < n;i++)
						averstu += sumstu[i];

					averstu/=n;
					printf("The average score of the %d students is %1.f\n",n,averstu);
					printf("\n");
					break;
			  	}

			 case 5:
			 	{
					for (j =0;j <3;j++)
					{
						avercou[j] = sumcou[j]/n;
					}
					printf("averMT\taverEN\taverPH\n");
					for (j =0;j <3;j++)
					{
						printf("%.1f\t",avercou[j]);
					}
					printf("\n\n");
					break;
					
			 	}

			 case 6:
			 	{
					LimitScore(p,n,sumstu);
					break;
			 	}

			 case 7:
			 	{
					SelectSortSum(p,n,sumstu,Ascending);
					PrintScore(p,n,sumstu);
					break;
			 	}

			 case 8:
			 	{
					SelectSortSum(p,n,sumstu,Descending);
					PrintScore(p,n,sumstu);
					break;
			 	}
			 
			 case 9:
			 	{
					SelectSortNum( p, n, sumstu);
					PrintScore(p,n,sumstu);
					break;
			 	}
			 
			 case 10:
			 	{
					SelectSortName(p,n,sumstu);
					PrintScore(p,n,sumstu);
					break;
			 	}

			 case 11:
			 	{
					SelectSortSum(p, n, sumstu, Ascending);
					i = SearchbyNum(p,n);
					if (i == -1)
					{
						printf("not found!\n\n");
					}
					else
					{
						printf("\nnum\t\tname\tsumstu\trandking\n");
						printf("%-12ld\t%s\t%.1f\t%d\n\n",p[i].num,p[i].name,sumstu[i],i+1);
						
					}
					break;
			 	}

			 case 12:
			 	{
					SelectSortSum(p,n,sumstu, Ascending);
					i = SearchbyName(p,n);
					if (i == -1)
					{
						printf("not found!\n");
					}
					else
					{
						printf("\nnum\t\tname\tsumstu\tranking\n");
						printf("%-12ld\t%s\t%.1f\t%d\n\n",p[i].num,p[i].name,sumstu[i],i+1);
						
					}
					break;
			 	}

			 case 13:
			 	{
					ListGrade(p,n,count);
					printf("\tMT\t\tEN\t\tPH\n");
					printf("A\t");
					for (j =0;j <3;j++)
					{
						printf("%d\t%.1f%%\t",count[j][0],(float)count[j][0]*20);
					}
					printf("\n");
					printf("B\t");
					for (j =0;j <3;j++)
					{
						printf("%d\t%.1f%%\t",count[j][1],(float)count[j][1]*20);
					}
					printf("\n");
					printf("C\t");
					for (j =0;j <3;j++)
					{
						printf("%d\t%.1f%%\t",count[j][2],(float)count[j][2]*20);
					}
					printf("\n");
					printf("D\t");

					for (j =0;j <3;j++)
					{
						printf("%d\t%.1f%%\t",count[j][3],(float)count[j][3]*20);
					}
					printf("\n");
					printf("E\t");
					for (j =0;j <3;j++)
					{
						printf("%d\t%.1f%%\t",count[j][4],(float)count[j][4]*20);
					}
					printf("\n");
					break;
			 	}

			 case 14:Print(p,n,sumstu,sumcou);break;
			 case 15:AboutAuthor();break;
			 case 16:return;
			 default:
			 	{
					printf("input error!\n\n");
					while((choose=getchar())!='\n');
			 	}
		}
	}
}


void Transcript(STUDENT *p,int n,float *sumstu,float *sumcou)
{
	int i,j;
	printf("\t\tTranscript\n\nnum\t\t\name\tMT\tEN\tPH\tsumstu\taverstu\n");
	for (i=0; i <n; i++)
	{
		printf("%ld %s",p[i].num,p[i].name);
		
		for (j=0;j <3;j++)
			printf("%f",p[i].score[j]);

		printf("%f %f\n",sumstu[i],sumcou[i]/3);
	}
	
	for (j=0;j <3;j++)
	{
		printf("%1.f\t",sumstu[j]);
	}
	printf("\navercou\t\t\t");
	
	for(j =0;j <3;j++)
	{
		printf("%f",sumcou[j]/n);
	}
	printf("\n\n");
	
}


void LimitScore(STUDENT *p,int n,float *sumstu)
{
	int i,maxnum = 0,minnum =0;
	float max = sumstu[0],min = sumstu[0];
	for (i =1;i < n;i++)
	{
		if (sumstu[i] > max)
		{
			max = sumstu[i];
			maxnum = i;
		}
		
		if (sumstu[i] < min)
		{
			min = sumstu[i];
			minnum = i;
		}
	}
	printf(" \t\tnum\t\tname\t sumstu\n ");

}


int Ascending(float a,float b)
{
	return a < b;

}

int Descending(float a,float b)
{
	return a > b;
}


void PrintScore(STUDENT *p,int n,float *sumstu)
{
	int i,j;
	printf("num\t\tname\tMT\tEN\tPH\tsumstu\n");
	for (i=0;i <n;i++)
	{
		printf("%-12ld\t\t%s\t",p[i].num,p[i].name);
		for (j=0;j <3;j++)
			printf("%.1f\t",p[i].score[j]);
		printf("%.1f\n",sumstu[i]);
	}
	printf("\n");
}

void SelectSortSum(STUDENT *p,int n,float *sumstu,int (*compare)(float a,float b))
{
	int i,j,k;
	for (i=0;i < n -1;i++)
	{
		k = i;
		for (j = i + 1;j < n;j++)
		{
			if ((*compare)(sumstu[k],sumstu[j]))
				k = j;
				
		}
		if (k != i)
		{
			Swap(p,i,k,sumstu);
		}
	}
	

}


void SelectSortNum(STUDENT *p,int n,float *sumstu)
{
	int i,j,k;
	for (i =0;i < n- 1;i++)
	{
		k = i;
		for (j =i +1;j <n;j++)
		{
			if (p[k].num > p[j].num)
				k =j;
			
		}
		if (k != i)
		{
			Swap(p, i,k, sumstu);
		}
	}

}

void Swap(STUDENT *p,int i,int k,float *sumstu)
{
	int m;
	long temp1;
	char temp2[LEN];
	float temp3;
	float temp[3];
	temp1 = p[i].num;p[i].num=p[k].num;p[k].num = temp1;
	strcpy(temp2,p[i].name);strcpy(p[i].name,p[k].name);strcpy(p[k].name,temp2);
	temp3 = sumstu[i];sumstu[i] =sumstu[k];sumstu[k] =temp3;
	
	for (m = 0;m <3;m++)
	{
		temp[m] = p[i].score[m];
		p[i].score[m] = p[k].score[m];
		p[k].score[m] = temp[m];

	}
}

void SelectSortName(STUDENT *p,int n,float *sumstu)
{
	int i,j,k;
	for (i=0;i < n -1;i++)
	{
		k =i;
		for (j = i +1;i <n;j++)
		{
			if (strcmp(p[k].name,p[j].name) > 0)
				k =j;
		}
		if (k != i)
		{
			Swap(p, i, k, sumstu);
		}

	}

}


int SearchbyNum(STUDENT *p,int n)
{
	int i,flag = 0;
	long search;
	printf("The search num: ");
	scanf("%ld",&search);
	for (i =0;i < n;i++)
	{
		if (search == p[i].num)
		{
			flag = 1;
			break;
		}
	}

	if (flag)
	{
		return i;
	}
	else
	{
		return -1;	
	}

}

int SearchbyName(STUDENT *p,int n)
{
	int i,flag = 0;
	char search[LEN];
	printf("The search name :");
	scanf("%s",search);
	for (i =0;i <n;i++)
	{
		if (strcmp(search,p[i].name) == 0)
			{
				flag =1;
				break;
			}
	}
	if (flag)
		return i;
	else
		return -1;
}


void ListGrade(STUDENT *p,int n,int count[][5])
{
	int i,j,t;
	for (i=0;i <n;i++)
	{
		for (j =0;j <3;j++)
			{
				t = (int)p[i].score[j]/10;

				switch (t)
				{
					case 6:count[j][3] ++;break;					
					case 7:count[j][2] ++;break;
					case 8:count[j][1] ++;break;
					case 9:
					case 10:count[j][0] ++;break;
					default:count[j][4] ++;break;
				}
			}
	}

}

void ReadfromFile(STUDENT *p, int n)
{	
	FILE *fp;
	int i,j;
	if ((fp = fopen("info.txt","r")) == NULL)
	{
		printf("info.txt cannot open!\n");
		exit(0);
	}

	for (i=0; i <n;i++)
	{
		fscanf(fp,"%ld %s",&p[i].num,p[i].name);
		for (j=0;j <3;j++)
			fscanf(fp,"%f",&p[i].score[j]);
	}
	fclose(fp);
}

int ReadN(void)
{
	FILE *fp;
	int n;
	if ((fp = fopen("n.txt","r")) == NULL)
	{
		printf("n.txt cannot open to read!\n");
		exit(0);
	}
	fscanf(fp,"%d",&n);
	fclose(fp);
	return n;
}

void SumStu(STUDENT *p,int n,float *sumstu)
{
	int i,j;
	for (i=0;i <n;i++)
	{
		sumstu[i] = 0;
		for (j=0;j <3;j++)
			{
				sumstu[i] += p[i].score[j];
			}
	}
}

void SumCou(STUDENT *p,int n,float *sumcou)
{
	int i,j;
	for (j =0;j <3;j++)
	{
		sumcou[j] = 0;
	}
	for (i=0;i <n;i++)
	{
		for (j =0;j <3;j++)
			sumcou[j] += p[i].score[j];
	}

}


void PasswordCorrect(void)
{
	FILE *fp1,*fp2;
	char ch1,ch,passwrod[20],oldpassword[20],newpassword1[20],newpassword2[20],name[20];
	int flag1 =0,flag2 = 0;
	printf("************mimaxiugai********\n");
	printf("ni quedingyao xiugai mima ma ?(Y\\y or N\\n) :");
	getchar();
	ch1 = getchar();
	if ((ch1 == 'Y') || (ch1 == 'y'))
		{
			printf("\n\n\t\t\tyuansimima:");
			scanf("%s",oldpassword);
			if ((fp1 = fopen("login.bin","rb")) == NULL)
				{
					printf("\n\n\t\t\tlogin.bin cannot open to read!\n");
					exit(0);
				}
			fscanf(fp1,"%s %s",name,passwrod);
			fclose(fp1);
			if (strcmp(passwrod,oldpassword) == 0)
				{
					do
					{
						printf("************mimaxiugai********\n");
						printf("\n\n\t\t\tyuanshimima :%s",passwrod);
						printf("\n\n\n\txindemima:");
						scanf("%s", newpassword1);
						if (strlen(newpassword1)==6)
							flag1 =1;
						else
						{
							printf("\n\t\t\tmimazhiyou 6wei:shifouchongshi?[Y\\y or N\\n]\n");
							printf("\n\t\t\t\tchoose");
							getchar();
							ch = getchar();
							if ((ch == 'Y') || (ch == 'y'))
							{
								continue;
							}
							else
							{
								return ;
							}
						}
						printf("\n\n\t\t\tquerenmingma");
						scanf("%s",newpassword2);
						if ((strcmp(newpassword1,newpassword2)) ==0)
							flag2 =1;
						else
							{
								printf("\n\n\t\t\tliangcimima?[Y\\y or N \\n]\n");
								printf("\n\t\t\tchoose :");
								getchar();
								ch = getchar();
								if ((ch == 'Y') || (ch == 'y'))
									{
										continue;
									}
								else
									{
										return ;
									}
							}
						
					}while(!flag1 || !flag2);
					if ((fp2 = fopen("login.bin","wb")) == NULL)
					{
						printf("\n\n\t\t\t\tlogin.bin cannot open to write");
						exit(0);
					}
					fprintf(fp2,"%s %s",name,newpassword1);
					printf("\n\n\t\t\t\txiugaimimachenggong!\n");
					fclose(fp2);
						
				}
			else
				{
					printf("\n\n\t\t\t miamashurucuowu!\n");
					
				}
		}
		else
			return ;

}

void Print(STUDENT *p,int n,float *sumstu,float *sumcou)
{
	FILE *fp;
	int i,j;
	char location[40];
	printf("Please enter the file path (including the file name) :\n");
	printf("For example : d\\\21.xls or d:\\\\2.txt\n");
	scanf("%s",location);
	if ((fp = fopen(location,"w")) == NULL)
		{
			printf("dayinshibai,qingjianchashurulujinggeshi");
			exit(0);
		}
	fprintf(fp,"\t\t\t%s\n\n%s\t\t%s\t%s\t%s\t%s\t%s\t%s\n","Transcript","num","name","MT","EN","PH","sumstu","averstu");
	for (i=0;i <n;i++)
	{
		fprintf(fp,"%-12ld\t%s\t",p[i].num,p[i].name);
		for (j =0;j <3;j++)
			fprintf(fp,"%.1f\t",p[i].score[j]);
		fprintf(fp,"%.1f\t%.1f\t",sumstu[i],sumstu[i]/3);
		fprintf(fp,"%c",'\n');
	}
	fprintf(fp,"%s","sumcout\t\t\t\t");
	for (j=0;j <3;j++)
	{
		fprintf(fp,"%.1f\t",sumcou[j]);
	}
	fprintf(fp,"%s","\navercou\t\t\t");
	for (j=0;j <3;j++)
		{
			fprintf(fp,"%.1f\t",sumcou[j]/n);
		}
	fclose(fp);
	printf("\nPrint suceess!\n\n");
}

