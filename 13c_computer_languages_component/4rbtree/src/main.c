#include "rbtree.h"
#include <string.h>
#include <stdio.h>

struct mytype {
    struct rb_node node;
    char *keystring;
};

struct rb_root mytree = RB_ROOT;

struct mytype *my_search(struct rb_root *root, char *string)
{
    struct rb_node *node = root->rb_node;
    while (node) {
        struct mytype *data = container_of(node, struct mytype, node);
        int result;
        result = strcmp(string, data->keystring);
        if (result < 0)
            node = node->rb_left;
        else if (result > 0)
            node = node->rb_right;
        else
            return data;
    }
    return NULL;
}

/*插入新节点*/

int my_insert(struct rb_root *root, struct mytype *data)
{
    struct rb_node **new = &(root->rb_node), *parent = NULL;
    /* Figure out where to put new node */
    while (*new) {
        struct mytype *this = container_of(*new, struct mytype, node);
        int result = strcmp(data->keystring, this->keystring);
        parent = *new;
        if (result < 0)
            new = &((*new)->rb_left);
        else if (result > 0)
            new = &((*new)->rb_right);
        else
            return false;
    }
    /* Add new node and rebalance tree. */
    rb_link_node(&data->node, parent, new);
    rb_insert_color(&data->node, root);
    return true;
}


void main (void)
{
/*未完成*/
	struct mytype *data = my_search(&mytree, "walrus");
	
	if (data) {
	  rb_erase(&data->node, &mytree);
	  //free(data);清除内存
	}



	struct rb_node *node;
	for (node = rb_first(&mytree); node; node = rb_next(node)){
		printf("key=%s\n", rb_entry(node, struct mytype, node)->keystring);
	}
}
