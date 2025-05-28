#include "qemu/osdep.h"
#include <glib.h>
#include <gmodule.h> 
#include <stdio.h>
#include "openasip.h"

unpackInstructionFn   *openasip_unpackInstruction   = NULL;
executeInstruction32Fn *openasip_executeInstruction32 = NULL;
executeInstruction64Fn *openasip_executeInstruction64 = NULL;
initializeMachineFn    *openasip_initializeMachine  = NULL;

static GModule *openasip_mod = NULL;

void openasip_load_module(void)
{
    if (openasip_mod) {
        return;
    }

    openasip_mod = g_module_open("libopenasip.so",
                                 G_MODULE_BIND_LAZY | G_MODULE_BIND_LOCAL);
    if (!openasip_mod) {
        fprintf(stderr, "openasip: cannot open libopenasip.so: %s\n",
                g_module_error());
        abort();
    }

    if (!g_module_symbol(openasip_mod, "unpackInstruction",
                         (gpointer)&openasip_unpackInstruction) ||
        !g_module_symbol(openasip_mod, "executeInstruction32",
                         (gpointer)&openasip_executeInstruction32) ||
        !g_module_symbol(openasip_mod, "executeInstruction64",
                         (gpointer)&openasip_executeInstruction64) ||
        !g_module_symbol(openasip_mod, "initializeMachine",
                         (gpointer)&openasip_initializeMachine))
    {
        fprintf(stderr, "openasip: missing symbol: %s\n", g_module_error());
        abort();
    }
}
