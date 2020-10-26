## CONFIGURATION #############################################################

OUTPUT	= HarshLoader
CPU		= cortex-m3
MCU		= STM32F103C8T6
OPT		= 2
LD_CMD	= harshloader.ld

## TOOLS #####################################################################

AS = @arm-none-eabi-as
CC = @arm-none-eabi-gcc
LD = @arm-none-eabi-ld
OC = @arm-none-eabi-objcopy

RM = @rm -f
RD = @rm -rf
MD = @mkdir -p

#wildcard for recursively searching directories
rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

## PATHS #####################################################################

PRJDIR 	= .
GCCDIR 	= gcc
SRCDIR 	= Src
DEVDIR	= Device
OBJDIR 	= Objects
LSTDIR 	= Listings

DIRS	:= $(SRCDIR)
DIRS	+= $(DEVDIR)

## FILES #####################################################################

ELF		= $(OBJDIR)/$(OUTPUT).elf
HEX		= $(OBJDIR)/$(OUTPUT).hex
BIN		= $(OBJDIR)/$(OUTPUT).bin
MAP		= $(LSTDIR)/$(OUTPUT).map

#call wildcard to recursively search DIRS for *.s and *.c files
SRCS	:= $(call rwildcard,$(DIRS),*.s)
SRCS	+= $(call rwildcard,$(DIRS),*.c)
#Filter out files so that only .s and .c files remain
SRCS	:= $(filter %.s %.c,$(SRCS))

OBJS	:= $(notdir $(SRCS))
#Replace suffix in variable
#$(var:suffix=replacement)
OBJS	:= $(OBJS:.s=.o)
OBJS	:= $(OBJS:.c=.o)
#$(patsubst %suffix,%replacement,$(var))
#so we are just adding the $(OBJDIR)/ to all items in OBJS
OBJS	:= $(patsubst %, $(OBJDIR)/%, $(OBJS))

#Remove dir prefixes from SRCS files
ASMS	:= $(notdir $(SRCS))
#$(var:suffix=replacement)
#so we are creating list of .asm files from .c files
ASMS	:= $(ASMS:.c=.asm)
ASMS	:= $(patsubst %, %(LSTDIR)/%, $(ASMS))

ALLDIRS	:= $(sort $(dir $(SRCS)))

#$(patsubst %suffix,%replacement,$(var))
#so appending -I$(PRJDIR)/ -I "directory" to everything
INCS	:= $(patsubst %, -I$(PRJDIR)/ -I "%", $(ALLDIRS))

VPATH := $(ALLDIRS)


## OPTIONS ###################################################################

FLAGS   = -mcpu=$(CPU) 
FLAGS  += -g 
FLAGS  += $(INCS) 

# assembler flags
AFLAGS  = $(FLAGS) 

# c compiler flags
CFLAGS := --specs=nosys.specs 
CFLAGS += -fno-exceptions
CFLAGS += -nostdlib 
CFLAGS += $(FLAGS) 
CFLAGS += -std=gnu99 
CFLAGS += -D$(MCU) 
CFLAGS += -O$(OPT) 
CFLAGS += -DSTM32F10X_MD 
CFLAGS += -mthumb
#CFLAGS +=  -split_sections 

# linker flags
LFLAGS := -lc -lnosys
LFLAGS += -nostartfiles
#LFLAGS  = --strict 
#LFLAGS += --summary_stderr 
#LFLAGS += --info summarysizes 
#LFLAGS += --map 
#LFLAGS += --xref 
#LFLAGS += --callgraph 
#LFLAGS += --symbols 
#LFLAGS += --info sizes 
#LFLAGS += --info totals 
#LFLAGS += --info unused 
#LFLAGS += --info veneers 

## TARGETS ###################################################################

.PHONY: all build rebuild bin reflash flash dirs cleanall clean pre_build pre_compile

all: build

rebuild: cleanall build

build: pre_build $(ELF) $(BIN) $(HEX)
	@echo "[DONE]"

reflash: cleanall build flash

flash: $(BIN)
	@echo "	[flash]"
	JLinkExe -Device "STM32F103C8" -AutoConnect 1 -If SWD \
	-CommandFile flash.jlink

bin:
	$(OC) -O binary $(ELF) $(BIN)

# output to console
pre_build:
	@echo "[Building $(ELF)]"

pre_compile: dirs
	@echo "[Compiling]"

# link object files to create .elf

$(HEX): $(ELF)
	$(OC) -O ihex $(ELF) $(HEX)

$(BIN): $(ELF)
	@echo "	$(ELF) -> $(BIN)"
	$(OC) -O binary $(ELF) $(BIN)

$(ELF): $(OBJS)
	@echo "[Linking]"
	@echo "	$(OBJS)"
	$(CC) -mcpu=$(CPU) $(CFLAGS) -T $(LD_CMD) \
	-o $(ELF) $(OBJS)

# compile source files

$(OBJDIR)/%.o: %.c | pre_compile
	@echo "	$< -> $@"
	$(CC) -c $(CFLAGS) \
	-o $@ $<

$(OBJDIR)/%.o: %.s | pre_compile
	@echo "	$< -> $@"
	$(AS) $(AFLAGS) \
	-o $@ $<

# debug output

$(LSTDIR)/%.asm: $(OBJDIR)/%.o
	@echo "  $< -> $@"
	$(OD) -c --output $@ $<

# create folders

dirs: $(OBJDIR) $(LSTDIR)

$(OBJDIR):
	-@$(MD) $(OBJDIR)

$(LSTDIR):
	-@$(MD) $(LSTDIR)

# delete files and folders

cleanall: clean
	@echo "	$(OBJDIR)"
	@echo "	$(LSTDIR)"
	$(RD) $(OBJDIR)
	$(RD) $(LSTDIR)

clean:
	@echo "[clean]"
	@echo "	$(OBJDIR)/*.o"
	$(RM) $(OBJDIR)/*.o
