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
class GDSuiteLocal;
class GDNode;
class GDPatternPair;
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
class GDEnumValue;
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
class GDDataType;

class GDDataType : public RefCounted {
	GDCLASS(GDDataType, RefCounted);

public:
	enum Kind {
		BUILTIN,
		NATIVE,
		SCRIPT,
		CLASS,
		ENUM,
		VARIANT,
		RESOLVING,
		UNRESOLVED,
	};

	enum TypeSource {
		UNDETECTED,
		INFERRED,
		ANNOTATED_EXPLICIT,
		ANNOTATED_INFERRED,
	};

protected:
	static void _bind_method();
	const GDScriptParser::DataType *node = nullptr;

public:
	GDDataType();
	~GDDataType();

	TypedArray<GDDataType> get_container_element_types() const;
	Kind get_kind() const;
	TypeSource get_type_source() const;

	bool is_constant() const;
	bool is_read_only() const;
	bool is_meta_type() const;
	bool is_pseudo_type() const;
	bool is_coroutine() const;

	Variant::Type get_builtin_type() const;
	StringName get_native_type() const;
	StringName get_enum_type() const;
	Ref<Script> get_script_type() const;
	String get_script_path() const;
	Ref<GDClassNode> get_class_type() const;

	Dictionary get_method_info() const;
	Dictionary get_enum_values() const;

	bool is_set() const;
	bool is_resolving() const;
	bool has_no_type() const;
	bool is_variant() const;
	bool is_hard_type() const;

	String to_string() const;
	String to_string_strict() const;
	Dictionary to_property_info(const String &p_name) const;

	int get_container_element_type_count() const;
	bool has_container_element_type(int p_index) const;
	bool has_container_element_types() const;
	bool is_typed_container_type() const;
	bool can_reference(const Ref<GDDataType> &p_other) const;

	void set_node(const GDScriptParser::DataType *p_node) { node = p_node; }
};

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
	Ref<GDEnumValue> get_enum_value() const;

	String get_name() const;
	String get_type_name() const;
	int get_line() const;

	Ref<GDDataType> get_datatype() const;
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
	GDScriptParser::Node *node = nullptr;

public:
	virtual void set_node(GDScriptParser::Node *p_node) { node = p_node; }

	GDNode::Type get_type() const;
	bool is_expression() const;
	int get_start_line() const;
	int get_end_line() const;
	int get_start_column() const;
	int get_end_column() const;
	Ref<GDNode> get_next() const;
	TypedArray<GDAnnotationNode> get_annotations() const;
	Ref<GDDataType> get_datatype() const;

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
	bool reduced() const;
	bool is_constant() const;
	Variant get_reduced_value() const;

	GDExpressionNode();
	~GDExpressionNode();

	void set_node(GDScriptParser::Node *p_node) override {
		GDNode::set_node(p_node);
		node = static_cast<GDScriptParser::ExpressionNode *>(p_node);
	}
};

class GDAnnotationNode : public GDNode {
	GDCLASS(GDAnnotationNode, GDNode);

protected:
	static void _bind_methods();
	GDScriptParser::AnnotationNode *node = nullptr;

public:
	GDAnnotationNode();
	~GDAnnotationNode();

	StringName get_name() const;
	TypedArray<GDExpressionNode> get_arguments() const;
	Array get_resolved_arguments() const;

	Dictionary get_export_info() const;
	bool is_resolved() const;
	bool is_applied() const;
	bool applies_to(uint32_t p_target_kinds) const;

	void set_node(GDScriptParser::Node *p_node) override {
		GDNode::set_node(p_node);
		node = static_cast<GDScriptParser::AnnotationNode *>(p_node);
	}
};

class GDArrayNode : public GDExpressionNode {
	GDCLASS(GDArrayNode, GDExpressionNode);

protected:
	static void _bind_methods();
	GDScriptParser::ArrayNode *node = nullptr;

public:
	GDArrayNode();
	~GDArrayNode();
	TypedArray<GDExpressionNode> get_elements() const;

