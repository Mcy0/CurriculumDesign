#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define  HEAD printf("\t|%-10s%-8s%-9s%-5s%-10s%-5s%-5s%-5s%-5s%-12s%-5s|\n","学号","姓名","专业","班级","公寓名","宿舍","床位","性别","年纪","手机号","级别")
/*
		密码登录 
		管理登录信息 
*/
typedef struct EN{//存用户和密码 
	char userName1[10];
	char passWorld1[10];
}EN;
void enter();
void encryption(char passWorld[])//加密
{
	int i; 
	for(i=0;i<strlen(passWorld);i++)
	{
		passWorld[i]+=20;
	} 
} 
void  sign_in(char userName[],char passWorld[])//注册
{
	FILE *fp;
	int flag=0;
	char userName1[10];
	char passWorld1[10];
	printf("\t注册(用户名密码最多9位)\n");
	printf("\t用户名:");
	fflush(stdin);
	gets(userName);
	printf("\t密码:");
	gets(passWorld);
	if((fp=fopen("enter.txt","rt"))==NULL)
	{
		exit(0);
	}
	while(!feof(fp))
	{
		fscanf(fp,"%s %s",userName1,passWorld1);
		if(!strcmp(userName,userName1))
		{
			printf("用户名重复\n");
			flag=1;
			break;
		}
	}
	fclose(fp);
	if(flag==1)
	enter();
	else
	{
		if((fp=fopen("enter.txt","at"))==NULL)
		exit(0);
		encryption(passWorld);//加密
		fprintf(fp,"%s %s\n",userName,passWorld);
	}
	fclose(fp);
	enter(); 
}
void alter()//删除不合法用户 
{
	FILE *fp;
	int n=0;
	EN en[1000];
	fp=fopen("enter.txt","rt");
	if(fp==NULL)
	{
		printf("\t打开文件失败\n");
		exit(0);
	}
	while(!feof(fp))
	{
		fscanf(fp,"%s %s",en[n].userName1,en[n].passWorld1);
		n++;
	}
	//printf("大小%d\n",--n);
	printf("\t%-8s\t%-8s\n","用户名","密码");
	int i;
	for(i=0;i<n;i++)
	{
		printf("\t%-8s\t%-8s\n",en[i].userName1,en[i].passWorld1);
	}
	fclose(fp);
	printf("\t输入你要删除的用户名\n");
	printf("\t用户名:");
	char ch[10];
	printf("\t");
	scanf("%s",ch);
	for(i=0;strcmp(ch,en[i].userName1);i++){}
	int k=i;
	for(i=k;i<n-1;i++)
	{
		en[i]=en[i+1];
	}
	n--;
//	for(i=0;i<n;i++)
//	{
//		printf("%-8s\t%-8s\n",en[i].userName1,en[i].passWorld1);
//	}
	fp=fopen("enter.txt","wt");
	if(fp==NULL)
	{
		printf("\t打开文件失败\n");
		exit(0);
	}
	for(i=0;i<n;i++)
	{
		fprintf(fp,"%s %s\n",en[i].userName1,en[i].passWorld1);
	}
	fclose(fp);	
}
void enter()		//登录入口 
{
	printf("\t=================================\n"); 
	printf("\t|\t登录:\t\t\t|\n");
	printf("\t=================================\n");
	FILE *fp;
	int i;
	
	printf("\t1.管理员\t2.登录\n");
	char userName[10];
	char passWorld[10];
	char userName1[10];
	char passWorld1[10];
	int choice;
	printf("\t");
	scanf("%d",&choice);
	int flag=0;
	switch(choice)
	{
		case 1:{        //管理员，注册用户和删除 
			char adm[10]; 
			printf("\t输入权限码\n");
			printf("\t");
			scanf("%s",adm);
			if(strcmp(adm,"12"))
			{
				printf("\t权限码错误\n");
				enter();
			}
			printf("\t");
			printf("1.注册\t2.修改\n");
			int j;
			printf("\t");
			scanf("%d",&j);
			switch(j)
			{
				case 1:{
					sign_in(userName,passWorld);
					break;
				}
				case 2:{
					int flag1=0;
					do
					{
						alter();
						flag1=0;
						printf("\t是否继续删除：1.是  2.否\n");
						printf("\t");
						scanf("%d",&flag1);
					}
					while(flag1==1);
					enter();
					break;
				}
				default:{
					break;
				}
			}			
			break;
		}
		case 2:{     //用户登录 
			printf("\t登录\n");
			printf("\t用户名:");
			fflush(stdin);
			printf("\t");
			gets(userName);
			printf("\t密码:");
			printf("\t");
			gets(passWorld);
			if((fp=fopen("enter.txt","rt"))==NULL)
			{
				exit(0);
			}
			while(!feof(fp))
			{
				fscanf(fp,"%s %s",userName1,passWorld1);
				encryption(passWorld);//加密
				if(!strcmp(userName,userName1)&&!strcmp(passWorld,passWorld1))
				{
					flag=1;
					break;
				}
			}
			if(flag==0)
			{
				printf("\t输入用户名密码不匹配或者错误\n");
				enter();
			}
			printf("\t成功\n");
			break;
		}
		default:{
			printf("输入选择不符合格式\n");
			break;
		}
	}
}
/*
			存储数据 
			操作数据 
*/

