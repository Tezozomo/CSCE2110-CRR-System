/* store resources
   function definitions

*/

#include"../headers/resources.h"
using namespace std;

//default constructor
Resources::Resources() {
   rID = "";
   rName = "";
   rType = "";
   rAvailability = "";

}
//parameterized constructor
Resources::Resources(string id, string name, string type, string availability) {
   rID = id;
   rName = name;
   rType = type;
   rAvailability = availability;

}
//open sort file
bool Resources::sortFile(const string& resourceFile) {
   ifstream resourceF(resourceFile);
   string line, id, name, type, availability;

   if(!resourceF.is_open()) {
      return false;                                                         //Error: failed to open

   }

   while(getline(resourceF, line)) {                                        //until last line of file
         stringstream ss(line);                                             //one line at a time
         if(getline(ss, id, '|') && getline(ss, name, '|' ) && getline(ss, type, '|') && getline(ss, availability, '|')) {
            resources.emplace_back(id, name, type, availability);           //construct obj in vector //emplace bc raw arguments 

         }
   }

   resourceF.close();                                                       //got what we need close
   return true;                                                             //open success

}
//accessors //get resources data for output
string Resources::getID() {
   return rID;

}
string Resources::getName() {
   return rName;

}
string Resources::getType() {
   return rType;

}
string Resources::getAvailability() {
   return rAvailability;

}