/**
 * @file nlog_config.h
 * @brief Configuration settings for the NanoLog logging system.
 *
 * This file contains compile-time settings for NanoLog. Adjust these
 * macros to customize logging features, such as output destination, log
 * levels, timestamping, colorized output, and file output settings.
 *
 * Author: Marti Dominguez
 * Date: 30/04/2025
 */

#ifndef __NLOG_CONFIG__
#define __NLOG_CONFIG__

/* *****************************************************************************
 *                          Global Logging Settings
 * *****************************************************************************
 */

/**
 * @brief Global enable/disable for logging.
 *
 * Set to 1 to enable all logging functions, or 0 to disable logging globally.
 */
#define ENABLE_LOG          1

/**
 * @brief Maximum buffer size for log messages.
 */
#define MAX_NLOG_MESSAGE    120

/**
 * @brief Enable or disable colored output.
 *
 * Set to 1 to output colored logs (if supported), or 0 for plain text.
 */
#define USE_COLOR           0

/**
 * @brief Minimum log level filter.
 *
 * Only messages with a log level equal to or greater than this will be recorded.
 * Use the enum values defined in nlog.h: NO_LEVEL, ERROR, WARNING, INFO, DEBUG.
 */
#define NLOG_MIN_LEVEL      ERROR

/* *****************************************************************************
 *                          Individual Log Level Settings
 * *****************************************************************************
 */

/**
 * @brief Enable error level logging.
 */
#define ENABLE_ERROR_LOGS       1

/**
 * @brief Enable warning level logging.
 */
#define ENABLE_WARNING_LOGS     1

/**
 * @brief Enable info level logging.
 */
#define ENABLE_INFO_LOGS        1

/**
 * @brief Enable debug level logging.
 */
#define ENABLE_DEBUG_LOGS       1

/* *****************************************************************************
 *                          Output Backend Settings
 * *****************************************************************************
 */

/**
 * @brief Output destination selection.
 *
 * Define the target backend for log messages:
 *   0 = Terminal
 *   1 = UART
 *   2 = File
 *   3 = Memory Buffer
 *   4 = Network
 */
#define NLOG_OUTPUT         0

/**
 * @brief Enable or disable timestamps in log messages.
 *
 * Set to 1 to include a timestamp in each log message, or 0 to omit.
 */
#define ENABLE_TIMESTAMP    1

/* *****************************************************************************
 *                          File Output Settings
 * *****************************************************************************
 */

/**
 * @brief Directory path for file output.
 * Logs will be written to this directory.
 */
#define LOG_FILE_OUTPUT_PATH    "LogOutput/"

/**
 * @brief Base name for the log file.
 */
#define LOG_FILE_OUTPUT_NAME    "log" 

/**
 * @brief Log file extension format.
 *
 * For example, _TEXT_ creates a file with extension "txt".
 */
#define LOG_FILE_OUTPUT_FORMAT  _TEXT_

/**
 * @brief Text file extension definition.
 */
#define _TEXT_                  "txt"

/**
 * @brief Markdown file extension definition.
 */
#define _MARKDOWN_              "md"


#define MAX_TAG_SIZE    16
#define MAX_DESC_SIZE   128

#endif // __NLOG_CONFIG__