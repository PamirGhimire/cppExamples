/**
 * Your MyCalendarTwo object will be instantiated and called as such:
 * MyCalendarTwo* obj = new MyCalendarTwo();
 * bool param_1 = obj->book(start,end);
 */
/*

You are implementing a program to use as your calendar. We can add a new event if adding the event will not cause a triple booking.

A triple booking happens when three events have some non-empty intersection (i.e., some moment is common to all the three events.).

The event can be represented as a pair of integers start and end that represents a booking on the half-open interval [start, end), the range of real numbers x such that start <= x < end.

Implement the MyCalendarTwo class:

MyCalendarTwo() Initializes the calendar object.
boolean book(int start, int end) Returns true if the event can be added to the calendar successfully without causing a triple booking. Otherwise, return false and do not add the event to the calendar.

Input
["MyCalendarTwo", "book", "book", "book", "book", "book", "book"]
[[], [10, 20], [50, 60], [10, 40], [5, 15], [5, 10], [25, 55]]
Output
[null, true, true, true, false, true, true]

Explanation
MyCalendarTwo myCalendarTwo = new MyCalendarTwo();
myCalendarTwo.book(10, 20); // return True, The event can be booked. 
myCalendarTwo.book(50, 60); // return True, The event can be booked. 
myCalendarTwo.book(10, 40); // return True, The event can be double booked. 
myCalendarTwo.book(5, 15);  // return False, The event ca not be booked, because it would result in a triple booking.
myCalendarTwo.book(5, 10); // return True, The event can be booked, as it does not use time 10 which is already double booked.
myCalendarTwo.book(25, 55); // return True, The event can be booked, as the time in [25, 40) will be double booked with the third event, the time [40, 50) will be single booked, and the time [50, 55) will be double booked with the second event.

*/

class MyCalendarTwo {
private:
    vector<tuple<int, int>> bookings_;
    vector<tuple<int, int>> overlaps_;
    
    bool overlapCheck(const tuple<int, int>& a, const tuple<int, int>& b, bool record=false)
    {
        enum Booking{start=0, end=1};
        bool overlap = false;
        
        int as = std::get<Booking::start>(a);
        int ae = std::get<Booking::end>(a);
    
        int bs = std::get<Booking::start>(b);
        int be = std::get<Booking::end>(b);
    
        
        if(as <= bs)
        {
            if(ae > bs)
            {
                overlap = true;
                if(record){
                    const int overlapStart = bs;
                    const int overlapEnd = std::min(ae, be);
                    overlaps_.emplace_back(std::make_tuple(overlapStart, overlapEnd));
                }                
            }
        }
        else
        {
            if(as < be)
            {
                overlap = true;
                if(record){
                    const int overlapStart = as;
                    const int overlapEnd = std::min(ae, be);
                    overlaps_.emplace_back(std::make_tuple(overlapStart, overlapEnd));
                }
            }
        }
        
        return overlap;
    }
    
    bool IsOverlappingWithExistingOverlaps(const tuple<int, int>& newBooking) 
    {
        for(const auto& existingOverlap : overlaps_)
        {
            if(overlapCheck(newBooking, existingOverlap))
                return true;
        }
        return false;
    }
    
    bool causesTripleBooking(const tuple<int, int>& newBooking) 
    {
        bool overlapsWithExistingOverlaps = IsOverlappingWithExistingOverlaps(newBooking);
        
        if(!overlapsWithExistingOverlaps)
        {
            const bool recordOverlap = true;
            for(const auto& booking : bookings_)
                overlapCheck(newBooking, booking, recordOverlap);
        }
        
        return overlapsWithExistingOverlaps;
    }
    
public:
    MyCalendarTwo() {
        
    }
    
    bool book(int start, int end) {
        tuple<int, int> newBooking{start, end};
        if(causesTripleBooking(newBooking))
            return false;
        
        bookings_.push_back(newBooking);
        return true;
    }
};
