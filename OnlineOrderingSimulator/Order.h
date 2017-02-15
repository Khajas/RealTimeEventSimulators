// The following header is for the entity 'Order'
#include<iostream>
using namespace std;
class Order{
        private:
                string order_id;                // Order id for an order
                string customer_name;           // Name of the customer, the order belongs too
                int days_passed=0;              // days since the order is received
                string status;                  // Status of the order(could be 'Processing', 'Shipped', 'Delivered')
                string courier_assigned;        // Courier assigned, once the order is shipped
                bool delivered_on_time;         // boolean field to know if the order is delivered on time
                string shipping_speed;          // Shipping speed choosen
                int max_age;                    // Max_age(max days within which the order should be delivered, else it will marked as delayed)
                int ship_priority;              // ship priority(0  for same day, 1 for one day, 2 for two day, 3 for three day & 4 for standard delivery)
        public:
                                // Constructors
                Order(){
                        this->order_id="not defined";
                        customer_name="unknown";
                        days_passed=0;
                        status="unknown";
                        courier_assigned="Not Assigned";
                        delivered_on_time=false;
                        shipping_speed="Unknown";
                        max_age=0;
                        ship_priority=-1;
                }
                 Order(string order_id, string customer_name, string shipping_speed, int ship_priority){
                        this->order_id=order_id;
                        this->customer_name=customer_name;
                        this->days_passed=0;
                        this->status="Processing";
                        this->shipping_speed=shipping_speed;
                        this->courier_assigned="Not Assigned";
                        this->delivered_on_time=false;
                        this->max_age=ship_priority*1.25;        // 0->0, 1->1, 2->2, 3->3, 4->5
                        this->ship_priority=ship_priority;
                }
                        // Setters and getters(all getters are const function, so that they can use in Comparator class)
                // Setter and getter for order_id
                void set_order_id(string order_id){
                        if(order_id!="")
                                this->order_id=order_id;
                }
                string get_order_id() const{
                        return this->order_id;
                }
                // Setter and getter for customer_name
                void set_customer_name(string name){
                        if(name!="")
                                this->customer_name=name;
                }
                string get_customer_name() const{
                        return customer_name;
                }
                // Setter and getter for status
                void set_order_status(string status){
                        if(status!="") this->status=status;
                }
                string get_order_status() const{
                        return status;
                }
                // Setter and getter for courier
                void set_courier_assigned(string courier){
                        if(courier!="")
                                this->courier_assigned=courier;
                }
                string get_courier_assigned(){
                        return courier_assigned;
                }
                // Setter and getter for shipping speed
                void set_shipping_speed(string speed){
                        this->shipping_speed=speed;
                }
                string get_shipping_speed() const{
                        return this->shipping_speed;
                }
                 // Setter and getter for max age(post which the order is marked as delayed if undelivered)
                void set_max_age(int m_age){
                        this->max_age=m_age;
                }

                int get_max_age() const{
                        return this->max_age;
                }
                // Setter and getter for ship_priority
                int get_ship_priority() const{
                        return this->ship_priority;
                }
                void set_ship_priority(int p){
                        this->ship_priority=p;
                }
                // Setter and getter for boolean field 'delivered_on_time'
                void set_delivered_on_time(bool t){
                        this->delivered_on_time=t;
                }
                bool get_delivered_on_time(){
                        return this->delivered_on_time;
                }
                        // Other functions
                // Checks if the order needs to be shipped
                bool needs_shipping(){
                        return this->status=="Processing";
                }
                // Checks if the order needs delivery(if it already been shipped)
                bool needs_delivery(){
                        return this->status=="Shipped";
                }
                // Increments the order age by 1
                void increment_age(){
                        ++days_passed;
                }
                // Returns the order age
                int get_order_age() const{
                        return days_passed;
                }
                // You may need this for debugging
                void print_order(){
                        cout<<"Order ID: "<<order_id<<'\n';
                        cout<<"\tCustomer: "<<customer_name<<"\n\tOrder Status: "<<status<<"\n\tShipping Speed: "<<shipping_speed;
                        cout<<endl;
                }
};
///////////////////     END OF SOURCE FILE      ///////////////////////
