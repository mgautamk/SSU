#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>    
#include <vector>
#include "dsexceptions.h"
using namespace std;

// AvlTree class
//
// CONSTRUCTION: with ITEM_NOT_FOUND object used to signal failed finds
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x (unimplemented)
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
//void searchTree()       --> Search the tree for a provided word
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class AvlTree
{
 public:
 AvlTree( ) : root( NULL )
    { }
 AvlTree( const AvlTree & rhs ) : root( NULL )
    {
      *this = rhs;
    }

  ~AvlTree( )
    {
      makeEmpty( );
    }
  struct AvlNode
    {
      Comparable element;
      AvlNode   *left;
      AvlNode   *right;
      int       height;
      int size;

    AvlNode( const Comparable & theElement, AvlNode *lt,
               AvlNode *rt, int h = 0 )
    : element( theElement ), left( lt ), right( rt ), height( h ), size( 1 ) { }
    };




  /**
   * Returns the type of tree as a string.
   * In this case, "AVL tree".
   */
  const string getTreeType() {
    return "AVL tree";
  }

  /**
   * Find the smallest item in the tree.
   * Throw UnderflowException if empty.
   */
  const Comparable & findMin( ) const
  {
    if( isEmpty( ) )
      throw UnderflowException( );
    return findMin( root )->element;
  }

  /**
   * Find the largest item in the tree.
   * Throw UnderflowException if empty.
   */
  const Comparable & findMax( ) const
  {
    if( isEmpty( ) )
      throw UnderflowException( );
    return findMax( root )->element;
  }

  //Returns Rank of Key
  int RankOfKey( const Comparable & x ){
    return RankOfKey( x, root );
  }

  //returns size
  int size (){
    size(root);
  }

  //Returns Key of Rank
  Comparable KeyOfRank( int rank ){
    return KeyOfRank( rank, root );
  }

  /**
   * Returns true if x is found in the tree.
   */
  bool contains( const Comparable & x ) const
  {
    return contains( x, root );
  }
  /**
   * Test if the tree is logically empty.
   * Return true if empty, false otherwise.
   */
  bool isEmpty( ) const
  {
    return root == NULL;
  }

  /**
   * Print the tree contents in sorted order.
   */
  void printTree( ) const
  {
    if( isEmpty( ) )
      cout << "Empty tree" << endl;
    else {
      cout << "AVL Tree Index:\n----------------------------------" <<endl;
      printTree( root);
    }
  }

  AvlNode * search ( const Comparable & x ) const
  {
    return search( x, root );
  }

  /**
   * Make the tree logically empty.
   */
  void makeEmpty( )
  {
    makeEmpty( root );
  }

  /**
   * Insert x into the tree; duplicates are ignored.
   */
  void insert( const Comparable & x )
  {
    insert( x, root );
  }

  void remove( const Comparable & x )
  {
    remove( x, root );
  }

  /**
   * Deep copy.
   */
  const AvlTree & operator=( const AvlTree & rhs )
    {
      if( this != &rhs )
        {
	  makeEmpty( );
	  root = clone( rhs.root );
        }
      return *this;
    }

    AvlNode *root;

 private:
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */

    bool insert( const Comparable & x, AvlNode * & t )
    {
      bool result;
      if( t == NULL ){
        t = new AvlNode{ x, NULL, NULL };

        return true;
      }
      else if( x < t->element )
        {
          if ( insert( x, t->left ) ){
            t->size++ ;
            result = true;
          }
        }
      else if( t->element < x )
        {
          if ( insert( x, t->right ) ){
            t->size++;
            result = true;
          }
        }
      else if( t->element == x)
        {
	  result = false;

        }

      balance(t);
      return result;
      }

    //removes x from the Tree
    bool remove( const Comparable & x, AvlNode * & t )
    {
      if( t == NULL )
        return false;   // Item not found; do nothing
      else if( t->element == x) //one child
        {
          if(t->left == NULL && t->right == NULL)
            {
              t = NULL;
              return true;
            }
          else if ((t->left != NULL && t->right != NULL))//two child
            {
              AvlNode* min = findMin(t->right);
              remove(min->element, t->right);
              t->element = min->element;
              t->size--;
            }
          else
            {
              if(t->left != NULL)
                {
                  t = t->left;
                }
              else
                {
                  t = t->right;
                }
            }
          return true;
        }
      bool result;
      if( x < t->element )
        {
          result = remove(x, t->left);
        }
      else
        {
          result = remove(x, t->right);
        }
      if(result)
        {
          t->size--;
        }
      balance(t);
      return result;

    }

    //Returns rank of key
    int RankOfKey( const Comparable & x, AvlNode * t){
      if ( t == NULL )
        return 0;
      if ( x < t->element )
        return RankOfKey( x, t->left );
      else if (x == t->element) {
        if (t->left != NULL){
          return ( 1 + (t->left)->size );
        }
        else{
          return 1;
        }
      }
      else if (x > t->element){
        if (t->left == NULL )
          return 1 + RankOfKey( x, t->right);
        return ( 1 + (t->left)->size + RankOfKey( x, t->right ) );
      }
    }
    //returns key of rank
    Comparable KeyOfRank(  int rank, AvlNode * t )
    {
      if (  t == NULL || rank > t->size || rank == 0)
        return 0;
      int current = (t->size-( t->right ? t->right->size : 0 ) );
      if ( rank == current )//equals current 
        return t->element;
      else if ( rank < current ) //less than current 
        return KeyOfRank( rank, t->left );
      // greater than current
      else{
        return KeyOfRank( rank - current, t->right );
      }
    }

    //Assume t is balanced or within one of being balanced
    void balance( AvlNode * & t )
    {
      if ( t == NULL )
	return;
      if ( (height(t->left) - height(t->right)) > 1 ){
	if (height(t->left->left) >= height(t->left->right)){
	  rotateWithLeftChild( t );
	}
	else{
	  doubleWithLeftChild( t );
	}
      }
      else
	if ( (height(t->right) - (height(t->left)) > 1 ))
	  if (height(t->right->right) >= height(t->right->left) )
	    rotateWithRightChild( t );
	  else
	    doubleWithRightChild( t );

      t->height = max( height(t->left), height(t->right) ) + 1;
    }

    //Search function
    AvlNode * search( const Comparable & x, AvlNode *t ) const
    {
      if( t == NULL)
	return NULL;
      else if (t->element == x)
        return t;
      else if( x < t->element )
        return search( x, t->left );
      else if( x > t->element )
        return search( x, t->right );
      else
	cout <<"Index doesn't contain given word"<<endl;
    }

    //Prints the item searched with line number
    void printsearch (AvlNode * t)
    {
      if (t == NULL){
        cout <<"Not in Index" <<endl;
        return;
      }
      cout << t->element << " ";
      for (int i = 0; i < t->lineNumberList.size(); i++)
        {
	  cout << t->lineNumberList[i];
	  if (i < t->lineNumberList.size()-1)
	    cout << ", ";
	  else
	    cout << endl;
        }//end for
    }//end printsearch

    //Returns the size of tree
    int size( AvlNode* t ){
      if (t == NULL)
        return 0;
      else
        return t->size;
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    AvlNode * findMin( AvlNode *t ) const
    {
      if( t == NULL )
	return NULL;
      if( t->left == NULL )
	return t;
      return findMin( t->left );
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    AvlNode * findMax( AvlNode *t ) const
    {
      if( t != NULL )
	while( t->right != NULL )
	  t = t->right;
      return t;
    }


    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the tree.
     */
    bool contains( const Comparable & x, AvlNode *t ) const
    {
      if( t == NULL )
	return false;
      else if( x < t->element )
	return contains( x, t->left );
      else if( t->element < x )
	return contains( x, t->right );
      else
	return true;    // Match
    }

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( AvlNode * & t )
    {
      if( t != NULL )
        {
	  makeEmpty( t->left );
	  makeEmpty( t->right );
	  delete t;
        }
      t = NULL;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree( AvlNode *t ) const
    {
      if( t != NULL )
        {
          printTree( t->left );
          cout << t->element << " ";
          for (int i = 0; i < t->lineNumberList.size(); i++) {
            cout << t->lineNumberList[i];
            if (i < t->lineNumberList.size()-1)
              cout << ", ";
            else
              cout << endl;
          }
          printTree( t->right );
        }
    }
  
    /**
     * Internal method to clone subtree.
     */
    AvlNode * clone( AvlNode *t ) const
    {
      if( t == NULL )
	return NULL;
      else
	return new AvlNode( t->element, clone( t->left ), clone( t->right ), t->height );
    }
    // Avl manipulations
    /**
     * Return the height of node t or -1 if NULL.
     */
    int height( AvlNode *t ) const
    {
      return t == NULL ? -1 : t->height;
    }

    int max( int lhs, int rhs ) const
    {
      return lhs > rhs ? lhs : rhs;
    }

    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild( AvlNode * & k2 )
    {
      AvlNode *k1 = k2->left;
      int k1mod = (k2->size - k1->size);
      int k2mod = - (k1->size - (k1->right ? k1->right->size : 0));
      k2->size += k2mod;
      k1->size += k1mod;
      k2->left = k1->right;
      k1->right = k2;
      k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
      k1->height = max( height( k1->left ), k2->height ) + 1;
      k2 = k1;
    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
    void rotateWithRightChild( AvlNode * & k1 )
    {
      AvlNode *k2 = k1->right;
      int k2mod = k1->size - k2->size;
      int k1mod = - (k2->size - (k2->left ? k2->left->size : 0));
      k2->size += k2mod;
      k1->size += k1mod;
      k1->right = k2->left;
      k2->left = k1;
      k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
      k2->height = max( height( k2->right ), k1->height ) + 1;
      k1 = k2;
    }

    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
    void doubleWithLeftChild( AvlNode * & k3 )
    {
      rotateWithRightChild( k3->left );
      rotateWithLeftChild( k3 );
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
    void doubleWithRightChild( AvlNode * & k1 )
    {
      rotateWithLeftChild( k1->right );
      rotateWithRightChild( k1 );
    }
};

#endif
