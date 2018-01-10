INCDIR=inc
SRCDIR=src
OBJDIR=obj
BINDIR=bin

TARGET=homesw

SRC=$(wildcard $(SRCDIR)/*.c)
OBJ=$(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

CC=gcc
CFLAGS=-I$(INCDIR) -Wall -O0 -g
LFLAGS=-lm

$(BINDIR)/$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LFLAGS)

all: clean $(BINDIR)/$(TARGET)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -o $@ -c $(CFLAGS) $<

clean:
	rm -v $(OBJDIR)/*.o || echo "No obj files to remove"
