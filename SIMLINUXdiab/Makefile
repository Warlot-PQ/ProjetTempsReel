# Wind River Workbench generated Makefile.
# Do not edit!!!
#
# The file ".wrmakefile" is the template used by the Wind River Workbench to
# generate the makefiles of this project. Add user-specific build targets and
# make rules only(!) in this project's ".wrmakefile" file. These will then be
# automatically dumped into the makefiles.

WIND_HOME := $(subst \,/,$(WIND_HOME))
WIND_BASE := $(subst \,/,$(WIND_BASE))
WIND_USR := $(subst \,/,$(WIND_USR))

all : pre_build main_all post_build

_clean ::
	@echo "make: removing targets and objects of `pwd`"

TRACE=0
TRACEON=$(TRACE:0=@)
TRACE_FLAG=$(TRACEON:1=)

MAKEFILE := Makefile

FLEXIBLE_BUILD := 1

BUILD_SPEC = SIMLINUXdiab
DEBUG_MODE = 1
ifeq ($(DEBUG_MODE),1)
MODE_DIR := Debug
else
MODE_DIR := NonDebug
endif
OBJ_DIR := .
PRJ_ROOT_DIR := /users/elo/jnokaya/ENSSAT2A/TPS\ REEL/WINDRIVER/ProjetTempsReel
WS_ROOT_DIR := /users/elo/jnokaya/ENSSAT2A/TPS\ REEL/WINDRIVER



#Global Build Macros
PROJECT_TYPE = DKM
DEFINES = 
EXPAND_DBG = 0


#BuildSpec specific Build Macros
VX_CPU_FAMILY = simlinux
CPU = SIMLINUX
TOOL_FAMILY = diab
TOOL = diab
TOOL_PATH = 
CC_ARCH_SPEC = -tX86LH:vxworks66
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 

IDE_LIBRARIES = 



#BuildTool flags
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
DEBUGFLAGS_C++-Compiler = -g
DEBUGFLAGS_Linker = -g
DEBUGFLAGS_Partial-Image-Linker = 
DEBUGFLAGS_Librarian = 
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
DEBUGFLAGS_Linker = -XO -Xsize-opt
DEBUGFLAGS_Partial-Image-Linker = 
DEBUGFLAGS_Librarian = 
DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif


#Project Targets
PROJECT_TARGETS = ProjetTempsReel/$(MODE_DIR)/ProjetTempsReel.out \
	 ProjetTempsReel_partialImage/$(MODE_DIR)/ProjetTempsReel_partialImage.o


#Rules

# ProjetTempsReel
ifeq ($(DEBUG_MODE),1)
ProjetTempsReel/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -g
ProjetTempsReel/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -g
ProjetTempsReel/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -g
ProjetTempsReel/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
ProjetTempsReel/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
ProjetTempsReel/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -g
else
ProjetTempsReel/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
ProjetTempsReel/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
ProjetTempsReel/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -XO -Xsize-opt
ProjetTempsReel/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
ProjetTempsReel/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
ProjetTempsReel/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif
ProjetTempsReel/$(MODE_DIR)/% : IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
ProjetTempsReel/$(MODE_DIR)/% : IDE_LIBRARIES = 
ProjetTempsReel/$(MODE_DIR)/% : PROJECT_TYPE = DKM
ProjetTempsReel/$(MODE_DIR)/% : DEFINES = 
ProjetTempsReel/$(MODE_DIR)/% : EXPAND_DBG = 0
ProjetTempsReel/$(MODE_DIR)/% : VX_CPU_FAMILY = simlinux
ProjetTempsReel/$(MODE_DIR)/% : CPU = SIMLINUX
ProjetTempsReel/$(MODE_DIR)/% : TOOL_FAMILY = diab
ProjetTempsReel/$(MODE_DIR)/% : TOOL = diab
ProjetTempsReel/$(MODE_DIR)/% : TOOL_PATH = 
ProjetTempsReel/$(MODE_DIR)/% : CC_ARCH_SPEC = -tX86LH:vxworks66
ProjetTempsReel/$(MODE_DIR)/% : LIBPATH = 
ProjetTempsReel/$(MODE_DIR)/% : LIBS = 
ProjetTempsReel/$(MODE_DIR)/% : OBJ_DIR := ProjetTempsReel/$(MODE_DIR)

