#
# Simple Makefile that compiles all .c and .s files in the same folder
#

# If you move this project you can change the directory
# to match your GBDK root directory (ex: GBDK_HOME = "C:/GBDK/"
ifndef GBDK_HOME
	GBDK_HOME = ~/gbdk/
endif

LCC = $(GBDK_HOME)bin/lcc
LCCFLAGS = -Wm-yC
PNG2BIN := ./tools/png2bin

# GBDK_DEBUG = ON
ifdef GBDK_DEBUG
	LCCFLAGS += -debug -v
endif

# You can set the name of the .gb ROM file here
PROJECTNAME    = TheMonsterManual

BINS	    = $(PROJECTNAME).gb
CSOURCES   := $(wildcard src/*.c)
ASMSOURCES := $(wildcard src/*.s)

TILEPNG := $(wildcard assets/tiles/*.png)
TILEBIN := $(subst assets/,res/,$(patsubst %.png,%.bin,$(TILEPNG)))

# TILEBIN := $(patsubst asset/%.png,res/%.bin,$(TILEPNG))

all: $(TILEBIN) $(BINS)

res/tiles/%.bin: assets/tiles/%.png
	$(PNG2BIN) $< $@

compile.bat: Makefile
	@echo "REM Automatically generated from Makefile" > compile.bat
	@make -sn | sed y/\\//\\\\/ | sed s/mkdir\ \-p/mkdir/ | grep -v make >> compile.bat

# Compile and link all source files in a single call to LCC
$(BINS):	$(CSOURCES) $(ASMSOURCES)
	$(LCC) $(LCCFLAGS) -o $@ $(CSOURCES) $(ASMSOURCES)

clean:
	rm -f *.o *.lst *.map *.gb *.ihx *.sym *.cdb *.adb *.asm *.noi *.rst
	rm -f res/tiles/*.bin
