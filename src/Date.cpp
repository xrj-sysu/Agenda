#include"Date.h"
#include<string>
#include<sstream>

Date::Date() {}
Date::Date(int y, int m, int d, int h, int mi) {
  year_ = y;
  month_ = m;
  day_ = d;
  hour_ = h;
  minute_ = mi;
}
int Date::getYear(void) const {
  return year_;
}
void Date::setYear(int year) {
  year_ = year;
}
int Date::getMonth(void) const {
  return month_;
}
void Date::setMonth(int month) {
  month_ = month;
}
int Date::getDay(void) const {
  return day_;
}
void Date::setDay(int day) {
  day_ = day;
}
int Date::getHour(void) const {
  return hour_;
}
void Date::setHour(int hour) {
  hour_ = hour;
}
int Date::getMinute(void) const {
  return minute_;
}
void Date::setMinute(int minute) {
  minute_ = minute;
}
bool Date::isValid(Date date) {
  int year = date.getYear();
  int month = date.getMonth();
  int day = date.getDay();
  int hour = date.getHour();
  int minute = date.getMinute();
  bool leap;
  if ((year % 4 == 0 && year % 100 != 0) || (year % 400) == 0) {
    leap = true;
  } else {
      leap = false;
    }
  int kind1[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int kind2[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if (year > 9999 || year < 1000) {
    return false;
  }
  if (month < 1 || month > 12 || day <= 0) {
    return false;
  }
  if (leap) {
      if (kind1[month-1] < day) {
        return false;
      }
  }
  if (!leap) {
      if (kind2[month-1] < day) {
        return false;
      }
  }
  if (hour < 0 || hour > 23) {
    return false;
  }
  if (minute < 0 || minute > 59) {
    return false;
  }
  return true;
}
Date Date::stringToDate(std::string dateString) {
  int year;
  int month;
  int day;
  int hour;
  int minute;
  year = (dateString[0] - '0') * 1000 + (dateString[1] - '0') * 100
         + (dateString[2] - '0') * 10 + dateString[3] - '0';
  month = (dateString[5] - '0') * 10 + dateString[6] - '0';
  day = (dateString[8] - '0') * 10 + dateString[9] - '0';
  hour = (dateString[11] - '0') * 10 + dateString[12] - '0';
  minute = (dateString[14] - '0') * 10 + dateString[15] - '0';
  Date d(year, month, day, hour, minute);
  return d;
}
std::string Date::dateToString(Date date) {
  std::string t;
  std::string year, month, day, hour, minute;
  std::stringstream ss0, ss1, ss2, ss3, ss4;
  ss0 << date.getYear();
  ss0 >> year;
  t = year + "-";
  if (date.getMonth() < 10) {
    t += "0";
  }
  ss1 << date.getMonth();
  ss1 >> month;
  t += month;
  t += "-";
  if (date.getDay() < 10) {
    t += "0";
  }
  ss2 << date.getDay();
  ss2 >> day;
  t += day;
  t += "/";
  if (date.getHour() < 10) {
    t += "0";
  }
  ss3 << date.getHour();
  ss3 >> hour;
  t += hour;
  t += ":";
  if (date.getMinute() < 10) {
    t += "0";
  }
  ss4 << date.getMinute();
  ss4 >> minute;
  t += minute;
  return t;
}
Date& Date::operator=(const Date& date) {
  year_ = date.year_;
  month_ = date.month_;
  day_ = date.day_;
  hour_ = date.hour_;
  minute_ = date.minute_;
  return *this;
}
bool Date::operator==(const Date& date) const {
  if (year_ == date.year_ && month_ == date.month_ && day_ == date.day_
      && hour_ == date.hour_ && minute_ == date.minute_) {
    return true;
  } else {
      return false;
    }
}
bool Date::operator>(const Date& date) const {
  if (year_ > date.year_) {
    return true;
  }
  if (year_ < date.year_) {
    return false;
  }
  if (month_ > date.month_) {
    return true;
  }
  if (month_ < date.month_) {
    return false;
  }
  if (day_ > date.day_) {
    return true;
  }
  if (day_ < date.day_) {
    return false;
  }
  if (hour_ > date.hour_) {
    return true;
  }
  if (hour_ < date.hour_) {
    return false;
  }
  if (minute_ > date.minute_) {
    return true;
  }
  return false;
}
bool Date::operator<(const Date& date) const {
  if (year_ < date.year_) {
    return true;
  }
  if (year_ > date.year_) {
    return false;
  }
  if (month_ < date.month_) {
    return true;
  }
  if (month_ > date.month_) {
    return false;
  }
  if (day_ < date.day_) {
    return true;
  }
  if (day_ > date.day_) {
    return false;
  }
  if (hour_ < date.hour_) {
    return true;
  }
  if (hour_ > date.hour_) {
    return false;
  }
  if (minute_ < date.minute_) {
    return true;
  }
  return false;
}
bool Date::operator>=(const Date& date) const {
  return !((*this) < date);
}
bool Date::operator<=(const Date& date) const {
  return !((*this) > date);
}

