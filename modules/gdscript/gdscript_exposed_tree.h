/*************************************************************************/
/*  gdscript_error_checker.h                                             */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2022 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2022 Godot Engine contributors (cf. AUTHORS.md).   */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#ifndef GDSCRIPT_EXPOSED_TREE_H
#define GDSCRIPT_EXPOSED_TREE_H

#include "core/object/ref_counted.h"

class GDScriptParser;

class GDAnnotationNode : public RefCounted {
	GDCLASS(GDAnnotationNode, RefCounted);

protected:
	static void _bind_methods();
	GDScriptParser::AnnotationNode *node = nullptr;

public:
	void set_node(GDScriptParser::AnnotationNode *p_node);
	GDAnnotationNode();
	~GDAnnotationNode();
};

class GDArrayNode : public RefCounted {
	GDCLASS(GDArrayNode, RefCounted);

protected:
	static void _bind_methods();
	GDScriptParser::ArrayNode *node = nullptr;

public:
	void set_node(GDScriptParser::ArrayNode *p_node);
	GDArrayNode();
	~GDArrayNode();
};

class GDAssertNode : public RefCounted {
	GDCLASS(GDAssertNode, RefCounted);

protected:
	static void _bind_methods();
	GDScriptParser::AssertNode *node = nullptr;

public:
	void set_node(GDScriptParser::AssertNode *p_node);
	GDAssertNode();
	~GDAssertNode();
};

class GDAssignableNode : public RefCounted {
	GDCLASS(GDAssignableNode, RefCounted);

protected:
	static void _bind_methods();
	GDScriptParser::AssignableNode *node = nullptr;

public:
	void set_node(GDScriptParser::AssignableNode *p_node);
	GDAssignableNode();
	~GDAssignableNode();
};

class GDAssignmentNode : public RefCounted {
	GDCLASS(GDAssignmentNode, RefCounted);

protected:
	static void _bind_methods();
	GDScriptParser::AssignmentNode *node = nullptr;

public:
	void set_node(GDScriptParser::AssignmentNode *p_node);
	GDAssignmentNode();
	~GDAssignmentNode();
};

class GDAwaitNode : public RefCounted {
	GDCLASS(GDAwaitNode, RefCounted);

protected:
	static void _bind_methods();
	GDScriptParser::AwaitNode *node = nullptr;

public:
	void set_node(GDScriptParser::AwaitNode *p_node);
	GDAwaitNode();
	~GDAwaitNode();
};

class GDBinaryOpNode : public RefCounted {
	GDCLASS(GDBinaryOpNode, RefCounted);

protected:
	static void _bind_methods();
	GDScriptParser::BinaryOpNode *node = nullptr;

public:
	void set_node(GDScriptParser::BinaryOpNode *p_node);
	GDBinaryOpNode();
	~GDBinaryOpNode();
};

class GDBreakNode : public RefCounted {
	GDCLASS(GDBreakNode, RefCounted);

protected:
	static void _bind_methods();
	GDScriptParser::BreakNode *node = nullptr;

public:
	void set_node(GDScriptParser::BreakNode *p_node);
	GDBreakNode();
	~GDBreakNode();
};

class GDBreakpointNode : public RefCounted {
	GDCLASS(GDBreakpointNode, RefCounted);

protected:
	static void _bind_methods();
	GDScriptParser::BreakpointNode *node = nullptr;

public:
	void set_node(GDScriptParser::BreakpointNode *p_node);
	GDBreakpointNode();
	~GDBreakpointNode();
};

class GDCallNode : public RefCounted {
	GDCLASS(GDCallNode, RefCounted);

protected:
	static void _bind_methods();
	GDScriptParser::CallNode *node = nullptr;

public:
	void set_node(GDScriptParser::CallNode *p_node);
	GDCallNode();
	~GDCallNode();
};

class GDCastNode : public RefCounted {
	GDCLASS(GDCastNode, RefCounted);

protected:
	static void _bind_methods();
	GDScriptParser::CastNode *node = nullptr;

public:
	void set_node(GDScriptParser::CastNode *p_node);
	GDCastNode();
	~GDCastNode();
};

class GDClassNode : public RefCounted {
	GDCLASS(GDClassNode, RefCounted);

protected:
	static void _bind_methods();
	GDScriptParser::ClassNode *node = nullptr;

public:
	void set_node(GDScriptParser::ClassNode *p_node);
	GDClassNode();
	~GDClassNode();
};

class GDConstantNode : public RefCounted {
	GDCLASS(GDConstantNode, RefCounted);

protected:
	static void _bind_methods();
	GDScriptParser::ConstantNode *node = nullptr;

public:
	void set_node(GDScriptParser::ConstantNode *p_node);
	GDConstantNode();
	~GDConstantNode();
};

