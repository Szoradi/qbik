# --------------------------------------------------------------------------------------
# Project name definition;
# --------------------------------------------------------------------------------------

PROJECT = BoulderDash

# --------------------------------------------------------------------------------------
# Base directory of the project. Replace this with wherever 
# you have put the sample application on your computer
# --------------------------------------------------------------------------------------

PROJECT_DIR	= D:/GBA_development/BoulderDash

# --------------------------------------------------------------------------------------
# GCC Version you're using. If you're using the latest DevKitAdv this 
# should be correct already.
# --------------------------------------------------------------------------------------
GCC_VERSION = 3.0.2

# --------------------------------------------------------------------------------------
# Base directory for GCC Arm-Agb-Elf compiler. Replace with 
# wherever you have put it. 
# --------------------------------------------------------------------------------------

GCC_DIR  = D:/GBA

# --------------------------------------------------------------------------------------
# Socrates library and header directories. Replace this with wherever 
# you have put the Socrates on your computer
# --------------------------------------------------------------------------------------

SOCRATES_LIB_DIR	= D:/GBA_development/lib/
KRAWALL_LIB_DIR		= $(PROJECT_DIR)/lib/
MODULES_LIB_DIR		= $(PROJECT_DIR)/modules/
SOCRATES_INC_DIR	= D:/GBA_development/include/

# --------------------------------------------------------------------------------------
# Socrates library itself;
# --------------------------------------------------------------------------------------
SOCRATES_LIB		= $(SOCRATES_LIB_DIR)/libSocrates.a
KRAWALL_LIB		= $(KRAWALL_LIB_DIR)/krawall.lib
MODULES_LIB		= $(MODULES_LIB_DIR)/modules.lib

# --------------------------------------------------------------------------------------
# Compiler directories for includes and libs.
# Assuming you are using Devkit Advance there should be no need to change these, 
# since they are derived from the above CMP_DIR directory definition.
# --------------------------------------------------------------------------------------

STD_LIB_DIR0 = $(GCC_DIR)/lib/gcc-lib/arm-agb-elf/$(GCC_VERSION)/interwork
STD_LIB_DIR1 = $(GCC_DIR)/arm-agb-elf/lib/interwork

STD_INC_DIR0 = $(GCC_DIR)/lib/gcc-lib/arm-agb-elf/$(GCC_VERSION)/include
STD_INC_DIR1 = $(GCC_DIR)/arm-agb-elf/include

# --------------------------------------------------------------------------------------
# Project directories.
# --------------------------------------------------------------------------------------

INC_DIR		= $(PROJECT_DIR)/include
SRC_DIR		= $(PROJECT_DIR)/source
ASM_DIR		= $(PROJECT_DIR)/assembly
LINK_SCRIPT_DIR = $(PROJECT_DIR)/build
OBJ_DIR		= $(PROJECT_DIR)/build/intermediate
ELF_DIR		= $(PROJECT_DIR)/build/intermediate
DAT_DIR		= $(PROJECT_DIR)/data

# --------------------------------------------------------------------------------------
# Define the flags for the compiler, the assembler and the linker;
# --------------------------------------------------------------------------------------
C_FLAGS  = -I$(DAT_DIR) -I$(INC_DIR) -I $(SOCRATES_INC_DIR) -I$(STD_INC_DIR0) -I$(STD_INC_DIR1) -I $(SGADE_SRC_DIR) -mthumb -mthumb-interwork -mlong-calls -c -g -O3 -Wall -fverbose-asm 
S_FLAGS  = -I$(DAT_DIR) -I$(INC_DIR) -I $(SOCRATES_INC_DIR) -I$(STD_INC_DIR0) -I$(STD_INC_DIR1) -mthumb -mthumb-interwork -mlong-calls

L_FLAGS = -lSocrates -L$(SOCRATES_LIB_DIR) -L$(STD_LIB_DIR0) -L$(STD_LIB_DIR1) -T$(LINK_SCRIPT_DIR)/lnkscript -lgcc -lc
L_FLAGS2 = -mthumb -mthumb-interwork -mlong-calls -T$(LINK_SCRIPT_DIR)/lnkscript -nostartfiles -Wl,-Map=$(LINK_SCRIPT_DIR)/sux.map

