/*
Jonathan Balina
CSCI 235
Shostak
Project 3
*/

//default constructor for myVector
template<class KeyType, class ItemType>
myVector<KeyType, ItemType>::myVector()
{
    SortedKeys = new KeyType[0];
    SortedItems = new ItemType[0];
    size = 0;
}

//destructor to prevent memory leaks
template<class KeyType, class ItemType>
myVector<KeyType, ItemType>::~myVector()
{
    delete[] SortedKeys;
    delete[] SortedItems;
}

//push_back adds an item by copying content to a temporary dynamic array,
//then copying content back and deleting temporary array
template<class KeyType, class ItemType>
void myVector<KeyType, ItemType>::push_back(const KeyType& new_key, const ItemType& new_item)
{
    //new temp arrays
    KeyType* keys2 = new KeyType[size];
    ItemType* items2 = new ItemType[size];
    //copying to temp arrays
    for (int i = 0; i < size; i++)
    {
        keys2[i] = SortedKeys[i];
        items2[i] = SortedItems[i];
    }
    //delete original content
    delete[] SortedKeys;
    delete[] SortedItems;
    size++;
    //resize original arrays
    SortedKeys = new KeyType[size];
    SortedItems = new ItemType[size];
    //copy content back to original
    for (int i = 0; i < size - 1; i++)
    {
        SortedKeys[i] = keys2[i];
        SortedItems[i] = items2[i];
    }
    //add new item
    SortedKeys[size-1] = new_key;
    SortedItems[size-1] = new_item;
    //delete temporary arrays
    delete[] keys2;
    delete[] items2;
}

//returns the size of myVector
template<class KeyType, class ItemType>
int myVector<KeyType, ItemType>::Size() const
{
    return size;
}

//returns key at index
template<class KeyType, class ItemType>
KeyType myVector<KeyType, ItemType>::GetKeyAt(int index) const
{
    return SortedKeys[index];
}

//returns item at index
template<class KeyType, class ItemType>
ItemType myVector<KeyType, ItemType>::GetItemAt(int index) const
{
    return SortedItems[index];
}

//Default constructor for Node
template<class KeyType, class ItemType>
Node<KeyType, ItemType>::Node()
{
    left = nullptr;
    right = nullptr;
}

//constructor with key only
template<class KeyType, class ItemType>
Node<KeyType, ItemType>::Node(const KeyType& new_key)
{
    key = new_key;
    left = nullptr;
    right = nullptr;
}

//constructor with both key and item
template<class KeyType, class ItemType>
Node<KeyType, ItemType>::Node(const KeyType& new_key, const ItemType& new_item)
{
    key = new_key;
    item = new_item;
    left = nullptr;
    right = nullptr;
}

//returns reference item of node
template<class KeyType, class ItemType>
ItemType& Node<KeyType, ItemType>::GetRef()
{
    return item;
}

//returns copy of Key
template<class KeyType, class ItemType>
KeyType Node<KeyType, ItemType>::GetKey() const
{
    return key;
}

//sets new Key
template<class KeyType, class ItemType>
void Node<KeyType, ItemType>::SetKey(KeyType new_key)
{
    key = new_key;
}

//returns pointer to left Node
template<class KeyType, class ItemType>
Node<KeyType, ItemType>* Node<KeyType, ItemType>::GetLeft() const
{
    return left;
}

//returns pointer to right Node
template<class KeyType, class ItemType>
Node<KeyType, ItemType>* Node<KeyType, ItemType>::GetRight() const
{
    return right;
}

//sets new node as left Node
template<class KeyType, class ItemType>
void Node<KeyType, ItemType>::SetLeft(Node<KeyType, ItemType>* const NewLeft)
{
    left = NewLeft;
}

//sets new node as right Node
template<class KeyType, class ItemType>
void Node<KeyType, ItemType>::SetRight(Node<KeyType, ItemType>* const NewRight)
{
    right = NewRight;
}

//default constructor for Dictionary
template<class KeyType, class ItemType>
Dictionary<KeyType, ItemType>::Dictionary()
{
    root = nullptr;
    size = 0;
}

