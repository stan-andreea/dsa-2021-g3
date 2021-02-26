#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    int key;
    struct node *next;
} NodeT;

typedef struct
{
    int count;
    NodeT *first; /* link to the first node in the list */
    NodeT *last; /* link to the last node in the list */
} ListT;


//function to open and check a file:
FILE *openAndCheck(char *filePath, char *mode)
{
    FILE *f = fopen(filePath, mode);
    if (NULL == f)
    {
        printf("Cannot open the file");
        exit(0);
    }
    return f;
}



ListT *createEmptyList() //function to create an initial empty list
{
    ListT *listPtr = (ListT*)malloc(sizeof(ListT));
    if (listPtr)
    {
        listPtr->count = 0;
        listPtr->first = listPtr->last = NULL;
    }
    return listPtr;
}

int isEmpty( ListT *listPtr )//check it the list is empty
{
    return listPtr->first == NULL;
}


int insertAtFront(ListT *listPtr, NodeT *p) //function to insert a node at the front of the list
{

    if (listPtr)
    {

        p->next = listPtr->first;
        if (listPtr==NULL)
        {

            listPtr->last = p;
        }
        listPtr->first = p;
        listPtr->count++;
        return 1; // success
    }
    return 0; // failure
}

int insertAtEnd(ListT *listPtr, NodeT *p)//function to insert a node at the end of the list
{
    if (listPtr)
    {

        if (listPtr->first==NULL)
        {
            listPtr->first = p;
        }
        else
        {
            listPtr->last->next = p;
        }
        listPtr->last = p;
        listPtr->count++;
        return 1; // success
    }
    return 0; // failure
}




void print(ListT *listPtr, FILE *pf)//print the list in the file
{
    NodeT *p;
    p = listPtr->first;
    if(p == NULL)
        fprintf(pf,"none");
    else
    {

        while (p!= NULL )
        {
            fprintf(pf,"%d ",p->key);

            p = p->next;
        }
    }
}


NodeT *createNode(int key)//function to create a node-here used when we insert
{
    NodeT *p = (NodeT *)malloc(sizeof(NodeT));
    if (p)
    {
        p->key = key;
        p->next = NULL;
    }
    return p;
}

int find(ListT *listPtr, int nr)//function to search for a specific number in a list
{
    NodeT *p;
    p = listPtr->first;
    while ( p != NULL )
        if ( p->key == nr )
        {
            return 1; //key found
        }
        else
            p = p->next;
    return 0; //key not found

}


void deleteByKey(ListT *listPtr, int givenKey)//function to delete a given number from a list
{
    NodeT *q, *q1;
    q1 = NULL;
    q =listPtr->first;

    while ( q != NULL )
    {
        if ( q->key == givenKey ) break;
        q1 = q;
        q = q->next;
    }
    if ( q != NULL )
    {

        if ( q == listPtr->first )
        {

            listPtr->first = listPtr->first->next;
            free( q );
            if ( listPtr->first == NULL ) listPtr->last = NULL;
        }
        else
        {

            q1->next = q->next;
            if ( q == listPtr->last ) listPtr->last = q1;
            free( q );
        }

    }

}



//function to extract the number from a given string:
int getnr(char s[])
{
    int k=0;
    for(int i=0; i<strlen(s); i++)
        if(strchr("0123456789",s[i])!=NULL)

            k=k*10+s[i]-'0';

    return k;
}

int main(int argc, char* argv[])
{
     if (argc < 2)
         {
             printf("No file name given\n");
             exit(1);
         }



    ListT *garage = createEmptyList(); //create an empty list for the cars in the garage


    ListT *road = createEmptyList(); //create an empty list for the cars on the road


    FILE *f, *pf;
    f=openAndCheck(argv[1], "r");  //argv[1]="commands.txt"
    pf=openAndCheck(argv[2], "w"); //argv[2]="data.txt"

    //count the number of commands given in the file:
    int lines=1;
    char c;
    c=fgetc(f);
    while(c!=EOF)
    {
        if(c=='\n') lines++;
        c=fgetc(f);
    }

    rewind(f);




    int  value;
    char choice[5];
    for(int i=0; i<lines; i++)
    {
        fscanf( f,"%s", choice );
        // printf("read string: %s\n\n\n", choice);

        value=getnr(choice);

        switch(choice[0])
        {
        case 'R':

            insertAtEnd(road,createNode(value));
            break;


        case 'E':

            if(find(road,value)==1)
            {
                insertAtEnd(garage,createNode(value));
                deleteByKey(road, value);

            }
            else fprintf(pf,"error: %d not on road!\n",value);
            break;



        case 'S':

            if(choice[2]=='G')
            {
                fprintf(pf,"G: ");
                print(garage,pf);
                fprintf(pf,"\n");
            }
            else if(choice[2]=='R')
            {
                fprintf(pf,"R: ");
                print(road,pf);
                fprintf(pf,"\n");
            }
            break;


        case 'X':

            if(find(garage,value)==1)
            {
                //check if the car can get out of the garage ie it must be the last who entered the garage:
                if(garage->first->key!=value) fprintf(pf,"error: %d not at exit!\n",value);
                else
                {
                    deleteByKey(garage, value);
                    insertAtFront(road,createNode(value));
                }
            }
            else fprintf(pf,"error: %d not in garage!\n",value);
            break;


        default:
            fprintf(pf,"The command %c is not valid",choice[0]);

        }

    }

    //close all the files
    fclose(pf);
    fclose(f);
    //free the memory
    free(garage);
    free(road);




    return 0;
}
