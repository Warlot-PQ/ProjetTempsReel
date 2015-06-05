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
PRJ_ROOT_DIR := /users/elo/pwarlot/Documents/temps_reel/workspace/Temps_reel_Nokaya_Warlot_projet
WS_ROOT_DIR := /users/elo/pwarlot/Documents/temps_reel/workspace



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
PROJECT_TARGETS = Temps_reel_Nokaya_Warlot_projet/$(MODE_DIR)/Temps_reel_Nokaya_Warlot_projet.out \
	 Temps_reel_Nokaya_Warlot_projet_partialImage/$(MODE_DIR)/Temps_reel_Nokaya_Warlot_projet_partialImage.o


#Rules

# Temps_reel_Nokaya_Warlot_projet
ifeq ($(DEBUG_MODE),1)
Temps_reel_Nokaya_Warlot_projet/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -g
Temps_reel_Nokaya_Warlot_projet/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -g
Temps_reel_Nokaya_Warlot_projet/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -g
Temps_reel_Nokaya_Warlot_projet/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
Temps_reel_Nokaya_Warlot_projet/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
Temps_reel_Nokaya_Warlot_projet/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -g
else
Temps_reel_Nokaya_Warlot_projet/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
Temps_reel_Nokaya_Warlot_projet/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
Temps_reel_Nokaya_Warlot_projet/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -XO -Xsize-opt
Temps_reel_Nokaya_Warlot_projet/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
Temps_reel_Nokaya_Warlot_projet/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
Temps_reel_Nokaya_Warlot_projet/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif
Temps_reel_Nokaya_Warlot_projet/$(MODE_DIR)/% : IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
Temps_reel_Nokaya_Warlot_projet/$(MODE_DIR)/% : IDE_LIBRARIES = 
Temps_reel_Nokaya_Warlot_projet/$(MODE_DIR)/% : PROJECT_TYPE = DKM
Temps_reel_Nokaya_Warlot_projet/$(MODE_DIR)/% : DEFINES = 
Temps_reel_Nokaya_Warlot_projet/$(MODE_DIR)/% : EXPAND_DBG = 0
Temps_reel_Nokaya_Warlot_projet/$(MODE_DIR)/% : VX_CPU_FAMILY = simlinux
Temps_reel_Nokaya_Warlot_projet/$(MODE_DIR)/% : CPU = SIMLINUX
Temps_reel_Nokaya_Warlot_projet/$(MODE_DIR)/% : TOOL_FAMILY = diab
Temps_reel_Nokaya_Warlot_projet/$(MODE_DIR)/% : TOOL = diab
Temps_reel_Nokaya_Warlot_projet/$(MODE_DIR)/% : TOOL_PATH = 
Temps_reel_Nokaya_Warlot_projet/$(MODE_DIR)/% : CC_ARCH_SPEC = -tX86LH:vxworks66
Temps_reel_Nokaya_Warlot_projet/$(MODE_DIR)/% : LIBPATH = 
Temps_reel_Nokaya_Warlot_projet/$(MODE_DIR)/% : LIBS = 
Temps_reel_Nokaya_Warlot_projet/$(MODE_DIR)/% : OBJ_DIR := Temps_reel_Nokaya_Warlot_projet/$(MODE_DIR)

OBJECTS_Temps_reel_Nokaya_Warlot_projet = Temps_reel_Nokaya_Warlot_projet_partialImage/$(MODE_DIR)/Temps_reel_Nokaya_Warlot_projet_partialImage.o

Temps_reel_Nokaya_Warlot_projet/$(MODE_DIR)/Temps_reel_Nokaya_Warlot_projet.out : $(OBJECTS_Temps_reel_Nokaya_Warlot_projet)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@";rm -f "$@";ddump -Ng $(OBJECTS_Temps_reel_Nokaya_Warlot_projet) $(IDE_LIBRARIES) | tclsh $(WIND_BASE)/host/resource/hutils/tcl/munch.tcl -c pentium > $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)dcc $(DEBUGFLAGS_Linker) $(CC_ARCH_SPEC) -Xdollar-in-ident -Xforce-declarations  $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES)  -o $(OBJ_DIR)/ctdt.o -c $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)dld -tX86LH:vxworks66 -X -r5 -f 0x90,1,1 -r4 -o "$@" $(OBJ_DIR)/ctdt.o $(OBJECTS_Temps_reel_Nokaya_Warlot_projet) $(IDE_LIBRARIES) $(LIBPATH) $(LIBS) $(ADDED_LIBPATH) $(ADDED_LIBS) && if [ "$(EXPAND_DBG)" = "1" ]; then plink "$@";fi

