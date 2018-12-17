/*** MODULEINFO
    <support_level>extended</support_level>
***/

#include "asterisk.h"

ASTERISK_FILE_VERSION(__FILE__, "$Revision: 1 $")

#include "asterisk/module.h"
#include "asterisk/logger.h"
#include "asterisk/pbx.h"
#include "asterisk/xmldoc.h"
#include "asterisk/strings.h"


#define AST_MODULE "app_dummy"


static char *name_dummy = "Dummy";
static char *syn_dummy = "Synopsis about Dummy";
static char *des_dummy = "Description. Dummy application. Do nothing\n";


static const struct ast_datastore_info dummy_datastore = {
        .type = "dummy",
};
struct dummy_data {
    char *value;
};

static int app_dummy(struct ast_channel *chan, const char *data) {
    ast_log(LOG_NOTICE, "Dummy App: data=%s\n", data);
}


static int func_dummy_read(struct ast_channel *chan, const char *cmd, char *data, char *buf, size_t len) {
    ast_log(LOG_NOTICE, "Dummy func read: cmd=%s, data=%s, buf=%s, len=%ld\n", cmd, data, buf, len);
    struct ast_datastore *datastore = NULL;
    struct dummy_data *dummy = NULL;
    char *val = NULL;
    if (!chan) {
        ast_log(LOG_WARNING, "No channel was provided to %s function.\n", cmd);
        return -1;
    }


    if (!(datastore = ast_channel_datastore_find(chan, &dummy_datastore, NULL))) {
        ast_log(LOG_NOTICE, "No datastore found\n");
        return -1;
    }

    dummy = datastore->data;
    ast_log(LOG_NOTICE, "From datastore: %s\n", dummy->value);
    snprintf(buf, len, "%s", dummy->value);


    return 0;
}

static int func_dummy_write(struct ast_channel *chan, const char *cmd, char *data, const char *value) {
    ast_log(LOG_NOTICE, "Dummy func write: cmd=%s, data=%s, value=%s\n", cmd, data, value);
    struct ast_datastore *datastore = NULL;
    struct dummy_data *dummy = NULL;
    int new = 0;

    if (!chan) {
        ast_log(LOG_WARNING, "No channel was provided to %s function.\n", cmd);
        return -1;
    }


    ast_channel_lock(chan);
    if (!(datastore = ast_channel_datastore_find(chan, &dummy_datastore, NULL))) {
        ast_channel_unlock(chan);

        if (!(datastore = ast_datastore_alloc(&dummy_datastore, NULL))) {
            return 0;
        }
        if (!(dummy = ast_calloc(1, sizeof(*dummy)))) {
            ast_datastore_free(datastore);
            return 0;
        }
        dummy->value = (char *) dummy + sizeof(*dummy);
        strcpy(dummy->value, value);

        ast_log(LOG_NOTICE, "New datastore created\n");

        datastore->data = dummy;
        new = 1;
    } else {
        ast_log(LOG_NOTICE, "Datastore already exists\n");
        ast_channel_unlock(chan);
        dummy = datastore->data;
        strcpy(dummy->value, value);
        datastore->data = dummy;

    }


    if (new) {
        ast_channel_lock(chan);
        ast_channel_datastore_add(chan, datastore);
        ast_channel_unlock(chan);

    }

    return 0;


}

static struct ast_custom_function dummy_function = {
        .name = "DUMMY",
        .read = func_dummy_read,
        .write=func_dummy_write,
        .read_max = 33,
        .desc="Description here",
        .synopsis="Synopsis here",
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