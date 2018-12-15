/*** MODULEINFO
    <support_level>extended</support_level>
***/

#include "asterisk.h"
ASTERISK_FILE_VERSION(__FILE__, "$Revision: 1 $")
#include <asterisk/module.h>
#include "asterisk/logger.h"

#define AST_MODULE "app_dummy"

static int load_module(void)
{
    ast_log(LOG_NOTICE, "Hello Dummy/n");
    return AST_MODULE_LOAD_SUCCESS;
}

static int unload_module(void)
{
    ast_log(LOG_NOTICE, "Goodbye Dummy/n");
    return AST_MODULE_LOAD_SUCCESS;
}


AST_MODULE_INFO_STANDARD(ASTERISK_GPL_KEY, "Dummy Module");