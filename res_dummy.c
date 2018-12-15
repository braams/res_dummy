/*** MODULEINFO
    <support_level>extended</support_level>
***/

#include "asterisk.h"
ASTERISK_FILE_VERSION(__FILE__, "$Revision: 1 $")
#include <asterisk/module.h>
#include "asterisk/logger.h"

#define AST_MODULE "app_dummy"


static char *name_dummy = "Dummy";
static char *syn_dummy = "Synopsis about Dummy";
static char *des_dummy = "Description. Dummy application. Do nothing\n";


static int app_dummy(struct ast_channel *chan, const char *data) {

}



static int load_module(void)
{
    int res;
    ast_log(LOG_NOTICE, "Hello Dummy\n");
    res=ast_register_application(name_dummy, app_dummy, syn_dummy, des_dummy);
    return AST_MODULE_LOAD_SUCCESS;
}

static int unload_module(void)
{
    int res;
    ast_log(LOG_NOTICE, "Goodbye Dummy\n");
    res = ast_unregister_application(name_dummy);
    return AST_MODULE_LOAD_SUCCESS;
}


AST_MODULE_INFO_STANDARD(ASTERISK_GPL_KEY, "Dummy Module");