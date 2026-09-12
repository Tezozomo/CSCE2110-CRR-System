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
//accessors //get resources data for output
string Resources::getID() {
   return rID;

}
string ResourcesL::getName() {
   return rName;

}
string Resources::getType() {
   return rType;

}
string rAvailability::getAvailability() {
   return rAvailability;

}