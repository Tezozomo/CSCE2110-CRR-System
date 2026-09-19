#ifndef RESERVATIONS_H
#define RESERVATIONS_H

#include "libraries.h"
using namespace std;

class Reservation {
public:
	Reservation();
	Reservation(const string& id, const string& studentID, const string& studentName,
					const string& resourceID, const string& date);

	string getID() const;
	string getStudentID() const;
	string getStudentName() const;
	string getResourceID() const;
	string getDate() const;
	void display() const;

private:
	string reservationID;
	string studentID;
	string studentName;
	string resourceID;
	string reservationDate;
};

struct WaitingRequest {
	Reservation reservation;
};

#endif