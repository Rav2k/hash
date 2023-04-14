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

void add(node** &Hashtable, student* newStu, int index);
void del(node** &Htable, int idDelete, int sizeT);
void print(node** table, int Tsize);
void printloop(node * cur, node* next, int inx);
student* studentMaker(char *name, char *name2, int stuNum, float GPA, node** &hashTable, int tableSize);
bool collisions(node ** &table, int size);
void gene(int numberOfStudCreations, char** firstArr, char** lastArr,node** & table);
void reHashTable(node ** &hashTable, int tableSize);
node *head = NULL;
int Tablesize = 100;
int main(){
  node **hashTable = new node*[100];
  for(int i = 0; i<100;i++){
    hashTable[i] = NULL;
  }
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
     if (collisions(hashTable, Tablesize)) {
      //rehash table
      Tablesize = Tablesize * 2;
      reHashTable(hashTable, Tablesize);
    }
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

void add(node** &Hashtable, student* newStu, int index) {

  bool loop = false;
  node* newNode = new node(newStu);
  cout<<"Hash number:"<<Hashtable[index]->number<<endl;
  cout<<"newNode: "<<newNode->number<<endl;
  if (Hashtable[index] != NULL) { // Add condition to check if Hashtable[index] is not NULL
    newNode->setNext(Hashtable[index]); // Set the next pointer of new node to the current node at the index
  }
  Hashtable[index] = newNode;
  
  /*bool loop = false;
  node* newNode = new node(newStu);
  cout<<"Hash number:"<<Hashtable[index]->number<<endl;
  cout<<"newNode: "<<newNode->number<<endl;
  if (Hashtable[index] == NULL) { // Fix this condition
    Hashtable[index] = newNode;
  } else {
    node* temp = Hashtable[index];
    while (temp->getNext() != NULL) {
      temp = temp->getNext();
    }
    temp->setNext(newNode);
  }*/
  
  //for(temp = Hashtable[index]; temp->nextNode !=NULL; temp = temp->nextNode);
  cout<<"DONE"<<endl; 
  }
  

void del(node** &Htable, int idDelete, int sizeT) {
  int index = idDelete % sizeT;
  node* current = Htable[index];
  node* previous = NULL;

  while (current != NULL && current->number != idDelete) {
    previous = current;
    current = current->getNext();
  }

  if (current == NULL) {
    cout << "Student not found" << endl;
    return;
  }

  if (previous == NULL) {
    // If the node to be deleted is the first node
    Htable[index] = current->getNext();
  } else {
    previous->setNext(current->getNext());
  }

  delete current;

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

    node** newHashTable = new node*[tableSize]; // Create a new hash table with the updated table size
  for(int i = 0; i < tableSize; i++) {
    newHashTable[i] = NULL; // Initialize all entries in the new hash table to NULL
  }

  // Rehash all existing nodes from the old hash table to the new hash table
  for(int i = 0; i < Tablesize/2; i++) {
    node* cur = hashTable[i];
    while(cur != NULL) {
      node* next = cur->getNext();
      int newIndex = cur->number % tableSize; // Get the new index in the new hash table
      cur->setNext(newHashTable[newIndex]); // Update the next pointer of the current node to point to the new index in the new hash table
      newHashTable[newIndex] = cur; // Set the current node as the new head of the list at the new index in the new hash table
      cur = next; // Move to the next node in the old hash table
    }
  }

  // Delete the old hash table and update the hashTable pointer to point to the new hash table
  delete[] hashTable;
  hashTable = newHashTable;
}

bool collisions(node** &table, int size) {

  int counter = 0;
  
  for (int i = 0; i < size; i++) {
    if (table[i] != NULL) {
      node *current = table[i];
      while (current != NULL) {
	counter++;
	current = current->nextNode;
      }
      if (counter > 3) {
	return true;//rehash
      }
    }
    counter = 0;
  }

  return false;
  
}