	void set_node(GDScriptParser::Node *p_node) override {
		GDExpressionNode::set_node(p_node);
		node = static_cast<GDScriptParser::ArrayNode *>(p_node);
	}
};

class GDAssertNode : public GDNode {
	GDCLASS(GDAssertNode, GDNode);

protected:
	static void _bind_methods();
	GDScriptParser::AssertNode *node = nullptr;

public:
	GDAssertNode();
	~GDAssertNode();
	Ref<GDExpressionNode> get_condition() const;
	Ref<GDExpressionNode> get_message() const;

	void set_node(GDScriptParser::Node *p_node) override {
		GDNode::set_node(p_node);
		node = static_cast<GDScriptParser::AssertNode *>(p_node);
	}
};

class GDAssignableNode : public GDNode {
	GDCLASS(GDAssignableNode, GDNode);

protected:
	static void _bind_methods();
	GDScriptParser::AssignableNode *node = nullptr;

public:
	Ref<GDIdentifierNode> get_identifier() const;
	Ref<GDExpressionNode> get_initializer() const;
	Ref<GDTypeNode> get_datatype_specifier() const;
	bool infer_datatype() const;
	bool use_conversion_assign() const;
	int get_usages() const;

	GDAssignableNode();
	~GDAssignableNode();

	void set_node(GDScriptParser::Node *p_node) override {
		GDNode::set_node(p_node);
		node = static_cast<GDScriptParser::AssignableNode *>(p_node);
	}
};

class GDAssignmentNode : public GDExpressionNode {
	GDCLASS(GDAssignmentNode, GDExpressionNode);

public:
	enum Operation {
		OP_NONE,
		OP_ADDITION,
		OP_SUBTRACTION,
		OP_MULTIPLICATION,
		OP_DIVISION,
		OP_MODULO,
		OP_POWER,
		OP_BIT_SHIFT_LEFT,
		OP_BIT_SHIFT_RIGHT,
		OP_BIT_AND,
		OP_BIT_OR,
		OP_BIT_XOR,
	};

protected:
	static void _bind_methods();
	GDScriptParser::AssignmentNode *node = nullptr;

public:
	Operation get_operation() const;
	Variant::Operator get_variant_op() const;
	Ref<GDExpressionNode> get_assignee() const;
	Ref<GDExpressionNode> get_assigned_value() const;
	bool use_conversion_assign() const;

	GDAssignmentNode();
	~GDAssignmentNode();

	void set_node(GDScriptParser::Node *p_node) override {
		GDExpressionNode::set_node(p_node);
		node = static_cast<GDScriptParser::AssignmentNode *>(p_node);
	}
};

class GDAwaitNode : public GDExpressionNode {
	GDCLASS(GDAwaitNode, GDExpressionNode);

protected:
	static void _bind_methods();
	GDScriptParser::AwaitNode *node = nullptr;

public:
	Ref<GDExpressionNode> get_to_await() const;

	GDAwaitNode();
	~GDAwaitNode();

	void set_node(GDScriptParser::Node *p_node) override {
		GDExpressionNode::set_node(p_node);
		node = static_cast<GDScriptParser::AwaitNode *>(p_node);
	}
};

class GDBinaryOpNode : public GDExpressionNode {
	GDCLASS(GDBinaryOpNode, GDExpressionNode);

public:
	enum OpType {
		OP_ADDITION,
		OP_SUBTRACTION,
		OP_MULTIPLICATION,
		OP_DIVISION,
		OP_MODULO,
		OP_POWER,
		OP_BIT_LEFT_SHIFT,
		OP_BIT_RIGHT_SHIFT,
		OP_BIT_AND,
		OP_BIT_OR,
		OP_BIT_XOR,
		OP_LOGIC_AND,
		OP_LOGIC_OR,
		OP_CONTENT_TEST,
		OP_COMP_EQUAL,
		OP_COMP_NOT_EQUAL,
		OP_COMP_LESS,
		OP_COMP_LESS_EQUAL,
		OP_COMP_GREATER,
		OP_COMP_GREATER_EQUAL,
	};

protected:
	static void _bind_methods();
	GDScriptParser::BinaryOpNode *node = nullptr;

public:
	OpType get_operation() const;
	Variant::Operator get_variant_op() const;
	Ref<GDExpressionNode> get_left_operand() const;
	Ref<GDExpressionNode> get_right_operand() const;

