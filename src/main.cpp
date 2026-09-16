/*

   //current[UPDATE: Does run]
   compile: g++ main.cpp resources.cpp
   execute: ./a.out ../data/resources.txt
*/
#include "../headers/libraries.h"
#include "../headers/reservations.h"
using namespace std;

//user-defined fx's
void banner();
string prompt(const string& label);
void printMenu();

int main(int argc, char* argv[]) {
   banner();                                    //display intro
   Resources resources;                         //create object of type Resources
   int option = 0;
   if(argc == 3) {
      if(!resources.sortFile(argv[1])) {        //check file open and sort
         cout << "Error:: File Not Open -" << argv[1] << endl;
         return 1;                              //failure exit 
      
      }
      ReservationManager manager(resources);
      if(!manager.loadReservations(argv[2])) {
         cout << "Error:: File Not Open -" << argv[2] << endl;
         return 1;
      }

      do {
         printMenu();
         string input = prompt("Select an option: ");
         stringstream optionInput(input);
         if(!(optionInput >> option)) option = -1;
         switch(option) {
            case 1:
               resources.displayResources();
               break;
            case 2: {
               Reservation reservation(prompt("Reservation ID: "), prompt("Student ID: "),
                  prompt("Student Name: "), prompt("Resource ID: "), prompt("Reservation Date: "));
               if(resources.findIndex(reservation.getResourceID()) < 0) cout << "Invalid resource ID.\n";
               else if(resources.getAvailability(reservation.getResourceID()) != "Available") manager.addToWaitingList(reservation);
               else if(manager.createReservation(reservation)) cout << "Reservation created successfully.\n";
               else cout << "Duplicate reservation ID.\n";
               break;
            }
            case 3:
               if(manager.cancelReservation(prompt("Reservation ID: "))) cout << "Reservation cancelled.\n";
               else cout << "Reservation not found.\n";
               break;
            case 4:
               manager.displayWaitingLists();
               break;
            case 5:
               if(manager.undoCancellation()) cout << "Reservation restored successfully.\n";
               else cout << "No cancellation can be undone.\n";
               break;
            case 6:
               if(!resources.displayResource(prompt("Resource ID: ")))
                  cout << "Resource not found.\n";
               break;
            case 7:
               manager.searchReservations(prompt("Search ID, student, or resource: "));
               break;
            case 8: {
               string criterion = prompt("Sort by id, name, or type: ");
               resources.sortResources(criterion);
               resources.displayResources();
               break;
            }
            case 9:
               manager.generateReport();
               break;
            case 0:
               break;
            default:
               cout << "Option not available.\n";
         }
      } while(option != 0);
      return 0;
   }
   else {                                       //Invalid amount of inputs need three
	   cout << "Three required arguments were not entered.\n";
	   cout << "Input expected: executable file1 file2\n";
	   return 1;

   }
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

}
string prompt(const string& label) {
   cout << label;
   string value;
   getline(cin >> ws, value);
   return value;
}

void printMenu() {
   cout << "+--------------------------------------------------------------+\n"
        << "|           Campus Resource Reservation System                 |\n"
        << "+--------------------------------------------------------------+\n"
      << "|   1 - View Resources        6 - Search Resource               |\n"
      << "|   2 - Create Reservation    7 - Search Reservations            |\n"
      << "|   3 - Cancel Reservation    8 - Sort Resources                |\n"
      << "|   4 - View Waiting Lists    9 - Generate Report               |\n"
      << "|   5 - Undo Cancellation     0 - Exit                          |\n"
        << "+--------------------------------------------------------------+\n\n";
}