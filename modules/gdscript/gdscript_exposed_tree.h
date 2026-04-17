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

#include "gdscript_exposed_tree.h"
#include "core/object/ref_counted.h"
#include "gdscript_parser.h"

class GDMember;
class GDNode;
class GDAnnotationNode;
class GDArrayNode;
class GDAssertNode;
class GDAssignableNode;
class GDAssignmentNode;
class GDAwaitNode;
class GDBinaryOpNode;
class GDBreakNode;
class GDBreakpointNode;
class GDCallNode;
class GDCastNode;
class GDClassNode;
class GDConstantNode;
class GDContinueNode;
class GDDictionaryNode;
class GDEnumNode;
class GDExpressionNode;
class GDForNode;
class GDFunctionNode;
class GDGetNodeNode;
class GDIdentifierNode;
class GDIfNode;
class GDLambdaNode;
class GDLiteralNode;
class GDMatchNode;
class GDMatchBranchNode;
class GDParameterNode;
class GDPassNode;
class GDPatternNode;
class GDPreloadNode;
class GDReturnNode;
class GDSelfNode;
class GDSignalNode;
class GDSubscriptNode;
class GDSuiteNode;
class GDTernaryOpNode;
class GDTypeNode;
class GDTypeTestNode;
class GDUnaryOpNode;
class GDVariableNode;
class GDWhileNode;

class GDMember : public RefCounted {
	GDCLASS(GDMember, RefCounted);

public:
	enum Type {
		UNDEFINED,
		CLASS,
		CONSTANT,
		FUNCTION,
		SIGNAL,
		VARIABLE,
		ENUM,
		ENUM_VALUE,
		GROUP,
	};

protected:
	static void _bind_methods();
	const GDScriptParser::ClassNode::Member *node = nullptr;

public:
	void set_node(const GDScriptParser::ClassNode::Member *p_node);
	static Ref<GDMember> build_from(const GDScriptParser::ClassNode::Member *p_node);

	Type get_type() const;
	Ref<GDClassNode> get_as_class_node() const;
	Ref<GDConstantNode> get_as_constant_node() const;
	Ref<GDFunctionNode> get_as_function_node() const;
	Ref<GDSignalNode> get_as_signal_node() const;
	Ref<GDVariableNode> get_as_signal_variable_node() const;
	Ref<GDEnumNode> get_as_enum_node() const;
	Ref<GDAnnotationNode> get_as_annotation_node() const;
	// enum value

	String get_name() const;
	String get_type_name() const;
	int get_line() const;

	//data type
	Ref<GDNode> get_source_node() const;

	GDMember();
	~GDMember();
};

class GDNode : public RefCounted {
	GDCLASS(GDNode, RefCounted);

public:
	enum Type {
		NONE,
		ANNOTATION,
		ARRAY,
		ASSERT,
		ASSIGNMENT,
		AWAIT,
		BINARY_OPERATOR,
		BREAK,
		BREAKPOINT,
		CALL,
		CAST,
		CLASS,
		CONSTANT,
		CONTINUE,
		DICTIONARY,
		ENUM,
		FOR,
		FUNCTION,
		GET_NODE,
		IDENTIFIER,
		IF,
		LAMBDA,
		LITERAL,
		MATCH,
		MATCH_BRANCH,
		PARAMETER,
		PASS,
		PATTERN,
		PRELOAD,
		RETURN,
		SELF,
		SIGNAL,
		SUBSCRIPT,
		SUITE,
		TERNARY_OPERATOR,
		TYPE,
		TYPE_TEST,
		UNARY_OPERATOR,
		VARIABLE,
		WHILE,
	};

protected:
	static void _bind_methods();
	GDScriptParser::Node *base_node = nullptr;

public:
	virtual void set_node(GDScriptParser::Node *p_node) {
	}

	GDNode::Type get_type() const;
	bool is_expression() const;
	int get_start_line() const;
	int get_end_line() const;
	int get_start_column() const;
	int get_end_column() const;
	Ref<GDNode> get_next() const;

	template <typename T>
	static Ref<T> build_from(GDScriptParser::Node *p_node);
	static Ref<GDNode> build_from(GDScriptParser::Node *p_node);
	GDNode();
	~GDNode();
};

