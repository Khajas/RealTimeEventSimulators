// This header is to read data(customers, couriers, shipping speeds)
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
// To read customer from customer.txt file
void readCustomerNames(string fileName, vector<string>& vecNames){
        ifstream in_file;
        in_file.open(fileName);
        while(in_file){
                string name;
                getline(in_file, name);
                vecNames.push_back(name);
        }
        in_file.close();
}
// To read couriers from couriers.txt
void readCourierNames(string fileName, vector<string>& couriers){
        ifstream in_file;
        in_file.open(fileName);
        while(in_file){
                string name;
                getline(in_file, name);
                couriers.push_back(name);
        }
        in_file.close();
}
// To read shipping speeds from shipping_speeds.txt
void readShippingSpeeds(string fileName, vector<string>& shippingSpeeds){
        ifstream in_file;
        in_file.open(fileName);
        while(in_file){
                string shipSpeed;
                getline(in_file, shipSpeed);
                shippingSpeeds.push_back(shipSpeed);
        }
        in_file.close();
}
/////////////// END OF SOURCE FILE      /////////////////////////
