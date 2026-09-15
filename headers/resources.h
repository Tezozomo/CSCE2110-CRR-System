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
      string getID() const;
      string getName() const;
      string getType() const;
      string getAvailability() const;
      string getAvailability(const string& id) const;

      //resource manage part
      void displayResources();                        //print list
      bool sortFile(const string& resourceFile);
      int findIndex(const string& id) const;
      bool setAvailability(const string& id, const string& availability);
      bool displayResource(const string& id) const;
      void sortResources(const string& criterion);

   private:
      friend class ReservationManager;
      string rID;
      string rName;
      string rType;
      string rAvailability;
      vector<Resources> resources;     //store resources.txt

};

#endif