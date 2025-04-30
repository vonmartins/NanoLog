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
 * Otherwise, it expande to a no-operation.
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





