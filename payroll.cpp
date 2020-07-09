//


#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

void printWelcome();
void displayMenu();
void selectChoice(int);
void insertEmployee();
void displayEmployeeList();
void searchID();
void updateEmployeeInfo();
void calculatePay(float, int, float&, float&);

int main()
{

    printWelcome();
    displayMenu();

}

void printWelcome(){

    cout << setw(13) << " **********************************************" << endl;
    cout << setw(13) << " *    WELCOME TO PAYROLL MANAGEMENT SYSTEM    *" << endl;
    cout << setw(13) << " **********************************************" << endl << endl;

}

void displayMenu(){

    int choice;
    char answer;
    cout << setw(13) << " **********************************************" << endl;
    cout << setw(13) << " *                  Menu:                     *" << endl;
    cout << setw(13) << " *  1. Insert new employee's information      *" << endl;
    cout << setw(13) << " *  2. Display available employee list        *" << endl;
    cout << setw(13) << " *  3. Search record from employee's ID       *" << endl;
    cout << setw(13) << " *  4. Update record of an employee           *" << endl;
    cout << setw(13) << " *                                            *" << endl;
    cout << setw(13) << " *      Enter your choice below:              *" << endl;
    cout << setw(13) << " **********************************************" << endl;
    cin>>choice;
    cout << endl;
    selectChoice(choice);
    cout << endl;
    cout << "Do you wish to continue? (Y/N)" << endl;
    cin >> answer;
    cout << endl;

    if(answer == 'Y'){

        displayMenu();
    }
    else{

        cout << "Thank you for using Payroll Management System" << endl;

    }

}

void selectChoice(int choice){

    switch(choice){

    case 1:
        insertEmployee();
        break;

    case 2:
        displayEmployeeList();
        break;

    case 3:
        searchID();
        break;

    case 4:
        updateEmployeeInfo();
        break;

    default:
        cout << "Invalid selection. Please choose again!" << endl;
        cout << endl;
        displayMenu();


    }

}

void insertEmployee(){

    string employeeName;
    string employeeID;
    int hours;
    float payRate;
    float gross;
    float net;
    ofstream employeeInfo;

    cout << endl;
    cout << " Insert New Employee Information" << endl;
    cout << " *******************************************************************************************************************" << endl <<endl;
    cout << " Enter Employee's Name  : ";
    cin >> employeeName;

    cout << " Enter Employee's ID    : ";
    cin >> employeeID;

    cout << " Enter Working Hours    : ";
    cin >> hours;

    cout << " Enter Pay Rate/Hours   : ";
    cin >> payRate;

    calculatePay(payRate, hours, gross, net);

    cout << endl;
    cout << "The gross pay for " << employeeName << "  : RM" << gross<< endl;
    cout << "The net pay for " << employeeName << "    : RM" << net<< endl;

    employeeInfo.open("employee.dat", ios::app);

    if(!employeeInfo.is_open()){
        cout << "Error opening file. Fail to save data. \n";

    }
    employeeInfo << setw(5) << employeeName << setw(20) << employeeID << setw(20) << hours << setw(20) << payRate << setw(25) << gross << setw(25) << net << endl;
    employeeInfo.close();

}

void displayEmployeeList(){


    ifstream employeeInfo;
    employeeInfo.open("employee.dat");

    if(!employeeInfo.is_open()){
        cout << "Error opening file. \n";

    }
    else{

    cout << " Display Employee List" << endl;
    cout << " *******************************************************************************************************************" << endl <<endl;

    string data;
    while(getline(employeeInfo, data)){
         cout << data << "\n";
      }
    }

    employeeInfo.close();

}

void searchID(){

    string ID;
    ifstream employeeInfo;
    int line_number = 0;
    string str;

    employeeInfo.open("employee.dat");

    cout << " Display Employee Info" << endl;
    cout << " *********************************************************************************************************************" << endl <<endl;

    cout << " Enter Employee's ID : ";
    cin >> ID;

    if(!employeeInfo.is_open()){
        cout << "Error opening file. Fail to save data. \n";

    }
    cout << endl;
    cout << setw(5) << "Employee's name" << setw(20) << "Employee's ID" << setw(20) << "Working Hours" << setw(20) << "Pay Rate/Hour" << setw(20) << "Gross Pay" << setw(20) << "Net Pay" << endl;


    while (getline(employeeInfo, str)){

        ++line_number;
        if(str.find(ID) != std::string::npos){
            cout << str;
        }
    }
    cout << endl;

}

void updateEmployeeInfo(){

    string line;
    string ID;
    ifstream employeeInfo;
    string employeeName;
    string employeeID;
    int hours;
    float payRate;
    float gross;
    float net;
    employeeInfo.open("employee.dat");

    ofstream temp;
    temp.open("temp.dat");

    cout << " Update Employee Info" << endl;
    cout << " *********************************************************************************************************************" << endl <<endl;

    cout << " Enter Employee's ID for update : ";
    cin >> ID;

    while(getline(employeeInfo, line)){

        if(line.find(ID) == std::string::npos){
            temp << line << endl;
        }
    }
    employeeInfo.close();
    temp.close();
    remove("employee.dat");
    rename("temp.dat", "employee.dat");

    cout << " Enter Employee's Name          : ";
    cin >> employeeName;

    cout << " Enter Working Hours            : ";
    cin >> hours;

    cout << " Enter Pay Rate/Hours           : ";
    cin >> payRate;

    calculatePay(payRate, hours, gross, net);

    cout << endl;
    cout << "New gross pay for " << employeeName << "  : RM" << gross<< endl;
    cout << "New net pay for " << employeeName << "    : RM" << net<< endl;

    ofstream file;
    file.open("employee.dat", ios::app);

    file << setw(5) << employeeName << setw(20) << ID << setw(20) << hours << setw(20) << payRate << setw(25) << gross << setw(25) << net << endl;
    file.close();

}

void calculatePay(float payRate, int hours, float& gross, float& net){

    float stateTax = 0.05;
    float fedTax = 0.12;

    gross = payRate*hours;
    net = gross - (gross * stateTax) - (gross * fedTax);

}

