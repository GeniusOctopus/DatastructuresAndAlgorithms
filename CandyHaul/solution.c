#include <stdlib.h>
#include <stdio.h>

typedef struct node {
	int candy;
	struct node *left, *right;
} node_t;

node_t *create_house_node(int candy)
{
	node_t *house = malloc(sizeof(node_t));
	if (house == NULL)
	{
		fprintf(stderr, "malloc error\n");
		exit(1);
	}
	house->candy = candy;
	house->left = NULL;
	house->right = NULL;
	return house;
}

node_t *create_crossing_node(node_t *left, node_t *right)
{
	node_t *crossing = malloc(sizeof(node_t));
	if (crossing == NULL)
	{
		fprintf(stderr, "malloc error\n");
		exit(1);
	}
	crossing->left = left;
	crossing->right = right;
	return crossing;
}

int calc_tree_candy(node_t *node)
{
	if (!node->left && !node->right)
		return node->candy;
	return calc_tree_candy(node->left) + calc_tree_candy(node->right);
}

int calc_number_of_nodes(node_t *node)
{
	if (!node->left && !node->right)
		return 1;
	return 1 + calc_number_of_nodes(node->left) + calc_number_of_nodes(node->right);
}

int calc_number_of_house_nodes(node_t *node)
{
	if (!node->left && !node->right)
		return 1;
	return calc_number_of_house_nodes(node->left) + calc_number_of_house_nodes(node->right);
}

int calc_streets_walked(node_t *node)
{
	if (!node->left && !node->right)
		return 0;
	return calc_streets_walked(node->left) + calc_streets_walked(node->right) + 4;
}

int max(int left, int right)
{
	if (left > right)
		return left;
	else
		return right;
}

int calc_tree_height(node_t *node)
{
	if (!node->left && !node->right)
		return 0;
	return 1 + max(calc_tree_height(node->left), calc_tree_height(node->right));
}

node_t *parse_tree_helper(char *definition, int *pos)
{
	node_t *tree;
	tree = malloc(sizeof(node_t));
	if (tree == NULL)
	{
		fprintf(stderr, "malloc error\n");
		exit(1);
	}
	if (definition[*pos] == '(')
	{
		(*pos)++;
		tree->left = parse_tree_helper(definition, pos);
		(*pos)++;
		tree->right = parse_tree_helper(definition, pos);
		(*pos)++;
		return tree;
	}
	else
	{
		tree->left = NULL;
		tree->right = NULL;
		tree->candy = definition[*pos] - '0';
		(*pos)++;
		if (definition[*pos] != ')' && definition[*pos] != ' ' && definition[*pos] != '\0')
		{
			tree->candy = tree->candy * 10 + definition[*pos] - '0';
			(*pos)++;
		}
		return tree;
	}
}

node_t *parse_tree(char *definition)
{
	int pos = 0;
	return parse_tree_helper(definition, &pos);
}

int main(void)
{
	int i;
	char definition[256];
	node_t *tree;
	gets(definition);
	tree = parse_tree(definition);
	printf("Total candy: %d\n", calc_tree_candy(tree));
	printf("Min number of streets walked: %d\n", calc_streets_walked(tree) - calc_tree_height(tree));

	return 0;
}
