# ICP Projekt 2018 | BlockEditor
# Authors: Andrej Nano (xnanoa00), Stanislav Mechl (xmechl00)
# Last Update: 06.05.2018
# Repository: https://github.com/andrejnano/ICP-BlockEditor


SOURCE_DIR = src
EXECUTABLE_GUI = blockeditor
EXECUTABLE_CLI = blockeditor-cli

all: build

build:
	$(MAKE) -C $(SOURCE_DIR)

run:
	./$(EXECUTABLE_GUI)

run-cli:
	./$(EXECUTABLE_CLI)

doxygen:
	doxygen ./$(SOURCE_DIR)/Doxyfile

clean:
	$(MAKE) clean -C $(SOURCE_DIR)