//destructor to prevent memory leaks
template<class KeyType, class ItemType>
Dictionary<KeyType, ItemType>::~Dictionary()
{
    Clear();
}

//checks if container is empty
template<class KeyType, class ItemType>
bool Dictionary<KeyType, ItemType>::IsEmpty()
{
    if(root==nullptr)
        return true;
    else
        return false;
}

//private function to be used with clear function
template<class KeyType, class ItemType>
void Dictionary<KeyType, ItemType>::util_clear(Node<KeyType, ItemType>* cur)
{
    //base case
    if (cur==nullptr)
        return;
    //first deletes left subtree
    util_clear(cur->GetLeft());
    //then right subtree
    util_clear(cur->GetRight());
    //then current node
    delete cur;
    root = cur = nullptr;
}

//public clear function to empty container
template<class KeyType, class ItemType>
void Dictionary<KeyType, ItemType>::Clear()
{
    //sets size to 0
    size = 0;
    util_clear(root);
}

//returns size
template<class KeyType, class ItemType>
int Dictionary<KeyType, ItemType>::Size() const
{
    return size;
}

//private function to be used in height
template<class KeyType, class ItemType>
int Dictionary<KeyType, ItemType>::util_height(Node<KeyType, ItemType>* cur) const
{
    //base case
    if(cur==nullptr)
        return 0;
    //checks for node to left or right
    int left = util_height(cur->GetLeft());
    int right = util_height(cur->GetRight());
    //returns larger returned value
    if(left>right)
        return 1+left;
    else
        return 1+right;
}

//public Height method
template<class KeyType, class ItemType>
int Dictionary<KeyType, ItemType>::Height() const
{
    return util_height(root);
}

//private method to find item with given key
template<class KeyType, class ItemType>
Node<KeyType, ItemType>* Dictionary<KeyType, ItemType>::search(const KeyType& Skey)
{
    Node<KeyType, ItemType>* cur = root;
    while(cur!=nullptr)
    {
        //checks if searched for key is larger or greater than currents key
        //then goes to left or right child to find it
        if(cur->GetKey()==Skey)
            return cur;
        else if(cur->GetKey()>Skey)
            cur=cur->GetLeft();
        else
            cur=cur->GetRight();
    }
    return nullptr;
}

//returns 1 if the object is found
template<class KeyType, class ItemType>
int Dictionary<KeyType, ItemType>::Count(const KeyType& Skey)
{
    //uses search to check
    if(search(Skey)==nullptr)
        return 0;
    else
        return 1;
}

//private function to be used as a helper for operator[]
template<class KeyType, class ItemType>
void Dictionary<KeyType, ItemType>::AddItem(const KeyType& new_key)
{
    size++;
    Node<KeyType, ItemType>* cur = root;
    //if container is empty then new item becomes root
    if(root==nullptr)
    {
        root = new Node<KeyType, ItemType>(new_key);
    }
    //searching for where to put new item
    while(cur!=nullptr)
    {
        //if greater then current key, go right, if less, go left
        if(cur->GetKey()>new_key)
        {
            if(cur->GetLeft()!=nullptr)
                cur=cur->GetLeft();
            //when nullptr found add item
            else
            {
                cur->SetLeft(new Node<KeyType, ItemType>(new_key));
                return;
            }
        }
        else if(cur->GetKey()<new_key)
        {
            if(cur->GetRight()!=nullptr)
                cur=cur->GetRight();
            //when nullptr found add item
            else
            {
                cur->SetRight(new Node<KeyType, ItemType>(new_key));
                return;
            }
        }
        //if equal to do nothing
        else if(cur->GetKey()==new_key)
            return;
    }
}

template<class KeyType, class ItemType>
ItemType& Dictionary<KeyType, ItemType>::operator[](const KeyType& Skey)
{
    //if item does not already exist, add item
    if(search(Skey)==nullptr)
        AddItem(Skey);
    //return reference to item with key
    return search(Skey)->GetRef();
}

