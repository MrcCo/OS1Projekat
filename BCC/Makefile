SRC = ..\*.cpp 
INCLUDES = ..\BCC\*.h ..\*.h 
LIBS = ..\BCC\*.lib 
INCLUDEPATH = C:\bc31\include;..\BCC;..\;
LIBSPATH = C:\bc31\lib;..\BCC;
TARGET = FinOS.exe
$(TARGET):	$(SRC) $(INCLUDES) configuration.xmi
	bcc.exe -mh -v -e$(TARGET) -I$(INCLUDEPATH) -L$(LIBSPATH) $(SRC) $(LIBS)
all:	$(TARGET)
clean:
	-del *.obj
	-del $(TARGET)
	-del *.asm
configuration.xmi:	
	configuration.xmi