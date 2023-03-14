File Edit Options Buffers Tools C++ Help
#include <iostream>
#include <cstring>
#include "student.h"

using namespace std;

student::student(char* nameF, char* nameL, int number, float GPA){
  name1 = new char[20];
  name2 = new char[20];
  strcpy(name1, nameF);
  strcpy(name2, nameL);
  this -> number = number;
  this -> GPA = GPA;
}

student::student(){
  //default constructor
}
void student::getDescription() {
  cout<<"yo"<<endl;
  cout << "Name: " << name1 << " " << name2 << endl;
  cout<<"ok"<<endl;
  cout << "ID number: " << number << endl;
  cout << "GPA: " << fixed << setprecision(2) << GPA << endl;
}
