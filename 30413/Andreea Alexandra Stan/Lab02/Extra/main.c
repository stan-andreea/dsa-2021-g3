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
    if (f==NULL)
    {
        printf("Cannot open the file");
        exit(0);
    }
    return f;
}


//function to create an initial empty list:
ListT *createEmptyList()
{
    ListT *listPtr = (ListT*)malloc(sizeof(ListT));
    if (listPtr)
    {
        listPtr->count = 0;
        listPtr->first = listPtr->last = NULL;
    }
    return listPtr;
}

//function to check it the list is empty
int isEmpty( ListT *listPtr )
{
    return listPtr->first == NULL;
}


//function to insert a node at the front of the list:
int insertAtFront(ListT *listPtr, NodeT *p)
{
    if (listPtr)
    {

        p->next = listPtr->first;
        if (isEmpty(listPtr))
        {
            listPtr->last = p;
        }
        listPtr->first = p;
        listPtr->count++;
        return 1;
    }
    return 0;
}

//function to insert a node at the end of the list:
int insertAtRear(ListT *listPtr, NodeT *p)
{
    if (listPtr)
    {

        if (isEmpty(listPtr))
        {

            listPtr->first = p;
        }
        else
        {

            listPtr->last->next = p;
        }
        listPtr->last = p;
        listPtr->count++;
        return 1;
    }
    return 0;
}


//function to delete all elements of the list:
void purge(ListT *listPtr)
{
    NodeT *p;
    while ( listPtr->first != NULL )
    {
        p = listPtr->first;
        listPtr->first = listPtr->first->next;
        free( p );
    }
    listPtr->last = NULL;
    listPtr->count = 0;
}


//print the list in the file
void print(ListT *listPtr,FILE *pf)
{
    NodeT *p;
    p = listPtr->first;
    if(p == NULL)
        fprintf(pf,"none");//the list is empty
    else
    {

        while (p!= NULL )
        {
            fprintf(pf,"%d ",p->key);

            p = p->next;
        }
        fprintf(pf,"\n");
    }
}

//print the first nr elements of the list in the file
void print_f(ListT *listPtr,int nr,FILE *pf)
{
    NodeT *p;
    int k=0;
    p = listPtr->first;
    if(p == NULL)
        printf("none");//the list is empty
    else
    {

        while (p!= NULL && k<nr)
        {
        fprintf(pf,"%d ",p->key);
            k++;

            p = p->next;
        }
        fprintf(pf,"\n");
    }
}


//print the last nr elements of the list in the file
void print_l(ListT *listPtr,int nr, FILE *pf)
{
    NodeT *p;
    int k;
    k=listPtr->count-nr;
    p = listPtr->first;

    if(p == NULL)
        fprintf(pf,"The list is empty");//the list is empty
    else
    {

        while (p!= NULL && k>0)
        {
            k--;

            p = p->next;
        }

        while (p!= NULL)
        {
            fprintf(pf,"%d ",p->key);

            p = p->next;
        }
        fprintf(pf,"\n");
    }
}


//function to create a node - here used when we insert in the list:

NodeT *createNode(int key)
{
    NodeT *p = (NodeT *)malloc(sizeof(NodeT));
    if (p)
    {
        p->key = key;
        p->next = NULL;
    }
    return p;
}

//function to search for a specific number in a list:
int find(ListT *listPtr, int nr)
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


//function to delete a given number from a list:

void deleteByKey(ListT *listPtr, int givenKey)
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
        listPtr->count--;

    }


}

//function to delete the first element of the list:
NodeT *deleteFirst(ListT *listPtr)
{
    NodeT *p;
    if ( listPtr->first != NULL )
    {
        p = listPtr->first;
        listPtr->first = listPtr->first->next;
        free( p ); // free up memory
        listPtr->count--; // decrease the number of nodes
        if ( listPtr->first == NULL ) // list is now empty
            listPtr->last = NULL;
        return p;
    }
    return NULL;
}


//function to delete the last element of the list
NodeT *deleteLast(ListT *listPtr)
{
    NodeT *q, *q1;
    q1 = NULL; /* initialize */
    q = listPtr->first;
    if ( q != NULL )
    {

        while ( q != listPtr->last )
        {
            q1 = q;
            q = q->next;
        }
        if ( q == listPtr->first )
        {
            /* only one node */
            listPtr->first = listPtr->last = NULL;
        }
        else
        {

            q1->next = NULL;
            listPtr->last = q1;
        }
        free( q );
        listPtr->count--;
    }

    return q;
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



int main()
{


    ListT *list= createEmptyList(); //create an empty list


    FILE *f, *pf;
    f=openAndCheck("input.dat", "r");
    pf=openAndCheck("output.dat", "w");

    //count the number of commands given in the file by counting the lines:

    int lines=1;
    char c;

    c=fgetc(f);
    while(c!=EOF)
    {
        if(c=='\n') lines++;
        c=fgetc(f);
    }

    rewind(f);


    int  x;
    char command[20],s[10];
    for(int i=0; i<lines; i++)
    {
        fscanf(f,"%s", command);

        c=fgetc(f);
        if(c==' ') fscanf(f,"%s",s);
        //if the next character is a space, skip it to obtain the number,otherwise, there is no number in the command


        x=getnr(s);

        /* printf("after command: ");
         print(list);
        // printf("\n");
         printf("number of elements: %d\n",list->count);*/


        if(strcmp(command,"AF")==0)
            insertAtFront(list,createNode(x));

        else if(strcmp(command,"AL")==0)
            insertAtRear(list,createNode(x));



        else if(strcmp(command,"DF")==0)
            deleteFirst(list);

        else if(strcmp(command,"DL")==0)
            deleteLast(list);

        else if(strcmp(command,"DE")==0)
            deleteByKey(list,x);



        else if(strcmp(command,"PRINT_ALL")==0)
        {
            print(list,pf);

        }

        else if(strcmp(command,"PRINT_F")==0)
        {
            if(x>list->count) print(list,pf);
            else
                print_f(list,x,pf);
        }

        else if(strcmp(command,"PRINT_L")==0)
        {
            if(x>list->count) print(list,pf);
            else
                print_l(list,x,pf);
            //this might be tricky because we have to go first trough the first list->count-x number of elements from the list
            //then print the remaining elements,which will be exactly the last x elements of the list
            //this is probably not the best approach because I went trough the entire list only to print the last x element
        }


        else if(strcmp(command,"DOOM_THE_LIST")==0)
            purge(list);

    }


    //close all the files
    fclose(pf);
    fclose(f);
    //free the memory
    free(list);


    return 0;
}
