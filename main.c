#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<errno.h>

void gotoxy(int x,int y){
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
struct Student{
	char name[35],address[25];
	int age;
};
enum FILTER{
	NAME,
	ADDRESS,
	AGE
};
enum ARRANGE{
	ASCENDING,
	DESCENDING
};
typedef enum FILTER Filter;
typedef enum ARRANGE Arrange;
typedef struct Student Cstudent;
/*typedef void (Callback)(Cstudent *student);*/
void allocateStudent(Cstudent **student,int num){
	*student = (Cstudent*)calloc(num,sizeof(Cstudent));
	if(*student==NULL){
		printf("Not able to allocate memory in heap\nError:%d",errno);
		exit(1);
	}
}
void reallocateStudent(Cstudent **student,int num){
	*student = (Cstudent*)realloc(*student,num*sizeof(Cstudent));
	if(student==NULL){
		printf("Not able to reallocate memory in heap\nError:%d",errno);
		exit(1);
	}
}
void readStudentFromUser(Cstudent *student,int num){
	int i=0;
	for(;i<num;i++){
		fflush(stdin);
		printf("Name:");
		gets(student[i].name);
		printf("\nAddress:");
		gets(student[i].address);
		printf("\nAge:");
		scanf("%d",&student[i].age);
	}
}
void addStudent(Cstudent *std,int num){
	FILE *fp;
	int i=0;
	fp = fopen("student1.csv","w");
	if(fp==NULL){
		printf("Filed to open a file");
		exit(1);
	}
	//printf("Writing...");
	for(;i<num;i++){
		printf("%s",std[i].name);
		fprintf(fp,"%s,%s,%d\n",std[i].name,std[i].address,std[i].age);
	}
	fclose(fp);
	free(std);
}
Cstudent *readRecord(int *size){
	Cstudent *students;
	FILE *fin;
	int assumed=10,len;
	fin=fopen("student1.csv","r");
	if(fin==NULL){
		printf("Failed to open a file");
		exit(1);
	}
	Cstudent s;
	allocateStudent(&students,assumed);
	/*while(fgets(,100,fin)!=NULL){
	printf("%s",s);	
	}*/
	/*
	while(fscanf(fin,"%[^,],%[^,],%d",&s.name,s.address,&s.age)!=EOF){		
	
	if(*size==assumed-1){
			assumed+=5;
			reallocateStudent(&students,assumed);
		}
		students[*size]=s;
		*size=*size+1;
	}
	*/
	int s_size = sizeof(Cstudent);
	int s_i;
	char text[s_size];
	while(fgets(text,s_size,fin)!=NULL){
		if(*size==assumed-1){
			assumed+=5;
			reallocateStudent(&students,assumed);
		}
		char *token = strtok(text,",");
		s_i=1;
		while(token!=NULL){
			switch(s_i){
				case 1:
					strcpy(s.name,token);
				break;
				case 2:
					strcpy(s.address,token);
				break;
				case 3:
					s.age=atoi(token);
				break;
			}
			s_i++;
			token=strtok(NULL,",");
		}	
		students[*size]=s;
		*size=*size+1;
	}
	
	for(assumed=0;assumed<*size;assumed++){
	//	printf("%s",students[assumed].name);
	}
	fclose(fin);
	return students;
}
void swap(Cstudent *std1,Cstudent *std2){
	Cstudent temp=*std1;
	*std1=*std2;
	*std2=temp;
}
void arrange(Cstudent students[],int size, const Filter filter,const Arrange arr){
	int i=0,j;
	Cstudent temp;
	for(;i<size;i++){
		for(j=i+1;j<size;j++){
			/*check */
			if(arr==ASCENDING){
				switch(filter){
					case NAME:
						if(strcmp(students[i].name,students[j].name)>0){
							swap(&students[i],&students[j]);	
							}
						break;
					case ADDRESS:
						if(strcmp(students[i].address,students[j].address)>0){
							swap(&students[i],&students[j]);	
						}
						break;
					case AGE:
						if(students[i].age > students[j].age){
							swap(&students[i],&students[j]);
						}
						break;
					default:
						if(strcmp(students[i].name,students[j].name)>0){
								swap(&students[i],&students[j]);
							}
				}
				
			}else{
				switch(filter){
					case NAME:
						if(strcmp(students[i].name,students[j].name)<0){
								swap(&students[i],&students[j]);	
							}
						break;
					case ADDRESS:
						if(strcmp(students[i].address,students[j].address)<0){
							swap(&students[i],&students[j]);	
						}
						break;
					case AGE:
						if(students[i].age < students[j].age){
							swap(&students[i],&students[j]);
						}
						break;
					default:
						if(strcmp(students[i].name,students[j].name)<0){
							swap(&students[i],&students[j]);	
						}
				}
			
			}
			
			
		}
	}
	
}
Cstudent *search(Cstudent students[],int *searchResultSize,char value[],int size,const Filter filter){
	int let=3,i=0,count=0,val,age;
	Cstudent *result = (Cstudent*)calloc(let,sizeof(Cstudent));
	if(filter==AGE){
		age= atoi(value);
	}
	for(;i<size;i++){
		if(let==count){
			let+=3;
			result= (Cstudent*)realloc(result,let*sizeof(Cstudent));
		}
		if(filter == NAME)
		if(strcmp(students[i].name,value)==0){
			result[count]=students[i];
			count++;
		}
		if(filter==ADDRESS)
		if(strcmp(students[i].address,value)==0){
			result[count]=students[i];
			count++;
		}
		if(filter==AGE){
			if(age==students[i].age){
				result[count]=students[i];
				count++;
			}
		}
	}
	*searchResultSize=count;
	for(i=count;i<let;i++){
		free(result+i);
	}
	
	return result;	
}

void hello()
{
	printf("hello safal");
}

void main(){
	hello();
	SetConsoleTitle("DEMO APPLICATION");
	Cstudent *student;	
 	int size=0;int i=0,searchResultSize=0;
 	gotoxy(25,5);
 	printf("DEMO APPLICATION");
 	gotoxy(15,10);
 	printf("\n");
	/*	int num;
	printf("How many student you want to admit now?\n");
	scanf("%d",&num);
	allocateStudent(&student,num);
	readStudentFromUser(student,num);
	addStudent(student,num);
	*/
	student=readRecord(&size);
	
//	arrange(student,size,AGE,DESCENDING);
	Cstudent *searchResult = search(student,&searchResultSize,"Jhapa",size,ADDRESS);
	arrange(searchResult,searchResultSize,NAME,ASCENDING);
	if(searchResultSize==0){
		gotoxy(25,15);
		printf("Search not found!!!\a\n");
		return;
	}
	printf("%-5s%-25s%-25s%-25s\n","S.N","Name","Address","Age");
	for(i=0;i<searchResultSize;i++){
		printf("%-5d%-25s%-25s%-25d\n",i+1,searchResult[i].name,searchResult[i].address,searchResult[i].age);
	}
	return;
}
