flags=-Wall -lbsd -lc
obj=gcc -c 
out=gcc -o 
name=wish
src=./src/
icd=./include/
build=./build/
target=$(build)$(name)

objs=src/main.o \
	 $(src)shell.o \
	 $(src)file.o \
	 $(src)io.o \
	 $(src)command.o \
	 $(src)parser.o \

all: compile clean

compile: $(objs)
	@[ -d "$(build)" ] || { mkdir "$(build)"; }
	$(out)$(target) $(objs) $(flags)

example%:
	$(target) $@.txt

clean:
	rm $(objs)