	GDBinaryOpNode();
	~GDBinaryOpNode();

	void set_node(GDScriptParser::Node *p_node) override {
		GDExpressionNode::set_node(p_node);
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

	void set_node(GDScriptParser::Node *p_node) override {
		GDNode::set_node(p_node);
		node = static_cast<GDScriptParser::BreakNode *>(p_node);
	}
};

class GDBreakpointNode : public GDNode {
	GDCLASS(GDBreakpointNode, GDNode);

protected:
	static void _bind_methods();
	GDScriptParser::BreakpointNode *node = nullptr;

public:
	GDBreakpointNode();
	~GDBreakpointNode();

	void set_node(GDScriptParser::Node *p_node) override {
		GDNode::set_node(p_node);
		node = static_cast<GDScriptParser::BreakpointNode *>(p_node);
	}
};

class GDCallNode : public GDExpressionNode {
	GDCLASS(GDCallNode, GDExpressionNode);

protected:
	static void _bind_methods();
	GDScriptParser::CallNode *node = nullptr;

public:
	Ref<GDExpressionNode> get_callee() const;
	TypedArray<GDExpressionNode> get_arguments() const;
	StringName get_function_name() const;
	bool is_super() const;
	bool is_static() const;
	GDNode::Type get_callee_type() const;

	GDCallNode();
	~GDCallNode();

	void set_node(GDScriptParser::Node *p_node) override {
		GDExpressionNode::set_node(p_node);
		node = static_cast<GDScriptParser::CallNode *>(p_node);
	}
};

class GDCastNode : public GDExpressionNode {
	GDCLASS(GDCastNode, GDExpressionNode);

protected:
	static auto _bind_methods() -> void;
	GDScriptParser::CastNode *node = nullptr;

public:
	Ref<GDExpressionNode> get_operand() const;
	Ref<GDTypeNode> get_cast_type() const;

	GDCastNode();
	~GDCastNode();

	void set_node(GDScriptParser::Node *p_node) override {
		GDExpressionNode::set_node(p_node);
		node = static_cast<GDScriptParser::CastNode *>(p_node);
	}
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
	Ref<GDClassNode> get_outer() const;
	bool extends_used() const;
	bool onready_used() const;
	bool is_abstract() const;
	bool has_static_data() const;
	bool annotated_static_unload() const;
	String get_extends_path() const;
	TypedArray<GDIdentifierNode> get_extends() const;
	Ref<GDDataType> get_base_type() const;
	String get_fqcn() const;
	bool resolved_interface() const;
	bool resolved_body() const;

	StringName get_global_name() const;
	Ref<GDMember> get_member(const StringName &p_name);
	bool has_member(const StringName &p_name) const;
	bool has_function(const StringName &p_name) const;

	void set_node(GDScriptParser::Node *p_node) override {
		GDNode::set_node(p_node);
		node = static_cast<GDScriptParser::ClassNode *>(p_node);
	}

	GDClassNode();
	~GDClassNode();

private:
	HashMap<StringName, Ref<GDMember>> _cached_members;
};

class GDConstantNode : public GDAssignableNode {
	GDCLASS(GDConstantNode, GDAssignableNode);

protected:
	static void _bind_methods();
	GDScriptParser::ConstantNode *node = nullptr;

public:
	GDConstantNode();
	~GDConstantNode();

