INCLUDE_CFLAGS=$(shell pkg-config --cflags gtk+-3.0)
INCLUDE_LIBS  =$(shell pkg-config --libs   gtk+-3.0)

.PHONY: gtk_layout.h gtk_css.h

all: main.o
	@echo "[LINK] all"
	@g++ $(INCLUDE_CFLAGS) main.o $(INCLUDE_LIBS) -rdynamic -o main

main.o: main.cc gtk_layout.h gtk_css.h
	@echo "[ CC ] main.cc"
	@g++ $(INCLUDE_CFLAGS) $(INCLUDE_LIBS) -c main.cc 

gtk_layout.h:
	@echo "[ H  ] gtk_layout.h"
	@xxd -i ui.glade > gtk_layout.h

gtk_css.h:
	@echo "[ H  ] gtk_css.h"
	@xxd -i ui.css > gtk_css.h

clean:
	@echo "Cleaning..."
	@rm *.o
	@rm gtk_layout.h
	@rm gtk_css.h