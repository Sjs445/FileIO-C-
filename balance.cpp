//Shane Spangenberg
//301 Section #2

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>

using namespace std;

struct PERSON{
  char Name[20];
  float Balance;
};

void printmenu() {
    cout << "Please enter a choice:" << endl;
    cout << "1. Display records"<< endl;
    cout << "2. Deposit funds"<< endl;
    cout << "3. Find Highest Balance" << endl;
    cout << "4. Update records" << endl;
    cout << "5. Exit the program" << endl;
}

PERSON * readData(int N);
int countLines(string);
bool searchName(struct PERSON a[], int size); //helper function
void display(struct PERSON a[], int size);
void findRichest(struct PERSON a[], int size);
void Deposit(struct PERSON arr[], int N, char custName[], double amount);
void newCopy(string filename, struct PERSON a[], int size);

int main()
{
  int count=countLines("data.txt");
  cout<<"There are "<<count<<" lines in the text file.\n"<<endl;
PERSON *P;

P=readData(count);

int done=0;

int choice;
do
{
    printmenu();
    cin >> choice;
    switch(choice)
    {
        case 1:
            // Act on display
            display(P, count);
            break;

        case 2:
            // Act on deposit
            while(done!=1)
            {
            done=searchName(P, count);
            }
            break;

        case 3:
            // Act highest balance
            findRichest(P, count);
            break;

        case 4:
            // Act on update records
            newCopy("data.txt", P, count);
            break;

        case 5:
            // Must call update records here before exiting the program
            newCopy("data.txt", P, count);
            break;

        default:
            cout << "Invalid entry" << endl;
            break;
    }
    cout << endl;
} while(choice != 5);

delete P; //handling memory leaks here
P=NULL;

  return 0;
}

int countLines(string file)
{
  string line;
  int count=0;
  ifstream inFile(file);

  while(getline(inFile, line)) //reads all words (whitespace included)
  {
    ++count; //increment count each line
  }

  inFile.close();
return count;
}


void display(struct PERSON a[], int size)
{
  cout<<"Name"<<"\t\t"<<"Balance\n";
  cout<<"-------------------------------\n";
  cout<<fixed;
  cout<<setprecision(2);
  for(int i=0; i<size; i++)
  {
    cout<<a[i].Name<<"\t";
    cout<<a[i].Balance<<endl;
  }
}

void findRichest(struct PERSON a[], int size)
{
  float richest=0;
  char richestname[20];

  for(int i=0; i<size; i++)
  {
    if(a[i].Balance>richest)
    {
      richest=a[i].Balance;
      strcpy(richestname, a[i].Name);
    }
  }
  cout<<"\nHighest balance: "<<richestname<<endl;
}

void Deposit(struct PERSON arr[], int N, char custName[], double amount)
{
  cout<<fixed;
  cout<<setprecision(2);

  for(int i=0; i<N; i++)
  {
    if(strcmp(arr[i].Name, custName)==0)
    {
      arr[i].Balance+=amount;
      cout<<"\n"<<"New Balance: "<<arr[i].Balance<<endl;
    }
  }
}

void newCopy(string filename, struct PERSON a[], int size)
{
  ofstream fileout;
  fileout.open(filename);
  for(int i=0; i<size; i++)
  {
    fileout<<a[i].Name<<" ";
    fileout<<a[i].Balance<<"\n";
  }
  fileout.close();
  cout<<"\nFile Updated..."<<endl;
}

PERSON * readData(int N)
{
  N=countLines("data.txt");
  PERSON *P=NULL;
  P=new PERSON [N];

char fName[9];  //Since fName is a char of size 9 we will only accept
                //the first 9 characters for input.
char lName[10];
char FullName[20];

  ifstream inData;
  inData.open("data.txt");

  for(int i=0; i<N; i++)
  {
    inData>>fName>>lName;
    strcpy(FullName, fName);
    strcat(FullName, " ");
    strcat(FullName, lName);
    strcpy(P[i].Name, FullName);
    inData>>P[i].Balance;
  }
inData.close();

return P;
}

bool searchName(struct PERSON a[], int size)
{
char name[20];
double amt;
int count=0;
cin.clear();
cin.ignore();
cout<<"Enter Name: ";
cin.get(name, 20);

  for(int i=0; i<size; i++)
  {
    count++;
    if(strcmp(a[i].Name, name)==0)
    {
      cout<<"Enter Amount: ";
      cin>>amt;
      Deposit(a, size, name, amt);
      return true;
    }
    else if(count==size)
    {
      cout<<"Name not valid. "<<endl;
      count=0;
      return false;
    }
  }
}
