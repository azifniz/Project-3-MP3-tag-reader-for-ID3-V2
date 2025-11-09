#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include "operations.h"

status validate_v_args(char *argv[], storage *st)                                //validate arguments for view
{
    if(argv[2] == NULL)                                          
    {
        printf(">> Error : MP3 file is not present\n");
        return e_failure ;
    }
    else if(strstr(argv[2],".mp3") != NULL)
    {
         st->mp3_fname_e = argv[2];
    }
    else
    {
        printf(">> Error : Invalid file. Argument 2 must be a mp3 file\n");
        return e_failure;
    }

    return e_success ;
}

status validate_e_args(char *argv[], storage *ste)                               //validate arguments for edit
{
    //to check for which edit option
    if(argv[2] == NULL)                                          
    {
        printf(">> Error : Editing argument is not present\n");
        printf("## Please pass tag argument which you want to edit\n");
        printf("   Eg : ./a.out -e -t/-a/-A/-y/-g/-c \"new value\" mp3filename\n");
        printf("   -t Modifies Title tag \n");
        printf("   -a Modifies Artist tag \n");
        printf("   -A Modifies Album tag \n");
        printf("   -y Modifies Year tag \n");
        printf("   -c Modifies Comment tag \n");
        printf("   -g Modifies Genre tag \n");
        printf("   -h Displays this help info \n");

        return e_failure ;
    }
    else if(strstr(argv[2],"-t") != NULL)
    {
         ste->tag = "TIT2"  ;                                          // title  TIT2
    }
    else if(strstr(argv[2],"-a") != NULL)
    {
         ste->tag = "TPE1"  ;                                          // artist  TPE1
    }
    else if(strstr(argv[2],"-A") != NULL)
    {
         ste->tag = "TALB"  ;                                          // album   TALB
    }
    else if(strstr(argv[2],"-y") != NULL)
    {
         ste->tag = "TYER"  ;                                          // year   TYER
    }
    else if(strstr(argv[2],"-g") != NULL)                           
    {
         ste->tag = "TCON"  ;                                          // genre TCON
    }
    else if(strstr(argv[2],"-c") != NULL)                           
    {
         ste->tag = "COMM"  ;                                          // language COMM                     
    }
    else
    {
        printf(">> Error : Invalid tag\n");
        printf("## Please pass tag argument which you want to edit\n");
        printf("   Eg : ./a.out -e -t/-a/-A/-y/-g/-c \"new value\" mp3filename\n");
        printf("   -t Modifies Title tag \n");
        printf("   -a Modifies Artist tag \n");
        printf("   -A Modifies Album tag \n");
        printf("   -y Modifies Year tag \n");
        printf("   -c Modifies Comment tag \n");
        printf("   -g Modifies Genre tag \n");
        printf("   -h Displays this help info \n");

        return e_failure;
    }

    //for new content
    if(argv[3] == NULL)                                          
    {
        printf(">> Error : new value is not present\n");
        printf("## please add the new value inside double quotes\n");
        return e_failure ;
    }
    else 
    {
         ste->new_value = argv[3];
    }
    
    //for mp3 file
    if(argv[4] == NULL)                                          
    {
        printf(">> Error : MP3 file is not present\n");
        return e_failure ;
    }
    else if(strstr(argv[4],".mp3") != NULL)
    {
         ste->mp3_fname_e = argv[4];
    }
    else
    {
        printf(">> Error : Invalid file. Argument 4 must be a mp3 file\n");
        return e_failure;
    }

    return e_success ;
}

void help()                                                                             //help function
{
    printf("----------------------------------MP3 Tag Reader Help--------------------------------\n\n");
    printf("## To view please pass : ./a.out -v mp3filename\n");
    printf("## To edit please pass : ./a.out -e -t/-a/-A/-y/-g/-c \"new value\" mp3filename\n");
    printf("-t Modifies Title tag \n");
    printf("-a Modifies Artist tag \n");
    printf("-A Modifies Album tag \n");
    printf("-y Modifies Year tag \n");
    printf("-c Modifies Comment tag \n");
    printf("-g Modifies Genre tag \n");
    printf("-h Displays this help info \n");
    printf("-------------------------------------------------------------------------------------\n");
}

status open_files(storage *stv)                                                  //to open files for view function
{
    stv->fptr_mp3_e = fopen(stv->mp3_fname_e,"rb");
    if (stv->fptr_mp3_e == NULL)
    {
        return e_failure;
    }

    return e_success;
}

status open_files_e(storage *ste)                                               //to open files for edit function
{
    ste->fptr_mp3_e = fopen(ste->mp3_fname_e,"rb");                             // read mode original file
    if (ste->fptr_mp3_e == NULL)
    {
        return e_failure;
    }

    ste->mp3_fname_dupe = "dupe_file.mp3"   ;                                   // to create a duplicate file name
    ste->fpter_mp3_dupe = fopen(ste->mp3_fname_dupe,"wb");                      // write mode duplicate file
    if (ste->fpter_mp3_dupe == NULL)
    {
        return e_failure;
    }

    return e_success;
}