class GDExpressionNode : public GDNode {
	GDCLASS(GDExpressionNode, GDNode);

protected:
	static void _bind_methods();
	GDScriptParser::ExpressionNode *node = nullptr;

public:
	Variant get_reduced_value() const;

	GDExpressionNode();
	~GDExpressionNode();

	void set_node(GDScriptParser::Node *p_node) override { node = static_cast<GDScriptParser::ExpressionNode *>(p_node); }
};

class GDAnnotationNode : public GDNode {
	GDCLASS(GDAnnotationNode, GDNode);

protected:
	static void _bind_methods();
	GDScriptParser::AnnotationNode *node = nullptr;

public:
	GDAnnotationNode();
	~GDAnnotationNode();
	void set_node(GDScriptParser::Node *p_node) override { node = static_cast<GDScriptParser::AnnotationNode *>(p_node); }
};

class GDArrayNode : public GDExpressionNode {
	GDCLASS(GDArrayNode, GDExpressionNode);

protected:
	static void _bind_methods();
	GDScriptParser::ArrayNode *node = nullptr;

public:
	GDArrayNode();
	~GDArrayNode();
	void set_node(GDScriptParser::Node *p_node) override { node = static_cast<GDScriptParser::ArrayNode *>(p_node); }
};

class GDAssertNode : public GDNode {
	GDCLASS(GDAssertNode, GDNode);

protected:
	static void _bind_methods();
	GDScriptParser::AssertNode *node = nullptr;

public:
	GDAssertNode();
	~GDAssertNode();
	void set_node(GDScriptParser::Node *p_node) override { node = static_cast<GDScriptParser::AssertNode *>(p_node); }
};

class GDAssignableNode : public GDNode {
	GDCLASS(GDAssignableNode, GDNode);

protected:
	static void _bind_methods();
	GDScriptParser::AssignableNode *node = nullptr;

public:
	Ref<GDExpressionNode> get_initializer() const;

	GDAssignableNode();
	~GDAssignableNode();

	virtual void set_node(GDScriptParser::Node *p_node) { node = static_cast<GDScriptParser::AssignableNode *>(p_node); }
};

class GDAssignmentNode : public GDExpressionNode {
	GDCLASS(GDAssignmentNode, GDExpressionNode);

protected:
	static void _bind_methods();
	GDScriptParser::AssignmentNode *node = nullptr;

public:
	GDAssignmentNode();
	~GDAssignmentNode();
	void set_node(GDScriptParser::Node *p_node) override { node = static_cast<GDScriptParser::AssignmentNode *>(p_node); }
	Ref<GDExpressionNode> get_assigned_value() const;
};

class GDAwaitNode : public GDExpressionNode {
	GDCLASS(GDAwaitNode, GDExpressionNode);

protected:
	static void _bind_methods();
	GDScriptParser::AwaitNode *node = nullptr;

public:
	GDAwaitNode();
	~GDAwaitNode();
	void set_node(GDScriptParser::Node *p_node) override { node = static_cast<GDScriptParser::AwaitNode *>(p_node); }
};

class GDBinaryOpNode : public GDExpressionNode {
	GDCLASS(GDBinaryOpNode, GDExpressionNode);

protected:
	static void _bind_methods();
	GDScriptParser::BinaryOpNode *node = nullptr;

public:
	GDBinaryOpNode();
	~GDBinaryOpNode();

	void set_node(GDScriptParser::Node *p_node) override {
		node = static_cast<GDScriptParser::BinaryOpNode *>(p_node);
	}
};

class GDBreakNode : public GDNode {
	GDCLASS(GDBreakNode, GDNode);

protected:
	static void _bind_methods();
	GDScriptParser::BreakNode *node = nullptr;

public:
	GDBreakNode();
	~GDBreakNode();
	void set_node(GDScriptParser::Node *p_node) override { node = static_cast<GDScriptParser::BreakNode *>(p_node); }
};

class GDBreakpointNode : public GDNode {
	GDCLASS(GDBreakpointNode, GDNode);

protected:
	static void _bind_methods();
	GDScriptParser::BreakpointNode *node = nullptr;

public:
	GDBreakpointNode();
	~GDBreakpointNode();
	void set_node(GDScriptParser::Node *p_node) override { node = static_cast<GDScriptParser::BreakpointNode *>(p_node); }
};

