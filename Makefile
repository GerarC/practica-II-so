flags=-Wall -lbsd
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
	 $(src)prompt.o \
	 $(src)tokenizer.o \

all: compile clean

compile: $(objs)
	@[ -d "$(build)" ] || { mkdir "$(build)"; }
	$(out)$(target) $(objs) $(flags)

%.o: $(src)%.c $(icd)%.h
	$(obj)$(src)%.c

example%:
	$(target) $@.txt

clean:
	rm $(objs)
