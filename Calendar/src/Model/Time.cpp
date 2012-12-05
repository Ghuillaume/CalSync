///

#include "../../headers/Model/Time.hpp"

// Name space:
using namespace std;

Time::Time ( int minute,
             int hour,
             int day,
             int month,
             int year ) {
    this -> setDate ( minute, hour, day, month, year );
}

Time::~Time() {
    
}

// Comparisons:
bool Time::operator== ( const Time &time ) const { return this -> timestamp == time . timestamp; }
bool Time::operator!= ( const Time &time ) const { return this -> timestamp != time . timestamp; }
bool Time::operator<  ( const Time &time ) const { return this -> timestamp <  time . timestamp; }
bool Time::operator>  ( const Time &time ) const { return this -> timestamp >  time . timestamp; }
bool Time::operator<= ( const Time &time ) const { return this -> timestamp <= time . timestamp; }
bool Time::operator>= ( const Time &time ) const { return this -> timestamp >= time . timestamp; }

Time& Time::operator= ( const Time &time ) {
    this -> timestamp = time.timestamp;
    return *this;
}

// Setters:
void Time::setWeek( const int &week ) {
    int weekDay     = this -> getWeekDay ();
    int currentWeek = this -> getWeek ();
    int i = ( currentWeek - week ) * 7 + weekDay;
    
    struct tm *timestruct = localtime ( &(this -> timestamp) );
    timestruct -> tm_mday -= i;
    this -> timestamp = mktime ( timestruct );
}

void Time::setDate( int minute, int hour, int day, int month, int year ) {
    time_t actualtimestamp;
    time ( &actualtimestamp );
    
    struct tm *actualtimestruct = localtime ( &actualtimestamp );
    
    year	= ( year	== -1 ? actualtimestruct -> tm_year + 1900 : year  );
    month	= ( month	== -1 ? actualtimestruct -> tm_mon  + 1    : month );
    day		= ( day		== -1 ? actualtimestruct -> tm_mday        : day   );
    hour	= ( hour	== -1 ? actualtimestruct -> tm_hour        : hour +1 );
    minute  = ( minute  == -1 ? actualtimestruct -> tm_min      : minute );
	
    struct tm timestruct;
    memset ( &timestruct, 0, sizeof ( struct tm ) );
    timestruct.tm_year = year  - 1900;
    timestruct.tm_mon  = month - 1;
    timestruct.tm_mday = day;
    timestruct.tm_hour = hour - 1;
    timestruct.tm_min  = minute;
    timestruct.tm_sec  = 0;
    
    this -> timestamp = mktime ( &timestruct );
}

void Time::nextDay() {
    struct tm *timestruct = localtime ( &(this -> timestamp) );
    timestruct -> tm_mday++;
    this -> timestamp = mktime ( timestruct );
}

void Time::previousDay()
{
    struct tm *timestruct = localtime ( &(this -> timestamp) );
    timestruct -> tm_mday--;
    this -> timestamp = mktime ( timestruct );
    //cout << "\t\t\tPrevious day : " << this->getDate() << endl;
}

// Getters:

int Time::getMinute() const {
    char minute[3] = { 0 };
    struct tm *timestruct = localtime ( &(this -> timestamp) );
    strftime ( minute, 3, "%M", timestruct );
    return atoi ( minute );
}

int Time::getHour() const {
    char hour[3] = { 0 };
    struct tm *timestruct = localtime ( &(this -> timestamp) );
    strftime ( hour, 3, "%H", timestruct );
    return atoi ( hour );
}

int Time::getDay() const {
    char day[3] = { 0 };
    struct tm *timestruct = localtime ( &(this -> timestamp) );
    strftime ( day, 3, "%d", timestruct );
    return atoi ( day );
}

int Time::getWeekDay() const {
    char weekDay[4] = { 0 };
    struct tm *timestruct = localtime ( &(this -> timestamp) );
    strftime ( weekDay, 4, "%w", timestruct );
    return ( atoi ( weekDay ) + 6 ) % 7;
}

int Time::getWeek() const {
    char week[3] = { 0 };
    struct tm *timestruct = localtime ( &(this -> timestamp) );
    strftime ( week, 3, "%W", timestruct );
    return atoi ( week );
}

int Time::getMonth() const {
    char month[3] = { 0 };
    struct tm *timestruct = localtime ( &(this -> timestamp) );
    strftime ( month, 3, "%m", timestruct );
    return atoi ( month );
}

int Time::getYear() const {
    char year[5] = { 0 };
    struct tm *timestruct = localtime ( &(this -> timestamp) );
    strftime ( year, 5, "%Y", timestruct );
    return atoi ( year );
}


string Time::getSimpleDate() const {
    int day   = this -> getDay   ();
    int month = this -> getMonth ();
    int year  = this -> getYear  ();
    
    stringstream s;
    s << ( ( day < 10 ) ? "0":"" )
      << day
      << "/"
      << ( ( month < 10 ) ? "0":"" )
      << month
      << "/"
      << year;

    string date ( s.str () );
    return date;
}

string Time::getXmlDate() const {
    int minute   = this -> getMinute   ();
    int hour   = this -> getHour   ();
    int day   = this -> getDay   ();
    int month = this -> getMonth ();
    int year  = this -> getYear  ();
    
    stringstream s;
    s << hour 
      << ":"
      << minute 
      << ":"
      << ( ( day < 10 ) ? "0":"" )
      << day
      << "/"
      << ( ( month < 10 ) ? "0":"" )
      << month
      << "/"
      << year;

    string date ( s.str () );
    return date;
}

string Time::getReadableDate() const {
    int minute   = this -> getMinute   ();
    int hour   = this -> getHour   ();
    int day   = this -> getDay   ();
    int month = this -> getMonth ();
    int year  = this -> getYear  ();
    
    stringstream s;
    s << hour 
      << "h"
      << ( ( minute < 10 ) ? "0":"" )
      << minute 
      << " : "
      << ( ( day < 10 ) ? "0":"" )
      << day
      << "/"
      << ( ( month < 10 ) ? "0":"" )
      << month
      << "/"
      << year;

    string date ( s.str () );
    return date;
}

///