//private function used with remove
template<class KeyType, class ItemType>
Node<KeyType, ItemType>* Dictionary<KeyType, ItemType>::util_remove(Node<KeyType, ItemType>* cur, KeyType Skey)
{
    //base case
    if(cur==nullptr)
        return cur;
    //searching for item
    else if(Skey < cur->GetKey())
        cur->SetLeft(util_remove(cur->GetLeft(), Skey));
    else if(Skey > cur->GetKey())
        cur->SetRight(util_remove(cur->GetRight(), Skey));
    //item is found
    else
    {
        //case 1: no children
        //just delete node
        if((cur->GetLeft()==nullptr) && (cur->GetRight()==nullptr))
        {
            delete cur;
            cur = nullptr;
        }
        //case 2: one child
        //make child take place of node
        else if((cur->GetLeft()==nullptr) && (cur->GetRight()!=nullptr))
        {
            Node<KeyType, ItemType>* temp = cur;
            cur = cur->GetRight();
            delete temp;
        }
        else if((cur->GetLeft()!=nullptr) && (cur->GetRight()==nullptr))
        {
            Node<KeyType, ItemType>* temp = cur;
            cur = cur->GetLeft();
            delete temp;
        }
        //case 3: two children
        //make smallest item of right subtree become Node
        else
        {
            Node<KeyType, ItemType>* temp = cur->GetRight();
            //find smallest item of right subtree
            while(temp->GetLeft()!=nullptr)
            {
                temp = temp->GetLeft();
            }
            //cur takes values of temporary node
            cur->GetRef() = temp->GetRef();
            cur->SetKey(temp->GetKey());
            cur->SetRight(util_remove(cur->GetRight(), temp->GetKey()));
        }
    }
    return cur;
}

//public remove method
template<class KeyType, class ItemType>
void Dictionary<KeyType, ItemType>::Remove(const KeyType& Skey)
{
    if(search(Skey)!=nullptr)
    {
        //decrement size
        size--;
        util_remove(root, Skey);
    }
}

//one of two private methods to be used with Balance
//adds elements to a container in order
//uses personally implemented version of vector
template<class KeyType, class ItemType>
void Dictionary<KeyType, ItemType>::util_balance1(myVector<KeyType, ItemType> &SortedList, Node<KeyType, ItemType>* cur)
{
    //base case
    if(cur==nullptr)
        return;
    //first adds smaller object
    util_balance1(SortedList, cur->GetLeft());
    //then current object
    SortedList.push_back(cur->GetKey(), cur->GetRef());
    //then larger object
    util_balance1(SortedList, cur->GetRight());
}

//one of two private methods to be used with Balance
//uses personally implemented version of vector
template<class KeyType, class ItemType>
Node<KeyType, ItemType>* Dictionary<KeyType, ItemType>::util_balance2(myVector<KeyType, ItemType> &SortedList, int small, int large)
{
    //base case
    if(small>large)
        return nullptr;
    //creates a Node from the middle item
    Node<KeyType, ItemType>* nn = new Node<KeyType, ItemType>(SortedList.GetKeyAt((small+large)/2),SortedList.GetItemAt((small+large)/2));
    //sets left and right node recursively
    nn->SetLeft(util_balance2(SortedList, small, (small+large)/2-1));
    nn->SetRight(util_balance2(SortedList, (small+large)/2+1, large));
    return nn;
}

//public balance method
template<class KeyType, class ItemType>
void Dictionary<KeyType, ItemType>::Balance()
{
    myVector<KeyType, ItemType> SortedList;
    //sorts myVector
    util_balance1(SortedList, root);
    //deletes current tree
    Clear();
    //sets tree to new sorted tree
    root = util_balance2(SortedList, 0, SortedList.Size()-1);
}

//private helper to print used for checking
template<class KeyType, class ItemType>
void Dictionary<KeyType, ItemType>::util_print(Node<KeyType, ItemType>* stree) const
{
    if(stree==nullptr)
        return;
    else
    {
        util_print(stree->GetLeft());
        std::cout << stree->GetKey() << " " << stree->GetRef() << " "/* << Count(stree->GetKey()) << " "*/;
        util_print(stree->GetRight());
    }
}

//print function used for checking
template<class KeyType, class ItemType>
void Dictionary<KeyType, ItemType>::print() const
{
    util_print(root);
}
