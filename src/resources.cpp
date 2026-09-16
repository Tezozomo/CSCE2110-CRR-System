#include "../headers/resources.h"
using namespace std;

// create empty resource
Resources::Resources() {
   rID = "";
   rName = "";
   rType = "";
   rAvailability = "";

}
// create resource entry
Resources::Resources(string id, string name, string type, string availability) {
   rID = id;
   rName = name;
   rType = type;
   rAvailability = availability;

}
// load resource file
bool Resources::sortFile(const string& resourceFile) {
   ifstream resourceF(resourceFile);
   string line, id, name, type, availability;

   if(!resourceF.is_open()) {                                               
      return false;

   }

   while(getline(resourceF, line)) {
         stringstream ss(line);
         if(getline(ss, id, '|') && getline(ss, name, '|' ) && getline(ss, type, '|') && getline(ss, availability, '|')) {
            resources.emplace_back(id, name, type, availability);

         }
   }

   resourceF.close();
   return true;

}
// access resource id
string Resources::getID() const {
   return rID;

}
string Resources::getName() const {
   return rName;

}
string Resources::getType() const {
   return rType;

}
string Resources::getAvailability() const {
   return rAvailability;

}
string Resources::getAvailability(const string& id) const {
   int index = findIndex(id);
   return index < 0 ? "" : resources[index].getAvailability();
}
// display all resources
void Resources::displayResources() {
   cout << left << setw(8) << "ID" << setw(24) << "Name" << setw(24)
        << "Type" << "Availability\n";
   cout << string(75, '-') << '\n';
   for(const Resources& resource : resources) {
      cout << left << setw(8) << resource.getID() << setw(24) << resource.getName()
           << setw(24) << resource.getType() << resource.getAvailability() << '\n';
}
   }

// find resource index
int Resources::findIndex(const string& id) const {
   for(size_t i = 0; i < resources.size(); ++i) {
      if(resources[i].getID() == id) return static_cast<int>(i);
   }
   return -1;
}

// update resource status
bool Resources::setAvailability(const string& id, const string& availability) {
   int index = findIndex(id);
   if(index < 0) return false;
   resources[index].rAvailability = availability;
   return true;
}

// display one resource
bool Resources::displayResource(const string& id) const {
   int index = findIndex(id);
   if(index < 0) return false;
   cout << left << setw(8) << "ID" << setw(24) << "Name" << setw(24)
        << "Type" << "Availability\n";
   cout << left << setw(8) << resources[index].getID() << setw(24)
        << resources[index].getName() << setw(24) << resources[index].getType()
        << resources[index].getAvailability() << '\n';
   return true;
}

// sort resource list
void Resources::sortResources(const string& criterion) {
   vector<Resources> sorted = resources;
   auto compare = [&criterion](const Resources& left, const Resources& right) {
      if(criterion == "name") return left.getName() < right.getName();
      if(criterion == "type") return left.getType() < right.getType();
      return left.getID() < right.getID();
   };
   for(size_t width = 1; width < sorted.size(); width *= 2) {
      for(size_t begin = 0; begin < sorted.size(); begin += 2 * width) {
         size_t middle = min(begin + width, sorted.size());
         size_t end = min(begin + 2 * width, sorted.size());
         vector<Resources> merged;
         size_t left = begin, right = middle;
         while(left < middle && right < end)
            merged.push_back(compare(sorted[left], sorted[right]) ? sorted[left++] : sorted[right++]);
         while(left < middle) merged.push_back(sorted[left++]);
         while(right < end) merged.push_back(sorted[right++]);
         copy(merged.begin(), merged.end(), sorted.begin() + begin);
      }
   }
   resources = sorted;
}
