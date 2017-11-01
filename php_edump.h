/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2016 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef PHP_EDUMP_H
#define PHP_EDUMP_H

extern zend_module_entry edump_module_entry;
#define phpext_edump_ptr &edump_module_entry

#define PHP_EDUMP_VERSION "0.1.0"

#ifdef PHP_WIN32
#	define PHP_EDUMP_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_EDUMP_API __attribute__ ((visibility("default")))
#else
#	define PHP_EDUMP_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

ZEND_BEGIN_MODULE_GLOBALS(edump)
	long  enabled;
	zend_op_array *(*orig_compile_string)(zval *source_string, char *filename TSRMLS_DC);
ZEND_END_MODULE_GLOBALS(edump)

#ifdef ZTS
#define EDUMP_G(v) TSRMG(edump_globals_id, zend_edump_globals *, v)
#else
#define EDUMP_G(v) (edump_globals.v)
#endif

#endif	/* PHP_EDUMP_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
