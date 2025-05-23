/**
 * @file nlog.h
 * @brief Public interface for the NanoLog logging system.
 *
 * This file is part of the NanoLog project. NanoLog is a lightweight logging
 * library designed for embedded systems. It supports multiple log levels,
 * optional color output, timestamping, and configurable output backends
 * such as the terminal and file.
 *
 * Use the provided logging macros (LOGE, LOGW, LOGI, LOGD) for convenience.
 * The behavior of the logging system can be configured via "nlog_config.h".
 *
 * Author: Marti Dominguez
 * Date: 30/04/2025
 */

#ifndef __NLOG__
#define __NLOG__

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "nlog_config.h"

/* *****************************************************************************
 *                             Public Types
 * *****************************************************************************
 */

/**
 * @brief Enumeration of log levels.
 */
enum nlog_level {
    NO_LEVEL, /*!< No specific logging level */
    ERROR,    /*!< Error level logging */
    WARNING,  /*!< Warning level logging */
    INFO,     /*!< Info level logging */
    DEBUG     /*!< Debug level logging */
};

typedef enum {
    DEVICE_OK,
    DEVICE_ERROR
} dev_err;

typedef struct {
    dev_err res;
    char tag[MAX_TAG_SIZE];
    char desc[MAX_DESC_SIZE];
} err_t;

/* *****************************************************************************
 *                             Public Macros
 * *****************************************************************************
 */

/**
 * @brief Log an error message.
 *
 * If ENABLE_ERROR_LOGS is nonzero, the macro calls nlog_messagev() with level ERROR.
 * Otherwise, it expands to a no-operation.
 */
#if ENABLE_ERROR_LOGS
    #define LOGE(TAG, fmt, ...) nlog_messagev(ERROR, TAG, fmt, ##__VA_ARGS__)
#else
    #define LOGE(TAG, fmt, ...) (void)0
#endif

/**
 * @brief Log a warning message.
 *
 * If ENABLE_WARNING_LOGS is nonzero, the macro calls nlog_messagev() with level WARNING.
 * Otherwise, it expands to a no-operation.
 */
#if ENABLE_WARNING_LOGS
    #define LOGW(TAG, fmt, ...) nlog_messagev(WARNING, TAG, fmt, ##__VA_ARGS__)
#else
    #define LOGW(TAG, fmt, ...) (void)0
#endif

/**
 * @brief Log an info message.
 *
 * If ENABLE_INFO_LOGS is nonzero, the macro calls nlog_messagev() with level INFO.
 * Otherwise, it expands to a no-operation.
 */
#if ENABLE_INFO_LOGS
    #define LOGI(TAG, fmt, ...) nlog_messagev(INFO, TAG, fmt, ##__VA_ARGS__)
#else
    #define LOGI(TAG, fmt, ...) (void)0
#endif

/**
 * @brief Log a debug message.
 *
 * If ENABLE_DEBUG_LOGS is nonzero, the macro calls nlog_messagev() with level DEBUG.
 * Otherwise, it expands to a no-operation.
 */
#if ENABLE_DEBUG_LOGS
    #define LOGD(TAG, fmt, ...) nlog_messagev(DEBUG, TAG, fmt, ##__VA_ARGS__)
#else
    #define LOGD(TAG, fmt, ...) (void)0
#endif

#define CREATE_ERROR(_name, _tag, _fmt, ...) ({               \
    err_t _error;                                             \
    _error.res = _name;                                       \
    strncpy(_error.tag, _tag, MAX_TAG_SIZE - 1);              \
    _error.tag[MAX_TAG_SIZE - 1] = '\0';                      \
    snprintf(_error.desc, MAX_DESC_SIZE, _fmt, ##__VA_ARGS__); \
    _error;                                                   \
})
/**
 * @brief Processes the result of a function and logs a message based on the result.
 *
 * This macro executes a function that returns an error (of type `err_t`).
 * If the result is not `DEVICE_OK`, it logs the error using NanoLog,
 * including the `tag` and the error description.
 * If the result is `DEVICE_OK` and the debug level is enabled,
 * it logs a success message indicating which function was executed successfully.
 *
 * @param fn The function to execute.
 */
#define ERROR_CHECK(fn)                                      \
do {                                                          \
    err_t _result = (fn);                                     \
    if (_result.res != DEVICE_OK) {                           \
        LOGE(_result.tag, "Error in function '%s': %s", #fn, _result.desc); \
    } else {                                                  \
        /* LOGI(_result.tag, "Success in function '%s'", #fn);  */ \
    }                                                         \
} while (0)

/* *****************************************************************************
 *                          Private Function Prototypes
 * *****************************************************************************
 */

/* *****************************************************************************
 *                          Public Function Prototypes
 * *****************************************************************************
 */

/**
 * @brief Formats and outputs a log message.
 *
 * This function receives a printf-like format string and parameters, formats
 * the message (inserting optional metadata such as timestamps or color codes)
 * and dispatches it to the appropriate output backend (terminal, file, etc.).
 *
 * @param level The log level (ERROR, WARNING, INFO, DEBUG).
 * @param TAG   A tag identifying the module or component generating the log.
 * @param fmt   A printf-like format string.
 * @param ...   Additional parameters for the format string.
 */
void nlog_messagev(const enum nlog_level level, const char *TAG, const char *fmt, ...);

#endif // __NLOG__