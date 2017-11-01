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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_edump.h"

ZEND_DECLARE_MODULE_GLOBALS(edump)


static zend_op_array *edump_compile_string(zval *source_string, char *filename TSRMLS_DC)
{
	int c, len;
	char *copy;

	if (Z_TYPE_P(source_string) != IS_STRING) {
		return EDUMP_G(orig_compile_string)(source_string, filename TSRMLS_CC);
	}

	if (strstr(filename, "eval()'d code")) {
		php_printf("/* ----- [start dump %s] ----- */\n", filename);
		php_printf("%s\n", Z_STRVAL_P(source_string));
		php_printf("/* ----- [end dump %s] ----- */\n", filename);
	}
 
	return EDUMP_G(orig_compile_string)(source_string, filename TSRMLS_CC);
}

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(edump)
{
	if (EDUMP_G(enabled) == 0) {
		EDUMP_G(enabled) = 1;
		EDUMP_G(orig_compile_string) = zend_compile_string;
		zend_compile_string = edump_compile_string;
	}
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(edump)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(edump)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(edump)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(edump)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "edump support", "enabled");
	php_info_print_table_end();
}
/* }}} */

/* {{{ edump_functions[]
 */
const zend_function_entry edump_functions[] = {
	PHP_FE_END	/* Must be the last line in edump_functions[] */
};
/* }}} */

/* {{{ edump_module_entry
 */
zend_module_entry edump_module_entry = {
	STANDARD_MODULE_HEADER,
	"edump",
	edump_functions,
	PHP_MINIT(edump),
	PHP_MSHUTDOWN(edump),
	PHP_RINIT(edump),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(edump),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(edump),
	PHP_EDUMP_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_EDUMP
ZEND_GET_MODULE(edump)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
