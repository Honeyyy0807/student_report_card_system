//***************************************************************
//                   HEADER FILE USED IN PROJECT
//****************************************************************

#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<fstream.h>
#include<iomanip.h>

//***************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************

class student
{
    int rollno;
    char name[50];
    int phy_marks,chem_marks,math_marks,eng_marks,cs_marks;
    float per;
    char grade;
    int std;
    void calculate()
    {
        per=(phy_marks+chem_marks+math_marks+eng_marks+cs_marks)/5.0;
        if(per>=90)
            grade='O';
        else if(per>=80 && per<90)
            grade='A';
        else if(per>=75 && per<80)
            grade='B';
        else if(per>=60 && per<70)
            grade='C';
        else if(per>=33 && per<60)
            grade='D';
        else
            grade='F';
    }
public:
    void getdata()
    {
        cout<<"\n ENTER THE ROLL NUMBER OF THE STUDENT ";
        cin>>rollno;
        cout<<"\n\n ENTER THE NAME OF STUDENT ";
        gets(name);
        cout<<"\n ENTER THE MARKS IN PHYSICS OUT OF 100 : ";
        cin>>phy_marks;
        cout<<"\n ENTER THE MARKS IN CHEMISTRY OUT OF 100 : ";
        cin>>chem_marks;
        cout<<"\n ENTER THE MARKS IN MATHEMATICS OUT OF 100 : ";
        cin>>math_marks;
        cout<<"\n ENTER THE MARKS IN ENGLIS OUT OF 100 : ";
        cin>>eng_marks;
        cout<<"\n ENTER THE MARKS IN COMPUTER SCIENCE OUT OF 100 : ";
        cin>>cs_marks;
        calculate();
    }

    void showdata()
    {
        cout<<"\n ROLL NUMBER OF THE STUDENT : "<<rollno;
        cout<<"\n NAME OF THE STUDENT : "<<name;
        cout<<"\n MARKS IN PHYSICS : "<<phy_marks;
        cout<<"\n MARKS IN CHEMISTRY : "<<chem_marks;
        cout<<"\n MARKS IN MATHEMATICS : "<<math_marks;
        cout<<"\n MARKS IN ENGLISH : "<<eng_marks;
        cout<<"\n MARKS IN COMPUTER SCIENCE :"<<cs_marks;
        cout<<"\n PERCENTAGE OF THE STUDENT IS :"<<setprecision(2)<<per;
        cout<<"\n GRADE OF THE STUDENT IS :"<<grade;
    }

    void show_tabular()
    {
	cout<<rollno<<setw(12)<<name<<setw(10)<<phy_marks<<setw(3)<<chem_marks<<setw(3)<<math_marks<<setw(3)<<eng_marks<<setw(3)<<cs_marks<<setw(6)<<setprecision(3)<<per<<"   "<<grade<<endl;
    }

    int  retrollno()
    {
        return rollno;
    }

};         //class ends here



//***************************************************************
//      global declaration for stream object, object
//****************************************************************

fstream fp;
student st;

//***************************************************************
//      function to write in file
//****************************************************************

void write_student()
{
    fp.open("student.dat",ios::out|ios::app);
    st.getdata();
    fp.write((char*)&st,sizeof(student));
    fp.close();
    cout<<"\n\n STUDENT RECORD HAS BEEN CREATED";
    getch();
}


//***************************************************************
//      function to read all records from file
//****************************************************************


void display_all()
{
    clrscr();
    cout<<"\n\n\n\t\t DISPLAY ALL RECORD !!!\n\n";
    fp.open("student.dat",ios::in);
    while(fp.read((char*)&st,sizeof(student)))
    {
        st.showdata();
        cout<<"\n\n====================================\n";
        getch();
    }
    fp.close();
    getch();
}


//***************************************************************
//      function to read specific record from file
//****************************************************************


void display_sp(int n)
{
    int flag=0;
    fp.open("student.dat",ios::in);
    while(fp.read((char*)&st,sizeof(student)))
    {
        if(st.retrollno()==n)
        {
            clrscr();
            st.showdata();
            flag=1;
        }
    }
    fp.close();
    if(flag==0)
        cout<<"\n\n RECORD NOT EXIST";
    getch();
}


//***************************************************************
//      function to modify record of file
//****************************************************************


void modify_student()
{
    int no,found=0;
    clrscr();
    cout<<"\n\n\t TO MODIFY";
    cout<<"\n\n\t PLEASE ENTER THE ROLL NUMBER OF THE STUDENT";
    cin>>no;
    fp.open("student.dat",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(student)) && found==0)
    {
        if(st.retrollno()==no)
        {
            st.showdata();
            cout<<"\n PLEASE ENTER THE NEW DETAILS OF THE STUDENT"<<endl;
            st.getdata();
            int pos=-1*sizeof(st);
            fp.seekp(pos,ios::cur);
            fp.write((char*)&st,sizeof(student));
            cout<<"\n\n\t RECORD UPDATED";
            found=1;
        }
    }
    fp.close();
    if(found==0)
        cout<<"\n\n RECORD NOT FOUND ";
    getch();
}


//***************************************************************
//      function to delete record of file
//****************************************************************