OBJECTS_ProjetTempsReel = ProjetTempsReel_partialImage/$(MODE_DIR)/ProjetTempsReel_partialImage.o

ProjetTempsReel/$(MODE_DIR)/ProjetTempsReel.out : $(OBJECTS_ProjetTempsReel)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@";rm -f "$@";ddump -Ng $(OBJECTS_ProjetTempsReel) $(IDE_LIBRARIES) | tclsh $(WIND_BASE)/host/resource/hutils/tcl/munch.tcl -c pentium > $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)dcc $(DEBUGFLAGS_Linker) $(CC_ARCH_SPEC) -Xdollar-in-ident -Xforce-declarations  $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES)  -o $(OBJ_DIR)/ctdt.o -c $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)dld -tX86LH:vxworks66 -X -r5 -f 0x90,1,1 -r4 -o "$@" $(OBJ_DIR)/ctdt.o $(OBJECTS_ProjetTempsReel) $(IDE_LIBRARIES) $(LIBPATH) $(LIBS) $(ADDED_LIBPATH) $(ADDED_LIBS) && if [ "$(EXPAND_DBG)" = "1" ]; then plink "$@";fi

ProjetTempsReel/$(MODE_DIR)/ProjetTempsReel_compile_file : $(FILE) ;

_clean :: ProjetTempsReel/$(MODE_DIR)/ProjetTempsReel_clean

ProjetTempsReel/$(MODE_DIR)/ProjetTempsReel_clean : 
	$(TRACE_FLAG)if [ -d "ProjetTempsReel" ]; then cd "ProjetTempsReel"; rm -rf $(MODE_DIR); fi


# ProjetTempsReel_partialImage
ifeq ($(DEBUG_MODE),1)
ProjetTempsReel_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -g
ProjetTempsReel_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -g
ProjetTempsReel_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -g
ProjetTempsReel_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
ProjetTempsReel_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
ProjetTempsReel_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -g
else
ProjetTempsReel_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
ProjetTempsReel_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
ProjetTempsReel_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -XO -Xsize-opt
ProjetTempsReel_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
ProjetTempsReel_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
ProjetTempsReel_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif
ProjetTempsReel_partialImage/$(MODE_DIR)/% : IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
ProjetTempsReel_partialImage/$(MODE_DIR)/% : IDE_LIBRARIES = 
ProjetTempsReel_partialImage/$(MODE_DIR)/% : PROJECT_TYPE = DKM
ProjetTempsReel_partialImage/$(MODE_DIR)/% : DEFINES = 
ProjetTempsReel_partialImage/$(MODE_DIR)/% : EXPAND_DBG = 0
ProjetTempsReel_partialImage/$(MODE_DIR)/% : VX_CPU_FAMILY = simlinux
ProjetTempsReel_partialImage/$(MODE_DIR)/% : CPU = SIMLINUX
ProjetTempsReel_partialImage/$(MODE_DIR)/% : TOOL_FAMILY = diab
ProjetTempsReel_partialImage/$(MODE_DIR)/% : TOOL = diab
ProjetTempsReel_partialImage/$(MODE_DIR)/% : TOOL_PATH = 
ProjetTempsReel_partialImage/$(MODE_DIR)/% : CC_ARCH_SPEC = -tX86LH:vxworks66
ProjetTempsReel_partialImage/$(MODE_DIR)/% : LIBPATH = 
ProjetTempsReel_partialImage/$(MODE_DIR)/% : LIBS = 
ProjetTempsReel_partialImage/$(MODE_DIR)/% : OBJ_DIR := ProjetTempsReel_partialImage/$(MODE_DIR)

