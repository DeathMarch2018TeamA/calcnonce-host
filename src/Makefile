CC		= g++
CFLAGS		= -O2
BINDIR		= ../bin
TARGET		= $(BINDIR)/calcnonce-host
SOURCES		= $(wildcard *.cpp)
CSOURCES	= $(wildcard *.c)
INCLUDE		= -I../include -I../lib/
OBJDIR		= ../obj
SRCDIR		= ../src
OBJECTS		= $(addprefix $(OBJDIR)/, $(SOURCES:%.cpp=%.o))
COBJECTS	= $(addprefix $(OBJDIR)/, $(CSOURCES:%.c=%.o))

$(TARGET):	$(OBJECTS) $(COBJECTS)
		@if [ ! -d $(BINDIR) ]; then\
			mkdir $(BINDIR);\
		fi
		$(CC) $(CFLAGS) $(INCLUDE) -o $@ $^

$(OBJECTS):	$(subst $(OBJDIR), $(SRCDIR), $(OBJECTS:%.o=%.cpp))
		@if [ ! -d $(OBJDIR) ]; then\
			mkdir $(OBJDIR);\
		fi
		@[ -d $(OBJDIR) ]
		$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

$(COBJECTS):	$(subst $(OBJDIR), $(SRCDIR), $(COBJECTS:%.o=%.c))
		$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<
clean:
		rm -rf $(OBJDIR)/*.o $(TARGET)