# --------------------------------------------------------------------------------------
# Define the list of object files
# --------------------------------------------------------------------------------------

O_FILES_FROM_C  = $(PROJECT).o \
		  BdGameIntro.o	\
		  BdCutScene.o \
		  BdGameEngine.o \
		  BdBackground.o \
		  BdMenuData.o \
		  BdGfxData.o \
		  BdMapData.o \
		  BdVblank.o \
		  BdLevelStartData.o \
		  BdCutSceneData.o \
		  BdGameIntroData.o \
		  BdScroll.o \
		  BdMusic.o \
		  BdStats.o \
		  BdBlend.o \
		  BdGame.o \
		  dsprintf.o \
		  BdRnd.o \
		  BdMenu.o \
		  BdMan.o \
		  BdGif.o \
		  BdMap.o
#		  BdJpegSlow.o \
#		  BdGameIntroData.o \
#		  BdJpeg.o \

O_FILES_FROM_S  = crt0.o 
#		  BdJpegPixel.o \
#		  BdJpega.o 

O_FILES_FROM_C_FULL_PATH = $(addprefix $(OBJ_DIR)/, $(O_FILES_FROM_C))
O_FILES_FROM_S_FULL_PATH = $(addprefix $(OBJ_DIR)/, $(O_FILES_FROM_S))

O_FILES_FULL_PATH	= $(O_FILES_FROM_S_FULL_PATH) $(O_FILES_FROM_C_FULL_PATH) 
							
# --------------------------------------------------------------------------------------
# Define the final dependecy;
# --------------------------------------------------------------------------------------
all : 	$(PROJECT_DIR)/$(PROJECT).gba
	@echo Done

# --------------------------------------------------------------------------------------
# Define the copy from .elf to .gba file
# --------------------------------------------------------------------------------------
$(PROJECT_DIR)/$(PROJECT).gba : $(ELF_DIR)/$(PROJECT).elf
	@echo Object copying 
	@$(GCC_DIR)/bin/objcopy -v -O binary $< $@
		
# --------------------------------------------------------------------------------------
# Define the linker instruction;
# --------------------------------------------------------------------------------------
$(ELF_DIR)/$(PROJECT).elf : $(O_FILES_FULL_PATH) $(SOCRATES_LIB) $(KRAWALL_LIB) $(MODULES_LIB)
	@echo Linking object files
#	@$(GCC_DIR)/bin/ld  $(O_FILES_FULL_PATH) -o$@ $(L_FLAGS) $(KRAWALL_LIB) $(MODULES_LIB)
	$(CC) $(L_FLAGS2) -o$@ $(O_FILES_FULL_PATH) $(SOCRATES_LIB) $(KRAWALL_LIB) $(MODULES_LIB)
	strip -g -S --strip-debug $(ELF_DIR)/$(PROJECT).elf
# --------------------------------------------------------------------------------------
# Define the C compiles;
# --------------------------------------------------------------------------------------
$(O_FILES_FROM_C_FULL_PATH) : $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@echo Making $@
	@$(GCC_DIR)/bin/gcc  -c $< -o$@ $(C_FLAGS) 
	
# --------------------------------------------------------------------------------------
# Define the assembly of the crt file;
# --------------------------------------------------------------------------------------
$(O_FILES_FROM_S_FULL_PATH) : $(OBJ_DIR)/%.o : $(ASM_DIR)/%.S
	@echo Making $@
	@$(GCC_DIR)/bin/gcc -c $< -o$@ $(S_FLAGS) 

# --------------------------------------------------------------------------------------
# Build Modules
# --------------------------------------------------------------------------------------
#	@echo Building S3M modules
#	make -C $(MODULES_LIB_DIR)
		
# --------------------------------------------------------------------------------------
# Clean definition;
# --------------------------------------------------------------------------------------
.PHONY : clean
clean :
	@echo Cleaning object, .elf and .gba files.
	@$(GCC_DIR)/bin/rm $(OBJ_DIR)/*.o
	@$(GCC_DIR)/bin/rm $(ELF_DIR)/$(PROJECT).elf
	@$(GCC_DIR)/bin/rm $(PROJECT_DIR)/$(PROJECT).gba
	
# --------------------------------------------------------------------------------------
# EOF;
# --------------------------------------------------------------------------------------