class GDCallNode : public GDExpressionNode {
	GDCLASS(GDCallNode, GDExpressionNode);

protected:
	static void _bind_methods();
	GDScriptParser::CallNode *node = nullptr;

public:
	GDCallNode();
	~GDCallNode();
	void set_node(GDScriptParser::Node *p_node) override { node = static_cast<GDScriptParser::CallNode *>(p_node); }
};

class GDCastNode : public GDExpressionNode {
	GDCLASS(GDCastNode, GDExpressionNode);

protected:
	static void _bind_methods();
	GDScriptParser::CastNode *node = nullptr;

public:
	GDCastNode();
	~GDCastNode();
	void set_node(GDScriptParser::Node *p_node) override { node = static_cast<GDScriptParser::CastNode *>(p_node); }
};

class GDClassNode : public GDNode {
	GDCLASS(GDClassNode, GDNode);

protected:
	static void _bind_methods();
	GDScriptParser::ClassNode *node = nullptr;

public:
	Ref<GDIdentifierNode> get_identifier() const;
	String get_icon_path() const;
	String get_simplified_icon_path() const;
	TypedArray<GDMember> get_members() const;
	Dictionary get_member_indices() const;
	Ref<GDClassNode> get_outer_class() const;
	bool extends_used() const;
	bool onready_used() const;
	bool is_abstract() const;
	bool has_static_data() const;
	bool annotated_static_unload() const;
	String get_extends_path() const;
	TypedArray<GDIdentifierNode> get_extends() const;
	// base_type
	String get_fqcn() const;
	bool resolved_interface() const;
	bool resolved_body() const;

	StringName get_global_name() const;
	Ref<GDMember> get_member(const StringName &p_name);
	bool has_member(const StringName &p_name) const;
	bool has_function(const StringName &p_name) const;

	void set_node(GDScriptParser::Node *p_node) override { node = static_cast<GDScriptParser::ClassNode *>(p_node); }

	GDClassNode();
	~GDClassNode();

private:
	HashMap<StringName, Ref<GDMember>> _cached_members;
};

class GDConstantNode : public GDAssignmentNode {
	GDCLASS(GDConstantNode, GDAssignmentNode);

protected:
	static void _bind_methods();
	GDScriptParser::ConstantNode *node = nullptr;

public:
	GDConstantNode();
	~GDConstantNode();

	void set_node(GDScriptParser::Node *p_node) override { node = static_cast<GDScriptParser::ConstantNode *>(p_node); }
};

class GDContinueNode : public GDNode {
	GDCLASS(GDContinueNode, GDNode);

protected:
	static void _bind_methods();
	GDScriptParser::ContinueNode *node = nullptr;

public:
	GDContinueNode();
	~GDContinueNode();

	void set_node(GDScriptParser::Node *p_node) override { node = static_cast<GDScriptParser::ContinueNode *>(p_node); }
};

class GDPair : public RefCounted {
	GDCLASS(GDPair, RefCounted);

protected:
	static void _bind_methods();
	const GDScriptParser::DictionaryNode::Pair *node;

public:
	void set_node(const GDScriptParser::DictionaryNode::Pair *p_node);
	static Ref<GDPair> build_from(const GDScriptParser::DictionaryNode::Pair *p_node);
	Ref<GDExpressionNode> get_key() const;
	Ref<GDExpressionNode> get_value() const;

	GDPair();
	~GDPair();
};

class GDDictionaryNode : public GDExpressionNode {
	GDCLASS(GDDictionaryNode, GDExpressionNode);

public:
	enum Style {
		LUA_TABLE,
		PYTHON_DICT,
	};

protected:
	static void _bind_methods();
	GDScriptParser::DictionaryNode *node = nullptr;

public:
	TypedArray<GDPair> get_elements() const;
	GDDictionaryNode::Style get_style() const;
	GDDictionaryNode();
	~GDDictionaryNode();

	void set_node(GDScriptParser::Node *p_node) override { node = static_cast<GDScriptParser::DictionaryNode *>(p_node); }
};

class GDEnumNode : public GDNode {
	GDCLASS(GDEnumNode, GDNode);

protected:
	static void _bind_methods();
	GDScriptParser::EnumNode *node = nullptr;

public:
	GDEnumNode();
	~GDEnumNode();

