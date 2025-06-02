#ifndef OPENASIP_H
#define OPENASIP_H

#include <stdint.h>

void openasip_load_module(void);

typedef int unpackInstructionFn(const uint32_t opcode,
                                char **output,
                                char **error);
extern unpackInstructionFn *openasip_unpackInstruction;

typedef int executeInstruction32Fn(const char *opName,
                                   const uint32_t *inputs,
                                   const uint32_t inputs_count,
                                   uint32_t *output,
                                   char **error_msg);
extern executeInstruction32Fn *openasip_executeInstruction32;
typedef int executeInstruction64Fn(const char *opName,
                                   const uint64_t *inputs,
                                   const uint64_t inputs_count,
                                   uint64_t *output,
                                   char **error_msg);
extern executeInstruction64Fn *openasip_executeInstruction64;

typedef int initializeMachineFn(const char *machine_path, char **error);
extern initializeMachineFn *openasip_initializeMachine;

#endif
