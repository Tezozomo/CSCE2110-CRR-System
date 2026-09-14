/*

   //current[UPDATE: Does run]
   compile: g++ main.cpp resources.cpp
   execute: ./a.out ../data/resources.txt
*/
#include"../headers/libraries.h"                //
using namespace std;

void banner();
void menu();
void resourceManagement();
void reservationManagement();
void waitingList();
void cancellationHistory();

int main(int argc, char* argv[]) {
   banner();                                    //display intro
   Resources resources;                         //create object of type Resources
   int option = 0;                                  //for menu
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
   //files accepted start menu
   do {
      menu();                                      //load files successful than display menu
      cout << endl << "Select an option: ";
      cin >> option;
   
      switch(option) {
         case 1:
            resourceManagement();
            break;
         case 2:
            reservationManagement();
            break;
         case 3:
            waitingList();
         case 4:
            cancellationHistory();
         case 0:
            break;
         default:
            cout << "Option not available\n";

      }
   } while(option != 0);

   return 0;

}

void banner() {
   cout << "+--------------------------------------------------------------+\n"
        << "|               Computer Science and Engineering               |\n"
        << "|            CSCE 2110 - Foundation of Data Structures         |\n"
        << "|                                                              |\n"
        << "|                Project 1 Student Resource Center             |\n"
        << "|                                                              |\n"
        << "|                  Section 400 Group Members:                  |\n"
        << "|             Dalen Ragsdale dalenragsdale@my.unt.edu          |\n"
        << "|               Ivan Garcia ivangarcia4@my.unt.edu             |\n"
        << "|              Trevor Sipes trevorsipes@my.unt.edu             |\n"
        << "+--------------------------------------------------------------+\n\n\n";

};
//menu CRRS category
void menu() {
   cout << "+--------------------------------------------------------------+\n"
        << "|                  Student Resource Center                     |\n"
        << "+--------------------------------------------------------------+\n"
        << "|   1 - Resource Management                                    |\n"
        << "|   2 - Reservation Management                                 |\n"
        << "|   3 - Waiting List Management                                |\n"
        << "|   4 - Cancellation History                                   |\n"
        << "|   0 - Exit Menu                                              |\n"
        << "+--------------------------------------------------------------+\n\n";

}

void resourceManagement() {
   int option;

}

void reservationManagement() {
   int option;

}

void waitingList() {
   int option;

}

void cancellationHistory() {
   int option;

}