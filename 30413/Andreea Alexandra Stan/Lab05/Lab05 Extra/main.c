#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//open the files/check if they can be opened
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

//functions for the tree:


typedef struct node_type
{
    char key[7];
    struct node_type *left, *right;

} BSTNodeT;


//functions to check if the word read is a character or a number
int check_node_number(char s[])
{
    if(strchr("0123456789",s[0]))
        return 1;// is a number
    if(s[0]=='-' && s[1]!='\0')
        return 1;
    return 0;//is not a number
}

int check_node_operator(char s[])
{
    if((s[0]=='+' || s[0]=='-' || s[0]=='*' ||s[0]=='/')&& s[1]=='\0')
        return 1;// is an operator
    return 0;//is not an operator
}

//function to create a node
BSTNodeT *createNode(char givenKey[])
{

    BSTNodeT *p = (BSTNodeT *) malloc (sizeof (BSTNodeT));
    if (p)
    {
        strcpy(p->key,givenKey);
        p->left = p-> right = NULL;
    }
    return p;
}

//function to insert a node:
BSTNodeT *insertNode(BSTNodeT *root, BSTNodeT *node1, FILE *f_out)
{
    /* If the tree is empty, then a single node tree is created */
    if (root == NULL)
        root = node1;
    else
    {
        if (root->left==NULL)
            root->left = node1;

        else
            root->right = node1;


    }
    return root;
}


//print inorder
void inorder(BSTNodeT *p,FILE *f_out)
{
    if (p != NULL)
    {
        inorder(p->left,f_out);
        fprintf(f_out,"%s\n", p->key);
        inorder(p->right,f_out);
    }
}

//print preorder
void preorder(BSTNodeT *p, FILE *f_out)
{
    if (p != NULL)
    {
        fprintf(f_out,"%s\n", p->key);
        preorder(p->left,f_out);
        preorder(p->right,f_out);
    }
}

//delete the BST:
void delTree(BSTNodeT *root)
{
    if (root != NULL)
    {
        delTree(root->left);
        delTree(root->right);
        free(root);
    }
}


//end of functions for the tree




//functions for stack:

//every node of the stack is a tree node
typedef struct node
{
    BSTNodeT *n;
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
        listPtr->count = 0; // list empty
        listPtr->first = listPtr->last = NULL;
    }
    return listPtr;
}

int isEmpty( ListT *listPtr )
{
    return listPtr->first == NULL;
}

//create a node to insert in the stack from a tree node
NodeT *createSLLNode(BSTNodeT *root)
{
    NodeT *p = (NodeT *)malloc(sizeof(NodeT));
    if (p)
    {
        p->n=root;
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
        return 1; // success
    }
    return 0; // failure
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
            fprintf(pf,"%s ",p->n->key);

            p = p->next;
        }
        fprintf(pf,"\n");
    }
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



//end of functions for the stack



int main()
{

    FILE *f_in, *f_out;
    f_in=openAndCheck("input.txt", "r");
    f_out=openAndCheck("output.txt", "w");

    //count spaces in the stack
    int spaces=0;
    char c;
    c=fgetc(f_in);
    while(c!=EOF)
    {
        if(c==' ') spaces++;
        c=fgetc(f_in);
    }

    rewind(f_in);


    BSTNodeT *root;
    char s[100];
    NodeT *p;

    /*To solve this problem I tried to make subtrees where every operator is the root.
    The operands are always leafs.
    After that i went from the first element added to the last and added every subtree to the other corresponding subtree,
    till i obtained the final tree
    */



    ListT *list= createEmptyList();


    fscanf(f_in,"%s",s);

    root=createNode(s);
    insertAtFront(list,createSLLNode(root));
    //since we read in prefix form the first element read is always the root of the entire tree

    fscanf(f_in,"%s",s);



    for(int i=0; i<spaces; i++)
    {


        if(check_node_number(s))
        {

            insertAtFront(list,createSLLNode(createNode(s)));
            fscanf(f_in,"%s",s);
            //if we read a number we consider it the root of a "tree with only one element"

        }

        else if (check_node_operator(s))
        {
            root=createNode(s);
            fscanf(f_in,"%s",s);
            insertNode(root,createNode(s),f_out);
            fscanf(f_in,"%s",s);
            insertNode(root,createNode(s),f_out);

            insertAtFront(list,createSLLNode(root)); //add the tree obtained to the stack

            if(check_node_number(s))
            {
                fscanf(f_in,"%s",s);
                i++;
                //if the current element is a number we continue
                //otherwise it is the root of the next "subtree" so remain on this element
            }
            i++;


        }

    }

    strcpy(s,list->first->n->key);

    deleteFirst(list);//last element will always be a number so it can't be a root


    //start updating the tree till we reach the final one
    p=list->first;
    NodeT *q;
    root=list->last->n;
    //printf("\n%s",p->next->n->key);
    while(p->next!=NULL)
    {
        q=p->next;
        insertNode(q->n,p->n,f_out);
        p=q;

    }
    insertNode(root,createNode(s),f_out);// insert the element i deleted earlier

    //print the tree in inorder and preoder ways:
    fprintf(f_out,"inorder print:\n");
    inorder(root,f_out);
    fprintf(f_out,"\n");
    fprintf(f_out,"preorder print:\n");
    preorder(root,f_out);





    //close all the files
    fclose(f_out);
    fclose(f_in);

    //purge the list
    purge(list);

    //delete the tree:
    delTree(root);

    return 0;
}
