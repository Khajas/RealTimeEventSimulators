#include "FulfillmentOps.h"
int main(){
        srand(1);
        vector<Order> vecOrders;
        vector<string> vecCustomerNames;
        vector<string> couriers;
        vector<string> shippingSpeeds;
        readCustomerNames("./files/customer_names.txt", vecCustomerNames);      // Replace this with link from prof's directory
        readCourierNames("./files/couriers.txt", couriers);
        readShippingSpeeds("./files/shipping_speeds.txt", shippingSpeeds);
        int days=10; int events=10;
        int total_orders_received=0, total_orders_delivered=0, total_orders_shipped=0;
        cout<<"**** ONLINE ORDERING SIMULATION ****"<<endl<<endl;
        for(int d=0; d<days; ++d){
                cout<<"\nDAY: "<<d+1<<endl<<endl;
                int new_orders=0, orders_delivered=0, orders_shipped=0;
                update_order_age(vecOrders);
                for(int e=0; e<events; ++e){
                        // New order could arrive or orders should be shipped or orders should be delivered
                        //cout<<r<<endl;
                        int r=getRandom(1,events);
                        if(r>=1 and r<((int)events*0.3)){
                                cout<<"\n*New* Order Received!";
                                new_orders+=take_new_order(vecOrders, vecCustomerNames, shippingSpeeds);
                        }
                        else if(r>=((int)events*0.3) and r <((int)events*0.6)){
                                // ship some orders
                                orders_shipped+=ship_orders(vecOrders, couriers);
                        }
                        else{
                                // deliver some orders
                                orders_delivered+=deliver_orders(vecOrders);
                        }
                }
                print_stats(d+1, vecOrders, new_orders, orders_shipped, orders_delivered);
                total_orders_received+=new_orders;
                total_orders_delivered+=orders_shipped;
                total_orders_shipped+=orders_delivered;
                cout<<"Press Enter to continue..."<<endl;
                cin.get();
        }
        print_all_days_report(days, events,vecOrders,total_orders_delivered, total_orders_shipped);
        cout<<"\t\t**********\tEND OF SIMULATION\t***********"<<endl<<endl;
        return 0;
}
