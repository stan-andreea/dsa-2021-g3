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


///1.


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



//1. function that has paramets two SLL and returns the intersection node if they intersect or NULL




NodeT *intersection(ListT *list1, ListT *list2)
{
    NodeT *p;
    p = list1->first;
    while ( p != NULL )
    {
        if(find(list2,p->key)==1)
            return p;
        p=p->next;

    }
    return NULL;


}


//end of first extra assignment




///2





void deleteNode(ListT *listPtr, NodeT *p)
{
    NodeT *q;
    q = p->next;


    if ( p->next != NULL )
    {



            p->next = q->next;
            if ( p->next == listPtr->last ) listPtr->last =p;
            free( q );

        listPtr->count--;

    }


}


void sort(ListT *listPtr)
{
    NodeT *p;

    int ok,aux;
    p=listPtr->first;

    //bubble sort:

    do
    {
        ok=0;
        p=listPtr->first;
        while(p->next!=NULL)
        {

            if(p->key>p->next->key)
            {
                aux=p->key;
                p->key=p->next->key;
                p->next->key=aux;

                ok=1; //we swapped something
            }

            p=p->next;
        }


    }
    while(ok);


}





//2. function to remove all duplicates from a SLL
//i used a sort function

void remove_dup(ListT *list1)
{
    NodeT *p;
    sort(list1);
    p = list1->first;
    if(p==NULL)
        return;

    while(p!=NULL)
    {

        int del=0;

        if(p->next!=NULL)
        {

            if(p->key==p->next->key)

            {
                deleteNode(list1,p);
                del=1;
            }


        }

       if(del==0)//no element deleted
            p=p->next;
    }


}

//end of second extra assignment









int main()
{


    ListT *list1 = createEmptyList();


    ListT *list2 = createEmptyList();


    FILE  *pf;

    pf=openAndCheck("output.txt", "w");


    //create two random lists for testing the functions
    insertAtFront(list1,createNode(10));
    insertAtFront(list1,createNode(17));
    insertAtFront(list1,createNode(20));
    insertAtFront(list1,createNode(25));
    insertAtFront(list1,createNode(25));
    insertAtFront(list1,createNode(25));
    insertAtFront(list1,createNode(30));
    insertAtFront(list1,createNode(30));

    insertAtFront(list2,createNode(16));
    insertAtFront(list2,createNode(20));
    insertAtFront(list2,createNode(40));
    insertAtFront(list2,createNode(45));
    insertAtFront(list2,createNode(70));
    insertAtFront(list2,createNode(40));
    insertAtFront(list2,createNode(60));


    //test for intersection function
    if(intersection(list1,list2)!=NULL)
        printf("The intersection is: %d\n",intersection(list1,list2)->key);
    else printf("The lists don't intersect");


    //check for removing duplicates function
    remove_dup(list1);
    print(list1,pf);

    fclose(pf);







    return 0;
}
