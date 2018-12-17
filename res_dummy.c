/*** MODULEINFO
    <support_level>extended</support_level>
***/

#include "asterisk.h"

ASTERISK_FILE_VERSION(__FILE__, "$Revision: 1 $")

#include "asterisk/module.h"
#include "asterisk/logger.h"
#include "asterisk/pbx.h"
#include "asterisk/xmldoc.h"


#define AST_MODULE "app_dummy"


static char *name_dummy = "Dummy";
static char *syn_dummy = "Synopsis about Dummy";
static char *des_dummy = "Description. Dummy application. Do nothing\n";


static int app_dummy(struct ast_channel *chan, const char *data) {
    ast_log(LOG_NOTICE, "Dummy App: %s\n", data);
}


static int func_dummy_read(struct ast_channel *chan, const char *cmd, char *data,
                           char *buf, size_t len) {
    ast_log(LOG_NOTICE, "Dummy func read: %s = %s", data, buf);

    return 0;
}

static int func_dummy_write(struct ast_channel *chan, const char *cmd, char *data, const char *value) {
    ast_log(LOG_NOTICE, "Dummy func write: %s = %s\n", data, value);

    return 0;
}


static struct ast_custom_function dummy_function = {
        .name = "DUMMY",
        .read = func_dummy_read,
        .write=func_dummy_write,
        .read_max = 33,
        .desc="Description here",
        .synopsis="Synopsis hele",
        .syntax="Syntax here",
        .arguments="Arguments here",
        .seealso="See also here",
        .docsrc=1,


};

static int load_module(void) {
    int res;
    ast_log(LOG_NOTICE, "Hello Dummy\n");
    res = ast_register_application(name_dummy, app_dummy, syn_dummy, des_dummy);
    res = ast_custom_function_register(&dummy_function);
    return AST_MODULE_LOAD_SUCCESS;
}

static int unload_module(void) {
    int res;
    ast_log(LOG_NOTICE, "Goodbye Dummy\n");
    res = ast_unregister_application(name_dummy);
    res = ast_custom_function_unregister(&dummy_function);
    return AST_MODULE_LOAD_SUCCESS;
}


AST_MODULE_INFO_STANDARD(ASTERISK_GPL_KEY, "Dummy Module");