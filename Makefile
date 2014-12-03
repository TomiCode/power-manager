CC = gcc
MODULES = gtk+-2.0 libudev
CFLAGS := -g -W -Werror -Wextra $(shell pkg-config --cflags $(MODULES))
LIBS = -lX11 $(shell pkg-config --libs $(MODULES))

SRC = power_manager.c udev_manager.c
OBJS = $(SRC:.c=.o)

define cecho
	@printf "%6s%30s\n" $1 $2
	@tput sgr0
endef

.PHONY: clean distclean

power_manager: $(OBJS)
	$(call cecho,"[CC]",$<)
	@$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIBS)

%.o : %.c
	$(call cecho,"[CC]",$<)
	@$(CC) -c $(CFLAGS) $<

clean:
	$(call cecho,"Cleaning..")
	@rm -f *.o

distclean: clean
	$(call cecho,"Removing application..")
	@rm -f power-manager
