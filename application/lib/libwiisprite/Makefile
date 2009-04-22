#---------------------------------------------------------------------------------
# Clear the implicit built in rules
#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------
ifeq ($(strip $(DEVKITPPC)),)
$(error "Please set DEVKITPPC in your environment. export DEVKITPPC=<path to>devkitPPC")
endif

include $(DEVKITPPC)/wii_rules

all:
	@echo This is a basic libwiisprite 0.3.0b installer.
	@echo ..which is just a Makefile
	@echo
	@echo If you are running linux:
	@echo Enter this into the command line:
	@echo make linux
	@echo 
	@echo If you are running Windows
	@echo Enter this into the command line:
	@echo make win
	@echo
	@echo This should install libwiisprite ready for you to use.

#---------------------------------------------------------------------------------
linux:
	@echo Installing libwiisprite for Linux...
	@cp libpng/lib/* libwiisprite/lib/* $(LIBOGC_LIB)
	@cp libpng/include/* libwiisprite/include/* $(LIBOGC_INC)
	@echo Done...
	 
#---------------------------------------------------------------------------------
win:
	@echo Installing libwiisprite for Windows...
	@copy libpng\lib\* libwiisprite\lib\* $(LIBOGC_LIB)
	@copy libpng\lib\* libwiisprite\lib\* $(LIBOGC_INC)
	@echo Done...
