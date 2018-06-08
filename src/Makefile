CC		= g++
CFLAGS		= -O2 -Wall
BINDIR		= ../bin
TARGET		= $(BINDIR)/calcnonce-host

SOURCES		= $(wildcard *.cpp)
CSOURCES	= $(wildcard *.c)
SHA256		= ../lib/crypto-algorithms/sha256.c

INCLUDE		= -I../include -I../lib/
OBJDIR		= ../obj
SRCDIR		= ../src
SHADIR		= ../lib/crypto-algorithms/

OBJECTS		= $(addprefix $(OBJDIR)/, $(SOURCES:%.cpp=%.o))
COBJECTS	= $(addprefix $(OBJDIR)/, $(CSOURCES:%.c=%.o))
SHAOBJ		= ../obj/sha256.o

$(TARGET):	$(OBJECTS) $(COBJECTS) $(SHAOBJ)
		@if [ ! -d $(BINDIR) ]; then\
			mkdir $(BINDIR);\
		fi
		$(CC) $(CFLAGS) $(INCLUDE) -o $@ $^

$(OBJECTS):	$(subst $(OBJDIR), $(SRCDIR), $(OBJECTS:%.o=%.cpp))
		@if [ ! -d $(OBJDIR) ]; then\
			mkdir $(OBJDIR);\
		fi
		@[ -d $(OBJDIR) ]
		$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $(subst ../obj, ../src, $(patsubst %.o, %.cpp, $@))

$(COBJECTS):	$(subst $(OBJDIR), $(SRCDIR), $(COBJECTS:%.o=%.c))
		$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $(subst ../obj, ../src, $(patsubst %.o, %.c, $@))

$(SHAOBJ):	$(SHADIR)sha256.c
		$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $^

clean:
		rm -rf $(OBJDIR)/*.o $(TARGET)