void delete_student()
{
    int no;
    clrscr();
    cout<<"\n\n\n\t DELETE RECORD";
    cout<<"\n\n PLEASE ENTER THE ROLL NUMBER OF STUDENT YOU WANT TO DELETE";
    cin>>no;
    fp.open("student.dat",ios::in|ios::out);
    fstream fp2;
    fp2.open("Temp.dat",ios::out);
    fp.seekg(0,ios::beg);
    while(fp.read((char*)&st,sizeof(student)))
    {
        if(st.retrollno()!=no)
        {
            fp2.write((char*)&st,sizeof(student));
        }
    }
    fp2.close();
    fp.close();
    remove("student.dat");
    rename("Temp.dat","student.dat");
    cout<<"\n\n\t Record Deleted ..";
    getch();
}


//***************************************************************
//      function to display all students grade report
//****************************************************************

void class_result()
{
    clrscr();
    fp.open("student.dat",ios::in);
    if(!fp)
    {
        cout<<"ERROR!!! FILE COULD NOT BE OPEN\n\n\n GO TO ENTRY MENU TO CREATE FILE";
        cout<<"\n\n\n PROGRAM IS CLOSING ....";
        getch();
        exit(0);
    }

    cout<<"\n\n\t\t\t   ALL STUDENTS RESULT \n\n";
    cout<<"================================================================================================================\n";
    cout<<"ROLL NO.   NAME       PHYSICS  CHEMISTRY  MATHEMATICS  ENGLISH  CS   %AGE  GRADE\n";
    cout<<"================================================================================================================\n";

    while(fp.read((char*)&st,sizeof(student)))
    {
        st.show_tabular();
    }
    fp.close();
    getch();
}




//***************************************************************
//      function to display result menu
//****************************************************************

void result()
{
    int ans,rno;
    char ch;
    clrscr();
    cout<<"\n\n\n  RESULT MENU";
    cout<<"\n\n\n  1. CLASS RESULT \n\n  2. STUDENT REPORT CARD\n\n  3.BACK TO MAIN MENU";
    cout<<"\n\n\n  ENTER YOUR CHOICE (1/2)? ";
    cin>>ans;
    switch(ans)
    {
    case 1 :
        class_result();
        break;
    case 2 :
    {
        do
        {
            clrscr();
            char ans;
            cout<<"\n\n  ENTER THE ROLL NUMBER OF THE STUDENT : ";
            cin>>rno;
            display_sp(rno);
            cout<<"\n\n  DO YOU WANT TO SEE MORE RESULT (y/n)?";
            cin>>ans;
        }
        while(ans=='y'||ans=='Y');

        break;
    }
    case 3:
        break;
    default:
        cout<<"\a";
    }
}

//***************************************************************
//      INTRODUCTION FUNCTION
//****************************************************************

void intro()
{
    clrscr();
    cout<<"\n\n\n\n\n    APEEJAY INSTITUTE OF MANAGEMENT & ENGINEERING TECHNICAL CAMPUS, JALANDHAR";
    gotoxy(35,11);
    cout<<"STUDENT";
    gotoxy(30,14);
    cout<<"REPORT CARD SYSTEM";
    gotoxy(35,17);
    cout<<"PROJECT";
    cout<<"\n\n\n\n MADE BY : HONEY PATHANIA";
    cout<<"\n\n CONTACT : 7986453586";
    getch();

}




//***************************************************************
//      ENTRY / EDIT MENU FUNCTION
//****************************************************************
void entry_menu()
{
    clrscr();
    char ch2;
    cout<<"\n\n\n\t ENTRY MENU";
    cout<<"\n\n\t   1.CREATE STUDENT RECORD";
    cout<<"\n\n\t   2.DISPLAY ALL STUDENTS RECORDS";
    cout<<"\n\n\t   3.SEARCH STUDENT RECORD ";
    cout<<"\n\n\t   4.MODIFY STUDENT RECORD";
    cout<<"\n\n\t   5.DELETE STUDENT RECORD";
    cout<<"\n\n\t   6.BACK TO MAIN MENU";
    cout<<"\n\n\t   PLEASE ENTER YOUR CHOICE (1-6) ";
    ch2=getche();
    switch(ch2)
    {
    case '1':
        clrscr();
        write_student();
        break;
    case '2':
        display_all();
        break;
    case '3':
        int num;
        clrscr();
        cout<<"\n\n\t PLEASE ENTER THE ROLL NUMBER \n ";
        cin>>num;
        display_sp(num);
        break;
    case '4':
        modify_student();
        break;
    case '5':
        delete_student();
        break;
    case '6':
        break;
    default:
        cout<<"\a";
        entry_menu();
    }
}


//***************************************************************
//      THE MAIN FUNCTION OF PROGRAM
//****************************************************************


void main()
{
    char ch;
    intro();
    do
    {
        clrscr();
        cout<<"\n\n\n\t MAIN MENU";
        cout<<"\n\n\t   01. RESULT MENU";
        cout<<"\n\n\t   02. ENTRY/EDIT MENU";
        cout<<"\n\n\t   03. EXIT";
        cout<<"\n\n\t   PLEASE SELECT YOUR OPTION (1-3) ";
        ch=getche();
        switch(ch)
        {
        case '1':
            clrscr();
            result();
            break;
        case '2':
            entry_menu();
            break;
        case '3':
            exit(0);
        default :
            cout<<"\a";
        }
    }
    while(ch!='3');
}

//***************************************************************
//                      END OF PROJECT
//***************************************************************
