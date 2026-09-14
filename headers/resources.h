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

      //accessors
      string getID();
      string getName();
      string getType();
      string getAvailability();

      //resource manage part
      void displayResources();                        //print list
      bool sortFile(const string& resourceFile);      //pass file by reference

   private:
      string rID;
      string rName;
      string rType;
      string rAvailability;
      vector<Resources> resources;     //store resources.txt

};

#endif