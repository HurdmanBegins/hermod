##
 # modDatabase - An Hermod module to use DBMS
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
TARGET = database.so
SRC    = modDatabase.cpp DB.cpp

CC = c++
CP = cp
RM = rm -f
CFLAGS   = -fPIC -I../../src
LIBS     = -lodb-pgsql -lodb

_COBJ =  $(SRC:.cpp=.o)
COBJ = $(patsubst %, %,$(_COBJ))

all: $(TARGET)
	@echo "  [CP] $(TARGET) => ../$(TARGET)"
	@$(CP) $(TARGET) ..

$(TARGET): $(COBJ)
	@echo "  [LD] $(TARGET)"
	@$(CC) $(CFLAGS) -shared  -Wl,-E,-soname,$@ -o $(TARGET) $(COBJ) $(LIBS)

clean:
	$(RM) $(TARGET) *.o
	$(RM) ../$(TARGET)
	$(RM) *~

$(COBJ) : %.o : %.cpp
	@echo "  [CC] $@"
	@$(CC) $(CFLAGS) -c $< -o $@
