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
	 $(src)io_prompt.o \
	 $(src)command.o \
	 $(src)execution.o \
	 $(src)builtin.o \
	 $(src)parser.o \

all: compile clean

compile: $(objs)
	@[ -d "$(build)" ] || { mkdir "$(build)"; }
	$(out)$(target) $(objs) $(flags)

example%:
	$(target) $@.txt

clean:
	rm $(objs)
