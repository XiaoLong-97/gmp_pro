
#ifndef _FILE_PROMPT_TOOLS_H_
#define _FILE_PROMPT_TOOLS_H_

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

    // ANSI escape sequences

    //////////////////////////////////////////////////////////////////////////
    // Font Style

    // Clear Font Style
#define PROMPT_TOOL_FONT_RESET      "\e[0m"
    // Bold
#define PROMPT_TOOL_FONT_BOLD       "\e[1m"
    // Italic
#define PROMPT_TOOL_FONT_ITALIC     "\e[3m"
    // underlined
#define PROMPT_TOOL_FONT_UNDERLINED "\e[4m"
    // Blink
#define PROMPT_TOOL_FONT_BLINK		"\e[5m"
    // inverted
#define PROMPT_TOOL_FONT_INVERTED   "\e[7m"

    //////////////////////////////////////////////////////////////////////////
    // Font Color

    // foreground color
#define PROMPT_TOOL_FG_COLOR_BLACK	"\e[30m"
#define PROMPT_TOOL_FG_COLOR_RED	"\e[31m"
#define PROMPT_TOOL_FG_COLOR_GREEN	"\e[32m"
#define PROMPT_TOOL_FG_COLOR_YELLOW "\e[33m"
#define PROMPT_TOOL_FG_COLOR_BLUE	"\e[34m"
#define PROMPT_TOOL_FG_COLOR_PINK	"\e[35m"
#define PROMPT_TOOL_FG_COLOR_CYAN	"\e[36m"
#define PROMPT_TOOL_FG_COLOR_WHITE  "\e[37m"

    // Background Color
#define PROMPT_TOOL_BG_COLOR_BLACK  "\e[40m"
#define PROMPT_TOOL_BG_COLOR_RED    "\e[41m"
#define PROMPT_TOOL_BG_COLOR_GREEN  "\e[42m"
#define PROMPT_TOOL_BG_COLOR_YELLOW "\e[43m"
#define PROMPT_TOOL_BG_COLOR_BLUE   "\e[44m"
#define PROMPT_TOOL_BG_COLOR_PINK   "\e[45m"
#define PROMPT_TOOL_BG_COLOR_CYAN   "\e[46m"
#define PROMPT_TOOL_BG_COLOR_WHITE  "\e[47m"
    
    // Light foreground color
#define PROMPT_TOOL_FG_LIGHT_BLACK  "\e[90"
#define PROMPT_TOOL_FG_LIGHT_RED    "\e[91m"
#define PROMPT_TOOL_FG_LIGHT_GREEN  "\e[92m"
#define PROMPT_TOOL_FG_LIGHT_YELLOW "\e[93m"
#define PROMPT_TOOL_FG_LIGHT_BLUE   "\e[94m"
#define PROMPT_TOOL_FG_LIGHT_PINK   "\e[95m"
#define PROMPT_TOOL_FG_LIGHT_CYAN   "\e[96m"
#define PROMPT_TOOL_FG_LIGHT_WHITE  "\e[97m"

    // Light background color
#define PROMPT_TOOL_BG_LIGHT_BLACK  "\e[100m"
#define PROMPT_TOOL_BG_LIGHT_RED    "\e[101m"
#define PROMPT_TOOL_BG_LIGHT_GREEN  "\e[102m"
#define PROMPT_TOOL_BG_LIGHT_YELLOW "\e[103m"
#define PROMPT_TOOL_BG_LIGHT_BLUE   "\e[104m"
#define PROMPT_TOOL_BG_LIGHT_PINK   "\e[105m"
#define PROMPT_TOOL_BG_LIGHT_CYAN   "\e[106m"
#define PROMPT_TOOL_BG_LIGHT_WHITE  "\e[107m"

    //////////////////////////////////////////////////////////////////////////
    // Curses Position
#define PROMPT_TOOL_CURSES_SAVE_POSITION "\e[s"
#define PROMPT_TOOL_CURSES_RESUME_POSITION "\e[u"


#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _FILE_PROMPT_TOOLS_H_
