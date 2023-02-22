#include <iostream>
#include <cstring>
#include "student.h"

using namespace std;

student::student(char* nameF, char* nameL, int number, float GPA){
  char* name1 = new char[20];
  char* name2 = new char[20];
  strcpy(name1, nameF);
  strcpy(name2, nameL);
  this -> number = number;
  this -> GPA = GPA;
}

student::student(){
  //default constructor
}

char* student::getName(){
  return name1;
}

char* student::getName2(){
  return name2;
}

void student::setNumber(int studentNum){
  number = studentNum;
}

int student::getNumber(){
  return number;
}

void student::setGPA(float grade){
  GPA = grade;
}

float student::getGPA(){
  return GPA;
}
