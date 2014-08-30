#ifndef WRITETOLOG_H
#define WRITETOLOG_H

#include"AgendaService.h"
#include<vector>
#include<string>
using namespace std;
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&); \
  void operator=(const TypeName&)
  
class WriteToLog {
    public:
        WriteToLog();
        ~WriteToLog();
        static WriteToLog* getInstance();
        vector<string>& getVector();
    private:
        vector<string> vector_;
        static WriteToLog* instance_;
        bool writeToFile(const char* fpath);
        DISALLOW_COPY_AND_ASSIGN(WriteToLog);
};

#endif
