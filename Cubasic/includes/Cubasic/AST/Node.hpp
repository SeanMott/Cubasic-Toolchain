#pragma once

//defines general nodes

#include <string>

namespace Cubasic::AST::Node
{
	//defines a node type
	enum class NodeType
	{
		General = 0, //define a general node, normally used for storing raw lexed tokens

		FunctionDef, //defines a function

		Count
	};

	//defines a function node
	struct FunctionNode
	{
		uint64_t symbolID = 0; //defines the symbol ID associated with the name
	};
}