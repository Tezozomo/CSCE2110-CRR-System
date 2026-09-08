/* fx calls for the resource info

*/

#ifndef RESOURCES_H
#define RESOURCES_H

#include"libraries.h"
using namespace std;

class Resources {
   public:
      Resources();      //default constructor
      Resources(string id, string name, string type, string availability);      //parameterized constructor

      //setters/getters here
      //void display(pass vector) fx
      //void sort(pass vector) fx

   private:
      string rID;
      string rName;
      string rType;
      string rAvailability;

};

#endif