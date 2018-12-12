#include "pch.h"
#include "../SnakeGame/util/node.h"

TEST(NodeTest, NodesGetDirection)
{
	Node a(1, 1);
	EXPECT_EQ(getDirection(a, Node(1, 2)), SOUTH);
	EXPECT_EQ(getDirection(a, Node(1, 0)), NORTH);
	EXPECT_EQ(getDirection(a, Node(0, 1)), WEST);
	EXPECT_EQ(getDirection(a, Node(2, 1)), EAST);
	EXPECT_EQ(getDirection(a, a), ERROR_DIRECTION);
}