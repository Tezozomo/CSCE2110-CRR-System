#makefile for SRC project
#create executable
main: main.o resources.o reservations.o reservationManager.o
	g++ main.o resources.o reservations.o reservationManager.o -o milestone

main.o: src/main.cpp headers/libraries.h headers/resources.h headers/reservations.h headers/reservationManager.h
	g++ -Iheaders -c src/main.cpp -o main.o

resources.o: src/resources.cpp headers/resources.h
	g++ -Iheaders -c src/resources.cpp -o resources.o

reservations.o: src/reservations.cpp headers/reservations.h
	g++ -Iheaders -c src/reservations.cpp -o reservations.o

reservationManager.o: src/reservationManager.cpp headers/reservationManager.h headers/resources.h headers/reservations.h
	g++ -Iheaders -c src/reservationManager.cpp -o reservationManager.o
#execute with .txt arguments
#initiate makefile with: make run
run: main
	./milestone data/resources.txt data/reservations.txt
#initiate cleanup with: make clean
clean:
	rm -f milestone main.o resources.o reservations.o reservationManager.o