	void set_node(GDScriptParser::Node *p_node) override {
		GDAssignableNode::set_node(p_node);
		node = static_cast<GDScriptParser::ConstantNode *>(p_node);
	}
};

class GDContinueNode : public GDNode {
	GDCLASS(GDContinueNode, GDNode);

protected:
	static void _bind_methods();
	GDScriptParser::ContinueNode *node = nullptr;

public:
	GDContinueNode();
	~GDContinueNode();

	void set_node(GDScriptParser::Node *p_node) override {
		GDNode::set_node(p_node);
		node = static_cast<GDScriptParser::ContinueNode *>(p_node);
	}
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

	void set_node(GDScriptParser::Node *p_node) override {
		GDExpressionNode::set_node(p_node);
		node = static_cast<GDScriptParser::DictionaryNode *>(p_node);
	}
};

class GDEnumValue : public RefCounted {
	GDCLASS(GDEnumValue, RefCounted);

protected:
	static void _bind_methods();
	const GDScriptParser::EnumNode::Value *node = nullptr;

public:
	Ref<GDIdentifierNode> get_identifier() const;
	Ref<GDExpressionNode> get_custom_value() const;
	Ref<GDEnumNode> get_parent_enum() const;
	int get_index() const;
	bool resolved() const;
	int64_t get_value() const;
	int get_line() const;
	int get_start_column() const;
	int get_end_column() const;

	void set_node(const GDScriptParser::EnumNode::Value *p_node) { node = p_node; }
};

class GDEnumNode : public GDNode {
	GDCLASS(GDEnumNode, GDNode);

protected:
	static void _bind_methods();
	GDScriptParser::EnumNode *node = nullptr;

public:
	GDEnumNode();
	~GDEnumNode();

	Ref<GDIdentifierNode> get_identifier() const;
	TypedArray<GDEnumValue> get_values() const;
	Variant get_dictionary() const;

	void set_node(GDScriptParser::Node *p_node) override {
		GDNode::set_node(p_node);
		node = static_cast<GDScriptParser::EnumNode *>(p_node);
	}
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

	void set_node(GDScriptParser::Node *p_node) override {
		GDNode::set_node(p_node);
		node = static_cast<GDScriptParser::ForNode *>(p_node);
	}
};

class GDFunctionNode : public GDNode {
	GDCLASS(GDFunctionNode, GDNode);

protected:
	static void _bind_methods();
	GDScriptParser::FunctionNode *node = nullptr;

public:
	Ref<GDIdentifierNode> get_identifier() const;
	StringName get_name() const;
	TypedArray<GDParameterNode> get_parameters() const;
	Dictionary get_parameter_indices() const;
	Ref<GDParameterNode> get_rest_parameter() const;
	Ref<GDTypeNode> get_return_type() const;
	Ref<GDSuiteNode> get_body() const;
	bool is_abstract() const;
	bool is_static() const;
	bool is_coroutine() const;
	Variant get_rpc_config() const;
	Dictionary get_info() const;
	Ref<GDLambdaNode> get_source_lambda() const;
	Array get_default_arg_values() const;
	bool resolved_signature() const;
	bool resolved_body() const;
	bool is_vararg() const;

	GDFunctionNode();
	~GDFunctionNode();

	void set_node(GDScriptParser::Node *p_node) override {
		GDNode::set_node(p_node);
		node = static_cast<GDScriptParser::FunctionNode *>(p_node);
	}
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

	void set_node(GDScriptParser::Node *p_node) override {
		GDExpressionNode::set_node(p_node);
		node = static_cast<GDScriptParser::GetNodeNode *>(p_node);
	}
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

	void set_node(GDScriptParser::Node *p_node) override {
		GDExpressionNode::set_node(p_node);
		node = static_cast<GDScriptParser::IdentifierNode *>(p_node);
	}
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