class GDContinueNode : public RefCounted {
	GDCLASS(GDContinueNode, RefCounted);

protected:
	static void _bind_methods();
	GDScriptParser::ContinueNode *node = nullptr;

public:
	void set_node(GDScriptParser::ContinueNode *p_node);
	GDContinueNode();
	~GDContinueNode();
};

class GDDictionaryNode : public RefCounted {
	GDCLASS(GDDictionaryNode, RefCounted);

protected:
	static void _bind_methods();
	GDScriptParser::DictionaryNode *node = nullptr;

public:
	void set_node(GDScriptParser::DictionaryNode *p_node);
	GDDictionaryNode();
	~GDDictionaryNode();
};

class GDEnumNode : public RefCounted {
	GDCLASS(GDEnumNode, RefCounted);

protected:
	static void _bind_methods();
	GDScriptParser::EnumNode *node = nullptr;

public:
	void set_node(GDScriptParser::EnumNode *p_node);
	GDEnumNode();
	~GDEnumNode();
};

class GDExpressionNode : public RefCounted {
	GDCLASS(GDExpressionNode, RefCounted);

protected:
	static void _bind_methods();
	GDScriptParser::ExpressionNode *node = nullptr;

public:
	void set_node(GDScriptParser::ExpressionNode *p_node);
	GDExpressionNode();
	~GDExpressionNode();
};

class GDForNode : public RefCounted {
	GDCLASS(GDForNode, RefCounted);

protected:
	static void _bind_methods();
	GDScriptParser::ForNode *node = nullptr;

public:
	void set_node(GDScriptParser::ForNode *p_node);
	GDForNode();
	~GDForNode();
};

class GDFunctionNode : public RefCounted {
	GDCLASS(GDFunctionNode, RefCounted);

protected:
	static void _bind_methods();
	GDScriptParser::FunctionNode *node = nullptr;

public:
	void set_node(GDScriptParser::FunctionNode *p_node);
	GDFunctionNode();
	~GDFunctionNode();
};

class GDGetNodeNode : public RefCounted {
	GDCLASS(GDGetNodeNode, RefCounted);

protected:
	static void _bind_methods();
	GDScriptParser::GetNodeNode *node = nullptr;

public:
	void set_node(GDScriptParser::GetNodeNode *p_node);
	GDGetNodeNode();
	~GDGetNodeNode();
};

class GDIdentifierNode : public RefCounted {
	GDCLASS(GDIdentifierNode, RefCounted);

protected:
	static void _bind_methods();
	GDScriptParser::IdentifierNode *node = nullptr;

public:
	void set_node(GDScriptParser::IdentifierNode *p_node);
	GDIdentifierNode();
	~GDIdentifierNode();
};

class GDIfNode : public RefCounted {
	GDCLASS(GDIfNode, RefCounted);

protected:
	static void _bind_methods();
	GDScriptParser::IfNode *node = nullptr;

public:
	void set_node(GDScriptParser::IfNode *p_node);
	GDIfNode();
	~GDIfNode();
};

class GDLambdaNode : public RefCounted {
	GDCLASS(GDLambdaNode, RefCounted);

protected:
	static void _bind_methods();
	GDScriptParser::LambdaNode *node = nullptr;

public:
	void set_node(GDScriptParser::LambdaNode *p_node);
	GDLambdaNode();
	~GDLambdaNode();
};

class GDLiteralNode : public RefCounted {
	GDCLASS(GDLiteralNode, RefCounted);

protected:
	static void _bind_methods();
	GDScriptParser::LiteralNode *node = nullptr;

public:
	void set_node(GDScriptParser::LiteralNode *p_node);
	GDLiteralNode();
	~GDLiteralNode();
};

class GDMatchNode : public RefCounted {
	GDCLASS(GDMatchNode, RefCounted);

protected:
	static void _bind_methods();
	GDScriptParser::MatchNode *node = nullptr;

public:
	void set_node(GDScriptParser::MatchNode *p_node);
	GDMatchNode();
	~GDMatchNode();
};

class GDMatchBranchNode : public RefCounted {
	GDCLASS(GDMatchBranchNode, RefCounted);

protected:
	static void _bind_methods();
	GDScriptParser::MatchBranchNode *node = nullptr;

public:
	void set_node(GDScriptParser::MatchBranchNode *p_node);
	GDMatchBranchNode();
	~GDMatchBranchNode();
};

class GDParameterNode : public RefCounted {
	GDCLASS(GDParameterNode, RefCounted);

protected:
	static void _bind_methods();
	GDScriptParser::ParameterNode *node = nullptr;

public:
	void set_node(GDScriptParser::ParameterNode *p_node);
	GDParameterNode();
	~GDParameterNode();
};

