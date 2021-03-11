#include <stdio.h>
#include <stdlib.h>

typedef struct node_type
{
    int id;
    struct node_type *left, *right;
} NodeT;

void fatalError( const char *msg )
{
    printf( msg );
    printf( "\n" );
    exit ( 1 );
}

void preorder( NodeT *p, int level )
{
    if ( p != NULL )
    {
        for ( int i = 0; i <= level; i++ ) printf( " " ); /* for nice listing */
        printf( "%2.2d\n", p->id );
        preorder( p->left, level + 1 );
        preorder( p->right, level + 1 );
    }
}

void inorder( NodeT *p, int level )
{
    if ( p != NULL )
    {
        inorder( p->left, level + 1 );
        for ( int i = 0; i <= level; i++ ) printf( " " ); /* for nice listing */
        printf( "%2.2d\n", p->id );
        inorder( p->right, level + 1 );
    }
}



void postorder( NodeT *p, int level )
{
    if ( p != NULL )
    {
        postorder( p->left, level + 1 );
        postorder( p->right, level + 1 );
        for ( int i = 0; i <= level; i++ ) printf( " " ); /* for nice listing */
        printf( "%2.2d\n", p->id );
    }
}


NodeT *createBinTree( int branch, NodeT *parent )
{
    NodeT *p;
    int d;

    /* read node id */
    if ( branch == 0 )
        printf( "Root identifier [0 to end] =" );
    else if ( branch == 1 )
        printf( "Left child of %d [0 to end] =",
                parent->id );
    else
        printf( "Right child of %d [0 to end] =",
                parent->id );
    scanf("%d", &d);
    if ( d == 0 )
        return NULL;
    else
    {

        p = ( NodeT *)malloc(sizeof( NodeT ));
        if ( p == NULL )
            fatalError( "Out of space in createBinTree" );
        /* fill in node */
        p->id = d;
        p->left = createBinTree( 1, p );
        p->right = createBinTree( 2, p );
    }
    return p;
}

NodeT *find(NodeT *root,int nr)
{
    if(root==NULL)
        return NULL;

    if(root->id==nr)
        return root;

    NodeT *find_left=find(root->left,nr);
    if(find_left!=NULL) return find_left;

    NodeT *find_right=find(root->right,nr);
    if(find_right!=NULL) return find_right;
}


void swap(NodeT *root)
{
    if(root==NULL)
        return ;

    NodeT *aux;
    aux=root->left;
    root->left=root->right;
    root->right=aux;
    swap(root->left);
    swap(root->right);
}



int nrLeafs(NodeT *root)
{
    if(root->left == NULL && root->right==NULL)
        return 1;
    return nrLeafs(root->left)+nrLeafs(root->right);
}

int height(NodeT *root)
{
    if(root==NULL)
        return 0;

    int hleft=height(root->left);
    int hright=height(root->right);

    if(hleft>hright)
        return hleft+1;
    else return hright+1;


}


int main()
{
    NodeT *root;

    root = createBinTree( 0, NULL );



    printf("\nThe nr of leafs is: %d\n",nrLeafs(root));

    printf("\nThe height of the tree is: %d\n",height(root));


    /*
    printf("\nWrite the id of a node for swapping:");
    int node;
    scanf("%d",&node);
    swap(find(root,node));
    */




    swap(root);

    printf("\nAfter the swap of right and left part: \n");


    printf( "\nPreorder listing\n" );
    preorder( root, 0 );


    printf( "\nInorder listing\n" );
    inorder( root, 0 );


    printf( "\nPostorder listing\n" );
    postorder( root, 0 );



    return 0;
}
