
#include "Utils.hpp"


#include <cstdio>
#include <cstring>
#include <time.h>

void Log(int severity, const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	Log(severity, fmt, args);
	va_end(args);
}

void Log(int severity, const char *fmt, va_list args)
{
	const char *type;
	const char *color;
	switch (severity)
	{
	case 0:
		type = "info";
		color = CONSOLE_COLOR_GREEN;
		break;
	case 1:
		type = "warning";
		color = CONSOLE_COLOR_PURPLE;
		break;
	case 2:
		type = "error";
		color = CONSOLE_COLOR_RED;
		break;
	case 3:
		type = "PRINT";
		color = CONSOLE_COLOR_YELLOW;
		break;
	default:
		type = "unknown";
		color = CONSOLE_COLOR_RESET;
		break;
	}


    char consoleFormat[1024];
    snprintf(consoleFormat, sizeof(consoleFormat), "%s%s%s%s:%s\n", CONSOLE_COLOR_CYAN,
              color, type, CONSOLE_COLOR_RESET, fmt);

  
    va_list argsCopy;
    va_copy(argsCopy, args);

    char consoleMessage[4096];
    vsnprintf(consoleMessage, sizeof(consoleMessage), consoleFormat, args);
    printf("%s", consoleMessage);


    va_end(argsCopy);
}



const char *FormatText(const char *text, ...)
{
    static char buffers[4][512] = { 0 };
    static int index = 0;

    char *currentBuffer = buffers[index];
    memset(currentBuffer, 0, 512);  

    va_list args;
    va_start(args, text);
    int requiredByteCount = vsnprintf(currentBuffer, 512, text, args);
    va_end(args);
    if (requiredByteCount >= 512)
    {

        char *truncBuffer = buffers[index] + 512 - 4; 
        sprintf(truncBuffer, "...");
    }

    index += 1;    
    if (index >= 4) index = 0;

    return currentBuffer;
}




double time_now()
{
    return (clock() / (double)CLOCKS_PER_SEC);
}