class GDPassNode : public RefCounted {
	GDCLASS(GDPassNode, RefCounted);

protected:
	static void _bind_methods();
	GDScriptParser::PassNode *node = nullptr;

public:
	void set_node(GDScriptParser::PassNode *p_node);
	GDPassNode();
	~GDPassNode();
};

class GDPatternNode : public RefCounted {
	GDCLASS(GDPatternNode, RefCounted);

protected:
	static void _bind_methods();
	GDScriptParser::PatternNode *node = nullptr;

public:
	void set_node(GDScriptParser::PatternNode *p_node);
	GDPatternNode();
	~GDPatternNode();
};

class GDPreloadNode : public RefCounted {
	GDCLASS(GDPreloadNode, RefCounted);

protected:
	static void _bind_methods();
	GDScriptParser::PreloadNode *node = nullptr;

public:
	void set_node(GDScriptParser::PreloadNode *p_node);
	GDPreloadNode();
	~GDPreloadNode();
};

class GDReturnNode : public RefCounted {
	GDCLASS(GDReturnNode, RefCounted);

protected:
	static void _bind_methods();
	GDScriptParser::ReturnNode *node = nullptr;

public:
	void set_node(GDScriptParser::ReturnNode *p_node);
	GDReturnNode();
	~GDReturnNode();
};

class GDSelfNode : public RefCounted {
	GDCLASS(GDSelfNode, RefCounted);

protected:
	static void _bind_methods();
	GDScriptParser::SelfNode *node = nullptr;

public:
	void set_node(GDScriptParser::SelfNode *p_node);
	GDSelfNode();
	~GDSelfNode();
};

class GDSignalNode : public RefCounted {
	GDCLASS(GDSignalNode, RefCounted);

protected:
	static void _bind_methods();
	GDScriptParser::SignalNode *node = nullptr;

public:
	void set_node(GDScriptParser::SignalNode *p_node);
	GDSignalNode();
	~GDSignalNode();
};

class GDSubscriptNode : public RefCounted {
	GDCLASS(GDSubscriptNode, RefCounted);

protected:
	static void _bind_methods();
	GDScriptParser::SubscriptNode *node = nullptr;

public:
	void set_node(GDScriptParser::SubscriptNode *p_node);
	GDSubscriptNode();
	~GDSubscriptNode();
};

class GDSuiteNode : public RefCounted {
	GDCLASS(GDSuiteNode, RefCounted);

protected:
	static void _bind_methods();
	GDScriptParser::SuiteNode *node = nullptr;

public:
	void set_node(GDScriptParser::SuiteNode *p_node);
	GDSuiteNode();
	~GDSuiteNode();
};

class GDTernaryOpNode : public RefCounted {
	GDCLASS(GDTernaryOpNode, RefCounted);

protected:
	static void _bind_methods();
	GDScriptParser::TernaryOpNode *node = nullptr;

public:
	void set_node(GDScriptParser::TernaryOpNode *p_node);
	GDTernaryOpNode();
	~GDTernaryOpNode();
};

class GDTypeNode : public RefCounted {
	GDCLASS(GDTypeNode, RefCounted);

protected:
	static void _bind_methods();
	GDScriptParser::TypeNode *node = nullptr;

public:
	void set_node(GDScriptParser::TypeNode *p_node);
	GDTypeNode();
	~GDTypeNode();
};

class GDTypeTestNode : public RefCounted {
	GDCLASS(GDTypeTestNode, RefCounted);

protected:
	static void _bind_methods();
	GDScriptParser::TypeTestNode *node = nullptr;

public:
	void set_node(GDScriptParser::TypeTestNode *p_node);
	GDTypeTestNode();
	~GDTypeTestNode();
};

class GDUnaryOpNode : public RefCounted {
	GDCLASS(GDUnaryOpNode, RefCounted);

protected:
	static void _bind_methods();
	GDScriptParser::UnaryOpNode *node = nullptr;

public:
	void set_node(GDScriptParser::UnaryOpNode *p_node);
	GDUnaryOpNode();
	~GDUnaryOpNode();
};

class GDVariableNode : public RefCounted {
	GDCLASS(GDVariableNode, RefCounted);

protected:
	static void _bind_methods();
	GDScriptParser::VariableNode *node = nullptr;

public:
	void set_node(GDScriptParser::VariableNode *p_node);
	GDVariableNode();
	~GDVariableNode();
};

class GDWhileNode : public RefCounted {
	GDCLASS(GDWhileNode, RefCounted);

protected:
	static void _bind_methods();
	GDScriptParser::WhileNode *node = nullptr;

public:
	void set_node(GDScriptParser::WhileNode *p_node);
	GDWhileNode();
	~GDWhileNode();
};


#endif // GDSCRIPT_EXPOSED_TREE_H
