#ifndef RESERVATIONMANAGER_H
#define RESERVATIONMANAGER_H

#include "libraries.h"
#include "resources.h"
#include "reservations.h"

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