	void set_node(GDScriptParser::Node *p_node) override { node = static_cast<GDScriptParser::EnumNode *>(p_node); }
};

class GDForNode : public GDNode {
	GDCLASS(GDForNode, GDNode);

protected:
	static void _bind_methods();
	GDScriptParser::ForNode *node = nullptr;

public:
	Ref<GDIdentifierNode> get_variable() const;
	Ref<GDTypeNode> get_datatype_specifier() const;
	bool use_conversion_assign() const;
	Ref<GDExpressionNode> get_list() const;
	Ref<GDSuiteNode> get_loop() const;

	GDForNode();
	~GDForNode();

	void set_node(GDScriptParser::Node *p_node) override { node = static_cast<GDScriptParser::ForNode *>(p_node); }
};

class GDFunctionNode : public GDNode {
	GDCLASS(GDFunctionNode, GDNode);

protected:
	static void _bind_methods();
	GDScriptParser::FunctionNode *node = nullptr;

public:
	Ref<GDIdentifierNode> get_identifier() const;
	TypedArray<GDParameterNode> get_parameters() const;
	Dictionary get_parameter_indices() const;
	Ref<GDParameterNode> get_rest_parameter() const;
	Ref<GDTypeNode> get_return_type() const;
	Ref<GDSuiteNode> get_body() const;
	bool is_abstract() const;
	bool is_static() const;
	bool is_coroutine() const;
	Variant get_rpc_config() const;
	// method info
	Ref<GDLambdaNode> get_source_lambda() const;
	Array get_default_arg_values() const;
	bool resolved_signature() const;
	bool resolved_body() const;
	bool is_vararg() const;

	GDFunctionNode();
	~GDFunctionNode();
	void set_node(GDScriptParser::Node *p_node) override { node = static_cast<GDScriptParser::FunctionNode *>(p_node); }
};

class GDGetNodeNode : public GDExpressionNode {
	GDCLASS(GDGetNodeNode, GDExpressionNode);

protected:
	static void _bind_methods();
	GDScriptParser::GetNodeNode *node = nullptr;

public:
	String get_full_path() const;
	bool use_dollar() const;

	GDGetNodeNode();
	~GDGetNodeNode();

	void set_node(GDScriptParser::Node *p_node) override { node = static_cast<GDScriptParser::GetNodeNode *>(p_node); }
};

class GDIdentifierNode : public GDExpressionNode {
	GDCLASS(GDIdentifierNode, GDExpressionNode);

public:
	enum Source {
		UNDEFINED_SOURCE,
		FUNCTION_PARAMETER,
		LOCAL_VARIABLE,
		LOCAL_CONSTANT,
		LOCAL_ITERATOR, // `for` loop iterator.
		LOCAL_BIND, // Pattern bind.
		MEMBER_VARIABLE,
		MEMBER_CONSTANT,
		MEMBER_FUNCTION,
		MEMBER_SIGNAL,
		MEMBER_CLASS,
		INHERITED_VARIABLE,
		STATIC_VARIABLE,
		NATIVE_CLASS,
	};

protected:
	static void _bind_methods();
	GDScriptParser::IdentifierNode *node = nullptr;

public:
	StringName get_name() const;
	Ref<GDSuiteNode> get_suite() const;
	GDIdentifierNode::Source get_source() const;

	Ref<GDParameterNode> get_source_as_parameter() const;
	Ref<GDIdentifierNode> get_source_as_bind() const;
	Ref<GDVariableNode> get_source_as_variable() const;
	Ref<GDConstantNode> get_source_as_constant() const;
	Ref<GDSignalNode> get_source_as_signal() const;
	Ref<GDFunctionNode> get_source_as_function() const;

	bool function_source_is_static() const;
	Ref<GDFunctionNode> get_source_function() const;

	int get_usages() const;

	GDIdentifierNode();
	~GDIdentifierNode();

	void set_node(GDScriptParser::Node *p_node) override { node = static_cast<GDScriptParser::IdentifierNode *>(p_node); }
};

class GDIfNode : public GDNode {
	GDCLASS(GDIfNode, GDNode);

protected:
	static void _bind_methods();
	GDScriptParser::IfNode *node = nullptr;

public:
	Ref<GDExpressionNode> get_condition() const;
	Ref<GDSuiteNode> get_true_block() const;
	Ref<GDSuiteNode> get_false_block() const;