status view(storage *stv)                                                       //view function
{
    if (open_files(stv) != e_success)
    {
        printf(">> Error : Failed to open files\n");
        return e_failure;
    }
    
    fseek(stv->fptr_mp3_e, 10, SEEK_SET);                                             // skip  header

    printf("---------------------------------------------------------------------\n");
    printf("         MP3 TAG READER AND EDITOR FOR ID3 V2       \n");
    printf("---------------------------------------------------------------------\n");

    for (int i = 1; i <= 6; i++)
    {
        char tag[5];                                                                // temp buffer
        unsigned char size_buf[4];                                                  // temp buffer
        unsigned int conv_size;                                                     // temp buffer

        fread(tag, 4, 1, stv->fptr_mp3_e);                                            // reading tag
        tag[4] = '\0';
    
        fread(size_buf, 4, 1, stv->fptr_mp3_e);                                       // reading size
        conv_size = (size_buf[0] << 24) | (size_buf[1] << 16) | (size_buf[2] << 8) | (size_buf[3]);  //convert big endian to little endian

        fseek(stv->fptr_mp3_e, 2, SEEK_CUR);                                          // skip flags

        char *data = malloc(conv_size + 1);                                         // memmory for reading data
        if (data == NULL)
        {
            printf(">> Error: Memory allocation to read data failed\n");
            return e_failure;   
        }
        fread(data, conv_size, 1, stv->fptr_mp3_e);                                   // reading data
        data[conv_size] = '\0';

        if(strcmp(tag, "TIT2") == 0)                                                //printing the tags
        {
            printf("# Title           : %s\n",data + 1);
        }
        else if (strcmp(tag, "TPE1") == 0)
        {
            printf("# Artist          : %s\n",data + 1);
        }
        else if (strcmp(tag, "TALB") == 0)
        {
            printf("# Album           : %s\n",data + 1);
        }
        else if (strcmp(tag, "TYER") == 0)
        {
            printf("# Year            : %s\n",data + 1);
        }
        else if (strcmp(tag, "TCON") == 0)
        {
            printf("# Genre           : %s\n",data + 1);
        }
        else if (strcmp(tag, "COMM") == 0)
        {
            printf("# Language        : %s\n",data + 1);
        }                                         
    }
    printf("---------------------------------------------------------------------\n");

    fclose(stv->fptr_mp3_e);                                                              //closing the file

    return e_success ;
}

status edit(storage *ste)                                                               //edit function 
{   
    if (open_files_e(ste) != e_success)
    {
        printf(">> Error : Failed to open files\n");
        return e_failure;
    }

    char header[10];                                                         //temp buffer
    
    fseek(ste->fptr_mp3_e, 0, SEEK_SET);
    fseek(ste->fpter_mp3_dupe, 0, SEEK_SET);

    //copying the header of mp3 file
    fread(header, 10, 1, ste->fptr_mp3_e);                                   //first 10 bytes are header of mp3 file file
    fwrite(header, 10, 1, ste->fpter_mp3_dupe);

    for (int i=1; i<=6; i++)
    {
        char tag[5];                                                        //tag buffer
        unsigned char raw_size[4];                                          //size buffer
        unsigned int conv_size;                                             //converted size buffer
        char flag[2];                                                       //flag buffer

        fread(tag, 4, 1, ste->fptr_mp3_e);                                  //reading the tag
        tag[4] = '\0';

        fread(raw_size, 4, 1, ste->fptr_mp3_e) ;                            //reading the size 
        conv_size = (raw_size[0] << 24) | (raw_size[1] << 16) |(raw_size[2] << 8)  | (raw_size[3]);   //converting big endian to little endian to read the data

        fread(flag, 2, 1, ste->fptr_mp3_e);                                 //reading the flag

        char *data = malloc(conv_size + 1);                                 //array to store the data
        if (!data) 
        { 
            printf("malloc failed\n"); 
            return e_failure; 
        }
        fread(data, conv_size, 1, ste->fptr_mp3_e);                         //reading the data
        data[conv_size] = '\0';

        if (strcmp(tag, ste->tag) == 0)                                     //if the tags matches 
        {  
            size_t text_len = strlen(ste->new_value);
            size_t new_frame_size = text_len + 1;                           // +1 for encoding byte ie null 
            unsigned int sz = (unsigned int)new_frame_size;
            
            //converting size of the new value to big endian
            unsigned char size_conv[4];
            size_conv[0] = (sz >> 24) & 0xFF;
            size_conv[1] = (sz >> 16) & 0xFF;
            size_conv[2] = (sz >> 8) & 0xFF;
            size_conv[3] = sz & 0xFF;

            //writing the tag, size , flag and data to the duplicate file 
            fwrite(tag, 4, 1, ste->fpter_mp3_dupe);
            fwrite(size_conv, 4, 1, ste->fpter_mp3_dupe);
            fwrite(flag, 2, 1, ste->fpter_mp3_dupe);

            unsigned char encoding = 0x00;                                 //after flag comes the encoding byte
            fwrite(&encoding, 1, 1, ste->fpter_mp3_dupe);
            fwrite(ste->new_value, text_len, 1, ste->fpter_mp3_dupe);

            printf("## Data edited successfully \n");
        }
        else
        {
            //write original tag, original  size , flags and data to the duplicate file 
            fwrite(tag, 4, 1, ste->fpter_mp3_dupe);
            fwrite(raw_size, 4, 1, ste->fpter_mp3_dupe);
            fwrite(flag, 2, 1, ste->fpter_mp3_dupe);
            fwrite(data, conv_size, 1, ste->fpter_mp3_dupe);
        }

        free(data);

    }

    //to copy the remaining data
    char rem_data;                                                                          // temp buffer
    while (fread(&rem_data, 1, 1, ste->fptr_mp3_e) == 1)
    {
        fwrite(&rem_data, 1, 1, ste->fpter_mp3_dupe);
    }
    
    fclose(ste->fptr_mp3_e);
    fclose(ste->fpter_mp3_dupe);

    // make a backup of the original
    rename(ste->mp3_fname_e, "backup_original.mp3");

    // rename the edited duplicate to original name
    rename(ste->mp3_fname_dupe, ste->mp3_fname_e);
    
    return e_success;
}