Temps_reel_Nokaya_Warlot_projet/$(MODE_DIR)/Temps_reel_Nokaya_Warlot_projet_compile_file : $(FILE) ;

_clean :: Temps_reel_Nokaya_Warlot_projet/$(MODE_DIR)/Temps_reel_Nokaya_Warlot_projet_clean

Temps_reel_Nokaya_Warlot_projet/$(MODE_DIR)/Temps_reel_Nokaya_Warlot_projet_clean : 
	$(TRACE_FLAG)if [ -d "Temps_reel_Nokaya_Warlot_projet" ]; then cd "Temps_reel_Nokaya_Warlot_projet"; rm -rf $(MODE_DIR); fi


# Temps_reel_Nokaya_Warlot_projet_partialImage
ifeq ($(DEBUG_MODE),1)
Temps_reel_Nokaya_Warlot_projet_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -g
Temps_reel_Nokaya_Warlot_projet_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -g
Temps_reel_Nokaya_Warlot_projet_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -g
Temps_reel_Nokaya_Warlot_projet_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
Temps_reel_Nokaya_Warlot_projet_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
Temps_reel_Nokaya_Warlot_projet_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -g
else
Temps_reel_Nokaya_Warlot_projet_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
Temps_reel_Nokaya_Warlot_projet_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
Temps_reel_Nokaya_Warlot_projet_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -XO -Xsize-opt
Temps_reel_Nokaya_Warlot_projet_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
Temps_reel_Nokaya_Warlot_projet_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
Temps_reel_Nokaya_Warlot_projet_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif
Temps_reel_Nokaya_Warlot_projet_partialImage/$(MODE_DIR)/% : IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
Temps_reel_Nokaya_Warlot_projet_partialImage/$(MODE_DIR)/% : IDE_LIBRARIES = 
Temps_reel_Nokaya_Warlot_projet_partialImage/$(MODE_DIR)/% : PROJECT_TYPE = DKM
Temps_reel_Nokaya_Warlot_projet_partialImage/$(MODE_DIR)/% : DEFINES = 
Temps_reel_Nokaya_Warlot_projet_partialImage/$(MODE_DIR)/% : EXPAND_DBG = 0
Temps_reel_Nokaya_Warlot_projet_partialImage/$(MODE_DIR)/% : VX_CPU_FAMILY = simlinux
Temps_reel_Nokaya_Warlot_projet_partialImage/$(MODE_DIR)/% : CPU = SIMLINUX
Temps_reel_Nokaya_Warlot_projet_partialImage/$(MODE_DIR)/% : TOOL_FAMILY = diab
Temps_reel_Nokaya_Warlot_projet_partialImage/$(MODE_DIR)/% : TOOL = diab
Temps_reel_Nokaya_Warlot_projet_partialImage/$(MODE_DIR)/% : TOOL_PATH = 
Temps_reel_Nokaya_Warlot_projet_partialImage/$(MODE_DIR)/% : CC_ARCH_SPEC = -tX86LH:vxworks66
Temps_reel_Nokaya_Warlot_projet_partialImage/$(MODE_DIR)/% : LIBPATH = 
Temps_reel_Nokaya_Warlot_projet_partialImage/$(MODE_DIR)/% : LIBS = 
Temps_reel_Nokaya_Warlot_projet_partialImage/$(MODE_DIR)/% : OBJ_DIR := Temps_reel_Nokaya_Warlot_projet_partialImage/$(MODE_DIR)

Temps_reel_Nokaya_Warlot_projet_partialImage/$(MODE_DIR)/Objects/Temps_reel_Nokaya_Warlot_projet/accesTampons.o : /users/elo/pwarlot/Documents/temps_reel/workspace/Temps_reel_Nokaya_Warlot_projet/accesTampons.c
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -Xforce-declarations   -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


