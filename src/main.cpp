/*

   //current[UPDATE: does not run]
   compile: g++ main.cpp resources.cpp
   execute: ./a.out ../data/resources.txt
*/
#include"../headers/libraries.h"                //
using namespace std;

void banner();

int main(int argc, char* argv[]) {
   banner();                                    //display intro
   Resources resources;                         //create object of type Resources
   
   //argument count need 3 for final product
   if(argc == 2) {                              //index 0-execute, 1-resources.txt, 2-reservation.txt
      if(!resources.sortFile(argv[1])) {        //check file open and sort
         cout << "Error:: File Not Open -" << argv[1] << endl;
         return 1;                              //failure exit 
      
      }
   }
   else {                                       //Invalid amount of inputs need three
	   cout << "Three required arguments were not entered.\n";
	   cout << "Input expected: executable file1 file2\n";
	   return 1;

   }
   
   return 0;

}

void banner() {
   cout << "+--------------------------------------------------------------+\n"
        << "|               Computer Science and Engineering               |\n"
        << "|            CSCE 2110 - Foundation of Data Structures         |\n"
        << "|                                                              |\n"
        << "|                  Project 1 Student Resource Center           |\n"
        << "|                                                              |\n"
        << "|                   Section 400 Group Members:                 |\n"
        << "|             Dalen Ragsdale dalenragsdale@my.unt.edu          |\n"
        << "|               Ivan Garcia ivangarcia4@my.unt.edu             |\n"
        << "|              Trevor Sipes trevorsipes@my.unt.edu             |\n"
        << "+--------------------------------------------------------------+\n\n\n";

};