ProjetTempsReel_partialImage/$(MODE_DIR)/Objects/ProjetTempsReel/accesTampons.o : /users/elo/jnokaya/ENSSAT2A/TPS\ REEL/WINDRIVER/ProjetTempsReel/accesTampons.c
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -Xforce-declarations   -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


ProjetTempsReel_partialImage/$(MODE_DIR)/Objects/ProjetTempsReel/main.o : /users/elo/jnokaya/ENSSAT2A/TPS\ REEL/WINDRIVER/ProjetTempsReel/main.c
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -Xforce-declarations   -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


ProjetTempsReel_partialImage/$(MODE_DIR)/Objects/ProjetTempsReel/taches.o : /users/elo/jnokaya/ENSSAT2A/TPS\ REEL/WINDRIVER/ProjetTempsReel/taches.c
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -Xforce-declarations   -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


OBJECTS_ProjetTempsReel_partialImage = ProjetTempsReel_partialImage/$(MODE_DIR)/Objects/ProjetTempsReel/accesTampons.o \
	 ProjetTempsReel_partialImage/$(MODE_DIR)/Objects/ProjetTempsReel/main.o \
	 ProjetTempsReel_partialImage/$(MODE_DIR)/Objects/ProjetTempsReel/taches.o

ProjetTempsReel_partialImage/$(MODE_DIR)/ProjetTempsReel_partialImage.o : $(OBJECTS_ProjetTempsReel_partialImage)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dld -tX86LH:vxworks66 -X -r5 -f 0x90,1,1  -o "$@" $(OBJECTS_ProjetTempsReel_partialImage) $(ADDED_OBJECTS) $(IDE_LIBRARIES) $(LIBPATH) $(LIBS) $(ADDED_LIBPATH) $(ADDED_LIBS) && if [ "$(EXPAND_DBG)" = "1" ]; then plink "$@";fi

ProjetTempsReel_partialImage/$(MODE_DIR)/ProjetTempsReel_partialImage_compile_file : $(FILE) ;

_clean :: ProjetTempsReel_partialImage/$(MODE_DIR)/ProjetTempsReel_partialImage_clean

ProjetTempsReel_partialImage/$(MODE_DIR)/ProjetTempsReel_partialImage_clean : 
	$(TRACE_FLAG)if [ -d "ProjetTempsReel_partialImage" ]; then cd "ProjetTempsReel_partialImage"; rm -rf $(MODE_DIR); fi

DEP_FILES := ProjetTempsReel_partialImage/$(MODE_DIR)/Objects/ProjetTempsReel/accesTampons.d ProjetTempsReel_partialImage/$(MODE_DIR)/Objects/ProjetTempsReel/main.d ProjetTempsReel_partialImage/$(MODE_DIR)/Objects/ProjetTempsReel/taches.d
-include $(DEP_FILES)


WIND_SCOPETOOLS_BASE := $(subst \,/,$(WIND_SCOPETOOLS_BASE))


-include $(PRJ_ROOT_DIR)/*.makefile

-include *.makefile

main_all : external_build $(PROJECT_TARGETS)
	@echo "make: built targets of `pwd`"

# entry point for extending the build
external_build ::
	@echo ""

# main entry point for pre processing prior to the build
pre_build :: $(PRE_BUILD_STEP) generate_sources
	@echo ""

# entry point for generating sources prior to the build
generate_sources ::
	@echo ""

# main entry point for post processing after the build
post_build :: $(POST_BUILD_STEP) deploy_output
	@echo ""

# entry point for deploying output after the build
deploy_output ::
	@echo ""

clean :: external_clean $(CLEAN_STEP) _clean

# entry point for extending the build clean
external_clean ::
	@echo ""
