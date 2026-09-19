#include "../headers/reservations.h"
// create empty reservation
Reservation::Reservation() = default;

// create reservation entry
Reservation::Reservation(const string& id, const string& studentIDValue,
								 const string& studentNameValue, const string& resourceIDValue,
								 const string& date)
	: reservationID(id), studentID(studentIDValue), studentName(studentNameValue),
	  resourceID(resourceIDValue), reservationDate(date) {}

string Reservation::getID() const { return reservationID; }
string Reservation::getStudentID() const { return studentID; }
string Reservation::getStudentName() const { return studentName; }
string Reservation::getResourceID() const { return resourceID; }
string Reservation::getDate() const { return reservationDate; }

void Reservation::display() const {
	// print reservation row
	cout << left << setw(8) << reservationID << setw(12) << studentID
		  << setw(22) << studentName << setw(12) << resourceID << reservationDate << '\n';
}