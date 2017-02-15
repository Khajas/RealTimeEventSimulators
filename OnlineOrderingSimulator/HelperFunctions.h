/******************************************
This file contains helper function need for
simplified operations(receiving orders,
shipping, deliveries)
******************************************/
// System headers
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <ctime>
#include <climits>
// User headers

#include "Order.h"
#include "ReadFiles.h"

using namespace std;

                /****** FUNCTIONS BELOW RETURNS RANDOM VALUES ************/

// The following function returns an random number in the given range
int getRandom(int low, int high){
        return rand()%(high+low-1)+low;
}
// The following function returns a randomly generated order id
// Formar: nnnn-nnnn-nnnn
string genOrderID(int low, int high){
        string order_id="";
        for(int i=0;i<3;++i){
                int r=getRandom(low, high);
                order_id+=to_string(r)+"-";
        }
        order_id.erase(order_id.size()-1);
        return order_id;
}
// The following function returns a randomly choosen customer
// from the list of given customers
string forCustomer(const vector<string>& customers){
        int idx=getRandom(0,customers.size()-1);
        return customers.at(idx);
}
// The following function randomly gets a shipping speed
// from the list of available shipping speeds
string getShippingSpeed(const vector<string>& shippingSpeeds){
        int idx=getRandom(0,shippingSpeeds.size()-1);
        return shippingSpeeds.at(idx);
}
// The following function gets a random courier
// from the list of available courier services
string getRandomCourier(const vector<string>& couriers){
        int idx=getRandom(0,couriers.size()-1);
        return couriers.at(idx);
}
// The following function assigns priority
// based on the shipping speed of the order
int getPriority(string speed, const vector<string>& shippingSpeeds){
        auto it=find(shippingSpeeds.begin(), shippingSpeeds.end(),speed);
        if(it!=shippingSpeeds.end()) return it-shippingSpeeds.begin();
        return -1;
}
                /******* Function to update the age for all orders which are not delivered ********/

// The following function updates the age of all orders by one day
void update_order_age(vector<Order>& vecOrders){
        for(unsigned i=0;i<vecOrders.size();++i){
                Order& o=vecOrders[i];
                if(o.get_order_status()!="Delivered")
                        o.increment_age();
        }
}
                /***** THE BELOW FUNCTIONS IS FOR PRINTING *****/

// The following function prints daily report
// i;e no. of  new orders, no. of orders shipped, no. of orders delivered
void print_stats(const int& day, const vector<Order> vecOrders, const int& new_orders, const int& orders_shipped, const int& orders_delivered){
        int delayed_orders=0;
        for(Order o: vecOrders)
                if(o.get_max_age()-o.get_order_age()>0) delayed_orders++;
        cout<<string(50,'*')<<"\nReport\tDay: "<<day<<"\n\tNew orders placed today: "<<new_orders;
        cout<<"\n\tOrders Shipped: "<<orders_shipped<<"\n\tOrders Delivered today: "<<orders_delivered;
        cout<<"\n\tTotal Orders: "<<vecOrders.size()<<endl;
        cout<<string(50,'*')<<endl;
}
// The following function prints the report of the entire simulation
// It gives the number of days, orders received, orders shipped, orders delivered, orders under processing, orders delayed
void print_all_days_report(const int& days, const int& events, const vector<Order>& vecOrders,
        const int& total_orders_delivered, const int& total_orders_shipped){
        cout<<"\n\n\t\t***********\tOverall Report\t\t**********"<<endl;
        cout<<"\tTotal Days:         "<<setw(5)<<days<<"\t\tOperations per Day: \t"<<events<<endl;
        cout<<"\tOrders Received:    "<<setw(5)<<vecOrders.size()<<"\t\tOrders Shipped: \t"<<total_orders_shipped<<endl;
        cout<<"\tOrders Delivered:   "<<setw(5)<<total_orders_delivered<<"\t\tOrders Processing: \t"<<vecOrders.size()-total_orders_shipped;
        int orders_on_time=0;
        for(Order o: vecOrders)
                if(o.get_delivered_on_time()) orders_on_time++;
        cout<<"\n\tDelivered on Time:  "<<setw(5)<<orders_on_time<<"\t\tDelayed Deliveries: "<<setw(5)<<(total_orders_delivered - orders_on_time)<<endl;
        cout<<"\t\t\tTotal Orders Received: "<<vecOrders.size()<<endl;
}
///////////////         END OF SOURCE FILE      /////////////////////
