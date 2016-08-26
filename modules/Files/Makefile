##
 # modFiles - An Hermod module to access static files
 #
 # Copyright (c) 2016 Cowlab
 #
 # Hermod is free software: you can redistribute it and/or modify
 # it under the terms of the GNU Lesser General Public License 
 # version 3 as published by the Free Software Foundation. You
 # should have received a copy of the GNU Lesser General Public
 # License along with this program, see LICENSE file for more details.
 # This program is distributed WITHOUT ANY WARRANTY see README file.
 #
 # Authors: Saint-Genest Gwenael <gwen@hooligan0.net>
 #
TARGET=files.so
SRC=modFiles.cpp PageFile.cpp File.cpp Directory.cpp

CC=g++
CP=cp
RM=rm -f

CFLAGS   = -fPIC -I../../src

_COBJ =  $(SRC:.cpp=.o)
COBJ = $(patsubst %, %,$(_COBJ))

all: $(TARGET)
	@echo "  [CP] $(TARGET) => ../$(TARGET)"
	@$(CP) $(TARGET) ..

$(TARGET): $(COBJ)
	@echo "  [LD] $(TARGET)"
	@$(CC) $(CFLAGS) -shared  -Wl,-E,-soname,$@ -o $(TARGET) $(COBJ)

clean:
	$(RM) $(TARGET) *.o *~
	$(RM) -f ../$(TARGET)

$(COBJ) : %.o : %.cpp
	@echo "  [CC] $@"
	@$(CC) $(CFLAGS) -c $< -o $@
