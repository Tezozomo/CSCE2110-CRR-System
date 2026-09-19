#include "../headers/reservationManager.h"

ReservationManager::ReservationManager(Resources& resourceList)
	// initialize manager state
	: resources(resourceList), head(nullptr) {}

ReservationManager::~ReservationManager() { clearReservations(); }

void ReservationManager::clearReservations() {
	while(head != nullptr) {
		ReservationNode* oldHead = head;
		head = head->next;
		delete oldHead;
	}
}

bool ReservationManager::reservationIDExists(const string& id) const {
	return findNode(id) != nullptr;
}

ReservationManager::ReservationNode* ReservationManager::findNode(const string& id) const {
	for(ReservationNode* current = head; current != nullptr; current = current->next) {
		if(current->value.getID() == id) return current;
	}
	return nullptr;
}

bool ReservationManager::loadReservations(const string& reservationFile) {
	// load reservation file
	ifstream input(reservationFile);
	if(!input.is_open()) return false;

	string line;
	while(getline(input, line)) {
		string id, studentID, studentName, resourceID, date;
		stringstream fields(line);
		if(getline(fields, id, '|') && getline(fields, studentID, '|') &&
			getline(fields, studentName, '|') && getline(fields, resourceID, '|') &&
			getline(fields, date, '|')) {
			createReservation(Reservation(id, studentID, studentName, resourceID, date));
		}
	}
	return true;
}

bool ReservationManager::createReservation(const Reservation& reservation) {
	// add active reservation
	if(reservationIDExists(reservation.getID()) ||
		resources.findIndex(reservation.getResourceID()) < 0) return false;
	head = new ReservationNode(reservation, head);
	resources.setAvailability(reservation.getResourceID(), "Unavailable");
	return true;
}

bool ReservationManager::cancelReservation(const string& reservationID) {
	// cancel active reservation
	ReservationNode* current = head;
	ReservationNode* previous = nullptr;
	while(current != nullptr && current->value.getID() != reservationID) {
		previous = current;
		current = current->next;
	}
	if(current == nullptr) return false;

	if(previous == nullptr) head = current->next;
	else previous->next = current->next;
	Reservation cancelled = current->value;
	delete current;
	cancellationHistory.push(cancelled);
	resources.setAvailability(cancelled.getResourceID(), "Available");

	auto waiting = waitingLists.find(cancelled.getResourceID());
	if(waiting != waitingLists.end() && !waiting->second.empty()) {
		Reservation next = waiting->second.front().reservation;
		waiting->second.pop();
		createReservation(next);
		cout << "Waiting request " << next.getID() << " was assigned the resource.\n";
	}
	return true;
}

bool ReservationManager::undoCancellation() {
	// restore last cancellation
	if(cancellationHistory.empty()) return false;
	Reservation restored = cancellationHistory.top();
	if(reservationIDExists(restored.getID()) ||
		resources.findIndex(restored.getResourceID()) < 0 ||
		resources.getAvailability(restored.getResourceID()) == "Unavailable") return false;
	cancellationHistory.pop();
	return createReservation(restored);
}

void ReservationManager::displayReservations() const {
	// display active reservations
	if(head == nullptr) {
		cout << "No active reservations.\n";
		return;
	}
	cout << left << setw(8) << "ID" << setw(12) << "Student ID" << setw(22)
		  << "Student Name" << setw(12) << "Resource" << "Date\n";
	cout << string(70, '-') << '\n';
	for(ReservationNode* current = head; current != nullptr; current = current->next)
		current->value.display();
}

void ReservationManager::searchReservations(const string& query) const {
	// search active reservations
	bool found = false;
	for(ReservationNode* current = head; current != nullptr; current = current->next) {
		const Reservation& reservation = current->value;
		if(reservation.getID() == query || reservation.getStudentID() == query ||
			reservation.getStudentName() == query || reservation.getResourceID() == query) {
			if(!found) {
				cout << left << setw(8) << "ID" << setw(12) << "Student ID" << setw(22)
					  << "Student Name" << setw(12) << "Resource" << "Date\n";
			}
			reservation.display();
			found = true;
		}
	}
	if(!found) cout << "No matching reservations found.\n";
}

void ReservationManager::addToWaitingList(const Reservation& request) {
	// queue waiting request
	if(reservationIDExists(request.getID())) {
		cout << "Duplicate reservation ID.\n";
		return;
	}
	for(const auto& entry : waitingLists) {
		queue<WaitingRequest> requests = entry.second;
		while(!requests.empty()) {
			if(requests.front().reservation.getID() == request.getID()) {
				cout << "Duplicate reservation ID.\n";
				return;
			}
			requests.pop();
		}
	}
	if(resources.findIndex(request.getResourceID()) < 0) {
		cout << "Invalid resource ID.\n";
		return;
	}
	waitingLists[request.getResourceID()].push({request});
	cout << "Resource unavailable. Request added to the waiting list.\n";
}

void ReservationManager::displayWaitingLists() const {
	// display waiting queues
	bool found = false;
	for(const auto& entry : waitingLists) {
		if(entry.second.empty()) continue;
		found = true;
		cout << "Resource " << entry.first << ": " << entry.second.size() << " waiting\n";
		queue<WaitingRequest> requests = entry.second;
		while(!requests.empty()) {
			cout << "  " << requests.front().reservation.getID() << " - "
				  << requests.front().reservation.getStudentName() << '\n';
			requests.pop();
		}
	}
	if(!found) cout << "No waiting requests.\n";
}

void ReservationManager::generateReport() const {
	// generate usage report
	map<string, int> counts;
	int active = 0;
	for(ReservationNode* current = head; current != nullptr; current = current->next) {
		++active;
		++counts[current->value.getResourceID()];
	}
	cout << "Active reservations: " << active << '\n';
	cout << "Reservation counts by resource:\n";
	for(const auto& entry : counts)
		cout << "  " << entry.first << ": " << entry.second << '\n';
	cout << "Waiting lists:\n";
	displayWaitingLists();
}
