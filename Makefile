PROGNAME = busy-beaver

CC = gcc
LD = gcc

CFLAGS = -g -std=gnu99 -Wall
CFLAGS += -I..

LDFLAGS = -lm

OBJDIR = build

OUT = $(OBJDIR)/$(PROGNAME)

SRCS = bb-main.c


OBJS=$(SRCS:.c=.o)

# -- sanitize, slowndown: 2x!
SANITIZE = no
ifeq ($(strip $(SANITIZE)), yes)
	CFLAGS  += -fsanitize=address
	LDFLAGS += -fsanitize=address
$(info ---------------------------------)
$(info SANITIZE IS ON --> 2x slowdown!  )
$(info ---------------------------------)
endif


all: pre clean $(OUT)

$(OUT): pre $(OBJS)
	$(LD) -o $(OUT) $(addprefix $(OBJDIR)/, $(notdir $(OBJS))) $(LDFLAGS)
	@echo "\n--- BUILD OK"

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $(OBJDIR)/$(notdir $@)


clean:
	rm -rf $(OBJDIR)/*
	@echo "CLEANED"

pre:
	@mkdir -p $(OBJDIR)


run:
	@echo "-- RUNNING..."
	$(OUT)

run-log:
	@echo "-- RUNNING..."
	$(OUT) > log.txt


.PHONY: run pre clean all

