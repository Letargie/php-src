/*
   +----------------------------------------------------------------------+
   | PHP Version 5                                                        |
   +----------------------------------------------------------------------+
   | Copyright (c) 1997-2014 The PHP Group                                |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Authors: Felipe Pena <felipe@php.net>                                |
   | Authors: Joe Watkins <joe.watkins@live.co.uk>                        |
   | Authors: Bob Weinand <bwoebi@php.net>                                |
   +----------------------------------------------------------------------+
*/

#ifndef PHPDBG_UTILS_H
#define PHPDBG_UTILS_H

/**
 * Input scan functions
 */
PHPDBG_API int phpdbg_is_numeric(const char*);
PHPDBG_API int phpdbg_is_empty(const char*);
PHPDBG_API int phpdbg_is_addr(const char*);
PHPDBG_API int phpdbg_is_class_method(const char*, size_t, char**, char**);
PHPDBG_API const char *phpdbg_current_file(TSRMLS_D);
PHPDBG_API char *phpdbg_resolve_path(const char* TSRMLS_DC);
PHPDBG_API char *phpdbg_trim(const char*, size_t, size_t*);
PHPDBG_API const zend_function *phpdbg_get_function(const char*, const char* TSRMLS_DC);

/**
 * Error/notice/formatting helpers
 */
enum {
	P_ERROR  = 1,
	P_NOTICE,
	P_WRITELN,
	P_WRITE,
	P_STDOUT,
	P_STDERR,
	P_LOG
};

#ifdef ZTS
PHPDBG_API int phpdbg_print(int severity TSRMLS_DC, int fd, const char *tag, const char *xmlfmt, const char *strfmt, ...) PHP_ATTRIBUTE_FORMAT(printf, 6, 7);
#else
PHPDBG_API int phpdbg_print(int severity TSRMLS_DC, int fd, const char *tag, const char *xmlfmt, const char *strfmt, ...) PHP_ATTRIBUTE_FORMAT(printf, 5, 6);
#endif

PHPDBG_API int phpdbg_xml_internal(int fd TSRMLS_DC, const char *fmt, ...);
PHPDBG_API int phpdbg_log_internal(int fd TSRMLS_DC, const char *fmt, ...);
PHPDBG_API int phpdbg_out_internal(int fd TSRMLS_DC, const char *fmt, ...);

PHPDBG_API int phpdbg_rlog_internal(int fd TSRMLS_DC, const char *fmt, ...);
#define phpdbg_rlog(fd, fmt, ...) phpdbg_rlog_internal(fd TSRMLS_CC, fmt, ##__VA_ARGS__)

#define phpdbg_error(tag, xmlfmt, strfmt, ...)              phpdbg_print(P_ERROR   TSRMLS_CC, PHPDBG_G(io)[PHPDBG_STDOUT].fd, tag,  xmlfmt, strfmt, ##__VA_ARGS__)
#define phpdbg_notice(tag, xmlfmt, strfmt, ...)             phpdbg_print(P_NOTICE  TSRMLS_CC, PHPDBG_G(io)[PHPDBG_STDOUT].fd, tag,  xmlfmt, strfmt, ##__VA_ARGS__)
#define phpdbg_writeln(tag, xmlfmt, strfmt, ...)            phpdbg_print(P_WRITELN TSRMLS_CC, PHPDBG_G(io)[PHPDBG_STDOUT].fd, tag,  xmlfmt, strfmt, ##__VA_ARGS__)
#define phpdbg_write(tag, xmlfmt, strfmt, ...)              phpdbg_print(P_WRITE   TSRMLS_CC, PHPDBG_G(io)[PHPDBG_STDOUT].fd, tag,  xmlfmt, strfmt, ##__VA_ARGS__)
#define phpdbg_script(type, fmt, ...)                       phpdbg_print(type      TSRMLS_CC, PHPDBG_G(io)[PHPDBG_STDOUT].fd, NULL, NULL,   fmt,    ##__VA_ARGS__)
#define phpdbg_log(fmt, ...) phpdbg_log_internal(PHPDBG_G(io)[PHPDBG_STDOUT].fd TSRMLS_CC, fmt, ##__VA_ARGS__)
#define phpdbg_xml(fmt, ...) phpdbg_xml_internal(PHPDBG_G(io)[PHPDBG_STDOUT].fd TSRMLS_CC, fmt, ##__VA_ARGS__)
#define phpdbg_out(fmt, ...) phpdbg_out_internal(PHPDBG_G(io)[PHPDBG_STDOUT].fd TSRMLS_CC, fmt, ##__VA_ARGS__)

#define phpdbg_error_ex(out, tag, xmlfmt, strfmt, ...)      phpdbg_print(P_ERROR   TSRMLS_CC, out, tag,  xmlfmt, strfmt, ##__VA_ARGS__)
#define phpdbg_notice_ex(out, tag, xmlfmt, strfmt, ...)     phpdbg_print(P_NOTICE  TSRMLS_CC, out, tag,  xmlfmt, strfmt, ##__VA_ARGS__)
#define phpdbg_writeln_ex(out, tag, xmlfmt, strfmt, ...)    phpdbg_print(P_WRITELN TSRMLS_CC, out, tag,  xmlfmt, strfmt, ##__VA_ARGS__)
#define phpdbg_write_ex(out, tag, xmlfmt, strfmt, ...)      phpdbg_print(P_WRITE   TSRMLS_CC, out, tag,  xmlfmt, strfmt, ##__VA_ARGS__)
#define phpdbg_script_ex(out, type, fmt, ...)               phpdbg_print(type      TSRMLS_CC, out, NULL, NULL,   fmt,    ##__VA_ARGS__)
#define phpdbg_log_ex(out, fmt, ...) phpdbg_log_internal(PHPDBG_G(io)[PHPDBG_STDOUT].fd TSRMLS_CC, fmt, ##__VA_ARGS__)
#define phpdbg_xml_ex(out, fmt, ...) phpdbg_xml_internal(PHPDBG_G(io)[PHPDBG_STDOUT].fd TSRMLS_CC, fmt, ##__VA_ARGS__)
#define phpdbg_out_ex(out, fmt, ...) phpdbg_out_internal(PHPDBG_G(io)[PHPDBG_STDOUT].fd TSRMLS_CC, fmt, ##__VA_ARGS__)

