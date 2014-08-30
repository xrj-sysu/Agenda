#include"AgendaUI.h"
#include<iostream>
#include<iomanip>
#include<string>
#include<list>
#include<vector>
#include<string>
#include"Date.h"
#include"AgendaService.h"
#include"WriteToLog.h"
using namespace std;
AgendaUI::AgendaUI() {
    startAgenda();
    std::cout << "-------------------------------" << " Agenda "
              << "-------------------------------" << std::endl;
    std::cout << "Action :" << std::endl;
    std::cout << "l   - log in Agenda by user name and password" << std::endl;
    std::cout << "r   - register an Agenda account" << std::endl;
    std::cout << "q   - quit Agenda" << std::endl;
    std::cout << std::endl;
}
void AgendaUI::OperationLoop(void) {
    std::string t;
    while (1) {
        std::cout << "Agenda : ~$ ";
        std::cin >> t;
        if (t == "l") {
            userLogIn();
        }
        if (t == "r") {
            userRegister();
        }
        if (t == "q") {
            quitAgenda();
            return;
        } 
        if ((t != "l") && (t != "r") && (t != "q")) {
            continue;
        }
    }
}
void AgendaUI::startAgenda(void) {
    agendaService_.startAgenda();
    string t = "***********Start the Agenda***********";
    WTL.getVector().push_back(t);
}
std::string AgendaUI::getOperation() {}
bool AgendaUI::executeOperation(std::string op) {
    if (op == "dc") {
        deleteUser();
        userLogOut();
    }
    if (op == "lu") {
        listAllUsers();
    }
    if (op == "cm") {
        createMeeting();
    }
    if (op == "la") {
        listAllMeetings();
    }
    if (op == "las") {
        listAllSponsorMeetings();
    }
    if (op == "lap") {
        listAllParticipateMeetings();
    }
    if (op == "qm") {
        queryMeetingByTitle();
    }
    if (op == "qt") {
        queryMeetingByTimeInterval();
    }
    if (op == "dm") {
        deleteMeetingByTitle();
    }
    if (op == "da") {
        deleteAllMeetings();
    }
    if (op == "o") {
        userLogOut();
    }
}
void AgendaUI::userLogIn(void) {
    string tt;
    std::cout << std::endl;
    std::cout << "[log in] [user name] [password]" << std::endl;
    std::cout << "[log in] ";
    std::cin >> userName_ >> userPassword_;
    if (agendaService_.userLogIn(userName_, userPassword_)) {
        std::cout << "[log in] succeed!" << std::endl;
        tt = "[log in] succeed";
        std::cout << std::endl;
        std::cout << "-----------------------" << " Agenda "
                  << "-------------------------------" << std::endl;
        std::cout << "Action :" << std::endl;
        std::cout << "0   - log out Agenda" << std::endl;
        std::cout << "dc  - delete Agenda account" << std::endl;
        std::cout << "lu  - list all Agenda user" << std::endl;
        std::cout << "cm  - create a meeting" << std::endl;
        std::cout << "la  - list all meetings" << std::endl;
        std::cout << "las - list all sponsor meetings" << std::endl;
        std::cout << "lap - list all participate meetings" << std::endl;
        std::cout << "qm  - query meeting by title" << std::endl;
        std::cout << "qt  - query meeting by time interval" << std::endl;
        std::cout << "dm  - delete meeting by title" << std::endl;
        std::cout << "da  - delete all meetings" << std::endl;
        std::cout << "-----------------------------------------------"
                  << "---------------" << std::endl;
        std::cout << std::endl;
        tt = "Agenda@" + userName_ + ": " + tt;
        WTL.getVector().push_back(tt); 
        std::string t;
        while (1) {
            std::cout << "Agenda@" << userName_ << " : # ";
            std::cin >> t;
            executeOperation(t);
            if (t == "o" || t == "dc") {
                return;
            }
        }
    } else {
          std::cout << "[error] log in fail!" << std::endl;
          tt = "[error] log in fail";
          std::cout << std::endl;
      }
    tt = "Agenda@" + userName_ + ": " + tt;
    WTL.getVector().push_back(tt); 
}
void AgendaUI::userRegister(void) {
    bool sign = false;
    std::string t = "*********Register a new user*********";
    WTL.getVector().push_back(t);
    std::cout << std::endl;
    std::cout << "[register] [user name] [password] [email] [phone]"
              << std::endl;
    std::cout << "[register] ";
    std::string name, password, email, phone;
    std::cin >> name >> password >> email >> phone;
    if (agendaService_.userRegister(name, password, email, phone)) {
        std::cout << "[register] succeed!" << std::endl;
        sign = true;
        t = "[register] succeed!";
    } else {
          std::cout << "[error] register fail!" << std::endl;
          t = "[error] register fail!";
      }
    std::cout << std::endl;
    t = "Agenda@" + name + ": " + t;
    WTL.getVector().push_back(t);
    if (sign) {
        t = "Agenda@" + name + ": password: " + password + "  email: "
            + email + "  phone: " + phone;
        WTL.getVector().push_back(t);
    }   
}
void AgendaUI::quitAgenda(void) {
    agendaService_.quitAgenda();
    string t = "*********Quit the agenda*********";
    WTL.getVector().push_back(t);
}
void AgendaUI::userLogOut(void) {
    std::cout << std::endl;
    std::cout << "-----------------------" << " Agenda "
              << "-------------------------------" << std::endl;
    std::cout << "Action :" << std::endl;
    std::cout << "l   - log in Agenda by user name and password" << std::endl;
    std::cout << "r   - register an Agenda account" << std::endl;
    std::cout << "q   - quit Agenda" << std::endl;
    std::cout << "---------------------------------------------------"
              << "-----------";
    std::cout << std::endl;
    userName_ = "";
    userPassword_ = "";
    string t = "Agenda@" + userName_ + ": log out the user";
    WTL.getVector().push_back(t);
}
void AgendaUI::deleteUser(void) {
    std::cout << std::endl;
    if (agendaService_.deleteUser(userName_, userPassword_)) {
        std::cout << "[delete agenda account] succeed!" << std::endl;
    }
    std::cout << std::endl;
    string t = "Agenda@" + userName_ + ": delete the user";
    WTL.getVector().push_back(t);
}
void AgendaUI::listAllUsers(void) {
    std::cout << std::endl;
    std::cout << "[list all users]" << std::endl;
    std::cout << std::endl;
    std::cout << std::left << std::setw(15) << "name"
         << std::left << std::setw(22) << "email"
         << std::left << std::setw(22) << "phone" << std::endl;
    std::list<User> l;
    l = agendaService_.listAllUsers();
    std::list<User>::iterator it;
    for (it = l.begin(); it != l.end(); ++it) {
        std::cout << std::left << std::setw(15) << it->getName()
             << std::left << std::setw(22) << it->getEmail()
             << std::left << std::setw(22) << it->getPhone() << std::endl;
    }
    std::cout << std::endl;
    string t = "Agenda@" + userName_ + ": list all users";
    WTL.getVector().push_back(t);
}
void AgendaUI::createMeeting(void) {
    string t;
    std::cout << std::endl;
    std::cout << "[create meeting] [title] [participator] "
         << "[start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]"
         << std::endl;
    std::string title, participator, start, end;
    std::cin >> title >> participator >> start >> end;
    if (agendaService_.createMeeting(userName_, title,
                                     participator, start, end)) {
        std::cout << "[create meeting] succeed!" << std::endl;
        t = "[create meeting] succeed!";
    } else {
          std::cout << "[error] create meeting fail!" << std::endl;
          t = "[error] create meeting fail!";
      }
   t = "Agenda@" + userName_ + ": " + t;
   WTL.getVector().push_back(t);
   t = "            Meeting's informaition: title: " + title + "  participator: "
       + participator + "  startDate: " + start + "  endDate: " + end;
   WTL.getVector().push_back(t);
}
void AgendaUI::listAllMeetings(void) {
    std::list<Meeting> l;
    l = agendaService_.listAllMeetings(userName_);
    std::cout << std::endl;
    std::cout << "[list all meetings]" << std::endl;
    std::cout << std::endl;
    printMeetings(l);
    string t = "Agenda@" + userName_ + ": list all meetings";
    WTL.getVector().push_back(t);
}
void AgendaUI::listAllSponsorMeetings(void) {
    std::list<Meeting> l;
    l = agendaService_.listAllSponsorMeetings(userName_);
    std::cout << std::endl;
    std::cout << "[list all sponsor meetings]" << std::endl;
    std::cout << std::endl;
    printMeetings(l);
    string t = "Agenda@" + userName_ + ": list all sponsorMeetings";
    WTL.getVector().push_back(t);
}
void AgendaUI::listAllParticipateMeetings(void) {
    std::list<Meeting> l;
    l = agendaService_.listAllParticipateMeetings(userName_);
    std::cout << std::endl;
    std::cout << "[list all participate meetings]" << std::endl;
    std::cout << std::endl;
    printMeetings(l);
    string t = "Agenda@" + userName_ + ": list all ParticipateMeetings";
    WTL.getVector().push_back(t);
}
void AgendaUI::queryMeetingByTitle(void) {
    std::string title;
    std::cout << std::endl;
    std::cout << "[query meeting] [title]:" << std::endl;
    std::cout << "[query meeting] ";
    std::cin >> title;
    std::list<Meeting> l;
    l = agendaService_.meetingQuery(userName_, title);
    std::cout << std::endl;
    printMeetings(l);
    string t = "Agenda@" + userName_ + ": query meetings by the title " + title;
    WTL.getVector().push_back(t);
}
void AgendaUI::queryMeetingByTimeInterval(void) {
    std::string start, end;
    std::cout << std::endl;
    std::cout << "[query meetings] [start time(yyyy-mm-dd/hh:mm)] "
              << "[end time(yyyy-mm-dd/hh:mm)]" << std::endl;
    std::cout << "[query meetings] ";
    std::cin >> start >> end;
    std::cout << "[query meetings]" << std::endl;
    std::list<Meeting> l;
    l = agendaService_.meetingQuery(userName_, start, end);
    printMeetings(l);
    string t = "Agenda@" + userName_ + ": query meetings by the timeInterval ";
    WTL.getVector().push_back(t);
}
void AgendaUI::deleteMeetingByTitle(void) {
    std::string title;
    std::cout << std::endl;
    string t = "Agenda@" + userName_ + ": delete meetings by the title " + title;
    WTL.getVector().push_back(t);
    std::cout << "[delete meeting] [title]" << std::endl;
    std::cout << "[delete meeting] ";
    std::cin >> title;
    std::cout << std::endl;
    if (agendaService_.deleteMeeting(userName_, title)) {
        std::cout << "[delete meeting by title] succeed!" << std::endl;
        t = "[delete meeting by title] succeed!";
    } else {
          std::cout << "[error] delete meeting fail!" << std::endl;
          t = "[error] delete meeting fail!";
      }
    t = "Agenda@" + userName_ + ": " + t;
    WTL.getVector().push_back(t);
}
void AgendaUI::deleteAllMeetings(void) {
    std::cout << std::endl;
    string t;
    if (agendaService_.deleteAllMeetings(userName_)) {
        std::cout << "[delete all meetings] succeeed!" << std::endl;
        t = "[delete all meetings] succeeed!";
    } else {
          std::cout << "[delete all meetings] fail!" << std::endl;
          t = "[delete all meetings] fail!";
      }
    t = "Agenda@" + userName_ + ": " + t;
    WTL.getVector().push_back(t);
}
void AgendaUI::printMeetings(std::list<Meeting> meetings) {
    std::list<Meeting>::iterator it;
    std::cout << std::left << std::setw(12) << "tite"
         << std::left << std::setw(12) << "sponsor"
         << std::left << std::setw(14) << "participator"
         << std::left << std::setw(22) << "start time"
         << std::left << std::setw(22) << "end time" << std::endl;
    for (it = meetings.begin(); it != meetings.end(); ++it) {
        std::cout << std::left << std::setw(12) << it->getTitle()
             << std::left << std::setw(12) << it->getSponsor()
             << std::left << std::setw(14) << it->getParticipator()
             << std::left << std::setw(22)
             << Date::dateToString(it->getStartDate())
             << std::left << std::setw(22)
             << Date::dateToString(it->getEndDate())
             << std::endl;
    }
}

