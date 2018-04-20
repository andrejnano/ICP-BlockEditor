# ICP Projekt 2018 | BlockEditor
# Authors: Andrej Nano (xnanoa00), Stanislav Mechl (xmechl00)
# Repository: https://github.com/andrejnano/ICP-BlockEditor

# @TODO: 'make doxygen'
# @TODO: 'make clean'
# @TODO: 'make pack'


SOURCE_DIR = src
EXECUTABLE = blockeditor

all: build

build:
	$(MAKE) -C $(SOURCE_DIR)
	mv ./src/blockeditor ./blockeditor

run:
	./$(EXECUTABLE)
