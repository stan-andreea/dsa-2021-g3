#include <stdio.h>
#include <stdlib.h>

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


//functions for the SLL

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


void print(ListT *listPtr,FILE *pf)
{
    NodeT *p;
    p = listPtr->first;
    if(p == NULL)
        fprintf(pf," \n");//the list is empty
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

//end of functions for the SLL


//print what's on the pegs and make sure the pegs are displayes in alphabetical order


void print_pegs(ListT *A, ListT *B, ListT *C, char a,char b,char c,FILE *pf)
{

    if(a<b && a<c)
    {
        fprintf(pf,"%c:",a);
        print(A,pf);

        if(b<c)
        {
            fprintf(pf,"%c:",b);
            print(B,pf);
            fprintf(pf,"%c:",c);
            print(C,pf);
        }
        else
        {
            fprintf(pf,"%c:",c);
            print(C,pf);
            fprintf(pf,"%c:",b);
            print(B,pf);

        }
    }
    else if (b<a && b<c)
    {
        fprintf(pf,"%c:",b);
        print(B,pf);
        if(a<c)
        {
            fprintf(pf,"%c:",a);
            print(A,pf);
            fprintf(pf,"%c:",c);
            print(C,pf);

        }
        else
        {

            fprintf(pf,"%c:",c);
            print(C,pf);
            fprintf(pf,"%c:",a);
            print(A,pf);
        }

    }
    else
    {
        fprintf(pf,"%c:",c);
        print(C,pf);

        if(a<b)
        {
            fprintf(pf,"%c:",a);
            print(A,pf);
            fprintf(pf,"%c:",b);
            print(B,pf);
        }
        else
        {

            fprintf(pf,"%c:",b);
            print(B,pf);
            fprintf(pf,"%c:",a);
            print(A,pf);
        }



    }


    fprintf(pf,"\n\n");
}


//recursive function to move the pegs from A to B, using C as an auxiliary
void tower(int n, ListT *A, ListT *B, ListT *C, char a,char b,char c, FILE *pf)
{
    if(n>0)
    {
        tower(n-1,A,C,B,a,c,b,pf);

        insertAtFront(B, createNode(A->first->key));
        deleteFirst(A);
        print_pegs(A,B,C,a,b,c,pf);

        tower(n-1,C,B,A,c,b,a,pf);

    }
}




int main(int argc, char* argv[])
{
    int n;


    FILE *fin, *fout;
    fin=openAndCheck(argv[1], "r");//argv[1]="input.txt"
    fout=openAndCheck(argv[2], "w");//argv[2]="output.txt"

    ListT *A= createEmptyList(); //create an empty list
    ListT *B= createEmptyList(); //create an empty list
    ListT *C= createEmptyList(); //create an empty list






    fscanf(fin,"%d",&n);

    for(int i=n; i>0; i--)
        insertAtFront(A,createNode(i));//put the n pegs on A

    print_pegs(A,B,C,'A','B','C',fout);

    tower(n,A,B,C,'A','B','C',fout);

    purge(A);
    purge(B);
    purge(C);
    fclose(fin);
    fclose(fout);


    return 0;
}
