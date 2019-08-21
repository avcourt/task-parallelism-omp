CC=gcc
OFLAGS=-O3 -g
WFLAGS=-Wall -Werror
LDFLAGS=-lm
CFLAGS=$(OFLAGS) $(WFLAGS)
OMPFLAGS=-fopenmp

SRC :=	quick_serial.c \
	merge_serial.c \
	quick_tasks.c \
	merge_tasks.c \
	quick_sect.c \
	quick_sect_d.c \
	merge_sect.c \
	merge_tasks_unnested.c

ALL :=  $(foreach src,$(SRC),$(subst .c,,$(src)))

default: $(ALL)

tags: $(SRC)
	ctags $^

quick_serial: quick_serial.c
	$(CC) $(CFLAGS) $(OMPFLAGS) $^ -o $@ $(LDFLAGS)

merge_serial: merge_serial.c get_time.o
	$(CC) $(CFLAGS) $(OMPFLAGS) $^ -o $@ $(LDFLAGS)

quick_tasks: quick_tasks.c
	$(CC) $(CFLAGS) $(OMPFLAGS) $^ -o $@ $(LDFLAGS)

merge_tasks: merge_tasks.c
	$(CC) $(CFLAGS) $(OMPFLAGS) $^ -o $@ $(LDFLAGS)

quick_sect: quick_sect.c
	$(CC) $(CFLAGS) $(OMPFLAGS) $^ -o $@ $(LDFLAGS)

quick_sect_d: quick_sect_d.c
	$(CC) $(CFLAGS) $(OMPFLAGS) $^ -o $@ $(LDFLAGS)

merge_sect: merge_sect.c
	$(CC) $(CFLAGS) $(OMPFLAGS) $^ -o $@ $(LDFLAGS)

merge_tasks_unnested: merge_tasks_unnested.c
	$(CC) $(CFLAGS) $(OMPFLAGS) $^ -o $@ $(LDFLAGS)


clean:
	@- rm -f get_time.o
	@- rm -f $(ALL) tags
