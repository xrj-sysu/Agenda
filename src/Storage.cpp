#include<list>
#include<string>
#include<functional>
#include<iostream>
#include<fstream>
#include"Date.h"
#include"User.h"
#include"Storage.h"
using namespace std;
Storage* Storage::instance_ = NULL;
Storage::Storage() {
    userList_.clear();
    meetingList_.clear();
    readFromFile("agenda.data");
}
bool Storage::readFromFile(const char *fpath) {
    string kind;
    string cases;
    string name;
    string password;
    string email;
    string phone;
    string sponsor;
    string participator;
    string sdate;
    string edate;
    string title;
    string c;
    int f, i, j;
    int num;
    ifstream inFile;
    inFile.open(fpath);
    if (!inFile) {
        return false;
    } else {
          getline(inFile, kind);
          f = kind.find_last_of(':', kind.size()-1);
          num = 0;
          for (i = f + 1; kind[i] != '}'; ++i) {
              num = num * 10 + (kind[i] - '0');
          }
          for (i = 0; i < num; ++i) {
              getline(inFile, cases);
              name = ""; password = ""; email = ""; phone = "";
              f = cases.find('"', 0);
              for (j = f + 1; cases[j] != '"'; ++j) {
                  name += cases[j];
              }
              f = cases.find('"', j+1);
              for (j = f + 1; cases[j] != '"'; ++j) {
                  password += cases[j];
              }
              f = cases.find('"', j+1);
              for (j = f + 1; cases[j] != '"'; ++j) {
                  email += cases[j];
              }
              f = cases.find('"', j+1);
              for (j = f + 1; cases[j] != '"'; ++j) {
                  phone += cases[j];
              }
              User u(name, password, email, phone);
              userList_.push_back(u);
          }
          getline(inFile, kind);
          f = kind.find_last_of(':', kind.size()-1);
          num = 0;
          for (i = f + 1; kind[i] != '}'; ++i) {
              num = num * 10 + (kind[i] - '0');
          }
          for (i = 0; i < num; ++i) {
              getline(inFile, cases);
              sponsor = ""; participator = "";
              sdate = ""; edate = ""; title = "";
              f = cases.find('"', 0);
              for (j = f + 1; cases[j] != '"'; ++j) {
                  sponsor += cases[j];
              }
              f = cases.find('"', j+1);
              for (j = f + 1; cases[j] != '"'; ++j) {
                  participator += cases[j];
              }
              f = cases.find('"', j+1);
              for (j = f + 1; cases[j] != '"'; ++j) {
                  sdate += cases[j];
              }
              f = cases.find('"', j+1);
              for (j = f + 1; cases[j] != '"'; ++j) {
                  edate += cases[j];
              }
              f = cases.find('"', j+1);
              for (j = f + 1; cases[j] != '"'; ++j) {
                  title += cases[j];
              }
              Date start = Date::stringToDate(sdate);
              Date end = Date::stringToDate(edate);
              Meeting m(sponsor, participator, start, end, title);
              meetingList_.push_back(m);
          }
      }
    inFile.close();
    return true;
}
bool Storage::writeToFile(const char *fpath) {
    char c = '"';
    ofstream outFile;
    outFile.open(fpath);
    if (!outFile) {
        return false;
    } else {
          outFile << "{collection:" << c << "User" << c <<",total:"
                  << userList_.size() << "}" << endl;
          list<User>::iterator it;
          for (it = userList_.begin(); it != userList_.end(); ++it) {
              outFile << "{name:" << c << it->getName() << c << ",password:"
                      << c << it->getPassword() << c << ",email:" << c
                      << it->getEmail() << c << ",phone:" << c
                      << it->getPhone() << c << "}" << endl;
          }
          outFile << "{collection:" << c << "Meeting" << c << ",total:"
                  << meetingList_.size() << "}" << endl;
          list<Meeting>::iterator iter;
          for (iter = meetingList_.begin(); iter != meetingList_.end();
               ++iter) {
              outFile << "{sponsor:" << c << iter->getSponsor() << c
                      << ",participator:" << c << iter->getParticipator()
                      << c << ",sdate:"<< c
                      << Date::dateToString(iter->getStartDate())
                      << c << ",edate:" << c
                      << Date::dateToString(iter->getEndDate()) << c
                      << ",title:" << c << iter->getTitle() << c << "}" << endl;
          }
      }
    outFile.close();
    return true;
}
Storage* Storage::getInstance(void) {
    if (instance_ == NULL) {
        instance_ = new Storage();
    }
    return instance_;
}
Storage::~Storage() {
    instance_ = NULL;
}
void Storage::createUser(const User& u) {
    userList_.push_back(u);
}
list<User> Storage::queryUser(std::function<bool(const User& u)> filter) {
    list<User> qUser;
    list<User>::iterator it;
    for (it = userList_.begin(); it != userList_.end(); ++it) {
        if (filter(*it)) {
            qUser.push_back(*it);
        }
    }
    return qUser;
}
int Storage::updateUser(std::function<bool(const User& u)> filter,
                        function<void(User& v)> switcher) {
    int count = 0;
    list<User>::iterator it;
    for (it = userList_.begin(); it != userList_.end(); ++it) {
        if (filter(*it)) {
            count++;
            switcher(*it);
        }
    }
    return count;
}
int Storage::deleteUser(std::function<bool(const User& u)> filter) {
    int count = 0;
    list<User>::iterator it;
    for (it = userList_.begin(); it != userList_.end(); ) {
        if (filter(*it)) {
            count++;
            it = userList_.erase(it);
        } else {
              it++;
          }
    }
    return count;
}
void Storage::createMeeting(const Meeting& m) {
    meetingList_.push_back(m);
}
list<Meeting> Storage::queryMeeting(std::function<bool(const Meeting& m)>
                                    filter) {
    list<Meeting> qMeeting;
    list<Meeting>::iterator it;
    for (it = meetingList_.begin(); it != meetingList_.end(); ++it) {
        if (filter(*it)) {
            qMeeting.push_back(*it);
        }
    }
    return qMeeting;
}
int Storage::updateMeeting(std::function<bool(const Meeting& m)> filter,
                           std::function<void(Meeting& n)> switcher) {
    int count = 0;
    list<Meeting>::iterator it;
    for (it = meetingList_.begin(); it != meetingList_.end(); it++) {
        if (filter(*it)) {
            count++;
            switcher(*it);
        }
    }
    return count;
}
int Storage::deleteMeeting(std::function<bool(const Meeting& m)> filter) {
    int count = 0;
    list<Meeting>::iterator it;
    for (it = meetingList_.begin(); it != meetingList_.end(); ) {
        if (filter(*it)) {
            count++;
            it = meetingList_.erase(it);
        } else {
              it++;
          }
    }
    return count;
}
bool Storage::sync(void) {
    return writeToFile("agenda.data");
}

