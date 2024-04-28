#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <fields.h>
#include <jval.h>
#include <dllist.h>

bool isInteger(const char *input) {
    int num;
    return sscanf(input, "%d", &num) == 1;
}

int main(int argc, char **argv) {
    IS is;
    int i , Sayac=0,strLength=0;

    Dllist l;
    l = new_dllist(); // Initialize the dllist this one will store the character and how many time will be written

    Dllist node, tmp,cursor ,NPtr; // Use 'node' for traversal and other operations
    cursor = (Dllist) malloc (sizeof(struct dllist));
    NPtr = (Dllist) malloc (sizeof(struct dllist));

    //sil dll
    Dllist lsil;// this store the char whos will be deleted from the l list
    const char *Commands[] = {"yaz:", "sil:", "sonagit:", "dur:"};
    bool yaz = false, sil = false, sonagit = false, dur = false, SyntaxError = false;
    int result; // it used to compare txts while checking the commands
      char *filename;
      char *outPutFilename;

    FILE  *outputFile;
    if (argc > 1) {
        filename = argv[1];
        printf("Input file provided: %s\n", filename);
    } else {
        printf("You haven't entered the input file; it will be set automatically to 'txt/input.txt'\n");
        filename = "txt/input.txt";  // Default input file
    }

    if (argc > 2) {
        outPutFilename = argv[2];
        printf("Output file provided: %s\n", outPutFilename);
    } else {
        printf("You haven't entered the output file; it will be set automatically to 'txt/output.txt'\n");
        outPutFilename = "txt/output.txt";  // Default output file
    }  
   
    is = new_inputstruct(filename);
    if (is == NULL) {
        perror(filename);
        exit(1);
    }
    outputFile = fopen(outPutFilename, "w");
    if (outputFile == NULL) {
        perror("Error opening output file");
        fclose(outputFile);  // Important to close inputFile if outputFile fails
        return EXIT_FAILURE;
    }
    while (get_line(is) >= 0 ) {
        if(dur||SyntaxError)// if the dur has been read quit the loop
            break;
        yaz = false, sil = false, sonagit = false, dur = false;
        lsil = new_dllist();
       
        for (i = 0; i < is->NF; i++) {

            if (is->NF == 0) continue;  // Skip processing if no fields

            if (i == 0) {  // Check commands only in the first word
                for (int x = 0; x < 4; x++) {
                    result = strcmp(is->fields[i], Commands[x]);
                    if (result == 0) {
                        switch (x) {
                            case 0: yaz = true; break;
                            case 1: sil = true; break;
                            case 2: //sonagit
                                    cursor = l-> blink; sonagit = true;
                                                break;
                            case 3: dur = true; break;
                        }
                    }
                    
                }
                if((yaz + sil + sonagit + dur) == 0 ){
                    SyntaxError = true;
                    break;
                }
            } else {
                if(i%2!=0)
                {
                    //it should be an int
                    if(isInteger(is->fields[i])==false){
                        SyntaxError = true;
                }
                }
                else
                {
                    //it should be a txt
                     if(isInteger(is->fields[i])==true){
                        SyntaxError = true;
                }}
                if (yaz) {
                    if(dll_empty(l)==1)//the list is empty
                    {
                        dll_append(l, new_jval_s(strdup(is->fields[i])));
                        cursor = dll_first(l);
                    }
                    else{
                    //insert after the cursor
                    dll_insert_a(cursor, new_jval_s(strdup(is->fields[i])));
                    cursor=cursor->flink;
                    }}
                //deleting from the dllist
                if (sil) {
                        dll_append(lsil, new_jval_s(strdup(is->fields[i])));
                }
                if(dur)
                {
                    break;
                }
            }
        }
        if(sil == true && dll_empty(l)!=1 && dll_empty(lsil) != 1){
        //do delete here
        int times;// how much should be deleted
        char* delchar;//the character will be deleted
        int sayac=0; // 
        int control = 0;//let the cursor look 2 times for the node because the cursor maybe at the 2nd loop and it will not make him able to look to all the nodes  
        Dllist TmpLsil;
         dll_traverse(node, lsil) {
            if(sayac %2 == 0)
                times=atoi(jval_s(node->val));
            else
            {
                delchar= jval_s(node->val);
                //deleting from l
                cursor = l-> blink;// make the cursor start from the back
                NPtr = l->flink;//apprnding the first node of the list to it sentinel node
                while (true)
                {
                     if(cursor->val.s==NULL)
                     {
                     cursor = cursor->blink;
                     control++;

                      if (control >= 2) {  // Adjust control limit as necessary
                          control = 0;
                          break;
                      }
                     }
                    if(strcmp(delchar,cursor->val.s) == 0)
                    {
                        //get to previos node to substact the times
                        cursor = cursor->blink;
                        int ChrTime = atoi(cursor->val.s);
                      if(ChrTime == times)
                      {
                             tmp = cursor ;
                            cursor=cursor->flink;
                            dll_delete_node(tmp);
                            tmp = cursor;
                            cursor=cursor->blink;
                            dll_delete_node(tmp);
                            break;
                      }
                      else if(ChrTime > times)
                      {
                        ChrTime -= times;
                        snprintf(cursor->val.s,sizeof(cursor->val.s),"%d",ChrTime);//append the new value to nodes value
                            cursor=cursor->blink;
                        break;
                      }
                      else if (ChrTime < times)//if(time>chrTime) the times is still bigger then the exist time it will keep looking
                      {
                              times -=  ChrTime;
                                tmp = cursor ;
                            cursor=cursor->flink;
                            dll_delete_node(tmp);
                            tmp = cursor;
                            cursor=cursor->blink;
                            dll_delete_node(tmp);
                      }
                    }
                     else{
                        cursor = cursor->blink;
                      if (control >= 2) {  // Adjust control limit as necessary
                           control = 0;
                            break;
                            }
                        if(cursor->val.s == NULL)
                            control++;
                     }
                }
            }
            sayac++;

        }
        }
        //Freeing the dll sil list
    dll_traverse(node, lsil) {  
        free(jval_s(node->val));
    }
    free_dllist(lsil);

    }
   
    //if their is not any syntax error in the file do the print 
    //else stop the program and give a note to the user 
    if(SyntaxError == false){
    //getting the length of the output Atring by adding all the nodes that contain int 
    dll_traverse(node, l) {
    ///getting the length of the OUTPUTstring
    if(Sayac%2==0)
    strLength += atoi(node->val.s);
    Sayac++;
    }
    Sayac = 0;
    int times;
    char * outputStr;
    char* str;
    // creting a pointer in the heap with the stinglength 
    outputStr = (char *) malloc(sizeof(char)*(strLength+1));
    
    strcpy(outputStr,"");
     dll_traverse(node, l) {
        //due to specail syntax the int values will be always at even number of the linked list
        if(Sayac%2 == 0)
            times = atoi(node->val.s);
            else{
            if(strcmp(node-> val.s,"\\b")==0)
                str=" ";
            else if(strcmp(node-> val.s,"\\n")==0)
                str="\n";
                else
            str= node-> val.s;
            //adding a chat with its specified time
            for(i = 0 ; i < times ; i++) strcat(outputStr+i,str);
            }
        Sayac++;
    }   
    //writning the output into output.txt file
    fprintf(outputFile, "%s", outputStr);
    // Close the output file
    fclose(outputFile);
    }
    else
    {
        printf("\nTHERE IS A SYNTAX ERROR PLEASE CHECK THE INPUT FILE\n");
    }
    // Free up dllists and inputstruct resources
    dll_traverse(node, l) {
        free(jval_s(node->val));
    }
    free_dllist(l);
    jettison_inputstruct(is);
    free(cursor);
    free(NPtr);


    return 0;
}
