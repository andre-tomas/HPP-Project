CC = gcc
LD = gcc
CFLAGS = -Wall -fopenmp -O0 -std=c99
INCLUDES = 
LDFLAGS =  -fopenmp -O0 -std=c99
RM = rm -f
OBJS = merge.o
EXECUTABLE = merge


$(EXECUTABLE): $(OBJS)
	$(LD) $(OBJS) -o $(EXECUTABLE)  $(LDFLAGS) 

merge.o: merge.c
	$(CC) $(CFLAGS)  $(INCLUDES) -c merge.c 

clean:
	$(RM) $(EXECUTABLE) $(OBJS) gmon.out result.gal spec.txt check.txt timings.txt