	void set_node(GDScriptParser::Node *p_node) override {
		GDNode::set_node(p_node);
		node = static_cast<GDScriptParser::IfNode *>(p_node);
	}
};

class GDLambdaNode : public GDExpressionNode {
	GDCLASS(GDLambdaNode, GDExpressionNode);

protected:
	static void _bind_methods();
	GDScriptParser::LambdaNode *node = nullptr;

public:
	Ref<GDFunctionNode> get_function() const;
	Ref<GDFunctionNode> get_parent_function() const;
	Ref<GDLambdaNode> get_parent_lambda() const;
	TypedArray<GDIdentifierNode> get_captures() const;
	Dictionary get_capture_indices() const;
	bool use_self() const;
	bool has_name() const;

	GDLambdaNode();
	~GDLambdaNode();

	void set_node(GDScriptParser::Node *p_node) override {
		GDExpressionNode::set_node(p_node);
		node = static_cast<GDScriptParser::LambdaNode *>(p_node);
	}
};

class GDLiteralNode : public GDExpressionNode {
	GDCLASS(GDLiteralNode, GDExpressionNode);

protected:
	static void _bind_methods();
	GDScriptParser::LiteralNode *node = nullptr;

public:
	Variant get_value() const;

	GDLiteralNode();
	~GDLiteralNode();

	void set_node(GDScriptParser::Node *p_node) override {
		GDExpressionNode::set_node(p_node);
		node = static_cast<GDScriptParser::LiteralNode *>(p_node);
	}
};

class GDMatchNode : public GDNode {
	GDCLASS(GDMatchNode, GDNode);

protected:
	static void _bind_methods();
	GDScriptParser::MatchNode *node = nullptr;

public:
	Ref<GDExpressionNode> get_test() const;
	TypedArray<GDMatchBranchNode> get_branches() const;

	GDMatchNode();
	~GDMatchNode();

	void set_node(GDScriptParser::Node *p_node) override {
		GDNode::set_node(p_node);
		node = static_cast<GDScriptParser::MatchNode *>(p_node);
	}
};

class GDMatchBranchNode : public GDNode {
	GDCLASS(GDMatchBranchNode, GDNode);

protected:
	static void _bind_methods();
	GDScriptParser::MatchBranchNode *node = nullptr;

public:
	TypedArray<GDPatternNode> get_patterns() const;
	Ref<GDSuiteNode> get_block() const;
	bool has_wildcard() const;
	Ref<GDSuiteNode> get_guard_body() const;

	GDMatchBranchNode();
	~GDMatchBranchNode();

	void set_node(GDScriptParser::Node *p_node) override {
		GDNode::set_node(p_node);
		node = static_cast<GDScriptParser::MatchBranchNode *>(p_node);
	}
};

class GDParameterNode : public GDAssignableNode {
	GDCLASS(GDParameterNode, GDAssignableNode);

protected:
	static void _bind_methods();
	GDScriptParser::ParameterNode *node = nullptr;

public:
	GDParameterNode();
	~GDParameterNode();

	void set_node(GDScriptParser::Node *p_node) override {
		GDAssignableNode::set_node(p_node);
		node = static_cast<GDScriptParser::ParameterNode *>(p_node);
	}
};

class GDPassNode : public GDNode {
	GDCLASS(GDPassNode, GDNode);

protected:
	static void _bind_methods();
	GDScriptParser::PassNode *node = nullptr;

public:
	GDPassNode();
	~GDPassNode();

	void set_node(GDScriptParser::Node *p_node) override {
		GDNode::set_node(p_node);
		node = static_cast<GDScriptParser::PassNode *>(p_node);
	}
};

class GDPatternNode : public GDNode {
	GDCLASS(GDPatternNode, GDNode);

public:
	enum Type {
		PT_LITERAL,
		PT_EXPRESSION,
		PT_BIND,
		PT_ARRAY,
		PT_DICTIONARY,
		PT_REST,
		PT_WILDCARD,
	};

protected:
	static void _bind_methods();
	GDScriptParser::PatternNode *node = nullptr;

public:
	Type get_pattern_type() const;
	Ref<GDLiteralNode> get_as_literal() const;
	Ref<GDIdentifierNode> get_as_identifier() const;
	Ref<GDExpressionNode> get_as_expression() const;
	TypedArray<GDPatternNode> get_array() const;
	bool rest_used() const;
	TypedArray<GDPatternPair> get_dictionary() const;
	Dictionary get_binds() const;
	bool has_bind(const StringName &p_name) const;
	Ref<GDIdentifierNode> get_bind(const StringName &p_name) const;