	GDIfNode();
	~GDIfNode();

	void set_node(GDScriptParser::Node *p_node) override { node = static_cast<GDScriptParser::IfNode *>(p_node); }
};

class GDLambdaNode : public GDExpressionNode {
	GDCLASS(GDLambdaNode, GDExpressionNode);

protected:
	static void _bind_methods();
	GDScriptParser::LambdaNode *node = nullptr;

public:
	GDLambdaNode();
	~GDLambdaNode();

	void set_node(GDScriptParser::Node *p_node) override { node = static_cast<GDScriptParser::LambdaNode *>(p_node); }
};

class GDLiteralNode : public GDExpressionNode {
	GDCLASS(GDLiteralNode, GDExpressionNode);

protected:
	static void _bind_methods();
	GDScriptParser::LiteralNode *node = nullptr;

public:
	GDLiteralNode();
	~GDLiteralNode();

	void set_node(GDScriptParser::Node *p_node) override { node = static_cast<GDScriptParser::LiteralNode *>(p_node); }
};

class GDMatchNode : public GDNode {
	GDCLASS(GDMatchNode, GDNode);

protected:
	static void _bind_methods();
	GDScriptParser::MatchNode *node = nullptr;

public:
	GDMatchNode();
	~GDMatchNode();
	void set_node(GDScriptParser::Node *p_node) override { node = static_cast<GDScriptParser::MatchNode *>(p_node); }
};

class GDMatchBranchNode : public GDNode {
	GDCLASS(GDMatchBranchNode, GDNode);

protected:
	static void _bind_methods();
	GDScriptParser::MatchBranchNode *node = nullptr;

public:
	GDMatchBranchNode();
	~GDMatchBranchNode();

	void set_node(GDScriptParser::Node *p_node) override { node = static_cast<GDScriptParser::MatchBranchNode *>(p_node); }
};

class GDParameterNode : public GDAssignableNode {
	GDCLASS(GDParameterNode, GDAssignableNode);

protected:
	static void _bind_methods();
	GDScriptParser::ParameterNode *node = nullptr;

public:
	GDParameterNode();
	~GDParameterNode();

	void set_node(GDScriptParser::Node *p_node) override { node = static_cast<GDScriptParser::ParameterNode *>(p_node); }
};

class GDPassNode : public GDNode {
	GDCLASS(GDPassNode, GDNode);

protected:
	static void _bind_methods();
	GDScriptParser::PassNode *node = nullptr;

public:
	GDPassNode();
	~GDPassNode();
	void set_node(GDScriptParser::Node *p_node) override { node = static_cast<GDScriptParser::PassNode *>(p_node); }
};

class GDPatternNode : public GDNode {
	GDCLASS(GDPatternNode, GDNode);

protected:
	static void _bind_methods();
	GDScriptParser::PatternNode *node = nullptr;

public:
	GDPatternNode();
	~GDPatternNode();

	void set_node(GDScriptParser::Node *p_node) override { node = static_cast<GDScriptParser::PatternNode *>(p_node); }
};

class GDPreloadNode : public GDExpressionNode {
	GDCLASS(GDPreloadNode, GDExpressionNode);

protected:
	static void _bind_methods();
	GDScriptParser::PreloadNode *node = nullptr;

public:
	GDPreloadNode();
	~GDPreloadNode();

	void set_node(GDScriptParser::Node *p_node) override { node = static_cast<GDScriptParser::PreloadNode *>(p_node); }
};

class GDReturnNode : public GDNode {
	GDCLASS(GDReturnNode, GDNode);

protected:
	static void _bind_methods();
	GDScriptParser::ReturnNode *node = nullptr;

public:
	GDReturnNode();
	~GDReturnNode();

	void set_node(GDScriptParser::Node *p_node) override { node = static_cast<GDScriptParser::ReturnNode *>(p_node); }
};

class GDSelfNode : public GDExpressionNode {
	GDCLASS(GDSelfNode, GDExpressionNode);

protected:
	static void _bind_methods();
	GDScriptParser::SelfNode *node = nullptr;

public:
	GDSelfNode();
	~GDSelfNode();

	void set_node(GDScriptParser::Node *p_node) override { node = static_cast<GDScriptParser::SelfNode *>(p_node); }
};

