#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

class student{
 public:
  char *name1;
  char *name2;
  int number;
  float GPA;
  void getDescription();
  char* getName();
  char* getName2();
  void setNumber(int studentNum);
  int getNumber();
  void setGPA(float grade);
  float getGPA();
  student();
  student(char* nameF, char* nameL, int number, float GPA);
};
#endif
