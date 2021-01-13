PROJECT_DIR = D:/GBA_development/BoulderDash

CONVERT = $(PROJECT_DIR)/converter/converter
MODULES = intro.s3m l11.s3m l21.s3m l31.s3m l41.s3m l51.s3m logo.s3m menu.s3m outro.s3m sfx.s3m

SHELL = sh.exe
CFLAGS = -c -mthumb-interwork -I../include/ -I../../include/
ASFLAGS = -mthumb-interwork
PROJECT = modules.lib
RM = rm -f

all : $(PROJECT)

$(PROJECT) : Makefile $(MODULES) $(CONVERT)
	-$(RM) *.s
	$(CONVERT) -d $(MODULES)
	$(AS) $(ASFLAGS) *.s -o $@
	-$(RM) *.s

.PHONY : clean

clean :
	-$(RM) *.s *.h *.lib

