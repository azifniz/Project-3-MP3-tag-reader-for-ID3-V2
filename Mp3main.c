/*
NAME : Azif Nizam
BATCH : 25021A
REG NO : 25021A_008 
DATE : 9-11-2025

PROJECT NAME : MP3 TAG READER
DESCRIPTION : A command-line application developed in C that extracts and displays metadata
             (ID3 tags) from MP3 audio files, such as title, artist, album, year, and genre.
             The project implements file handling, bitwise operations, and structured programming
             concepts to read, modify, and update tag information efficiently. It follows a modular
             design with separate header and source files for better readability and maintainability.

*/

#include <stdio.h>
#include<string.h>
#include "operations.h"
#include "types.h"


int main(int argc, char *argv[])
{
    storage stv;                                                                  //creating a structure variable stv
    if (check_operation_type(argv) == e_help)                                     //for help
    {
        help();
    }
    else if (check_operation_type(argv) == e_view)                                //for view
    {
        if(validate_v_args(argv,&stv) == e_success)
        {
            if(view(&stv) != e_success)
            {
                printf(">> Error : View details failed\n");
            }
        }
    } 
    else if (check_operation_type(argv) == e_edit)                                //for edit 
    {
        if(validate_e_args(argv,&stv) == e_success)
        {
            if (edit(&stv) != e_success)
            {
                printf(">> Error : Edit details failed\n");
            }
        }
    }  
    else
    {
        printf(">> Error : Invalid/Missing Arguments \n");
        printf("## for help please pass : ./a.out -h\n");
    }
}

OperationType check_operation_type(char *argv[])                                  //to check whether the help/view/edit             
{
    if(argv[0] == NULL || argv[1] == NULL )
    {
        return e_unsupported ;
    }

    if(strcmp(argv[1],"-h") == 0)                                               // '-h' for help
    {
        return e_help;
    }
    else if(strcmp(argv[1],"-v") == 0)                                          // '-v' for view
    {
        return e_view;
    }
    else if (strcmp(argv[1],"-e") == 0)                                         // '-e' for edit
    {
        return e_edit;
    }
    else
    {
        return e_unsupported ;
    }
}