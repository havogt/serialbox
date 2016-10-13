/*===-- serialbox-c/ErrorHandling.h -------------------------------------------------*- C++ -*-===*\
 *
 *                                    S E R I A L B O X
 *
 * This file is distributed under terms of BSD license.
 * See LICENSE.txt for more information
 *
 *===------------------------------------------------------------------------------------------===//
 *
 *! \file
 *! This file contains the error handling of the C Interface of Serialbox.
 *
\*===------------------------------------------------------------------------------------------===*/

#ifndef SERIALBOX_C_ERRORHANDLING_H
#define SERIALBOX_C_ERRORHANDLING_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Report a fatal error
 *
 * This will function will invoke the installed FatalErrorHandler.
 *
 * \see serialboxInstallFatalErrorHandler
 */
void serialboxFatalError(const char* reason);

/**
 * \brief Error handler callback
 */
typedef void (*serialboxFatalErrorHandler_t)(const char* reason);

/**
 * \brief Install a fatal error handler
 *
 * By default, if Serialbox detects a fatal error it will emit the last error string to stderr and
 * call exit(1).
 *
 * This may not be appropriate in some contexts. For example, the Python module might want to
 * translate the errror into an exception. This function allows you to install a callback that will
 * be invoked after a fatal error occurred.
 */
void serialboxInstallFatalErrorHandler(serialboxFatalErrorHandler_t handler);

/**
 * \brief Reset the fatal error handler.
 *
 * This resets Serialbox's fatal error handling behavior to the default.
 */
void serialboxResetFatalErrorHandler(void);

/*===------------------------------------------------------------------------------------------===*\
 *     Default Error Handler
\*===------------------------------------------------------------------------------------------===*/

/**
 * \brief Emit the last error string to stderr and call exit(1)
 */
void serialboxDefaultFatalErrorHandler(const char* Reason);

/*===------------------------------------------------------------------------------------------===*\
 *     State Error Handler
\*===------------------------------------------------------------------------------------------===*/

/**
 * \brief Store the the current state of the error which can be queried via
 * serialboxStateErrorHandlerGetLastError()
 */
void serialboxStateErrorHandler(const char* Reason);

/**
 * \brief Query the current error state
 *
 * This function requires to set the ErrorHandler to ´serialboxStateErrorHandler´.
 *
 * \param[out]  hasError        Set to 1 if an error occured, 0 otherwise
 * \param[out]  errorMessage    Error message of the last error (NULL if no error occured)
 */
void serialboxStateErrorHandlerGetCurrentError(int* hasError, char** errorMessage);

/**
 * \brief Reset the current error state
 */
void serialboxStateErrorHandlerResetState(void);

/**
 * \brief Query the current error state and \b reset it
 *
 * \see serialboxStateErrorHandlerGetCurrentError
 * \see serialboxStateErrorHandlerResetState.
 */
void serialboxStateErrorHandlerGetCurrentErrorAndReset(int* hasError, char** errorMessage);

#ifdef __cplusplus
}
#endif

#endif
