CC       = $(shell printenv CC)
CFLAGS   = -g -O3 -mavx -MMD -MP -Wall
CPPFLAGS = 
LIBS     = 
LDFLAGS  = 
SRCS     = mt19937.c
OBJS     = $(SRCS:%.c=%.o)
DEPS     = $(SRCS:%.c=%.d)
BIN      = a.out

.SUFFIXES: .c .o
.PHONY: clean

.c.o:
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $<

$(BIN): $(OBJS) $(LIBS)
	$(CC) $(LDFLAGS) $(LIBS) $^ -o $@

ALL: $(BIN)

-include $(DEPS)

clean:
	rm -f $(OBJS) $(DEPS) *~ $(BIN)
