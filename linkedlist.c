
struct node {
    int value; //should be able to hold any type of object
    struct node *next;
} 

node* first;
node* last;

node* newNode(value, node *next)
{
    node* new_node = (node*)malloc(sizeof(node));
    if(new_node == NULL)
    {
        printf("no");
        exit(0);
    }
    new_node -> value = value;
    new_node -> next = next;

    return new_node;
}

node* addEndNewNode(node* last, value)
{
    node*
}
