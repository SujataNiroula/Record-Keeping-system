#include<iostream>
#include<conio.h>
#include<fstream>
#include<cstdlib>
#include<strings.h>
#include<time.h>
#include <windows.h>
#include <stdlib.h>
using std::cout;
using std::cin;
using std::endl;
using std::fstream;
using std::ofstream;
using std::ifstream;
using std::ios;
class account_system
{
    private:
        char account_number[20];
		char firstName[20];
        char lastName[20];
		char address [20];
        float total_Balance;
    public:
        void read_data();
        void retrieve_data();
        void write_rec();
        void read_rec();
        void search_rec();
        void update_rec();
        void delete_rec();
        void modify_data(char acc_number[]);
};
void account_system::read_data()
{
	char account_no[20];
	int n,flag;
	a:
    cout<<"\nEnter Transaction Id: ";
    cin>>account_no;
    ifstream infile;
    infile.open("transaction.rcd", ios::binary);
    flag=0;
    while(!infile.eof())
    {
        if(infile.read(reinterpret_cast<char*>(this), sizeof(*this))>0)
        {
            n=strcmp(account_number,account_no);
            if (n==0)
            {
            	flag=1;
            }
         }
    }
    infile.close();
    if(flag==1)
    {
    	cout<<"\nTransaction Id already exists!";
    	goto a;
    }
    else
    {
    strcpy(account_number,account_no);
    cout<<"Enter First Name: ";
    cin>>firstName;
    cout<<"Enter Last Name: ";
    cin>>lastName;
    cout<<"Enter Address: ";
    cin>>address;
    cout<<"Enter Balance: Rs. ";
    cin>>total_Balance;
    cout<<endl;
	}
}
void account_system::modify_data(char acc_number[])
{
	cout<<"Transaction Id: "<<acc_number<<endl;
	cout<<"Enter First Name: ";
    cin>>firstName;
    cout<<"Enter Last Name: ";
    cin>>lastName;
    cout<<"Enter Address: ";
    cin>>address;
    cout<<"Enter Balance: Rs. ";
    cin>>total_Balance;
}
void account_system::retrieve_data()
{
    cout<<"\nTransaction Id: "<<account_number<<endl;
    cout<<"First Name: "<<firstName<<endl;
    cout<<"Last Name: "<<lastName<<endl;
    cout<<"Address: "<<address<<endl;
    cout<<"Current Balance: Rs.  "<<total_Balance<<endl;
    cout<<"-------------------------------"<<endl;

}
void account_system::write_rec()
{
    ofstream outfile;
    outfile.open("transaction.rcd", ios::binary|ios::app);
    read_data();
    outfile.write(reinterpret_cast<char *>(this), sizeof(*this));
    outfile.close();
    cout<<"\nThe Record has been added.";
}
void account_system::read_rec()
{
    ifstream infile;
    infile.open("transaction.rcd", ios::binary);
    if(!infile)
    {
        cout<<"Error!! File is Not Found!!"<<endl;
        return;
    }
    cout<<"\n\t\t\t**** Records on file ****"<<endl;
    while(!infile.eof())
    {
        if(infile.read(reinterpret_cast<char*>(this), sizeof(*this))>0)
        {
            retrieve_data();
        }
    }
    infile.close();
}
void account_system::search_rec()
{
    char acc_number[20];
    int n;
    ifstream infile;
    infile.open("transaction.rcd", ios::binary);
    if(!infile)
    {
        cout<<"\nError!! File is Not Found!!"<<endl;
        return;
    }
	infile.seekg(0,ios::end);
    int count = infile.tellg()/sizeof(*this);
    cout<<"\nThere are "<<count<<" records in the file.";
    infile.seekg(0,ios::beg);
    cout<<"\n\nEnter Transaction Id to Search: ";
    cin>>acc_number;
    while(!infile.eof())
    {
        if(infile.read(reinterpret_cast<char*>(this), sizeof(*this))>0)
        {
            n=strcmp(account_number,acc_number);
            if (n==0)
            {
            retrieve_data();
            return;
            }
         }
    }

    infile.close();
	cout<<"There is no such record in the file."<<endl;
}
void account_system::update_rec()
{
    int n,flag,coun=0;
    char acc_number[20];
    fstream iofile;
    ifstream infile;
    infile.open("transaction.rcd", ios::binary);
    if(!infile)
    {
        cout<<"\nError!! File is Not Found!!"<<endl;
        return;
    }
	infile.seekg(0,ios::end);
    int count = infile.tellg()/sizeof(*this);
    cout<<"\nThere are "<<count<<" records in the file.";
    if(count==0)
    {
		cout<<"\n";
    }
    else
    {
    infile.seekg(0,ios::beg);
    cout<<"\n\nEnter Transaction Id to Update: ";
    cin>>acc_number;
    flag=0;
	while(!infile.eof())
    {
        if(infile.read(reinterpret_cast<char*>(this), sizeof(*this))>0)
        {
            n=strcmp(account_number,acc_number);
            coun++;
			if (n==0)
            {
            cout<<"\nTransaction Id "<<acc_number<<" has the following data:"<<endl;
            retrieve_data();
            flag=1;
            break;
            }
         }
    }
    infile.close();
	if(flag==0)
	{
	cout<<"\nThere is no such record in the file."<<endl;
	}
	else
	{
	iofile.open("transaction.rcd", ios::out|ios::in|ios::binary);
    iofile.seekp((coun-1)*sizeof(*this));
	cout<<"\nEnter data to Update. "<<endl<<endl;
    modify_data(acc_number);
    iofile.write(reinterpret_cast<char*>(this), sizeof(*this));
    cout<<"\nRecord of Transaction Id "<<acc_number<<" has been Updated.";
	}
	}
}
void account_system::delete_rec()
{
	char acc_number[20];
    int n,count1=0,flag=0,button;
    ifstream infile;
    infile.open("transaction.rcd", ios::binary);
    if(!infile)
    {
        cout<<"\nError!! File is Not Found!!"<<endl;
        return;
    }
    infile.seekg(0,ios::end);
    int count = infile.tellg()/sizeof(*this);
    cout<<"\nThere are "<<count<<" records in the file.";
    if(count==0)
    {
		cout<<"\n";
		infile.close();
    }
    else
    {
    infile.seekg(0,ios::beg);
	cout<<"\n\nEnter Transaction Id to Delete: ";
    cin>>acc_number;
    while(!infile.eof())
    {
        if(infile.read(reinterpret_cast<char*>(this), sizeof(*this))>0)
        {
            n=strcmp(account_number,acc_number);
            count1++;
			if (n==0)
            {
            cout<<"\nTransaction Id "<<acc_number<<" has the following data:"<<endl;
            retrieve_data();
            flag=1;
            break;
            }
         }
    }
    infile.close();
    if(flag==0)
	{
	cout<<"\nThere is no such record in the file."<<endl;
	}
	else
	{
		cout<<"\nAre you sure you want to Continue?"<<endl;
		cout<<"\nPress 1 to Continue.";
		cout<<"\nPress 2 to return to the main menu."<<endl;
		cout<<"\n\nEnter your choice.";
		cin>>button;
		if(button==1)
		{
    	infile.open("transaction.rcd", ios::binary);
    	fstream tmpfile;
    	tmpfile.open("temp.file", ios::out|ios::binary);
    	infile.seekg(0);
    	for(int i=0; i<count; i++)
    	{
        	infile.read(reinterpret_cast<char*>(this),sizeof(*this));
        	if(i==(count1-1))
            continue;
        	tmpfile.write(reinterpret_cast<char*>(this), sizeof(*this));
    	}
    	infile.close();
    	tmpfile.close();
    	remove("transaction.rcd");
    	rename("temp.file", "transaction.rcd");
    	cout<<"\nRecord of Transaction Id "<<acc_number<<" has been deleted.";
		}
 		else
		{
			cout<<"\nRecord of Transaction Id "<<acc_number<<" is not Deleted.";
			return;
 		}
	}
	}
}
int main()
{
    account_system A;
    int choice,n,press,i=0;
	char password[10]="Cosmos";
	char pass[10],ch;
	b:
    system("cls");
    cout<<"\n\n\n\n\n\t\t\t##############################";
    cout<<"\n\t\t\t##############################";
    cout<<"\n\t\t\t###                        ###";
    cout<<"\n\t\t\t###  RECORD KEEPING SYSTEM ###";
    cout<<"\n\t\t\t###                        ###";
    cout<<"\n\t\t\t##############################";
    cout<<"\n\t\t\t##############################";
    //cout<<"\n\n\t\t\t\t\tBy:";
    cout<<"\n\n\t\t\t\t\tBy: Sujata Niroula";
    cout<<"\n\t\t\t\t\t    Rista Parajuli";
    cout<<"\n\t\t\t\t\t    Kailash Ghimire";
    cout<<"\n\t\t\t\t\t    Manoj Shrestha";
    cout<<"\n\n\n\t\t\tENTER THE PASSWORD:";
     do
   {
	ch=getch();
	if(ch!=13 && ch!=8)
	{
	putch('*');
	pass[i] = ch;
	i++;
	}
   }
   while(ch!=13);
   pass[i] = '\0';
   i=0;
    n=strcmp(pass,password);
    if(n==0)
    {
		cout<<"\n\n\t\t\tPASSWORD MATCHED.";
		cout<<"\n\n\t\t\tPRESS ENTER KEY TO CONTINUE";
		cin.get();
    system("cls");
    while(true)
    {
        cout<<"\nPlease Select one of the option below."<<endl;
        cout<<"\n1-->\tAdd a record to file";
        cout<<"\n2-->\tDisplay the record from file";
        cout<<"\n3-->\tSearch the Record from file";
        cout<<"\n4-->\tUpdate the Record";
        cout<<"\n5-->\tDelete the Record";
        cout<<"\n6-->\tExit";
        cout<<"\n\n\tEnter your choice: ";
        cin>>choice;
        system("cls");
        switch(choice)
        {
            case 1:
                A.write_rec();
    			cout<<"\n\n\t\t\tPRESS ENTER KEY TO CONTINUE:";
    			cin.ignore();
    			cin.get();
    			system("cls");
                break;
            case 2:
                A.read_rec();
                cout<<"\n\n\t\t\tPRESS ENTER KEY TO CONTINUE:";
              	cin.ignore();
    			cin.get();
    			system("cls");
                break;
            case 3:
                A.search_rec();
                cout<<"\n\n\t\t\tPRESS ENTER KEY TO CONTINUE:";
                cin.ignore();
    			cin.get();
    			system("cls");
                break;
            case 4:
                A.update_rec();
                cout<<"\n\n\t\t\tPRESS ENTER KEY TO CONTINUE:";
                cin.ignore();
    			cin.get();
                system("cls");
                break;
            case 5:
                A.delete_rec();
                cout<<"\n\n\t\t\tPRESS ENTER KEY TO CONTINUE:";
                cin.ignore();
    			cin.get();
                system("cls");
                break;
            case 6:
                exit(0);
                break;
            default:
                cout<<"\nEnter corret choice";
                exit(0);
        }
    }
	}
	else
	{
		cout<<"\n\n\t\t\tPASSWORD DO NOT MATCH";
		cout<<"\n\n\t\t\tPRESS ENTER TO TRY AGAIN.";
    	cin.get();
		goto b;
	}
    system("pause");
    return 0;
}
