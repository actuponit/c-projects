#include <iostream>
#include<conio.h>
#include<stdio.h>
#include <string>
#include <stdlib.h>
#include <fstream>
using namespace std;

struct worker
{
    string id;
    string Fname;
    string Lname;
    float salary;
    float fullSalary;
    string position;
    float workHour, ot;
}emp, e[25];

void intro();
void addEmployee();
void fireEmployee();
void empList();
void firedEmp();
void calc(worker &emp);
void admin();
void employee();
void createAccount();
void verifier(string, string);
void logIn();
void read();
void empOfTheYear();
void total();
int index;

int main()
{
	int c;
	
	intro();
	
	while (true){
		cout << "\t Wellcome to our Employee Payroll System!!! \n1. Administrator\n2. Employee \n3. Exit\n>> ";
		cin >> c;
		system ("cls");
		switch(c){
		case 1:
			admin();
			break;
		case 2: 
			employee();
			break;
		case 3:
		    return -1;
		    break;
		}
	}
 
}

//The first front page 
void intro()
{
	cout <<"\n\n\tEMPLOYEE MONTHLY PAYROLL MANAGEMENT SYSTEM";
  	cout << "\n\nBY: COMPUTER SCIENCE SECTION 1\n";
  	cout << "\tADMAS TEREFE  IMRAN MOHAMMED\tFEYSEL MOHAMMED\n";
  	cout << "\tBADRI SIRAJ   EMMANUEL SAMSON\n";
  	cout << "\n\npress any key to continue...";
    getch();
    system("cls");
}

//Registers a new employee to the system
void addEmployee()
{
    char c;

    fstream empFile;
    empFile.open("employee.txt", ios::out | ios::app);

    while (true)
    {
        cout << "Employee id: ";
        cin >> emp.id;
        cout << "\nEmployee first name: ";
        cin >> emp.Fname;
        cout << "\nEmployee last name: ";
        cin >> emp.Lname;
        cout << "\nEmployee position executive/staff/clerk: ";
        cin >> emp.position;
        cout << "\nEmployee working hour: ";
        cin >> emp.workHour;
        
        calc(emp);
        
        empFile << "\n" << emp.id << '\t' << emp.Fname << '\t' << emp.Lname << '\t'
                << emp.position << '\t' << emp.workHour << '\t' << emp.salary << '\t'
                << emp.fullSalary << endl;
        cout << "Press n to abort or any key to continue: ";
        cin >> c;
        system("cls");

        if (c == 'n' || c =='N')
            break;
    }
}

//Calculates employee's overtime work
void read(){
	index = 0;
	ifstream file("employee.txt");
	while (file.good()){
		file >> e[index].id >> e[index].Fname >> e[index].Lname >> e[index].position >> e[index].workHour >> e[index].salary >> e[index].fullSalary;
		if (e[index].position == "clerk")
		e[index].ot = e[index].workHour - 160;
		else if (e[index].position == "excutive")
		e[index].ot = e[index].workHour - 120;
		else if (e[index].position == "staff")
		e[index].ot = e[index].workHour - 160;
		index += 1;
	}
	file.close();
}

//Deletes an employee form employees list
void fireEmployee()
{
	string id, line;
	bool found = false;
	int x = 2;
	char n;
	
	fstream fire;
	fstream temp;
	fstream removedEmp;
	removedEmp.open("RemovedEmployees.txt", ios::out | ios::app);
	temp.open("Temp.txt", ios::out);
	fire.open("employee.txt", ios::in | ios::out);
	
		cout << "Enter the id of the employee to be deleted: ";
    	cin >> id;
 
    	fire.seekg(0, ios::beg);
    	while( fire >> emp.id >> emp.Fname >> emp.Lname >> emp.position >> emp.workHour >> emp.salary >> emp.fullSalary)
    	{

    		if(emp.id != id)
    		{
				temp << "\n" << emp.id << '\t' << emp.Fname << '\t' << emp.Lname << '\t'
                << emp.position << '\t' << emp.workHour << '\t' << emp.salary << '\t'
                << emp.fullSalary << endl;
			}
			
			else
			{
				removedEmp << "\n" << emp.id << '\t' << emp.Fname << '\t' << emp.Lname << '\t'
                << emp.position << '\t' << emp.workHour << '\t' << emp.salary << '\t'
                << emp.fullSalary << endl;
                cout << "\n\t Employee is fired!!!\n";
                found = true;
			}

    	}
    	if (!found)
    		cout << "The id you entered is not found";
    	fire.close();
    	removedEmp.close();
    	temp.close();
    	remove("employee.txt");
		rename("Temp.txt", "employee.txt");
		
		cout << endl;
}

//Calculates net salary of an employee
void calc(worker &emp)
{
    if (emp.position == "executive")
    {
        emp.salary = 15000;
        if (emp.workHour <= 120)
            emp.fullSalary = emp.salary;
        else
            emp.fullSalary = emp.salary * (emp.workHour - 120) * 0.01 + emp.salary;
    }
    if (emp.position == "staff")
    {
        emp.salary = 7000;
        if (emp.workHour <= 160)
            emp.fullSalary = emp.salary;
        else
            emp.fullSalary = emp.salary * (emp.workHour - 160) * 0.01 + emp.salary;
    }
    if (emp.position == "clerk")
    {
        emp.salary = 3000;
        if (emp.workHour <= 160)
            emp.fullSalary = emp.salary;
        else
            emp.fullSalary = emp.salary * (emp.workHour - 160) * 0.01 + emp.salary;
    }
}

