#------------------------------------------------------------------------------
# Tool configuration
#------------------------------------------------------------------------------
DEL_FILE                :=  rm -rf
MAKE                    +=  --quiet --no-print-directory
MAKEFLAGS               +=  --quiet --no-print-directory

#------------------------------------------------------------------------------
# Display color macros
#------------------------------------------------------------------------------
BLUE                    :=  \033[1;34m
YELLOW                  :=  \033[1;33m
NORMAL                  :=  \033[0m

SUCCESS                 :=  $(YELLOW)SUCCESS$(NORMAL)

all:
	@cd src && $(MAKE) -f Makefile all

clean:
	@cd src && $(MAKE) -f Makefile clean
	@-$(DEL_FILE) out
	@echo "$(BLUE)[clean]$(NORMAL) Generated files deleted"