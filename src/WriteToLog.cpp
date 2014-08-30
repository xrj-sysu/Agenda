#include"WriteToLog.h"
#include<vector>
#include<fstream>
#include<string>
using namespace std;

WriteToLog* WriteToLog::instance_ = NULL;
WriteToLog::~WriteToLog() {
     writeToFile("log.data");
     instance_ = NULL;
}
WriteToLog* WriteToLog::getInstance() {
    if (instance_ = NULL) {
        instance_ = new WriteToLog();
    }
    return instance_;
}
WriteToLog::WriteToLog() {}
vector<string>& WriteToLog::getVector() {
    return vector_;
}
bool WriteToLog::writeToFile(const char* fpath) {
    ofstream outFile;
    outFile.open(fpath, ostream::app);
    if (!outFile) {
        return false;
    } else {
          vector<string>::iterator it;
          for (it = vector_.begin(); it != vector_.end(); ++it) {
              outFile << *it << endl;
              outFile << endl;
          }
          return true;   
      }
}