	GDPatternNode();
	~GDPatternNode();

	void set_node(GDScriptParser::Node *p_node) override {
		GDNode::set_node(p_node);
		node = static_cast<GDScriptParser::PatternNode *>(p_node);
	}
};

class GDPatternPair : public RefCounted {
	GDCLASS(GDPatternPair, RefCounted);

protected:
	static void _bind_methods();
	const GDScriptParser::PatternNode::Pair *node = nullptr;

public:
	Ref<GDExpressionNode> get_key() const;
	Ref<GDPatternNode> get_value_pattern() const;
	void set_node(const GDScriptParser::PatternNode::Pair *p_node) { node = p_node; }
};

class GDPreloadNode : public GDExpressionNode {
	GDCLASS(GDPreloadNode, GDExpressionNode);

protected:
	static void _bind_methods();
	GDScriptParser::PreloadNode *node = nullptr;

public:
	Ref<GDExpressionNode> get_path() const;
	String get_resolved_path() const;
	Ref<Resource> get_resource() const;

	GDPreloadNode();
	~GDPreloadNode();

	void set_node(GDScriptParser::Node *p_node) override {
		GDExpressionNode::set_node(p_node);
		node = static_cast<GDScriptParser::PreloadNode *>(p_node);
	}
};

class GDReturnNode : public GDNode {
	GDCLASS(GDReturnNode, GDNode);

protected:
	static void _bind_methods();
	GDScriptParser::ReturnNode *node = nullptr;

public:
	Ref<GDExpressionNode> get_return_value() const;
	bool void_return() const;

	GDReturnNode();
	~GDReturnNode();

	void set_node(GDScriptParser::Node *p_node) override {
		GDNode::set_node(p_node);
		node = static_cast<GDScriptParser::ReturnNode *>(p_node);
	}
};

class GDSelfNode : public GDExpressionNode {
	GDCLASS(GDSelfNode, GDExpressionNode);

protected:
	static void _bind_methods();
	GDScriptParser::SelfNode *node = nullptr;

public:
	Ref<GDClassNode> get_current_class() const;

	GDSelfNode();
	~GDSelfNode();

	void set_node(GDScriptParser::Node *p_node) override {
		GDExpressionNode::set_node(p_node);
		node = static_cast<GDScriptParser::SelfNode *>(p_node);
	}
};

class GDSignalNode : public GDNode {
	GDCLASS(GDSignalNode, GDNode);

protected:
	static void _bind_methods();
	GDScriptParser::SignalNode *node = nullptr;

public:
	Ref<GDIdentifierNode> get_identifier() const;
	TypedArray<GDParameterNode> get_parameters() const;
	Dictionary get_parameter_indices() const;
	Dictionary get_method_info() const;
	int get_usages() const;

	GDSignalNode();
	~GDSignalNode();

	void set_node(GDScriptParser::Node *p_node) override {
		GDNode::set_node(p_node);
		node = static_cast<GDScriptParser::SignalNode *>(p_node);
	}
};

class GDSubscriptNode : public GDExpressionNode {
	GDCLASS(GDSubscriptNode, GDExpressionNode);

protected:
	static void _bind_methods();
	GDScriptParser::SubscriptNode *node = nullptr;

public:
	Ref<GDExpressionNode> get_base() const;
	Ref<GDExpressionNode> get_as_index() const;
	Ref<GDIdentifierNode> get_as_attribute() const;
	bool is_attribute() const;

