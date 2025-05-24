# NanoLog 

Currently under development...

## Overview

NanoLog is a lightweight logging system designed for embedded systems. The project focuses on providing a flexible, configurable logging library that:

- Supports multiple log levels (Error, Warning, Info, Debug)
- Allows configuration through compile-time macros
- Enables colored output, timestamping, and various output backends (terminal, file, UART, memory buffer, network)
- Is designed to be extensible and easily integrated into multiple projects

## Current Functionality

- **Log Levels and Tags**:  
  The system supports error, warning, info, and debug levels. Each log message is associated with a tag that identifies the source module.

- **Output Backends**:  
  - **Terminal Output**: Logs can be displayed via the terminal (using standard output).
  - **File Output**: Logs can be written to a file. The file path is constructed using configurable macros for output path, file name, and format.
  - **UART Output**: Basic support is planned (placeholder present in backend selection).
  
- **Formatting and Metadata**:  
  - Each log message can optionally include a timestamp.
  - If enabled, colored output (via ANSI escape codes) is supported.
  - A new execution header is added at the start of each run to separate sessions.

- **Macro-Based Configuration**:  
  The system makes extensive use of macros for:
  - Enabling/disabling logging globally or per log level
  - Configuring the maximum message buffer size
  - Selecting the output backend
  - Toggling timestamp and color usage

## What NanoLog Can Do Today

- **Log Message Generation**:  
  Developers can use the provided logging macros (LOGE, LOGW, LOGI, LOGD) to easily generate log messages with different severity levels.  
- **Message Formatting**:  
  Log messages are formatted to include log level indicators, tags, and optionally timestamp and color codes.
- **Output Routing**:  
  Using backend selection, log messages are either displayed in the terminal or written into a file. The system is designed for easy extension to other outputs in the future.

## Remaining Tasks and Future Updates

- **Process Functions like PROCESS(wifi_init())**
PROCESS(X) will manage the status return if its error, etc

- **UART Backend Implementation**:  
  The UART output option is currently a placeholder. Implementation for UART should be added to support logging via serial interfaces.

- **Network Backend Implementation**:

    Send to UDP/TCP direction?

- **Buffer Management and Ring Buffer Support**:  
  - Implement support for circular (ring) buffers to temporarily store logs in memory.
  - Ensure safe buffer operations to prevent overflows and manage memory efficiently.
  - Incorporate measures for handling buffering in concurrent environments (e.g., mutexes or critical sections).

- **Documentation and Examples**:  
  Continue enhancing the documentation (both inline and external) and provide sample projects to demonstrate how to integrate and use NanoLog in various scenarios.

Funcion que convierta HAL_StatusTypeDef de stm32 a err_t

-------

Que hará?

- Ejecutar función y mostrar resultado: error, no error, etc 
- Niveles de log: error, warning, info, debug
- TAGs para realizar distintos logs
- Hacerlo lo mas independiente posible para poder usarlo desde cualquier proyecto
- Diferentes salidas: terminal, archivo o buffer de memoria, network
- por defecto se transmite por uart pero poder enviar por jtag o swd
- Sin buffer por defecto, pero con opción de activarlo.???

Una funcion devuelve un struct:

- Tipo de error: enum
- Comentario
- TAG: Tags presonalizados de cada proyecto


el log recibe: nivel de log, tag, mensaje

error_check ejecuta la funcion y imprime logs


Futuros Updates:

- Soporte a buffer circular

    ```c
    #if NLOG_USE_BUFFER
        // En vez de imprimir, guarda en buffer aquí
    #else
        // Salida directa
    #endif
    ```

--------
### Manejo de buffers 

En cuanto al manejo de buffers, en sistemas embebidos es crucial conservar recursos. Algunas consideraciones en el manejo de buffers son:

- Uso de buffers estáticos: Reservar buffers de tamaño fijo para evitar asignaciones dinámicas en tiempo de ejecución, lo que reduce el riesgo de fragmentación.
- Seguridad y validación: Asegurarse de que las operaciones con buffers no excedan la capacidad predefinida (por ejemplo, MAX_NLOG_MESSAGE) para evitar overflows.
- Buffers circulares (ring buffers): Si se requiere almacenar logs de manera temporal para ser enviados o procesados posteriormente, se puede implementar un buffer circular que permita guardar una cantidad limitada de mensajes y sobreescribir los más viejos cuando se alcance el límite.
- Concurrencia: Si el log se utiliza en un entorno con múltiples hilos o interrupciones, hay que tener medidas de sincronización para evitar condiciones de carrera mientras se escribe o se lee del buffer.