typedef struct stu{  //宿舍信息 
	char dorm[50];
	int dorm_num;
	int dorm_num_id;
	char id[10];
	char name[10];
	int banji;
	char major[20];
	int age;
	int enUniversity;
	char number[12];
	char sex[3]; 
	struct stu *next;
}stu;
void print(stu *head);
void interface()//主界面 
{
	printf("\n\n");
	printf("\t---------------------------------------------------------\n"); 
	printf("\t|\t\t欢迎使用宿舍信息管理系统\t\t|\n");
	printf("\t---------------------------------------------------------\n");
	/*
		数据录入 
	*/ 
	printf("\t|\t\t\t1-录入数据\t\t\t|\n"); 
	/*
		数据增删改查 
	*/ 
	printf("\t|\t\t\t2-数据增加\t\t\t|\n");  
	printf("\t|\t\t\t3-数据删除\t\t\t|\n");
	printf("\t|\t\t\t4-数据修改\t\t\t|\n");
	printf("\t|\t\t\t5-数据查询\t\t\t|\n");
	/*
		数据统计 
	*/ 
	printf("\t|\t\t\t6-数据统计\t\t\t|\n");
	/*
		报表 
	*/ 
	printf("\t|\t\t\t7-数据报表\t\t\t|\n");
	printf("\t---------------------------------------------------------\n");
}
int find_id(char id[],stu *head)//学号查重,重复返回0，否则1 
{
	stu *i;
	for(i=head->next;i!=NULL;i=i->next)
	{
		if(strcmp(id,i->id)==0)
		{
			printf("\t学号重复\n");
			return 0;
		}
	}
	return 1;
}
int find_check(stu *head,stu *p) //检查宿舍是否满员,符合返回1，不符合返回0 
{
	//print(head);   //测试 
	//printf("进入\n");
	stu *i;
	for(i=head->next;i!=NULL;i=i->next)
	{
		if(!strcmp(p->dorm,i->dorm)&&(p->dorm_num_id==i->dorm_num_id)&&(p->dorm_num==i->dorm_num))
		{
			printf("\t宿舍信息重复\n");
			return 0;
		}
	}
	return 1;
}
stu *creat()//创建链表 
{
	
	stu *head,*end,*p;
	char id[10];
	head=NULL;
	head=(stu*)malloc(sizeof(stu));
	head->next=NULL;
	end=head;
	printf("\t输入学号:");
	fflush(stdin);
	gets(id);
	while(strlen(id)>0)
	{
		
		if(find_id(id,head))//学号查重,重复返回0，否则1 
		{
			p=(stu*)malloc(sizeof(stu));
			strcpy(p->id,id);
			printf("\t输入姓名:");	
			gets(p->name);
			printf("\t输入公寓名称:");			
			scanf("%s",p->dorm);
			printf("\t输入宿舍名称:");
			scanf("%d",&p->dorm_num);
			printf("\t输入床位号:");
			scanf("%d",&p->dorm_num_id);
			if(find_check(head,p))  //检查宿舍是否满员,符合返回1，不符合返回0 
			{		
				printf("\t手机号:");
				fflush(stdin);
				gets(p->number); 
				printf("\t年龄:");
				scanf("%d",&p->age); 
				printf("\t性别:");
				scanf("%s",p->sex); 
				printf("\t专业班级:");
				scanf("%s %d",p->major,&p->banji);
				printf("\t输入入学年份:");
				scanf("%d",&p->enUniversity);
				end->next=p;
				end=p;
				p->next=NULL;
			} 	
		}
		printf("\t输入学号:");
		fflush(stdin);
		gets(id);
	}
	return head;
}
void print(stu *head)//链表打印输出 
{
	
	stu *i;
	for(i=head->next;i!=NULL;i=i->next)
	{
		printf("\t|%-10s%-8s%-9s%-5d%-10s%-5d%-5d%-5s%-5d%-12s%-5d|\n",i->id,i->name,i->major,i->banji,i->dorm,i->dorm_num,i->dorm_num_id,i->sex,i->age,i->number,i->enUniversity);
	}
}
stu *write_linked()  //文件生成链表 
{
	
	FILE *fp;
	fp=fopen("student.txt","rt");
	stu *i;
	stu *head;
	head=NULL;
	head=(stu*)malloc(sizeof(stu));
	stu *end,*p;
	end=head;
	while(!feof(fp))
	{
		p=(stu*)malloc(sizeof(stu));
		fread(p,sizeof(stu),1,fp);
		fgetc(fp);
		end->next=p;
		end=p;
		p->next=NULL;
	}
	fclose(fp);
	return head; 
}
void write_file(stu *head)  //用链表，生成文件 
{
	FILE *fp;
	fp=fopen("student.txt","wt");
	stu *i;
	for(i=head->next;i!=NULL;i=i->next)
	{
		fwrite(i,sizeof(stu),1,fp);
		if(i->next!=NULL)
		fputc('\n',fp);
	}
	fclose(fp);
}
void header()//数据表头
{
	printf("\t---------------------------------------------------------------------------------\n");
	HEAD;
	printf("\t---------------------------------------------------------------------------------\n");
}
void exchange_num(int *x,int *y)//交换int 
{
	int t=*x;
	*x=*y;
	*y=t;
}
void exchange_string(char a[],char b[])//交换字符串 
{
	char t[20];
	strcpy(t,a);
	strcpy(a,b);
	strcpy(b,t);
}
void exchange(stu *ec1,stu *ec2) //交换stu结构体类型 
{
	exchange_num(&ec1->age,&ec2->age);
	exchange_num(&ec1->banji,&ec2->banji);
	exchange_string(ec1->dorm,ec2->dorm);
	exchange_num(&ec1->dorm_num,&ec2->dorm_num);
	exchange_num(&ec1->dorm_num_id,&ec2->dorm_num_id);
	exchange_string(ec1->id,ec2->id);
	exchange_num(&ec1->enUniversity,&ec2->enUniversity);
	exchange_string(ec1->major,ec2->major);
	exchange_string(ec1->name,ec2->name);
	exchange_string(ec1->number,ec2->number);
	exchange_string(ec1->sex,ec2->sex);
}
void sort(stu *head) //根据公寓 宿舍 床位 排序 
{
	stu *i,*j;
	for(i=head->next;i!=NULL;i=i->next)
	{
		for(j=i->next;j!=NULL;j=j->next)
		{
			if(strcmp(i->dorm,j->dorm)>0)
			{
				exchange(i,j);
			}
		}
	}
	
	for(i=head->next;i!=NULL;i=i->next)
	{
		for(j=i->next;j!=NULL;j=j->next)
		{
			if(!strcmp(i->dorm,j->dorm)&&i->dorm_num>j->dorm_num)
			{
				exchange(i,j);
			}
		}
	}
	
	for(i=head->next;i!=NULL;i=i->next)
	{
		for(j=i->next;j!=NULL;j=j->next)
		{
			if(strcmp(i->dorm,j->dorm)==0&&i->dorm_num==j->dorm_num&&i->dorm_num_id>j->dorm_num_id)
			{
				exchange(i,j);
			}
		}
	}
	
}
void add(stu *head)//添加数据 
{
	stu *end;
	for(end=head->next;end->next!=NULL;end=end->next){}
	stu *p;
	char id[20];
	printf("\t输入学号:");
	fflush(stdin);
	gets(id);
	while(strlen(id)>0)
	{
		
		if(find_id(id,head))//学号查重,重复返回0，否则1 
		{
			p=(stu*)malloc(sizeof(stu));
			p->next=NULL;
			strcpy(p->id,id);
			printf("\t输入姓名:");	
			gets(p->name);
			printf("\t输入公寓名称:");			
			scanf("%s",p->dorm);
			printf("\t输入宿舍名称:");
			scanf("%d",&p->dorm_num);
			printf("\t输入床位号:");
			scanf("%d",&p->dorm_num_id);
			if(find_check(head,p))  //检查宿舍是否满员,符合返回1，不符合返回0 
			{		
				printf("\t手机号:");
				fflush(stdin);
				gets(p->number); 
				printf("\t年龄:");
				scanf("%d",&p->age); 
				printf("\t性别:");
				scanf("%s",p->sex); 
				printf("\t专业班级:");
				scanf("%s %d",p->major,&p->banji);
				printf("\t输入入学年份:");
				scanf("%d",&p->enUniversity);	
				end->next=p;
				end=p;	
			} 	
		}
		printf("\t输入学号:");
		fflush(stdin);
		gets(id);
	}
	printf("\t结束\n");
}
void dele(stu *head)//按学号删除数据 
{
	printf("\t输入你要删除的学号:");
	char id[20];
	fflush(stdin);
	gets(id);
	stu *end1;//倒数第二个 	
	stu *i;
	while(strlen(id)>0)
	{
		for(end1=head->next;end1->next->next!=NULL;end1=end1->next){}
		i=head;
		while((i=i->next)!=NULL)
		{
			if(strcmp(id,i->id)==0)
			{
				exchange(i,end1->next);
				free(end1->next);
				end1->next=NULL;
				sort(head);
				printf("\t成功\n");
				break;
			}
			else if(i->next==NULL)
			{
				printf("\t->未找到相匹配的学号<-\n");
			}
		}
		printf("\t输入你要删除的学号:");
		gets(id);
	}	
}
void modify(stu *head)//按学号修改数据 
{
	char flag[5];
	printf("\t输入你要修改的学号:");
	char id[20];
	char new_id[20];
	fflush(stdin);
	gets(id);
	stu *i;
	stu *k;
	k=(stu*)malloc(sizeof(stu));
	k->next=NULL;
	while(strlen(id)>0)
	{	
		i=head;
		while((i=i->next)!=NULL)
		{
			if(strcmp(id,i->id)==0)
			{
				printf("\t是否修改学号(yes/no):") ;
				gets(flag);
				if(strcmp(flag,"yes")==0)
				{
					printf("\t输入修改的学号:");
					gets(new_id);
					if(find_id(new_id,head)||strcmp(id,new_id)==0)
					{
						strcpy(k->id,new_id);
					}
					else
					{
						printf("\t新学号重复");
						break;
					}
				}
				else
				{
					strcpy(k->id,i->id);
				} 
				printf("\t输入姓名:");	
				gets(k->name);
				printf("\t输入公寓名称:");			
				scanf("%s",k->dorm);
				printf("\t输入宿舍名称:");
				scanf("%d",&k->dorm_num);
				printf("\t输入床位号:");
				scanf("%d",&k->dorm_num_id);
				if(find_check(head,k)||(!strcmp(k->dorm,i->dorm)&&i->dorm_num==k->dorm_num&&i->dorm_num_id==k->dorm_num_id))  //检查宿舍是否满员,符合返回1，不符合返回0 
				{		
					printf("\t手机号:");
					fflush(stdin);
					gets(k->number); 
					printf("\t年龄:");
					scanf("%d",&k->age); 
					printf("\t性别:");
					scanf("%s",k->sex); 
					printf("\t专业班级:");
					scanf("%s %d",k->major,&k->banji);
					printf("\t输入入学年份:");
					scanf("%d",&k->enUniversity);
					
					exchange(i,k);
				} 				
			}
			else if(i->next==NULL)
			{
				printf("\t->未找到相匹配的学号<-\n");
			}
		}
		printf("\t输入你要修改的学号:");
		fflush(stdin);
		gets(id);
	}	
	free(k);
}
void interface1()//数据查询子界面 
{
	printf("\t\t------------------\n");
	printf("\t\t|1.按学号查询    |\n");
	printf("\t\t|2.按姓名查询    |\n");
	printf("\t\t|3.按公寓宿舍查询|\n");
	printf("\t\t------------------\n");
}
void lookup_id(stu *head)//按学号查找 
{
	char id[20];
	printf("\t输入学号:");
	fflush(stdin);
	gets(id);
	stu *i;
	while(strlen(id)>0)
	{	
		i=head;
		while((i=i->next)!=NULL)
		{
			if(strcmp(id,i->id)==0)
			{
				header();
				printf("\t|%-10s%-8s%-9s%-5d%-10s%-5d%-5d%-5s%-5d%-12s%-5d|\n",i->id,i->name,i->major,i->banji,i->dorm,i->dorm_num,i->dorm_num_id,i->sex,i->age,i->number,i->enUniversity);
				printf("\t---------------------------------------------------------------------------------\n");
				break;
			}
			else if(i->next==NULL)
			{
				printf("\t未找到相应学号\n");
			}
		}
		printf("\t输入学号:");
		fflush(stdin);
		gets(id);
	}
}
void lookup_name(stu *head)//按姓名查找 
{
	char name[20];
	printf("\t输入姓名:");
	fflush(stdin);
	
	gets(name);
	stu *i;
	int flag;//判断是否找到数据，1找到，0枚找到 
	int flag1;//判断是否输出表头 ，1输出，0不输出
	flag1=1; 
	while(strlen(name)>0)
	{	flag=0;
		i=head;
		while((i=i->next)!=NULL)
		{
			if(strcmp(name,i->name)==0)
			{
				if(flag1==1)
				{
					header();
					flag1=0;
				}				
				printf("\t|%-10s%-8s%-9s%-5d%-10s%-5d%-5d%-5s%-5d%-12s%-5d|\n",i->id,i->name,i->major,i->banji,i->dorm,i->dorm_num,i->dorm_num_id,i->sex,i->age,i->number,i->enUniversity);
				flag=1;
			}
			else if(i->next==NULL&&flag==0)
			{
				printf("\t未找到相应姓名\n");
			}
		}
		printf("\t---------------------------------------------------------------------------------\n");
		printf("\n");
		printf("\t输入姓名:");
		fflush(stdin);
		gets(name);
	}
}
void lookup_dorm_num(stu *head)//按公寓宿舍查找 
{
	int  num=0;
	char dorm[20];
	printf("\t输入公寓和宿舍号:");
	scanf("%s %d",dorm,&num);
	stu *i;
	int flag;//判断是否找到数据，1找到，0枚找到 
	int flag1;//判断是否输出表头 ，1输出，0不输出
	flag1=1; 
	while(strlen(dorm)>0&&num!=0)
	{	flag=0;
		i=head;
		while((i=i->next)!=NULL)
		{
			if(num==i->dorm_num&&strcmp(dorm,i->dorm)==0)
			{
				if(flag1==1)
				{
					header();
					flag1=0;
				}				
				printf("\t|%-10s%-8s%-9s%-5d%-10s%-5d%-5d%-5s%-5d%-12s%-5d|\n",i->id,i->name,i->major,i->banji,i->dorm,i->dorm_num,i->dorm_num_id,i->sex,i->age,i->number,i->enUniversity);
				flag=1;
			}
			else if(i->next==NULL&&flag==0)
			{
				printf("\t未找到相应宿舍号\n");
			}
		}
		printf("\t---------------------------------------------------------------------------------\n");
		printf("\n");
		num=0;
		printf("\t输入公寓和宿舍号:");
		scanf("%s %d",dorm,&num);
	}
}
void son_operation(stu *head)//查询操作选项表 
{
	
	printf("\t输入选项(0退出):");
	int choice;
	scanf("%d",&choice);
	if(choice==0)
	{
		return;
	}
	switch(choice)
	{
		case 1:{
			lookup_id(head);//按id查询 
			break;
		}
		case 2:{
			lookup_name(head);//按姓名查询 
			break;
		}
		case 3:{
			lookup_dorm_num(head);//按公寓宿舍查询 
			break;
		}
		default :{
			printf("\t->输入格式有误<-\n");
			break;
		} 
	}
}
void son_statistical()//统计操作表子目录 
{
	printf("\t\t----------------\n");
	printf("\t\t|1.统计总人数  |\n");
	printf("\t\t|2.统计单个公寓|\n");
	printf("\t\t|3.统计公寓宿舍|\n");
	printf("\t\t----------------\n");
}
void  statistical_total(stu *head)//统计总人数
{
	stu *i;
	int n=0;
	for(i=head->next;i!=NULL;i=i->next)
	{
		n++;
	}
	printf("\t->共%d人<-\n",n); 
}
void statistical_dorm(stu *head)//统计单个公寓
{
	int n=0;
	char dorm[20];
	printf("\t输入公寓:");
	fflush(stdin);
	gets(dorm);
	stu *i;
	while(strlen(dorm)>0)
	{	
		i=head;
		n=0;
		while((i=i->next)!=NULL)
		{
			if(strcmp(dorm,i->dorm)==0)
			{
				n++;
			}		
		}
		printf("\t->该公寓共%d人<-\n",n);
		printf("\t输入公寓:");
		fflush(stdin);
		gets(dorm);
	}
}
void statistical_dorm_num(stu *head)//统计公寓宿舍
{
	int  num=0;
	int n;
	char dorm[20];
	printf("\t输入公寓和宿舍号:");
	scanf("%s %d",dorm,&num);
	stu *i;
	while(strlen(dorm)>0&&num!=0)
	{	n=0;
		i=head;
		while((i=i->next)!=NULL)
		{
			if(num==i->dorm_num&&strcmp(dorm,i->dorm)==0)
			{			
					n++;
			}
			
		}		
		printf("\t->该宿舍工%d人<-\n",n);
		num=0;
		printf("\t输入公寓和宿舍号:");
		scanf("%s %d",dorm,&num);
	}
}
void statistical_operation(stu *head) //统计操作选项表 
{
	printf("\t输入选项(0退出):");
	int choice;
	scanf("%d",&choice);
	if(choice==0)
	{
		return;
	}
	switch(choice)
	{
		case 1:{
			statistical_total(head);//统计总人数
			break;
		}
		case 2:{
			statistical_dorm(head);//统计单个公寓
			break;
		}
		case 3:{
			statistical_dorm_num(head);//统计公寓宿舍
			break;
		}
		default :{
			printf("\t->输入格式有误<-\n");
			break;
		} 
	}
} 
int main() 
{	
	enter();//登录 
	system("cls");
	printf("\t登陆成功\n");
	int choice;
	while(1)
	{
		interface();
		stu *head;
		printf("\t输入1~7：");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:{//录入信息 
				head=creat();//创建链表
				//print(head); 
				write_file(head);//写入文件 
				
				break;
			}
			case 2:{//增加 
				head=write_linked();
				add(head);
				sort(head);
				write_file(head);
				break;
			}
			case 3:{ //按学号删除 
				head=write_linked();
				dele(head);
				write_file(head);
				break;
			}
			case 4:{//改按学号 
				head=write_linked();
				modify(head);
				write_file(head);
				break;
			}
			case 5:{//查，按姓名，宿舍，学号 
				interface1();//子目录 
				head=write_linked();
				son_operation(head);
				break;
			}
			case 6:{ //统计，总人数，每个宿舍人数，一个楼人数 
				head=write_linked();
				son_statistical();
				statistical_operation(head); 
				//statistical_date(); 
				break;
			}
			case 7:{//报表 
				head=write_linked();
				header(); 
				sort(head);
				print(head);
				printf("\t---------------------------------------------------------------------------------\n");
				break;
			}
			default :{
				//system("cls");
				printf("\t->输入有误,重新输入<-\n");
				break;
			}
		}
		printf("\t按任意键继续");
		fflush(stdin);
		getchar();
		system("cls");
	}
}