	GDSubscriptNode();
	~GDSubscriptNode();

	void set_node(GDScriptParser::Node *p_node) override {
		GDExpressionNode::set_node(p_node);
		node = static_cast<GDScriptParser::SubscriptNode *>(p_node);
	}
};

class GDSuiteNode : public GDNode {
	GDCLASS(GDSuiteNode, GDNode);

protected:
	static void _bind_methods();
	GDScriptParser::SuiteNode *node = nullptr;

public:
	Ref<GDSuiteLocal> get_empty() const;
	TypedArray<GDSuiteLocal> get_locals() const;
	Dictionary get_locals_indices() const;
	Ref<GDFunctionNode> get_parent_function() const;
	Ref<GDIfNode> get_parent_if() const;
	bool has_return() const;
	bool has_continue() const;
	bool has_unreachable_code() const;
	bool is_in_loop() const;
	bool has_local(const StringName &p_name);
	Ref<GDSuiteLocal> get_local(const StringName &p_name);

	TypedArray<GDNode> get_statements() const;

	GDSuiteNode();
	~GDSuiteNode();

	void set_node(GDScriptParser::Node *p_node) override {
		GDNode::set_node(p_node);
		node = static_cast<GDScriptParser::SuiteNode *>(p_node);
	}
};

class GDSuiteLocal : public RefCounted {
	GDCLASS(GDSuiteLocal, RefCounted);

public:
	enum Type {
		UNDEFINED,
		CONSTANT,
		VARIABLE,
		PARAMETER,
		FOR_VARIABLE,
		PATTERN_BIND,
	};

protected:
	static void _bind_methods();
	const GDScriptParser::SuiteNode::Local *node = nullptr;

public:
	Type get_type() const;
	Ref<GDConstantNode> get_as_constant() const;
	Ref<GDVariableNode> get_as_variable() const;
	Ref<GDParameterNode> get_as_parameter() const;
	Ref<GDIdentifierNode> get_as_bind() const;
	StringName get_local_name() const;
	String get_name() const;
	Ref<GDFunctionNode> get_source_function() const;
	int get_start_line() const;
	int get_start_column() const;
	int get_end_line() const;
	int get_end_column() const;
	Ref<GDDataType> get_datatype() const;

	GDSuiteLocal();
	~GDSuiteLocal();
	void set_node(const GDScriptParser::SuiteNode::Local *p_node) { node = p_node; }
};

class GDTernaryOpNode : public GDExpressionNode {
	GDCLASS(GDTernaryOpNode, GDExpressionNode);

protected:
	static void _bind_methods();
	GDScriptParser::TernaryOpNode *node = nullptr;

public:
	Ref<GDExpressionNode> get_condition() const;
	Ref<GDExpressionNode> get_true_expr() const;
	Ref<GDExpressionNode> get_false_expr() const;

	GDTernaryOpNode();
	~GDTernaryOpNode();

	void set_node(GDScriptParser::Node *p_node) override {
		GDExpressionNode::set_node(p_node);
		node = static_cast<GDScriptParser::TernaryOpNode *>(p_node);
	}
};

class GDTypeNode : public GDNode {
	GDCLASS(GDTypeNode, GDNode);

protected:
	static void _bind_methods();
	GDScriptParser::TypeNode *node = nullptr;

public:
	TypedArray<GDIdentifierNode> get_type_chain() const;
	TypedArray<GDTypeNode> get_container_types() const;
	Ref<GDTypeNode> get_container_type_or_null(int p_index) const;

	GDTypeNode();
	~GDTypeNode();

	void set_node(GDScriptParser::Node *p_node) override {
		GDNode::set_node(p_node);
		node = static_cast<GDScriptParser::TypeNode *>(p_node);
	}
};

class GDTypeTestNode : public GDExpressionNode {
	GDCLASS(GDTypeTestNode, GDExpressionNode);

protected:
	static void _bind_methods();
	GDScriptParser::TypeTestNode *node = nullptr;

public:
	Ref<GDExpressionNode> get_operand() const;
	Ref<GDTypeNode> get_test_type() const;
	Ref<GDDataType> get_test_datatype() const;

