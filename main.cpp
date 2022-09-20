#include <iostream>
#include <fstream>
#include <deque>
#include <vector>
#include<queue>
#include<algorithm>
// std is a namespace: https://www.cplusplus.com/doc/oldtutorial/namespaces/
const int TIME_ALLOWANCE = 8;  // allow to use up to this number of time slots at once
const int PRINT_LOG = 0; // print detailed execution trace

class Customer
{
public:
    std::string name;
    int priority;
    int arrival_time;
    int slots_remaining; // how many time slots are still needed
    int playing_since;

    Customer(std::string par_name, int par_priority, int par_arrival_time, int par_slots_remaining)
    {
        name = par_name;
        priority = par_priority;
        arrival_time = par_arrival_time;
        slots_remaining = par_slots_remaining;
        playing_since = -1;
    }
};

class Event
{
public:
    int event_time;
    int customer_id;  // each event involes exactly one customer

    Event(int par_event_time, int par_customer_id)
    {
        event_time = par_event_time;
        customer_id = par_customer_id;
    }
};



void initialize_system(
    std::ifstream& in_file, std::deque<Event>& arrival_events0, std::deque<Event>& arrival_events1,std::vector<Customer>& customers)
{
    std::string name;
    int priority, arrival_time, slots_requested;

    
    int customer_id = 0;
    while (in_file >> name >> priority >> arrival_time >> slots_requested)
    {
        Customer customer_from_file(name, priority, arrival_time, slots_requested);
        customers.push_back(customer_from_file);
        Event arrival_event(arrival_time, customer_id);
        if(priority==0){
            arrival_events0.push_back(arrival_event);
        }
        else if (priority == 1) {
            arrival_events1.push_back(arrival_event);
        }
        

       

        customer_id++;
    }
}

void print_state(
    std::ofstream& out_file,
    int current_time,
    int current_id,
    const std::deque<Event>& arrival_events,
    const std::deque<std::pair<int,int>>& customer_queue)
{
    out_file << current_time << " " << current_id << '\n';
    if (PRINT_LOG == 0)
    {
        return;
    }
    std::cout << current_time << ", " << current_id << '\n';
    for (int i = 0; i < arrival_events.size(); i++)
    {
        std::cout << "\t" << arrival_events[i].event_time << ", " << arrival_events[i].customer_id << ", ";
    }
    std::cout << '\n';
    for (int i = 0; i < customer_queue.size(); i++)
    {
        std::cout << "\t" << customer_queue[i].second << ", ";
    }
    std::cout << '\n';
}

bool cmp1(std::pair<int, int>a, std::pair<int, int> b) {
    if (a.first <= b.first) {
        return true;
    }
    else {
        return false;
    }
}
// process command line arguments
// https://www.geeksforgeeks.org/command-line-arguments-in-c-cpp/
int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cerr << "Provide input and output file names." << std::endl;
        return -1;
    }
    std::ifstream in_file(argv[1]);
    std::ofstream out_file(argv[2]);
    if ((!in_file) || (!out_file))
    {
        std::cerr << "Cannot open one of the files." << std::endl;
        return -1;
    }

    // deque: https://www.geeksforgeeks.org/deque-cpp-stl/
    // vector: https://www.geeksforgeeks.org/vector-in-cpp-stl/
    std::deque<Event> arrival_events0; // new customer arrivals
    std::deque<Event> arrival_events1; // new customer arrivals
    std::vector<Customer> customers; // information about each customer

    // read information from file, initialize events queue
    initialize_system(in_file, arrival_events0,arrival_events1,customers);

    int current_id = -1; // who is using the machine now, -1 means nobody
    int time_out = -1; // time when current customer will be preempted
    std::deque<std::pair<int,int>> queue0;
    std::deque<std::pair<int, int>> queue1;
    // step by step simulation of each time slot
    bool all_done = false;
    bool prio = true;
    for (int current_time = 0; !all_done; current_time++)
    {
        // welcome newly arrived customers
        while ((!arrival_events0.empty() || !arrival_events1.empty()) && (current_time == arrival_events0[0].event_time || current_time == arrival_events1[0].event_time)) {
            if (current_time == arrival_events0[0].event_time && current_time == arrival_events1[0].event_time) {
                queue0.push_back(std::pair<int, int>{customers[arrival_events0[0].customer_id].slots_remaining,arrival_events0[0].customer_id});
                sort(queue0.begin(), queue0.end(), cmp1);
                //queue.push_back(arrival_events0.top().event_time);
                arrival_events0.pop_front();
            }
            else if (current_time == arrival_events0[0].event_time && current_time != arrival_events1[0].event_time) {
                queue0.push_back(std::pair<int, int>{customers[arrival_events0[0].customer_id].slots_remaining, arrival_events0[0].customer_id});
                sort(queue0.begin(), queue0.end(), cmp1);
                //queue.push_back(arrival_events0.top().event_time);
                arrival_events0.pop_front();
            }
            else if (current_time != arrival_events0[0].event_time && current_time == arrival_events1[0].event_time) {
                queue1.push_back(std::pair<int, int>{customers[arrival_events1[0].customer_id].slots_remaining, arrival_events1[0].customer_id});
                sort(queue1.begin(), queue1.end(), cmp1);
                //queue.push_back(arrival_events1.top().event_time);
                arrival_events1.pop_front();
            }
        }
        if (current_id == -1) {
            if (!queue0.empty()|| !queue1.empty()) {
                if (!queue0.empty()) {
                    current_id = queue0.front().second;
                    queue0.pop_front();
                    prio = true;
                }
                else {
                    current_id = queue1.front().second;
                    queue1.pop_front();
                    prio = false;
                }
                
                
                if (TIME_ALLOWANCE > customers[current_id].slots_remaining) {
                    time_out = current_time + customers[current_id].slots_remaining;
                }
                else {
                    time_out = current_time + TIME_ALLOWANCE;
                }
                customers[current_id].playing_since = current_time;

            }
        }

        if (current_id >= 0) {
            if (current_time == time_out) {
                int last_run = current_time - customers[current_id].playing_since;
                customers[current_id].slots_remaining -= last_run;
                if (customers[current_id].slots_remaining > 0) {
                    if (prio == true) {
                        queue0.push_front(std::pair<int, int>{customers[current_id].slots_remaining,current_id});
                        sort(queue0.begin(), queue0.end(), cmp1);
                    }
                    else {
                        queue1.push_front(std::pair<int, int>{customers[current_id].slots_remaining, current_id});
                        sort(queue1.begin(), queue1.end(), cmp1);
                    }
                    current_id = -1;
                }
            }
        }

       






        if (prio == true) {
            print_state(out_file, current_time, current_id, arrival_events0, queue0);
        }
        else {
            print_state(out_file, current_time, current_id, arrival_events1, queue1);
        }

        // exit loop when there are no new arrivals, no waiting and no playing customers
        all_done = (arrival_events0.empty()&&arrival_events1.empty() && queue0.empty() &&queue1.empty() && (current_id == -1));
    }

    return 0;
}