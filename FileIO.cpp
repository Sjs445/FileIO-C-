#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

struct PERSON{
  char Name[20];
  float Balance;
};

int countLines(string);
void display(struct PERSON a[], int size);
void findRichest(struct PERSON a[], int size);
void deposit(char CustName[], struct PERSON a[], int size);
void newCopy(string filename, struct PERSON a[], int size);

int main()
{
  string file="data.txt";
  int count=countLines(file);
  cout<<"There are "<<count<<" lines in the text file.\n"<<endl;

  PERSON P[count];
  char lname[20];

//Read in the text file here
  ifstream infile;
  infile.open(file);

for(int i=0; i<6; i++)
{
  infile>>P[i].Name;
  infile>>lname;
  infile>>P[i].Balance;

  strcat(P[i].Name, " ");
  strcat(P[i].Name, lname);
}
infile.close();

char newName[20];

display(P, count);
findRichest(P, count);
deposit(newName, P, count);

newCopy("data.txt", P, count);

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
  cout<<"\nThe customer with the maximum balance is "<<richestname<<"."<<endl;
}

void deposit(char CustName[], struct PERSON a[], int size)
{
  float deposit;
  cout<<"Enter your full name to deposit money: ";
  cin.get(CustName, 20);
  cout<<"\n"<<CustName<<", how much would you like to deposit?"<<endl;
  cin>>deposit;
  for(int i=0; i<size; i++)
  {
    if(strcmp(a[i].Name, CustName)==0)
    {
      a[i].Balance+=deposit;
      cout<<"\n"<<CustName<<", your new balance is "<<a[i].Balance<<endl;
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
  cout<<"\nFile copied!"<<endl;
}