#if PHPDBG_DEBUG
#	define phpdbg_debug(fmt, ...) phpdbg_log_ex(PHPDBG_G(io)[PHPDBG_STDERR].fd TSRMLS_CC, fmt, ##__VA_ARGS__)
#else
#	define phpdbg_debug(fmt, ...)
#endif

PHPDBG_API void phpdbg_free_err_buf(TSRMLS_D);
PHPDBG_API void phpdbg_activate_err_buf(zend_bool active TSRMLS_DC);
PHPDBG_API int phpdbg_output_err_buf(const char *tag, const char *xmlfmt, const char *strfmt TSRMLS_DC, ...);


/* {{{ For separation */
#define SEPARATE "------------------------------------------------" /* }}} */

/* {{{ Color Management */
#define PHPDBG_COLOR_LEN 12
#define PHPDBG_COLOR_D(color, code) \
	{color, sizeof(color)-1, code}
#define PHPDBG_COLOR_END \
	{NULL, 0L, {0}}
#define PHPDBG_ELEMENT_LEN 3
#define PHPDBG_ELEMENT_D(name, id) \
	{name, sizeof(name)-1, id}
#define PHPDBG_ELEMENT_END \
	{NULL, 0L, 0}

#define PHPDBG_COLOR_INVALID	-1
#define PHPDBG_COLOR_PROMPT 	 0
#define PHPDBG_COLOR_ERROR		 1
#define PHPDBG_COLOR_NOTICE		 2
#define PHPDBG_COLORS			 3

typedef struct _phpdbg_color_t {
	char       *name;
	size_t      name_length;
	const char  code[PHPDBG_COLOR_LEN];
} phpdbg_color_t;

typedef struct _phpdbg_element_t {
	char		*name;
	size_t		name_length;
	int			id;
} phpdbg_element_t;

PHPDBG_API const phpdbg_color_t *phpdbg_get_color(const char *name, size_t name_length TSRMLS_DC);
PHPDBG_API void phpdbg_set_color(int element, const phpdbg_color_t *color TSRMLS_DC);
PHPDBG_API void phpdbg_set_color_ex(int element, const char *name, size_t name_length TSRMLS_DC);
PHPDBG_API const phpdbg_color_t *phpdbg_get_colors(TSRMLS_D);
PHPDBG_API int phpdbg_get_element(const char *name, size_t len TSRMLS_DC); /* }}} */

/* {{{ Prompt Management */
PHPDBG_API void phpdbg_set_prompt(const char* TSRMLS_DC);
PHPDBG_API const char *phpdbg_get_prompt(TSRMLS_D); /* }}} */

/* {{{ Console Width */
PHPDBG_API int phpdbg_get_terminal_width(TSRMLS_D); /* }}} */

PHPDBG_API void phpdbg_set_async_io(int fd);

int phpdbg_rebuild_symtable(TSRMLS_D);

#if PHP_VERSION_ID < 50500
/* copy from zend_hash.c PHP 5.5 for 5.4 compatibility */
static void zend_hash_get_current_key_zval_ex(const HashTable *ht, zval *key, HashPosition *pos) {
	Bucket *p;

	p = pos ? (*pos) : ht->pInternalPointer;

	if (!p) {
		Z_TYPE_P(key) = IS_NULL;
	} else if (p->nKeyLength) {
		Z_TYPE_P(key) = IS_STRING;
		Z_STRVAL_P(key) = IS_INTERNED(p->arKey) ? (char*)p->arKey : estrndup(p->arKey, p->nKeyLength - 1);
		Z_STRLEN_P(key) = p->nKeyLength - 1;
	} else {
		Z_TYPE_P(key) = IS_LONG;
		Z_LVAL_P(key) = p->h;
	}
}
#endif

int phpdbg_safe_class_lookup(const char *name, int name_length, zend_class_entry ***ce TSRMLS_DC);

char *phpdbg_get_property_key(char *key);

typedef int (*phpdbg_parse_var_func)(char *name, size_t len, char *keyname, size_t keylen, HashTable *parent, zval **zv TSRMLS_DC);
typedef int (*phpdbg_parse_var_with_arg_func)(char *name, size_t len, char *keyname, size_t keylen, HashTable *parent, zval **zv, void *arg TSRMLS_DC);

PHPDBG_API int phpdbg_parse_variable(char *input, size_t len, HashTable *parent, size_t i, phpdbg_parse_var_func callback, zend_bool silent TSRMLS_DC);
PHPDBG_API int phpdbg_parse_variable_with_arg(char *input, size_t len, HashTable *parent, size_t i, phpdbg_parse_var_with_arg_func callback, zend_bool silent, void *arg TSRMLS_DC);

#endif /* PHPDBG_UTILS_H */
