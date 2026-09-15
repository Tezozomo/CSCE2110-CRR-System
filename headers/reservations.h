#ifndef RESERVATIONS_H
#define RESERVATIONS_H

#include "resources.h"

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

class ReservationManager {
public:
	ReservationManager(Resources& resources);
	~ReservationManager();

	bool loadReservations(const string& reservationFile);
	bool createReservation(const Reservation& reservation);
	bool cancelReservation(const string& reservationID);
	bool undoCancellation();
	void displayReservations() const;
	void searchReservations(const string& query) const;
	void addToWaitingList(const Reservation& request);
	void displayWaitingLists() const;
	void generateReport() const;

private:
	struct ReservationNode {
		Reservation value;
		ReservationNode* next;
		ReservationNode(const Reservation& reservation, ReservationNode* nextNode = nullptr)
			: value(reservation), next(nextNode) {}
	};

	Resources& resources;
	ReservationNode* head;
	map<string, queue<WaitingRequest>> waitingLists;
	stack<Reservation> cancellationHistory;

	bool reservationIDExists(const string& id) const;
	ReservationNode* findNode(const string& id) const;
	void clearReservations();
};

#endif
