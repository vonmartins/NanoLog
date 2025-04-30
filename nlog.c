/**
 * @file nlog.c
 * @brief Implementation of the NanoLog logging system.
 *
 * This file is part of the NanoLog project. NanoLog is a lightweight logging
 * library designed for embedded systems. It supports multiple log levels,
 * optional color output, timestamping, and configurable output backends such
 * as terminal and file. The logging functions are implemented with extensibility
 * and ease-of-use in mind.
 *
 * Author: Marti Dominguez
 * Date: 30/04/2025
 */

#include "nlog.h"
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
// #include <direct.h>
// #include <errno.h>

#if ENABLE_TIMESTAMP
    #include <time.h>
#endif

const char *new_execution_msg = "\n---------- NEW EXECUTION -----------\n\n";

// *****************************************************************************
//                        Private Definitions and Functions
// *****************************************************************************

/**
 * @brief Returns the ANSI color code for a given log level.
 *
 * This function is used internally to colorize log messages if USE_COLOR is enabled.
 *
 * @param level The log level.
 * @return A constant string with the ANSI code for the given level.
 */
const char * get_level_color(const enum nlog_level level) 
{
    switch(level) {
        case ERROR:   return "\x1b[31m"; /* RED */ 
        case WARNING: return "\x1b[33m"; /* YELLOW */
        case INFO:    return "\x1b[34m"; /* GREEN */
        case DEBUG:   return "\x1b[32m"; /* BLUE */
        default:      return "\x1b[0m";  /* DEFAULT */
    }
}

/**
 * @brief Returns a short string representing the given log level.
 *
 * This function maps the log level enum to a corresponding one-character string.
 *
 * @param level The log level.
 * @return A string representing the log level (e.g., "E" for ERROR).
 */
const char * get_level_string(const enum nlog_level level) 
{
    switch(level) {
        case ERROR:   return "E";
        case WARNING: return "W";
        case INFO:    return "I";
        case DEBUG:   return "D";
        default:      return "_";
    }
}

/**
 * @brief Backend output routine.
 *
 * This private function selects an output method based on the configuration.
 * Currently, it supports output to terminal (NLOG_OUTPUT 0) and file (NLOG_OUTPUT 2).
 *
 * @param msg The final log message to output.
 */
void nlog_backend_output(const char *msg) 
{
    #if NLOG_OUTPUT == 0
        /* Terminal output */
        printf("%s", msg);
    #elif NLOG_OUTPUT == 1
        /* UART output – TO DO */
    #elif NLOG_OUTPUT == 2
        /* File output: Append the log message to a file located in LOG_FILE_OUTPUT_PATH */
        char full_path[256];
        /* Construct the full path: e.g., "LogOutput/log.txt" */
        snprintf(full_path, sizeof(full_path), "%s%s.%s", LOG_FILE_OUTPUT_PATH, LOG_FILE_OUTPUT_NAME, LOG_FILE_OUTPUT_FORMAT);
        
        /* Check if the output directory exists; if not, try to create it */
        if (_access(LOG_FILE_OUTPUT_PATH, 0) != 0) {
            if (_mkdir(LOG_FILE_OUTPUT_PATH) != 0) {
                perror("Failed to create output directory");
            }
        }
        
        FILE *fp = fopen(full_path, "a");
        if (fp) {
            fputs(msg, fp);
            fclose(fp);
        }
    #endif
}

// *****************************************************************************
//                           Public Functions
// *****************************************************************************

/**
 * @brief Formats and outputs a log message.
 *
 * This public function formats the log message, inserting a timestamp and optional color codes
 * if enabled. It then delegates the final output to nlog_backend_output(). The first log of each
 * execution is preceded by a "new execution" header.
 *
 * @param level The log level for the message (ERROR, WARNING, INFO, DEBUG).
 * @param TAG   A tag identifying the module or source of the log.
 * @param fmt   A printf-like format string.
 * @param ...   Additional arguments for the format string.
 */
void nlog_messagev(const enum nlog_level level, const char *TAG, const char *fmt, ...)
{
    static unsigned int log_id = 0;  /* Static variable: persists across calls during an execution */
    log_id++;

    /* Buffer for the formatted message (without final formatting) */
    char buffer[MAX_NLOG_MESSAGE];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, MAX_NLOG_MESSAGE, fmt, args);
    va_end(args);

    /* Buffer for the final log message */
    char final_msg[512];

    #if ENABLE_TIMESTAMP
        /* Retrieve and format the current timestamp */
        time_t now = time(NULL);
        struct tm *tm_info = localtime(&now);
        char timestamp[20];
        strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", tm_info);
    #endif

    #if USE_COLOR
        const char* color = get_level_color(level);
    #endif

    /* Format the final message based on the available options */
    #if ENABLE_TIMESTAMP
        #if USE_COLOR
            snprintf(final_msg, sizeof(final_msg), "%s[%u] %s : [%s] [%s] %s\x1b[0m\n", 
                     color, log_id, get_level_string(level), TAG, timestamp, buffer);
        #else
            snprintf(final_msg, sizeof(final_msg), "[%u] %s : [%s] [%s] %s\n", 
                     log_id, get_level_string(level), TAG, timestamp, buffer);
        #endif
    #else
        #if USE_COLOR
            snprintf(final_msg, sizeof(final_msg), "%s[%u] %s : [%s] %s\x1b[0m\n", 
                     color, log_id, get_level_string(level), TAG, buffer);
        #else
            snprintf(final_msg, sizeof(final_msg), "[%u] %s : [%s] %s\n", 
                     log_id, get_level_string(level), TAG, buffer);
        #endif
    #endif

    /* Prepend a header if this is the first log of the execution */
    if(log_id == 1)
    {
        char tmp_msg[600];
        snprintf(tmp_msg, sizeof(tmp_msg), "%s%s", new_execution_msg, final_msg);
        nlog_backend_output(tmp_msg);
    }
    else
    {
        nlog_backend_output(final_msg);
    }
}