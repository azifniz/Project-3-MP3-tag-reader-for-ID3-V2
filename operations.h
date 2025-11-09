#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "types.h"

typedef struct _storage
{ 
    char *mp3_fname_e ;
    FILE *fptr_mp3_e ;

    char *tag;
    char *new_value;

    char *mp3_fname_dupe;
    FILE *fpter_mp3_dupe;
   
}storage ;


OperationType check_operation_type(char *argv[]);

status validate_v_args(char *argv[], storage *st);

status validate_e_args(char *argv[], storage *st);

status open_files(storage *st);

status open_files_e(storage *st);

void help();

status view(storage *st);

status edit(storage *st);

#endif

