///

#ifndef _TIME_HPP_
#define _TIME_HPP_

// Includes:
#include <sstream>
#include <cstring> // memset
#include <ctime>
#include <cstdlib>

// Name space:
using namespace std;

// Enumeration for minutes
enum minute_t
{
	notDefined = -1,
	oclock = 0,
	half = 30
};

// Class declaration:
class Time
{
    private:
        time_t timestamp;
    
    public:
       ~Time ();
        Time ( minute_t minute = notDefined, 
			   int hour		   = -1,
               int day         = -1,
               int month	   = -1,
               int year		   = -1 );
		
		//Time::~Time ();
        
        Time& operator=  ( const Time &time );
        bool  operator== ( const Time &time ) const;
        bool  operator!= ( const Time &time ) const;
        bool  operator<  ( const Time &time ) const;
        bool  operator>=  ( const Time &time ) const;
        
        void setWeek  ( const int &week );
        void setDate  ( minute_t minute = notDefined, int hour = -1,
					    int day = -1, int month = -1, int week = -1 );
        void nextDay  ();
        
        int    getMinute	() const;
        int			getHour		() const;
        int			getDay		() const;
        int			getWeek		() const;
        int			getWeekDay	() const;
        int			getMonth	() const;
        int			getYear		() const;
        string		getDate		() const;
};

#endif

///
