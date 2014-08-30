#include"AgendaService.h"
#include<functional>
#include<iostream>
#include"User.h"
#include"Date.h"
#include"Meeting.h"
#include"Storage.h"

AgendaService::AgendaService() {}
AgendaService::~AgendaService() {}
bool AgendaService::userLogIn(std::string userName, std::string password) {
    std::list<User> l;
    l = storage_ -> queryUser([&] (const User& u) {
        if ((userName == u.getName()) && (password == u.getPassword())) {
            return true;
        } else {
              return false;
          }
      });
    if (l.size() > 0) {
        return true;
    } else {
          return false;
      }
}
bool AgendaService::userRegister(std::string userName, std::string password,
                                 std::string email, std::string phone) {
    User u(userName, password, email, phone);
    std::list<User> l;
    l = storage_ -> queryUser([&] (const User& us) {
        if (userName == us.getName()) {
            return true;
        } else {
              return false;
          }
      });
    if (l.size() == 0) {
        int i, count = 0;
        if (password.size() < 6) {
            std::cout << "      您设置的密码长度过短，安全性低，请确认后修改！" << std::endl;
            return false; 
        }
        for (i = 0; i < password.size(); ++i) {
            if (password[i] >= '0' && password[i] <= '9') {
                count++;
                break;
            }
        }
        for (i = 0; i < password.size(); ++i) {
            if (password[i] >= 'a' && password[i] <= 'z') {
                count++;
                break;
            }
        }
        for (i = 0; i < password.size(); ++i) {
            if (password[i] >= 'A' && password[i] <= 'Z') {
                count++;
                break;
            }
        }
        for (i = 0; i < password.size(); ++i) {
            if (!((password[i] >= '0' && password[i] <= '9')
              || (password[i] >= 'a' && password[i] <= 'z')
              || (password[i] >= 'A' && password[i] <= 'Z'))) {
                  count++;
                  break;
              }
        }
        if (count == 1) {
            std::cout << "      您输入的密码形式过于简单，请结合字符，字母大小写，数字进行修改" << std::endl;
            return false;
        }
        if (email.find('@', 0) == -1) {
            std::cout << "      您输入的邮箱信息不合法，请确认后修改！" << std::endl;
            return false;
        }
        if (email.find(".", 0) == -1) {
            std::cout << "      您输入的邮箱信息不合法，请确认后修改！" << std::endl;
            return false;
        }
        for (i = 0; i < phone.size(); ++i) {
            if (!((phone[i] >= '0' && phone[i] <= '9') || phone[i] == '-')) {
                std::cout << "      您输入的电话号码不合法，请确认后修改！" << std::endl;
                return false;
            }
        }
        storage_ -> createUser(u);
        return true;
    } else {
          return false;
      }
}
bool AgendaService::deleteUser(std::string userName, std::string password) {
    if (userLogIn(userName, password)) {
        int count1 = 0;
        int count2 = 0;
        count1 = storage_ -> deleteUser([&] (const User& u) {
             if ((userName == u.getName()) && (password == u.getPassword())) {
                 return true;
             } else {
                   return false;
               }
           });
        count2 = storage_ -> deleteMeeting([&] (const Meeting& m) {
             if ((userName == m.getSponsor()) ||
                 (userName == m.getParticipator())) {
                 return true;
             } else {
                   return false;
               }
           });
        if (count1 == 0) {
            return false;
        } else {
              return true;
          }
    }
    return false;
}
std::list<User> AgendaService::listAllUsers(void) {
    return storage_ -> queryUser([&] (const User& user) { return true; });
}
bool AgendaService::createMeeting(std::string userName, std::string title,
                                  std::string participator,
                                  std::string startDate, std::string endDate) {
    Date start = Date::stringToDate(startDate);
    Date end = Date::stringToDate(endDate);
    std::list<Meeting>::iterator it;
    if (userName == participator) {
        return false;
    }
    if (start >= end || !(Date::isValid(start)) || !(Date::isValid(end))) {
        return false;
    }
    Meeting m(userName, participator, start, end, title);
    std::list<Meeting> l;
    std::list<User> l1;
    l1 = storage_ -> queryUser([&] (const User& u) {
         if (u.getName() == userName || u.getName() == participator) {
             return true;
         } else {
               return false;
           }
       });
    if (l1.size() != 2) {
        return false;
    }
    l = storage_ -> queryMeeting([&] (const Meeting& m) {
        if ((title == m.getTitle()) && (userName == m.getSponsor() ||
            userName == m.getParticipator() || participator == m.getSponsor()
            || participator == m.getParticipator())) {
            return true;
        } else {
              return false;
          }
      });
    if (l.size() > 0) {
        return false;
    } else {
          l = storage_ -> queryMeeting([&] (const Meeting& m) {
              if ((userName == m.getSponsor())
                  || (userName == m.getParticipator())
                  || (participator == m.getSponsor())
                  || (participator == m.getParticipator())) {
                  return true;
              } else {
                    return false;
                }
            });
          if (l.size() > 0) {
              for (it = l.begin(); it != l.end(); ++it) {
                  if ((start >= it->getStartDate() && start < it->getEndDate())
                     || (end > it->getStartDate() && end <= it->getEndDate())
                     || (end >= it->getEndDate()
                     && start <= it->getStartDate())) {
                      return false;
                  }
              }
          }
      }
    storage_ -> createMeeting(m);
    return true;
}
std::list<Meeting> AgendaService::meetingQuery(std::string userName,
                                               std::string title) {
    std::list<Meeting> l;
    l = storage_ -> queryMeeting([&] (const Meeting& m) {
        if (((userName == m.getSponsor()) ||
            (userName == m.getParticipator())) && (title == m.getTitle())) {
            return true;
        } else {
              return false;
          }
      });
    return l;
}
std::list<Meeting> AgendaService::meetingQuery(std::string userName,
                                               std::string startDate,
                                               std::string endDate) {
    std::list<Meeting> l;
    Date start = Date::stringToDate(startDate);
    Date end = Date::stringToDate(endDate);
    l = storage_ -> queryMeeting([&] (const Meeting& m) {
        if (((userName == m.getSponsor()) || (userName == m.getParticipator()))
            && (!(end < m.getStartDate() || start > m.getEndDate())) ) {
            return true;
        } else {
              return false;
          }
      });
    return l;
}
std::list<Meeting> AgendaService::listAllMeetings(std::string userName) {
    std::list<Meeting> l;
    l = storage_ -> queryMeeting([&] (const Meeting& m) {
        if ((userName == m.getSponsor()) || (userName == m.getParticipator())) {
            return true;
        } else {
              return false;
          }
      });
    return l;
}
std::list<Meeting> AgendaService::listAllSponsorMeetings(std::string userName) {
    std::list<Meeting> l;
    l = storage_ -> queryMeeting([&] (const Meeting& m) {
        if (userName == m.getSponsor()) {
            return true;
        } else {
              return false;
          }
      });
    return l;
}
std::list<Meeting> AgendaService::listAllParticipateMeetings(
                                        std::string userName) {
    std::list<Meeting> l;
    l = storage_ -> queryMeeting([&] (const Meeting& m) {
        if (userName == m.getParticipator()) {
            return true;
        } else {
              return false;
          }
      });
    return l;
}
bool AgendaService::deleteMeeting(std::string userName, std::string title) {
    int count = 0;
    count = storage_ -> deleteMeeting([&] (const Meeting& m) {
         if (userName == m.getSponsor() && title == m.getTitle()) {
             return true;
         } else {
               return false;
           }
       });
    if (count > 0) {
        return true;
    } else {
          return false;
      }
}
bool AgendaService::deleteAllMeetings(std::string userName) {
    int count = 0;
    count = storage_ -> deleteMeeting([&] (const Meeting& m) {
        if (userName == m.getSponsor()) {
            return true;
        } else {
              return false;
          }
      });
    if (count > 0) {
        return true;
    } else {
          return false;
      }
}
void AgendaService::startAgenda(void) {
    storage_ = Storage::getInstance();
}
void AgendaService::quitAgenda(void) {
    storage_ -> sync();
    storage_ = NULL;
}