//Prompts the admin to choose form a number of actions he/has 3 trials for the correct password
void admin()
{
	int choice;
	string pass;
	int c = 3;
	
	here:
	cout << "Enter the password: ";
	cin >> pass;
	system ("cls");
	do
    {
	if(pass == "1234")
	{
		cout << "1. Add empolyee\n2. Fire employee\n3. Employees list \n4. Fired employees list \n5. Employee of the month\n6. total\n" <<
				"7. Go to main menu\n";
		cout << ">> ";
		cin >> choice;
		system("cls");
		
		switch(choice)
		{
			case 1:
				addEmployee();
				break;
			case 2:
				fireEmployee();
				break;
			case 3:
				empList();
				break;
			case 4:
				firedEmp();
				break;	
			case 5:
				empOfTheYear();
				break;
			case 6:
				total();
				break;
			case 7:
				main();
				break;
		}
	}
	else
	{
		c--;
		cout << "Wrong password!!! you have " << c << " trials left\n";
		if (c == 0)
		{
			cout << "\tYou ran out of trials!!!\n\n";
			break;
		}
		goto here;
	}
	}while (true);
	
	system("pause");
	system("cls");
}

//Prompts the employee for to choose to create an acoount or login
void employee()
{
	int c;
	
	cout << "1. Create account\n2. Log in\n3. Go to main menu\n";
	cout << ">> ";
	cin >> c;
	system("cls");
	
	switch(c){
		case 1:
			createAccount();
			break;
		case 2:
			logIn();
		case 3: 
			main();
			break;
		}
	
}

//Takes and stores users login information, username and password in a file
void createAccount()
{
   string username, password;
   
   cout << "Please enter id: ";
   cin >> username;
   cout << "Please create a password: ";
   cin >> password;
   
   ofstream createaccount;
   createaccount.open("accounts.txt", ios::app);
   createaccount << username << " " << password << endl;
   createaccount.close();
   cout << "Account succesfully created!" << endl << endl;
   
   system ("cls");
   employee();
   //system ("pause");
}

//Prompts the employee for id and username to show him his credentials
void logIn()
{
	string username, password;
	cout << "Id: ";
	cin >> username;
	cout << "Password: ";
	cin >> password;
	verifier(username, password);
	employee();
}

//Cross checks id and password with list of id and password stored in a file
//it also checks whether the person exists in employees list
void verifier(string username, string password)
{
	string id, key;
	bool found = false;
	ifstream file("employee.txt");
	while (file.good())
	{
		file >> emp.id >> emp.Fname >> emp.Lname >> emp.position >> emp.workHour >> emp.salary >> emp.fullSalary;
    ifstream myfile("accounts.txt");
    while (myfile >> id >> key) 
	{
        if (username == id && password == key)
		{
			if(emp.id == id)
			{
				cout << "\n===========================";
				cout << "\nId: " << emp.id <<endl << "First name: " << emp.Fname <<endl << "Last name: " << emp.Lname <<endl 
				<<"Position: " << emp.position <<endl << "Work hour: " << emp.workHour << endl << "Salary: " << emp.salary <<
				endl << emp.fullSalary;
				cout << "\n===========================\n\n";

         		found = true;
        	}
            break;
        }
    }
    if(id == emp.id && key == password)
    	break;
	}
    if (found == false)
        cout << "\nNo such contact is found!\n";
        
    system("pause");
    system("cls");
}

//Chooses top 3 star employees based on their overtime work
void empOfTheYear(){
	read();

	worker temp;
	for (int x = 0; x <= index; x++){
		for (int j = x + 1; j <= index; j++){
			if (e[x].ot < e[j].ot){
				temp = e[j];
				e[j] = e[x];
				e[x] = temp;
			}
		}
	}

	
	cout << "Employees of the month \n";
	for (int j = 0; j < 3; j++){
		cout << "***********************\n";
		cout << j + 1;
		cout << ".Name: " << e[j].Fname << " " <<e[j].Lname << endl;
		cout << "  ID: " << e[j].id << endl;
		cout << "  Position: " << e[j].position << endl;
		cout << "  Working hour: " << e[j].workHour << endl;
		cout << "  Total payment: " << e[j].fullSalary << endl << endl;
	}
	cout << "***********************\n\n";
	
	system ("pause");
	system ("cls");
}

//Lists employees with all their credentials
void empList()
{
	char ch;
	
	ifstream list;
	list.open("employee.txt");
	
    cout << "Id\t" << "Full Name Position   Worktime   Salary\t   Full Salary";
	cout << "\n==============================================================\n";  
	while(list>>noskipws>>ch)
		cout << ch;
    cout << "\n==============================================================";  

    list.close();
    cout<<endl;
}

//Removes an employee and writes his/hers credentials on removed employees file
void firedEmp()
{
	char ch;
	
	ifstream list;
	list.open("RemovedEmployees.txt");
	
    cout << "Id\t" << "Full Name\t" << "Position\t";
	cout << "\n==============================================================\n";  
	while(list>>noskipws>>ch)
		cout << ch;
    cout << "\n==============================================================";  

    list.close();
    cout<<endl;
}

//Summerizes total expendture of the company
void total(){
	read();
	long sum = 0, sum1 = 0;
	for (int j = 0; j <= index; j++){
		sum += e[j].salary;
		sum1 += e[j].fullSalary;	
	}
	cout << "Total amount paid by the company is: " << sum1 << "$" << endl;
	cout << "Total amount paid by the company in regular time is: " << sum << "$" << endl;
	cout << "Total amount paid by the company in overtime: " << sum1 - sum << "$" << endl;
}




