Final: User.o Meeting.o Storage.o Date.o AgendaUI.o AgendaService.o WriteToLog.o Agenda.cpp
	g++ -std=c++0x -o Final Agenda.cpp User.o Meeting.o Storage.o Date.o AgendaUI.o AgendaService.o WriteToLog.o
User.o: User.h User.cpp
	g++ -std=c++0x -c User.cpp
Meeting.o: Meeting.h Meeting.cpp
	g++ -std=c++0x -c Meeting.cpp
Storage.o: Storage.h Storage.cpp
	g++ -std=c++0x -c Storage.cpp
Date.o: Date.cpp Date.h
	g++ -std=c++0x -c Date.cpp
AgendaUI.o: AgendaUI.cpp
	g++ -std=c++0x -c AgendaUI.cpp
AgendaService.o: AgendaService.cpp AgendaService.h
	g++ -std=c++0x -c AgendaService.cpp
WriteToLog.o: WriteToLog.cpp WriteToLog.h
	g++ -std=c++0x -c WriteToLog.cpp
clean:
	rm User.o Meeting.o Storage.o Date.o AgendaUI.o AgendaService.o WriteToLog.o Final
