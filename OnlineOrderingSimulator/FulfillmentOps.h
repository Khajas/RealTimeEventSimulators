//              ASSIGNMENT ON HEAP, covers make_heap(), sort()
// User defined header for helper functions
#include "HelperFunctions.h"
/***
        The !dea is to use a heap to prioritize the orders for shipping & deliveries
***/

        /*********      TAKING A NEW ORDER      **************/
//      The following function takes a new order
// To radomize the ordering process, it uses various functions from HelperFunctions.h
//
int take_new_order(vector<Order>& vecOrders, const vector<string>& customers, const vector<string>& shippingSpeeds){
        int orders_placed=0;
        string order_id=genOrderID(1000, 4999);                         // Get a random order id
        string customer_name=forCustomer(customers);                    // Get a random customer
        string ship_speed=getShippingSpeed(shippingSpeeds);             // Get a random shipping speed
        int priority=getPriority(ship_speed, shippingSpeeds);           // Get the priority for the above shipping speed
        cout<<endl;
        Order new_order(order_id, customer_name, ship_speed, priority); // And then take a new order
        new_order.print_order();                                        // print the order which is just received
        vecOrders.push_back(new_order);
        ++orders_placed;                                        // Push it to the vector of orders
        return orders_placed;
}
        /*********      SHIPPING ORDERS BASED ON SHIP PRIORITY & ORDER AGE      *******/
//      Comparator for shipping priority
// An order is prioritize for shipping if it needs_shipping() & based on its shipping speed & age
// priority function f = shipping priority + days since the order is placed
bool sortShip(const Order& a, const Order& b){
        int f1=a.get_ship_priority()+(a.get_max_age()-a.get_order_age());
        int f2=b.get_ship_priority()+(b.get_max_age()-b.get_order_age());
                if(f1==f2) return a.get_ship_priority() > b.get_ship_priority();
        return f1 > f2;
}
//      We first make a heap(based on above comparator), check if an order needs shipping
// We ship the order, mark it as shipped, dispay the details, increase the prioroty
// increment the count and sort the heap.
int ship_orders(vector<Order>& vecOrders, const vector<string>& couriers){
        if(vecOrders.size()==0) return 0;
        int orders_shipped=0;
        make_heap(vecOrders.begin(), vecOrders.end(), sortShip);                                // make a heap
        for(int count=0; count< 10; ++count){                                                   // Let's make 10 tries(because some orders might have been shipped)
                Order& o=vecOrders.front();                                                     // Get the front
                if(o.needs_shipping()){                                                         // Check if it needs shipping
                        o.set_courier_assigned(getRandomCourier(couriers));                     // Get a random courier, and assign it to the order
                        o.set_order_status("Shipped");                                          // If so change the status as 'shipped'
                        cout<<string(50,'#')<<"\n\tOrder Shipped To: "                          // Display the details
                                <<o.get_customer_name()<<"\n\tOrder_ID: "<<o.get_order_id()
                                <<"\n\tCourier: "<<o.get_courier_assigned()
                                <<"\n\tShipping Speed: "<<o.get_shipping_speed()
                                <<endl<<string(50,'#')<<endl;
                        ++orders_shipped;                                                       // Increment the count
                        o.set_ship_priority(INT_MAX);                                           // Increment the priority
                        pop_heap(vecOrders.begin(), vecOrders.end(), sortShip);                 // pop the element with least priority
                }
                sort_heap(vecOrders.begin(), vecOrders.end(), sortShip);                        // Sort the heap to reflect the changes after shipping the current order
        }
        return orders_shipped;                                                                  // Return the count
}
        /*********      DELIVERING ORDERS BASED ON SHIP PRIORITY & ORDER AGE      *******/
//      Comparator for deliveries priority
// An order is prioritize for delivery if needs_delivery() & based on its age
// priority function f = days since the order is shipped
// We may not use ship priority here since we're increasing the ship_priority after shipping it
bool sortDelivery(const Order& a, const Order& b){
        int delay1=a.get_max_age()-a.get_order_age();
        int delay2=b.get_max_age()-b.get_order_age();
        return delay1 > delay2;
}
//      We first make a heap(based on above comparator), check if an order needs delivery
// We deliver the order, mark it as delivered, dispay the details & duration(early, ontime, delayed),
// increase the max age, increment the count and sort the heap.
int deliver_orders(vector<Order>& vecOrders){
        if(vecOrders.size()==0) return 0;
        int orders_delivered=0;
        make_heap(vecOrders.begin(), vecOrders.end(),sortDelivery);                             // make a heap
        for(int count=0;count < 10 ; ++count){                                                  // Let's make 10 tries(because more than one order might need delivery)
                Order& o=vecOrders.front();                                                     // Get the front
                if(o.needs_delivery()){                                                         // Check if it needs to be delivered
                        o.set_order_status("Delivered");                                        // If so change the status as 'Delivered'
                        if(o.get_max_age() >= o.get_order_age()){                               // Check if it's delivered on time & set the delivered_on_time field of order entity
                                o.set_delivered_on_time(true);
                        }
                        cout<<string(50,'+')<<"\nOrder Delivered: "<<o.get_order_id()           // Display the details
                                <<"\n\tDelivered by: "<<o.get_courier_assigned()
                                <<"\n\tShipping Speed: "<<o.get_shipping_speed()<<endl;
                        if(o.get_delivered_on_time()){                                          // Display if it's delivered on time or early or delayed
                                if(o.get_order_age()==o.get_max_age())
                                        cout<<"\tDelivered on time!"<<endl;
                                else  cout<<"\tDelivered before time, "
                                        <<o.get_max_age()-o.get_order_age()<<" day(s) early!"<<endl;
                        } else{
                                cout<<"\tDelivered late by: "
                                        <<o.get_order_age()-o.get_max_age()<<" day(s)."<<endl;
                        }
                        cout<<"\tSigned by: "<<o.get_customer_name()<<endl;                     // Show the recepient
                        o.set_max_age(INT_MAX);                                                 // Increment the priority
                        pop_heap(vecOrders.begin(), vecOrders.end(), sortDelivery);             // pop the element with least priority
                        cout<<string(50,'+')<<endl;
                        ++orders_delivered;                                                     // Increment the count
                }
                sort_heap(vecOrders.begin(), vecOrders.end(), sortDelivery);                    // Sort the heap to reflect the changes after shipping the current order
        }
        return orders_delivered;                                                                // Return the count
}
/////////////////////////////////////     END OF SOURCE FILE      /////////////////////////////