class GDSignalNode : public GDNode {
	GDCLASS(GDSignalNode, GDNode);

protected:
	static void _bind_methods();
	GDScriptParser::SignalNode *node = nullptr;

public:
	GDSignalNode();
	~GDSignalNode();

	void set_node(GDScriptParser::Node *p_node) override { node = static_cast<GDScriptParser::SignalNode *>(p_node); }
};

class GDSubscriptNode : public GDExpressionNode {
	GDCLASS(GDSubscriptNode, GDExpressionNode);

protected:
	static void _bind_methods();
	GDScriptParser::SubscriptNode *node = nullptr;

public:
	GDSubscriptNode();
	~GDSubscriptNode();

	void set_node(GDScriptParser::Node *p_node) override { node = static_cast<GDScriptParser::SubscriptNode *>(p_node); }
};

class GDSuiteNode : public GDNode {
	GDCLASS(GDSuiteNode, GDNode);

protected:
	static void _bind_methods();
	GDScriptParser::SuiteNode *node = nullptr;

public:
	TypedArray<GDNode> get_statements() const;

	GDSuiteNode();
	~GDSuiteNode();

	void set_node(GDScriptParser::Node *p_node) override { node = static_cast<GDScriptParser::SuiteNode *>(p_node); }
};

class GDTernaryOpNode : public GDExpressionNode {
	GDCLASS(GDTernaryOpNode, GDExpressionNode);

protected:
	static void _bind_methods();
	GDScriptParser::TernaryOpNode *node = nullptr;

public:
	GDTernaryOpNode();
	~GDTernaryOpNode();

	void set_node(GDScriptParser::Node *p_node) override { node = static_cast<GDScriptParser::TernaryOpNode *>(p_node); }
};

class GDTypeNode : public GDNode {
	GDCLASS(GDTypeNode, GDNode);

protected:
	static void _bind_methods();
	GDScriptParser::TypeNode *node = nullptr;

public:
	GDTypeNode();
	~GDTypeNode();
	void set_node(GDScriptParser::Node *p_node) override { node = static_cast<GDScriptParser::TypeNode *>(p_node); }
};

class GDTypeTestNode : public GDExpressionNode {
	GDCLASS(GDTypeTestNode, GDExpressionNode);

protected:
	static void _bind_methods();
	GDScriptParser::TypeTestNode *node = nullptr;

public:
	GDTypeTestNode();
	~GDTypeTestNode();

	void set_node(GDScriptParser::Node *p_node) override { node = static_cast<GDScriptParser::TypeTestNode *>(p_node); }
};

class GDUnaryOpNode : public GDExpressionNode {
	GDCLASS(GDUnaryOpNode, GDExpressionNode);

protected:
	static void _bind_methods();
	GDScriptParser::UnaryOpNode *node = nullptr;

public:
	GDUnaryOpNode();
	~GDUnaryOpNode();

	void set_node(GDScriptParser::Node *p_node) override { node = static_cast<GDScriptParser::UnaryOpNode *>(p_node); }
};

class GDVariableNode : public GDAssignableNode {
	GDCLASS(GDVariableNode, GDAssignableNode);

protected:
	static void _bind_methods();
	GDScriptParser::VariableNode *node = nullptr;

public:
	GDVariableNode();
	~GDVariableNode();

	Dictionary get_export_info() const;

	void set_node(GDScriptParser::Node *p_node) override { node = static_cast<GDScriptParser::VariableNode *>(p_node); GDAssignableNode::set_node(p_node); }
};

class GDWhileNode : public GDNode {
	GDCLASS(GDWhileNode, GDNode);

protected:
	static void _bind_methods();
	GDScriptParser::WhileNode *node = nullptr;

public:
	GDWhileNode();
	~GDWhileNode();

	void set_node(GDScriptParser::Node *p_node) override { node = static_cast<GDScriptParser::WhileNode *>(p_node); }
};


VARIANT_ENUM_CAST(GDNode::Type);

VARIANT_ENUM_CAST(GDMember::Type);

VARIANT_ENUM_CAST(GDDictionaryNode::Style);

VARIANT_ENUM_CAST(GDIdentifierNode::Source);

#endif // GDSCRIPT_EXPOSED_TREE_H
