/* BY SIMRAN KATHURIA *?
#include<fstream>
#include<conio.h>
#include<stdio.h>
#include<iomanip>
#include<iostream>
#include<stdlib.h>
#include<stdlib.h>
using namespace std;

void createfile();                     //CREATE THE RECORD FILE
void display();                           //READ ALL THE RECORDS
void displaybyroll();              //ACCEPT ROLL NUMBER AND READ RECORD
void displaybyrecno();          //ACCEPT RECORD NUMBER AND READ  RECORD
void modifybyroll();              //ACCEPT RECORD AND MODIFY RECORD
void modifybyrecno();          //ACCEPT RECORD NUMBER AND MODIFY  RECORD                                        
void appendfile();                    //ADD MORE RECORDS
void deletefile();                             //DELETE RECORD
void intro();                              //DISPLAY WELCOME SCREEN   
void entry_menu();                //DISPLAY ENTRY MENU ON SCREEN
void result();                            //DISPLAY RESULT MENU
void class_result();               //DISPLAY ALL RECORDS IN TABULAR FORMATE 


class student
{	
  int rollno;
  char name[50];
  int phy_marks,chem_marks,maths_marks,eng_marks,cs_marks;
  float per;
  char grade;
  void calculate();
 public:
  void getdata();
  void showdata();
  void show_table();
  int retroll();
};

void student :: getdata()
{
 cout<<"Enter the name of the student\n";
 cin>>name;
 cout<<"Enter the roll number of the student\n";
 cin>>rollno;
 cout<<"Enter the marks in physics\n";
 cin>>phy_marks;
 cout<<"Enter the marks in chemistry\n";
 cin>>chem_marks;
 cout<<"Enter the marks in maths\n";
 cin>>maths_marks;
 cout<<"Enter the marks in english\n";
 cin>>eng_marks;
 cout<<"Enter the marks in computer science\n";
 cin>>cs_marks;
 calculate();
}

void student :: showdata()
{
 cout<<"\nSTUDENT NAME:"<<name;
 cout<<"\nROLL NUMBER:"<<rollno;
 cout<<"\nMARKS IN PHYSICS:"<<phy_marks;
 cout<<"\nMARKS IN CHEMISTRY:"<<chem_marks;
 cout<<"\nMARKS IN MATHS:"<<maths_marks;
 cout<<"\nMARKS IN ENGLISH:"<<eng_marks;
 cout<<"\nMARKS IN COMPUTER SCIENCE:"<<cs_marks;
 cout<<"\nGRADE OF STUDENT:"<<grade;
}

void student :: calculate()
{
 per=(phy_marks+chem_marks+eng_marks+maths_marks+cs_marks)/5;

 if(per>=90)
 grade='A+';
 else if(per>=80)
 grade='A';
 else if(per>=70)
 grade='B+';
 else if(per>=60)
 grade='B';
 else if(per>=50)
 grade='C+';
 else if(per>=40)
 grade='C';
 else
 grade='F';
}

void student :: show_table()
{
 cout<<"\t"<<rollno<<setw(14)<<name<<setw(8)<<phy_marks<<setw(6)<<chem_marks<<setw(5)<<maths_marks<<setw(5)<<eng_marks<<setw(5)<<cs_marks<<setw(6)<<per<<setw(6)<<" "<<grade<<endl;
}

int student :: retroll()
{
 return rollno;
}

//FUNCTION TO CREATE FILE
void createfile ()
{
 fstream file;
 char ch;
 student s;
 int num=1;
 file.open("student.dat",ios::out|ios::binary);
 do
 {
  cout<<"Enter the details for student "<<num<<endl<<endl;
  s.getdata();
  file.write((char*)&s,sizeof(s));
  num++;
  cout<<"Want more records.....\n";
  cin>>ch;
  cout<<"\n\nStudents Records Has Been Created\n";
  system("cls");
 }
 while(ch=='y'|| ch=='Y');
 file.close();
}

//FUNCTION TO DISPLAY ALL THE RECORDS
void display()
{
 fstream file;
 student s;
 file.open("student.dat",ios::in|ios::binary);
 cout<<"Displaying all the records\n\n";
 while(file.read((char*)&s,sizeof(s)))
 {
   s.showdata();
   cout<<"\n\n-----------------------------------------------\n";
 }
 file.close();
}


//FUNCTION TO DISPLAY SPECIFIC RECORD (BY ROLL NUMBER)
void displaybyroll()
{
 fstream file;
 student s;
 int roll,flag=0;
 cout<<"\nEnter the roll number of the student you want to search for\n";
 cin>>roll;
 file.open("student.dat",ios::in|ios::binary);
 while(file.read((char*)&s,sizeof(s)))
 {
  if(roll==s.retroll())
  {
   s.showdata();
   flag=1;
   break;
  }
 }
 file.close();
 if(flag==0)
 cout<<"Record not found\n";
}

//FUNCTION TO MODIFY THE RECORD (BY ROLL NUMBER)
void modifybyroll()
{
 fstream file;
 student s;
 int roll,flag=0;
 cout<<"Enter the roll number of the student to want to edit\n";
 cin>>roll;
 file.open("student.dat",ios::in|ios::out|ios::binary);
 while(file.read((char*)&s,sizeof(s)))
 {
  if(s.retroll()==roll)
  {
   file.seekp(file.tellg()-sizeof(s),ios::beg);
   s.getdata();
   file.write((char*)&s,sizeof(s));
   flag=1;
   cout<<"\n\nRecord Updated\n";
  }
 }
 file.close();
 if(flag==0)
 cout<<"Record not found\n";
}

//FUNCTION TO MODIFY THE RECORD (BY RECORD NUMBER)
void modifybyrecno()
{
 fstream file;
 student s;
 int recno;
 cout<<"Enter the record number you want to modify\n";
 cin>>recno;
 file.open("student.dat",ios::out|ios::in|ios::binary);
 file.seekg(sizeof(s)*(recno-1),ios::beg);
 s.getdata();
 file.write((char*)&s,sizeof(s));
 file.close();
 cout<<"\n\nRecord Updated....\n";
}

//FUNCTION TO ADD MORE RECORDS 
void appendfile()
{
 fstream file;
 student s;
 char ch;
 file.open("student.dat",ios::app|ios::binary);
 do
 {
  s.getdata();
  file.write((char*)&s,sizeof(s));
  cout<<"Want more records\n";
  cin>>ch;
  system("cls");
 }
 while(ch=='y'|| ch=='Y') ;
 file.close();
 cout<<"\n\nRecord Has Been Added\n";
}

//FUNCTION TO DELETE THE RECORD
void deletefile()
{
 fstream file1,file2;
 student s;
 int rno;
 cout<<"Enter the roll number\n";
 cin>>rno;
 file1.open("student.dat",ios::in|ios::binary);
 file2.open("temp.dat",ios::out|ios::binary);
 while(file1.read((char*)&s,sizeof(s)))
 {
  if(s.retroll()!=rno)
  file2.write((char*)&s,sizeof(s));
 }
 file1.close();
 file2.close();
 file1.open("student.dat",ios::out|ios::binary);
 file2.open("temp.dat",ios::in|ios::binary);
 while(file2.read((char*)&s,sizeof(s)))
 {
  file1.write((char*)&s,sizeof(s));
 }
 file1.close();
 file2.close();
 cout<<"\n\nRecord Deleted....\n";
}

//FUNCTION TO DISPLAY THE SPECIFIC RECORD (BY RECORD NUMBER)
void displaybyrecno()
{
 fstream file;
 student s;
 int recno,flag=0;
 cout<<"Enter the record number you want to search for\n";
 cin>>recno;
 file.open("student.dat",ios::in|ios::binary);
 file.seekg(sizeof(s)*(recno-1),ios::beg);
 if(file.read((char*)&s,sizeof(s)))
 {
  s.showdata();
  flag=1;
 }
 if(flag==0)
 cout<<"Record not found\n";
 file.close();
}

//THE MAIN FUNCTION OF THE PROGRAM
int main()
{
 system("cls");
 int ch;
 intro();
 do
 {
  cout<<"\n========================MENU===========================\n";
  cout<<"1.RESULT MENU\n";
  cout<<"2.ENTRY/EDIT MENU\n";
  cout<<"3.EXIT\n";
  cout<<"\nplease select your option\n";
  cin>>ch;
  switch(ch)
  {
   case 1 : result();break;
   case 2 : entry_menu();break;
   case 3 : break;
   default : cout<<"\a";
  }
 }while(ch!=3);
 return 0;
}

//FUNCTION TO DISPLAY RESULT MENU 
void result()
{
 system("cls");
 int ch;
 cout<<"\n========================RESULT MENU=========================\n";
 cout<<"1.CLASS RESULT\n";
 cout<<"2.STUDENT REPORT CARD\n";
 cout<<"3.BACK TO MAIN MENU\n";
 cout<<"\nplease enter your option\n";
 cin>>ch;
 system("cls");
 switch(ch)
 {
  case 1 : class_result();break;
  case 2 : displaybyroll();break;
  case 3 : break;
  default : cout<<"\a";result();
 }
}

//FUNCTION TO DISPLAY THE CLASS RESULT
void class_result()
{
 student s;
 fstream file;
 file.open("student.dat",ios::in|ios::binary);
 cout<<"\n\t------------------------__CLASS RESULT__---------------------------\n";
 cout<<"\t==============================================================\n";
 cout<<"\tR.no      NAME        P    C    M    E    CS    %age   Grade"<<endl;
 cout<<"\t==============================================================\n";
 while(file.read((char*)&s,sizeof(s)))
 {
  s.show_table();
 }
 file.close();
}

//INTRODUCTION FUNCTION 
void intro()
{
 cout<<"\t\t\t\tSTUDENT REPORT CARD";
 cout<<"\n\n\t\t\t\t      PROJECT";
 cout<<"\n\n\n\t\t\t       MADE BY:SIMRAN KATHURIA";
 cout<<"\n\n\t\t\t   SCHOOL : HANS RAJ MODEL SCHOOL\n\n";
}



//FUNCTION TO DISPLAY ENTRY/EDIT MENU
void entry_menu()
{
 int ch;
 system("cls");
 cout<<"\n=============================EDIT MENU==============================\n";
 cout<<"1.CREATE STUDENT RECORD\n";
 cout<<"2.DISPLAY ALL THE RECORDS\n";
 cout<<"3.MODIFY THE RECORD BY ROLL NUMBER\n";
 cout<<"4.MODIFY THE RECORD BY RECORD NUMBER\n";
 cout<<"5.ADD MORE RECORD\n";
 cout<<"6.DELETE THE RECORD\n";
 cout<<"7.DISPLAY RECORDS BY RECORD NUMBER\n";
 cout<<"8.BACK TO MAIN MENU\n";
 cout<<"\nplease enter your option\n";
 cin>>ch;
 system("cls");
 switch(ch)
 {
  case 1 : createfile();break;
  case 2 : display();break;
  case 3 : modifybyroll();break;
  case 4 : modifybyrecno();break;
  case 5 : appendfile();break;
  case 6 : deletefile();break;
  case 7 : displaybyrecno();break;
  case 8 : break;
  default : cout<<"\a";
  entry_menu();
 }
}

