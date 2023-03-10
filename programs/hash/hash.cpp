#include <iostream>
#include <cstring>
#include <fstream>
#include "student.h"
#include "node.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <cstdlib>

using namespace std;
void add(node ** &Hashtable, student* newStu, int index);
void del(node** &Htable, int idDelete, int sizeT);
void print(node** table, int Tsize);
void printloop(node * cur, node* next, int inx);
student* studentMaker(char *name, char *name2, int stuNum, float GPA, node** &hashTable, int tableSize);
void gene(int numberOfStudCreations, char** firstArr, char** lastArr,node** & table);
void reHashTable(node ** &hashTable, int tableSize);
node *head = NULL;
int Tablesize = 100;
int main(){
  node **hashTable = new node*[100];
  char userInput[20];
  srand (time(NULL));
  ifstream inFile("Fnames.txt");
  ifstream inFile2("Lnames.txt");
  char **firstArr =  new char*[20];
  char **lastArr =  new char*[20];
  for(int a = 0; a<20; a++){
    firstArr[a] = new char[15];
    inFile>>firstArr[a];
  }
  for(int b = 0; b<20; b++){
    lastArr[b] = new char[15];
    inFile>>lastArr[b];
  }
  cout<<"Generating random students..."<<endl;
  gene(20, firstArr, lastArr, hashTable);
  cout<<"done..."<<endl;
   do{//do this until the user says quit
    cout<<"Type 'add' to add student;Type 'del' to delete;Type 'print' to print all students' info;Type 'quit' to quit"<<endl;

    cin.getline(userInput,10,'\n');//gets the user's request then clears the cin
    int numDelete;
    if(strcmp(userInput, "add") == 0){//if they say add run the add function
      char *firstName = new char[20];
      char *lastName = new char[20];
      int idNum;
      float grade;
      cout<<"First Name: "<<endl;
      cin>> firstName;
      cout<<"Last Name: "<<endl;
      cin>> lastName;
      cout<<"ID number: "<<endl;
      cin>> idNum;
      cout<<"GPA: "<<endl;
      cin>> grade;
      student* student = studentMaker(firstName, lastName, idNum, grade, hashTable, 100);
      add(hashTable, student, student->number % Tablesize);
      cout<<"Student Added!"<<endl;
    }
    if(strcmp(userInput, "print")==0){//if they say print run the print function
      print(hashTable, Tablesize);
    }
    if(strcmp(userInput, "del")==0){//if they say delete run the delete function
      cout<<"Enter the Student's ID"<<endl;
      cin>>numDelete;
      cin.get();
      del(hashTable,numDelete, Tablesize);
      cout<<"Student deleted"<<endl;
    }
  }while(strcmp(userInput, "quit") != 0);

  return 0;
}
student* studentMaker(char *name, char *name2, int stuNum, float GPA, node ** & hashTable, int tableSize){
  char* test = new char[20];
  char* test2 = new char[20];
  int numstud;
  float gradepoint;
  strcpy(test, name);
  strcpy(test2, name2);
  numstud = stuNum;
  gradepoint = GPA;
  student *student4 = new student(test, test2, numstud, gradepoint);
  node* newStud = new node(student4);
  if(hashTable[numstud%tableSize] != NULL){
    while(newStud->getNext() != NULL){
      newStud = newStud->getNext();
    }
    hashTable[numstud%tableSize] = newStud;
   }
  else{
    hashTable[numstud%tableSize] = newStud;
  }
  return student4;
}
void gene(int numberOfStudCreations, char** firstArr, char** lastArr, node** & table){
  for(int i = 0;i<numberOfStudCreations;i++){
    //generates random number
    int randomNum = rand() % 100 + 1;
    //random 6 number gen
    int low;
    int high;
    high = 4;
    low = 0;
    double random;
    random=(double)(rand()%400)/100.0;
    //random 3 digit decimal generator
    studentMaker(firstArr[rand()%20], lastArr[rand()%20], randomNum, random, table, 100);
  }
}
void add(node ** &Hashtable, student* newStu, int index) {
  bool loop = false;
  node* newNode = new node(newStu);
  if (Hashtable[index] != NULL) {
    node* current = Hashtable[index];
    while (!loop) {
      if (current->nextNode == NULL) {
        current->nextNode = newNode;
        newNode->nextNode = NULL;
        loop = true;
      }
      else {
        current = current->nextNode;
      }
    }
  }
  else {
    Hashtable[index] = newNode;
    newNode->nextNode = NULL;
  }

}
void del(node** &Htable, int idDelete, int sizeT) {
  int i = idDelete % sizeT;
  node * cur2 = Htable[i];
  node * pre = cur2;
  int counter = 0;
  bool doneDeleting = false;
  while (cur2 != NULL) {//while the current node is not empty
     if (cur2->stu->number == idDelete && counter == 0){//looping throught the table and if the student's id is equal to the id that is to be deleted then...
      node * removeHead = cur2; //node pointer equals the current node so I can delete it later
      pre = cur2->nextNode;//moving the previous node up to replace the currnet node that will be deleted
      cur2 = cur2->nextNode;
      Htable[i] = cur2;
      delete removeHead;
      doneDeleting = true;
    }
    else if (cur2->stu->number == idDelete) {
      node* tempVar = cur2;
      pre->nextNode = cur2->nextNode;
      cur2 = cur2->nextNode;
      delete tempVar;
      doneDeleting = true;
    }
    else {
      pre = cur2;
      cur2 = cur2->nextNode;
    }
    counter++;
  }
  if (doneDeleting == true) {
    cout << "Student deleted" << endl;
  }
  else {
    cout << "No student matches the ID, try again..." << endl;
  }

}

void print(node** table, int Tsize) {
  cout<<"here"<<endl;
  for (int i = 0; i < Tsize; i++) {
    if (table[i] != NULL) {//making sure there is stuff in there
      printloop(table[i], table[i], i);
      cout<<"done"<<endl;
    }
    else {
      //don't do anything
    }
  }
}
void printloop(node* cur, node* next, int inx) {//printing out
  if (next == cur) {
    cout << endl;
    cout << "Student(s) in row " << inx << ":" << endl;
  }

  if (next != NULL) {
    cout<<next->stu<<endl;
    next->stu->getDescription();
    cout<<"here"<<endl;
    printloop(cur, next->getNext(), inx);
  }
}
void reHashTable(node ** &hashTable, int tableSize) {
  node** reHash = new node*[tableSize];
  for (int i = 0; i < tableSize; i++) {
    reHash[i] = NULL;
  }
  int indexNum = 0;
  for (int i = 0; i < tableSize / 2; i++) {
    if (hashTable[i] != NULL) {
      node* newnode2 = hashTable[i];
      while (newnode2 != NULL) {
        indexNum = newnode2->getStudent()->number % tableSize;
        add(reHash, newnode2->getStudent(), indexNum);
        newnode2 = newnode2->nextNode;
      }
    }
  }
  delete [] hashTable;
  hashTable = reHash;
}
