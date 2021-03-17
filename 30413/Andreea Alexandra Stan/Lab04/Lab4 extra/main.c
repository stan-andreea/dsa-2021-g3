#include <stdio.h>
#include <stdlib.h>

typedef struct node_type
{
    int id;
    struct node_type *left, *right;

} NodeT;


//for error messages:
void fatalError( const char *msg )
{
    printf( msg );
    printf( "\n" );
    exit ( 1 );
}


//construct a binary tree of the managers
NodeT *createBinTree( int branch, NodeT *parent )
{
    NodeT *p;
    int id;

    if ( branch == 0 )
        printf( "Root identifier [0 to end] =" );

    else if ( branch == 1 )
        printf( "Left child of %d [0 to end] =",parent->id );

    else
        printf( "Right child of %d [0 to end] =",parent->id );

    scanf("%d", &id);

    if ( id == 0 )
        return NULL;
    else
    {

        p = ( NodeT *)malloc(sizeof( NodeT ));
        if ( p == NULL )
            fatalError( "Out of space in createBinTree" );

        p->id = id;
        p->left = createBinTree( 1, p );
        p->right = createBinTree( 2, p );
    }
    return p;
}


//function to find the sum of tenure for each manager
int sum(NodeT *root)
{
    if(root==NULL)
        return 0;
    return root->id + sum(root->left)+sum(root->right);
}


//calculate the number of employees a manager has
int nr_employees(NodeT *root)
{
    if(root==NULL)
        return 0;
    return  1+nr_employees(root->left)+nr_employees(root->right);
}



//average tenure of a manager:
double tenure(NodeT *root)
{
    if(root==NULL) return 0;
    return (double)(sum(root))/(nr_employees(root));
}



//function the find the oldest one:


NodeT *maximt=NULL;//declared it global

NodeT *max_tenure(NodeT *root)
{

    if(root->left==NULL && root->right==NULL)//don't consider the leafs
        return NULL;


    NodeT *lmax=max_tenure(root->left);
    NodeT *rmax=max_tenure(root->right);

    if(tenure(root)>tenure(maximt))
    {
        maximt=root;
    }
    return maximt;

}




int main()
{
    NodeT *root;

    root = createBinTree( 0, NULL );


    printf("\n\nId of the node with the oldest team: %d\n\n", max_tenure(root)->id);



    return 0;
}
