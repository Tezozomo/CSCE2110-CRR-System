/*[UPDATE: does not run right now,
    applying abstraction changing the file upload in respective class] 

   //current[UPDATE: does not run]
   compile: g++ main.cpp resources.cpp
   execute: ./a.out ../data/resources.txt
*/
#include"../headers/libraries.h"
using namespace std;

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

int main(int argc, char* argv[]) {
   banner();      //display intro
   //argument count need 3 for final product
   if(argc == 2) {      //index 0-execute, 1-resource, 2-reservation
      ifstream resourceF(argv[1]);     //input file stream resources.txt
      // ifstream reservF(argc[2]);  //reservations.txt
      

      if(!resourceF.is_open()) {             //check both files opened
         cout << "Error:: File Not Open -" << argv[1] << endl;
         return 1;      //failure exit 
      
      }
      // if(!reservF.is_open()) {
      //    cout << "Error:: File Not Open -" << argv[2] << endl;
      //    return 1;
      
      // }

      while(getline(resourceF, line)) {      //until last line of file
         stringstream ss(line);     //one line at a time
         //seperate data to variables
         if(getline(ss, id, '|') && getline(ss, name, '|' ) && getline(ss, type, '|') && getline(ss, availability, '|')) {
            resources.emplace_back(id, name, type, availability);     //construct obj in vector //emplace bc raw arguments 

         }

      }
      resourceF.close();      //close input filestream 
      //reservF.close();

   }
   else {
      // If 3 args not input
	   cout << "Three required arguments were not entered.\n";
	   cout << "Arugments expected: ./a.out resource.txt reservation.txt\n";
	   return 1;

   }
   
   return 0;
}