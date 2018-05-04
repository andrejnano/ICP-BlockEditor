# ICP Projekt 2018 | BlockEditor
# Authors: Andrej Nano (xnanoa00), Stanislav Mechl (xmechl00)
# Repository: https://github.com/andrejnano/ICP-BlockEditor

CXX = g++
CXXFLAGS = -std=c++14 -stdlib=libc++ -Wall -Weffc++ -O2

EXEC_GUI = blockeditor
EXEC_CLI = blockeditor-cli

# all C++ source files
SOURCES = blocks.cc loader.cc port.cc scheduler.cc scheme.cc utilities.cc

all: $(EXEC_GUI) $(EXEC_CLI) clean

$(EXEC_CLI): $(SOURCES) main-cli.cc
	$(CXX) $(CXXFLAGS) $(SOURCES) main-cli.cc -o ../$(EXEC_CLI)

$(EXEC_GUI):
	qmake gui.pro -o Makefile-gui
	$(MAKE) -f Makefile-gui

clean:
	rm -f *.o moc_mainwindow.cpp moc_predefs.h ui_mainwindow.h blockeditor-cli Makefile-gui .qmake.stash