	GDTypeTestNode();
	~GDTypeTestNode();

	void set_node(GDScriptParser::Node *p_node) override {
		GDExpressionNode::set_node(p_node);
		node = static_cast<GDScriptParser::TypeTestNode *>(p_node);
	}
};

class GDUnaryOpNode : public GDExpressionNode {
	GDCLASS(GDUnaryOpNode, GDExpressionNode);

public:
	enum OpType {
		OP_POSITIVE,
		OP_NEGATIVE,
		OP_COMPLEMENT,
		OP_LOGIC_NOT,
	};

protected:
	static void _bind_methods();
	GDScriptParser::UnaryOpNode *node = nullptr;

public:
	OpType get_operation() const;
	Variant::Operator get_variant_op() const;
	Ref<GDExpressionNode> get_operand() const;

	GDUnaryOpNode();
	~GDUnaryOpNode();

	void set_node(GDScriptParser::Node *p_node) override {
		GDExpressionNode::set_node(p_node);
		node = static_cast<GDScriptParser::UnaryOpNode *>(p_node);
	}
};

class GDVariableNode : public GDAssignableNode {
	GDCLASS(GDVariableNode, GDAssignableNode);

public:
	enum PropertyStyle {
		PROP_NONE,
		PROP_INLINE,
		PROP_SETGET,
	};

protected:
	static void _bind_methods();
	GDScriptParser::VariableNode *node = nullptr;

public:
	PropertyStyle get_property() const;
	Ref<GDFunctionNode> get_setter_as_function() const;
	Ref<GDIdentifierNode> get_setter_as_pointer() const;
	Ref<GDIdentifierNode> get_setter_parameter() const;
	Ref<GDFunctionNode> get_getter_as_function() const;
	Ref<GDIdentifierNode> get_getter_as_pointer() const;
	bool exported() const;
	bool onready() const;
	Dictionary get_export_info() const;
	int get_assignments() const;
	bool is_static() const;

	GDVariableNode();
	~GDVariableNode();

	void set_node(GDScriptParser::Node *p_node) override {
		GDAssignableNode::set_node(p_node);
		node = static_cast<GDScriptParser::VariableNode *>(p_node);
	}
};

class GDWhileNode : public GDNode {
	GDCLASS(GDWhileNode, GDNode);

protected:
	static void _bind_methods();
	GDScriptParser::WhileNode *node = nullptr;

public:
	Ref<GDExpressionNode> get_condition() const;
	Ref<GDSuiteNode> get_loop() const;

	GDWhileNode();
	~GDWhileNode();

	void set_node(GDScriptParser::Node *p_node) override {
		GDNode::set_node(p_node);
		node = static_cast<GDScriptParser::WhileNode *>(p_node);
	}
};

VARIANT_ENUM_CAST(GDNode::Type);
VARIANT_ENUM_CAST(GDMember::Type);
VARIANT_ENUM_CAST(GDDictionaryNode::Style);
VARIANT_ENUM_CAST(GDIdentifierNode::Source);
VARIANT_ENUM_CAST(GDDataType::Kind);
VARIANT_ENUM_CAST(GDDataType::TypeSource);
VARIANT_ENUM_CAST(GDAssignmentNode::Operation);
VARIANT_ENUM_CAST(GDBinaryOpNode::OpType);
VARIANT_ENUM_CAST(GDPatternNode::Type);
VARIANT_ENUM_CAST(GDSuiteLocal::Type);
VARIANT_ENUM_CAST(GDUnaryOpNode::OpType);
VARIANT_ENUM_CAST(GDVariableNode::PropertyStyle);

#endif // GDSCRIPT_EXPOSED_TREE_H