Temps_reel_Nokaya_Warlot_projet_partialImage/$(MODE_DIR)/Objects/Temps_reel_Nokaya_Warlot_projet/main.o : /users/elo/pwarlot/Documents/temps_reel/workspace/Temps_reel_Nokaya_Warlot_projet/main.c
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -Xforce-declarations   -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


Temps_reel_Nokaya_Warlot_projet_partialImage/$(MODE_DIR)/Objects/Temps_reel_Nokaya_Warlot_projet/signauxExterieur.o : /users/elo/pwarlot/Documents/temps_reel/workspace/Temps_reel_Nokaya_Warlot_projet/signauxExterieur.c
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -Xforce-declarations   -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


Temps_reel_Nokaya_Warlot_projet_partialImage/$(MODE_DIR)/Objects/Temps_reel_Nokaya_Warlot_projet/taches.o : /users/elo/pwarlot/Documents/temps_reel/workspace/Temps_reel_Nokaya_Warlot_projet/taches.c
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -Xforce-declarations   -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


OBJECTS_Temps_reel_Nokaya_Warlot_projet_partialImage = Temps_reel_Nokaya_Warlot_projet_partialImage/$(MODE_DIR)/Objects/Temps_reel_Nokaya_Warlot_projet/accesTampons.o \
	 Temps_reel_Nokaya_Warlot_projet_partialImage/$(MODE_DIR)/Objects/Temps_reel_Nokaya_Warlot_projet/main.o \
	 Temps_reel_Nokaya_Warlot_projet_partialImage/$(MODE_DIR)/Objects/Temps_reel_Nokaya_Warlot_projet/signauxExterieur.o \
	 Temps_reel_Nokaya_Warlot_projet_partialImage/$(MODE_DIR)/Objects/Temps_reel_Nokaya_Warlot_projet/taches.o

Temps_reel_Nokaya_Warlot_projet_partialImage/$(MODE_DIR)/Temps_reel_Nokaya_Warlot_projet_partialImage.o : $(OBJECTS_Temps_reel_Nokaya_Warlot_projet_partialImage)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dld -tX86LH:vxworks66 -X -r5 -f 0x90,1,1  -o "$@" $(OBJECTS_Temps_reel_Nokaya_Warlot_projet_partialImage) $(ADDED_OBJECTS) $(IDE_LIBRARIES) $(LIBPATH) $(LIBS) $(ADDED_LIBPATH) $(ADDED_LIBS) && if [ "$(EXPAND_DBG)" = "1" ]; then plink "$@";fi

Temps_reel_Nokaya_Warlot_projet_partialImage/$(MODE_DIR)/Temps_reel_Nokaya_Warlot_projet_partialImage_compile_file : $(FILE) ;

_clean :: Temps_reel_Nokaya_Warlot_projet_partialImage/$(MODE_DIR)/Temps_reel_Nokaya_Warlot_projet_partialImage_clean

Temps_reel_Nokaya_Warlot_projet_partialImage/$(MODE_DIR)/Temps_reel_Nokaya_Warlot_projet_partialImage_clean : 
	$(TRACE_FLAG)if [ -d "Temps_reel_Nokaya_Warlot_projet_partialImage" ]; then cd "Temps_reel_Nokaya_Warlot_projet_partialImage"; rm -rf $(MODE_DIR); fi

DEP_FILES := Temps_reel_Nokaya_Warlot_projet_partialImage/$(MODE_DIR)/Objects/Temps_reel_Nokaya_Warlot_projet/accesTampons.d Temps_reel_Nokaya_Warlot_projet_partialImage/$(MODE_DIR)/Objects/Temps_reel_Nokaya_Warlot_projet/main.d Temps_reel_Nokaya_Warlot_projet_partialImage/$(MODE_DIR)/Objects/Temps_reel_Nokaya_Warlot_projet/signauxExterieur.d \
	 Temps_reel_Nokaya_Warlot_projet_partialImage/$(MODE_DIR)/Objects/Temps_reel_Nokaya_Warlot_projet/taches.d
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
