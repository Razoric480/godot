/*************************************************************************/
/*  gdscript_error_checker.cpp                                           */
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

#include "gdscript_exposed_tree.h"

#include "gdscript_parser.h"
#include "gdscript_parser.h"

void GDMember::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_type"), &GDMember::get_type);
	ClassDB::bind_method(D_METHOD("get_as_class_node"), &GDMember::get_as_class_node);
	ClassDB::bind_method(D_METHOD("get_as_constant_node"), &GDMember::get_as_constant_node);
	ClassDB::bind_method(D_METHOD("get_as_function_node"), &GDMember::get_as_function_node);
	ClassDB::bind_method(D_METHOD("get_as_signal_node"), &GDMember::get_as_signal_node);
	ClassDB::bind_method(D_METHOD("get_as_signal_variable_node"), &GDMember::get_as_signal_variable_node);
	ClassDB::bind_method(D_METHOD("get_as_enum_node"), &GDMember::get_as_enum_node);
	ClassDB::bind_method(D_METHOD("get_as_annotation_node"), &GDMember::get_as_annotation_node);
	ClassDB::bind_method(D_METHOD("get_name"), &GDMember::get_name);
	ClassDB::bind_method(D_METHOD("get_type_name"), &GDMember::get_type_name);
	ClassDB::bind_method(D_METHOD("get_line"), &GDMember::get_line);
	ClassDB::bind_method(D_METHOD("get_source_node"), &GDMember::get_source_node);

	BIND_ENUM_CONSTANT(UNDEFINED);
	BIND_ENUM_CONSTANT(CLASS);
	BIND_ENUM_CONSTANT(CONSTANT);
	BIND_ENUM_CONSTANT(FUNCTION);
	BIND_ENUM_CONSTANT(SIGNAL);
	BIND_ENUM_CONSTANT(VARIABLE);
	BIND_ENUM_CONSTANT(ENUM);
	BIND_ENUM_CONSTANT(ENUM_VALUE);
	BIND_ENUM_CONSTANT(GROUP);
}

GDMember::Type GDMember::get_type() const {
	return static_cast<GDMember::Type>(node->type);
}

Ref<GDClassNode> GDMember::get_as_class_node() const {
	if (get_type() != GDMember::Type::CLASS) {
		return nullptr;
	}
	return GDClassNode::build_from<GDClassNode>(node->m_class);
}

Ref<GDConstantNode> GDMember::get_as_constant_node() const {
	if (get_type() != GDMember::Type::CONSTANT) {
		return nullptr;
	}
	return GDConstantNode::build_from<GDConstantNode>(node->constant);
}

Ref<GDFunctionNode> GDMember::get_as_function_node() const {
	if (get_type() != GDMember::Type::FUNCTION) {
		return nullptr;
	}
	return GDFunctionNode::build_from<GDFunctionNode>(node->function);
}

Ref<GDSignalNode> GDMember::get_as_signal_node() const {
	if (get_type() != GDMember::Type::SIGNAL) {
		return nullptr;
	}
	return GDSignalNode::build_from<GDSignalNode>(node->signal);
}

Ref<GDVariableNode> GDMember::get_as_signal_variable_node() const {
	if (get_type() != GDMember::Type::VARIABLE) {
		return nullptr;
	}
	return GDVariableNode::build_from<GDVariableNode>(node->variable);
}

Ref<GDEnumNode> GDMember::get_as_enum_node() const {
	if (get_type() != GDMember::Type::ENUM) {
		return nullptr;
	}
	return GDEnumNode::build_from<GDEnumNode>(node->m_enum);
}

Ref<GDAnnotationNode> GDMember::get_as_annotation_node() const {
	if (get_type() != GDMember::Type::GROUP) {
		return nullptr;
	}
	return GDAnnotationNode::build_from<GDAnnotationNode>(node->annotation);
}

String GDMember::get_name() const {
	return node->get_name();
}

String GDMember::get_type_name() const {
	return node->get_type_name();
}

int GDMember::get_line() const {
	return node->get_line();
}

Ref<GDNode> GDMember::get_source_node() const {
	switch (node->type) {
		case GDMember::Type::CLASS:
			return GDNode::build_from<GDClassNode>(node->m_class);
		case GDMember::Type::CONSTANT:
			return GDNode::build_from<GDConstantNode>(node->constant);
		case GDMember::Type::FUNCTION:
			return GDNode::build_from<GDFunctionNode>(node->function);
		case GDMember::Type::VARIABLE:
			return GDNode::build_from<GDVariableNode>(node->variable);
		case GDMember::Type::ENUM:
			return GDNode::build_from<GDEnumNode>(node->m_enum);
		case GDMember::Type::ENUM_VALUE:
			return nullptr;
		case GDMember::Type::SIGNAL:
			return GDNode::build_from<GDSignalNode>(node->signal);
		case GDMember::Type::GROUP:
			return GDNode::build_from<GDAnnotationNode>(node->annotation);
		case GDMember::Type::UNDEFINED:
			return nullptr;
	}

	return nullptr;
}

GDMember::GDMember() = default;

GDMember::~GDMember() {
}

void GDMember::set_node(const GDScriptParser::ClassNode::Member *p_node) {
	node = p_node;
}

Ref<GDMember> GDMember::build_from(const GDScriptParser::ClassNode::Member *p_node) {
	Ref member = memnew(GDMember);
	member->set_node(p_node);
	return member;
}

void GDNode::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_type"), &GDNode::get_type);
	ClassDB::bind_method(D_METHOD("is_expression"), &GDNode::is_expression);
	ClassDB::bind_method(D_METHOD("get_start_line"), &GDNode::get_start_line);
	ClassDB::bind_method(D_METHOD("get_end_line"), &GDNode::get_end_line);
	ClassDB::bind_method(D_METHOD("get_start_column"), &GDNode::get_start_column);
	ClassDB::bind_method(D_METHOD("get_end_column"), &GDNode::get_end_column);
	ClassDB::bind_method(D_METHOD("get_next"), &GDNode::get_next);

	BIND_ENUM_CONSTANT(NONE);
	BIND_ENUM_CONSTANT(ANNOTATION);
	BIND_ENUM_CONSTANT(ARRAY);
	BIND_ENUM_CONSTANT(ASSERT);
	BIND_ENUM_CONSTANT(ASSIGNMENT);
	BIND_ENUM_CONSTANT(AWAIT);
	BIND_ENUM_CONSTANT(BINARY_OPERATOR);
	BIND_ENUM_CONSTANT(BREAK);
	BIND_ENUM_CONSTANT(BREAKPOINT);
	BIND_ENUM_CONSTANT(CALL);
	BIND_ENUM_CONSTANT(CAST);
	BIND_ENUM_CONSTANT(CLASS);
	BIND_ENUM_CONSTANT(CONSTANT);
	BIND_ENUM_CONSTANT(CONTINUE);
	BIND_ENUM_CONSTANT(DICTIONARY);
	BIND_ENUM_CONSTANT(ENUM);
	BIND_ENUM_CONSTANT(FOR);
	BIND_ENUM_CONSTANT(FUNCTION);
	BIND_ENUM_CONSTANT(GET_NODE);
	BIND_ENUM_CONSTANT(IDENTIFIER);
	BIND_ENUM_CONSTANT(IF);
	BIND_ENUM_CONSTANT(LAMBDA);
	BIND_ENUM_CONSTANT(LITERAL);
	BIND_ENUM_CONSTANT(MATCH);
	BIND_ENUM_CONSTANT(MATCH_BRANCH);
	BIND_ENUM_CONSTANT(PARAMETER);
	BIND_ENUM_CONSTANT(PASS);
	BIND_ENUM_CONSTANT(PATTERN);
	BIND_ENUM_CONSTANT(PRELOAD);
	BIND_ENUM_CONSTANT(RETURN);
	BIND_ENUM_CONSTANT(SELF);
	BIND_ENUM_CONSTANT(SIGNAL);
	BIND_ENUM_CONSTANT(SUBSCRIPT);
	BIND_ENUM_CONSTANT(SUITE);
	BIND_ENUM_CONSTANT(TERNARY_OPERATOR);
	BIND_ENUM_CONSTANT(TYPE);
	BIND_ENUM_CONSTANT(TYPE_TEST);
	BIND_ENUM_CONSTANT(UNARY_OPERATOR);
	BIND_ENUM_CONSTANT(VARIABLE);
	BIND_ENUM_CONSTANT(WHILE);
}

template <typename T>
Ref<T> GDNode::build_from(GDScriptParser::Node *p_node) {
	Ref<T> result = memnew(T);
	result->set_node(p_node);
	result->base_node = p_node;
	return result;
}

GDNode::Type GDNode::get_type() const {
	return static_cast<GDNode::Type>(base_node->type);
}

bool GDNode::is_expression() const {
	return base_node->is_expression();
}

int GDNode::get_start_line() const {
	return base_node->start_line;
}

int GDNode::get_end_line() const {
	return base_node->end_line;
}

int GDNode::get_start_column() const {
	return base_node->start_column;
}

int GDNode::get_end_column() const {
	return base_node->end_column;
}

Ref<GDNode> GDNode::get_next() const {
	return build_from(base_node->next);
}

Ref<GDNode> GDNode::build_from(GDScriptParser::Node *p_node) {
	switch (p_node->type) {
		case ANNOTATION:
			return GDNode::build_from<GDAnnotationNode>(p_node);
		case ARRAY:
			return GDNode::build_from<GDArrayNode>(p_node);
		case ASSERT:
			return GDNode::build_from<GDAssertNode>(p_node);
		case ASSIGNMENT:
			return GDNode::build_from<GDAssignableNode>(p_node);
		case AWAIT:
			return GDNode::build_from<GDAwaitNode>(p_node);
		case BINARY_OPERATOR:
			return GDNode::build_from<GDBinaryOpNode>(p_node);
		case BREAK:
			return GDNode::build_from<GDBreakNode>(p_node);
		case BREAKPOINT:
			return GDNode::build_from<GDBreakpointNode>(p_node);
		case CALL:
			return GDNode::build_from<GDCallNode>(p_node);
		case CAST:
			return GDNode::build_from<GDCastNode>(p_node);
		case CLASS:
			return GDNode::build_from<GDClassNode>(p_node);
		case CONSTANT:
			return GDNode::build_from<GDConstantNode>(p_node);
		case CONTINUE:
			return GDNode::build_from<GDContinueNode>(p_node);
		case DICTIONARY:
			return GDNode::build_from<GDDictionaryNode>(p_node);
		case ENUM:
			return GDNode::build_from<GDEnumNode>(p_node);
		case FOR:
			return GDNode::build_from<GDForNode>(p_node);
		case FUNCTION:
			return GDNode::build_from<GDFunctionNode>(p_node);
		case GET_NODE:
			return GDNode::build_from<GDGetNodeNode>(p_node);
		case IDENTIFIER:
			return GDNode::build_from<GDIdentifierNode>(p_node);
		case IF:
			return GDNode::build_from<GDIfNode>(p_node);
		case LAMBDA:
			return GDNode::build_from<GDLambdaNode>(p_node);
		case LITERAL:
			return GDNode::build_from<GDLiteralNode>(p_node);
		case MATCH:
			return GDNode::build_from<GDMatchNode>(p_node);
		case MATCH_BRANCH:
			return GDNode::build_from<GDMatchBranchNode>(p_node);
		case PARAMETER:
			return GDNode::build_from<GDParameterNode>(p_node);
		case PASS:
			return GDNode::build_from<GDPassNode>(p_node);
		case PATTERN:
			return GDNode::build_from<GDPatternNode>(p_node);
		case PRELOAD:
			return GDNode::build_from<GDPreloadNode>(p_node);
		case RETURN:
			return GDNode::build_from<GDReturnNode>(p_node);
		case SELF:
			return GDNode::build_from<GDSelfNode>(p_node);
		case SIGNAL:
			return GDNode::build_from<GDSignalNode>(p_node);
		case SUBSCRIPT:
			return GDNode::build_from<GDSubscriptNode>(p_node);
		case SUITE:
			return GDNode::build_from<GDSuiteNode>(p_node);
		case TERNARY_OPERATOR:
			return GDNode::build_from<GDTernaryOpNode>(p_node);
		case TYPE:
			return GDNode::build_from<GDTypeNode>(p_node);
		case TYPE_TEST:
			return GDNode::build_from<GDTypeTestNode>(p_node);
		case UNARY_OPERATOR:
			return GDNode::build_from<GDUnaryOpNode>(p_node);
		case VARIABLE:
			return GDNode::build_from<GDVariableNode>(p_node);
		case WHILE:
			return GDNode::build_from<GDWhileNode>(p_node);
		default:
		case NONE:
			return nullptr;
	}
}

GDNode::GDNode() = default;
GDNode::~GDNode() {}


void GDAnnotationNode::_bind_methods() {
}

GDAnnotationNode::GDAnnotationNode() = default;
GDAnnotationNode::~GDAnnotationNode() {
}

void GDArrayNode::_bind_methods() {
}

GDArrayNode::GDArrayNode() = default;
GDArrayNode::~GDArrayNode() {
}

void GDAssertNode::_bind_methods() {
}

GDAssertNode::GDAssertNode() = default;
GDAssertNode::~GDAssertNode() {
}

void GDAssignableNode::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_initializer"), &GDAssignableNode::get_initializer);
}

Ref<GDExpressionNode> GDAssignableNode::get_initializer() const {
	return build_from<GDExpressionNode>(node->initializer);
}

GDAssignableNode::GDAssignableNode() = default;
GDAssignableNode::~GDAssignableNode() {
}

void GDAssignmentNode::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_assigned_value"), &GDAssignmentNode::get_assigned_value);
}

GDAssignmentNode::GDAssignmentNode() = default;
GDAssignmentNode::~GDAssignmentNode() {
}

Ref<GDExpressionNode> GDAssignmentNode::get_assigned_value() const {
	return build_from<GDExpressionNode>(node->assigned_value);
}

void GDAwaitNode::_bind_methods() {
}

GDAwaitNode::GDAwaitNode() = default;
GDAwaitNode::~GDAwaitNode() {
}

void GDBinaryOpNode::_bind_methods() {
}

GDBinaryOpNode::GDBinaryOpNode() = default;
GDBinaryOpNode::~GDBinaryOpNode() {
}

void GDBreakNode::_bind_methods() {
}

GDBreakNode::GDBreakNode() = default;
GDBreakNode::~GDBreakNode() {
}

void GDBreakpointNode::_bind_methods() {
}

GDBreakpointNode::GDBreakpointNode() = default;
GDBreakpointNode::~GDBreakpointNode() {
}

void GDCallNode::_bind_methods() {
}

GDCallNode::GDCallNode() = default;
GDCallNode::~GDCallNode() {
}

void GDCastNode::_bind_methods() {
}

GDCastNode::GDCastNode() = default;
GDCastNode::~GDCastNode() {
}

void GDClassNode::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_identifier"), &GDClassNode::get_identifier);
	ClassDB::bind_method(D_METHOD("get_icon_path"), &GDClassNode::get_icon_path);
	ClassDB::bind_method(D_METHOD("get_simplified_icon_path"), &GDClassNode::get_simplified_icon_path);
	ClassDB::bind_method(D_METHOD("get_members"), &GDClassNode::get_members);
	ClassDB::bind_method(D_METHOD("get_member_indices"), &GDClassNode::get_member_indices);
	ClassDB::bind_method(D_METHOD("get_outer_class"), &GDClassNode::get_outer_class);
	ClassDB::bind_method(D_METHOD("extends_used"), &GDClassNode::extends_used);
	ClassDB::bind_method(D_METHOD("onready_used"), &GDClassNode::onready_used);
	ClassDB::bind_method(D_METHOD("is_abstract"), &GDClassNode::is_abstract);
	ClassDB::bind_method(D_METHOD("has_static_data"), &GDClassNode::has_static_data);
	ClassDB::bind_method(D_METHOD("annotated_static_unload"), &GDClassNode::annotated_static_unload);
	ClassDB::bind_method(D_METHOD("get_extends_path"), &GDClassNode::get_extends_path);
	ClassDB::bind_method(D_METHOD("get_extends"), &GDClassNode::get_extends);
	ClassDB::bind_method(D_METHOD("get_fqcn"), &GDClassNode::get_fqcn);
	ClassDB::bind_method(D_METHOD("resolved_interface"), &GDClassNode::resolved_interface);
	ClassDB::bind_method(D_METHOD("resolved_body"), &GDClassNode::resolved_body);
	ClassDB::bind_method(D_METHOD("get_global_name"), &GDClassNode::get_global_name);
	ClassDB::bind_method(D_METHOD("get_member", "member_name"), &GDClassNode::get_member);
	ClassDB::bind_method(D_METHOD("has_member", "member_name"), &GDClassNode::has_member);
	ClassDB::bind_method(D_METHOD("has_function", "function_name"), &GDClassNode::has_function);
}

Ref<GDIdentifierNode> GDClassNode::get_identifier() const {
	return build_from<GDIdentifierNode>(node->identifier);
}

String GDClassNode::get_icon_path() const {
	return node->icon_path;
}

String GDClassNode::get_simplified_icon_path() const {
	return node->simplified_icon_path;
}

TypedArray<GDMember> GDClassNode::get_members() const {
	TypedArray<GDMember> members;
	for (int i=0; i<node->members.size(); i++) {

		members.append(GDMember::build_from(&node->members[i]));
	}
	return members;
}

Dictionary GDClassNode::get_member_indices() const {
	Dictionary member_indices;
	for (int i=0; i<node->members.size(); i++) {
		member_indices[node->members[i].get_name()] = i;
	}
	return member_indices;
}

Ref<GDClassNode> GDClassNode::get_outer_class() const {
	return build_from<GDClassNode>(node->outer);
}

bool GDClassNode::extends_used() const {
	return node->extends_used;
}

bool GDClassNode::onready_used() const {
	return node->onready_used;
}

bool GDClassNode::is_abstract() const {
	return node->is_abstract;
}

bool GDClassNode::has_static_data() const {
	return node->has_static_data;
}

bool GDClassNode::annotated_static_unload() const {
	return node->annotated_static_unload;
}

String GDClassNode::get_extends_path() const {
	return node->extends_path;
}

TypedArray<GDIdentifierNode> GDClassNode::get_extends() const {
	TypedArray<GDIdentifierNode> extends;
	for (int i=0; i<node->extends.size(); i++) {
		extends.append(build_from<GDIdentifierNode>(node->extends[i]));
	}
	return extends;
}

String GDClassNode::get_fqcn() const {
	return node->fqcn;
}

bool GDClassNode::resolved_interface() const {
	return node->resolved_interface;
}

bool GDClassNode::resolved_body() const {
	return node->resolved_body;
}

StringName GDClassNode::get_global_name() const {
	return node->get_global_name();
}

Ref<GDMember> GDClassNode::get_member(const StringName &p_name) {
	if (_cached_members.has(p_name)) {
		return _cached_members[p_name];
	}
	GDMember * member = memnew(GDMember);
	member->set_node(&node->members[node->members_indices[p_name]]);
	_cached_members[p_name] = member;
	return _cached_members[p_name];
}

bool GDClassNode::has_member(const StringName &p_name) const {
	return node->has_member(p_name);
}

bool GDClassNode::has_function(const StringName &p_name) const {
	return node->has_function(p_name);
}


GDClassNode::GDClassNode() = default;
GDClassNode::~GDClassNode() {
	_cached_members.clear();
}

void GDConstantNode::_bind_methods() {
}

GDConstantNode::GDConstantNode() = default;
GDConstantNode::~GDConstantNode() {
}

void GDContinueNode::_bind_methods() {
}

GDContinueNode::GDContinueNode() = default;
GDContinueNode::~GDContinueNode() {
}

GDPair::GDPair() = default;
GDPair::~GDPair() {}

void GDPair::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_key"), &GDPair::get_key);
	ClassDB::bind_method(D_METHOD("get_value"), &GDPair::get_value);
}

void GDPair::set_node(const GDScriptParser::DictionaryNode::Pair *p_node) {
	node = p_node;
}

Ref<GDPair> GDPair::build_from(const GDScriptParser::DictionaryNode::Pair *p_node) {
	Ref pair = memnew(GDPair);
	pair->set_node(p_node);
	return pair;
}

Ref<GDExpressionNode> GDPair::get_key() const {
	return GDNode::build_from<GDExpressionNode>(node->key);
}

Ref<GDExpressionNode> GDPair::get_value() const {
	return GDNode::build_from<GDExpressionNode>(node->value);
}

void GDDictionaryNode::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_elements"), &GDDictionaryNode::get_elements);
	ClassDB::bind_method(D_METHOD("get_style"), &GDDictionaryNode::get_style);

	BIND_ENUM_CONSTANT(LUA_TABLE);
	BIND_ENUM_CONSTANT(PYTHON_DICT);
}

TypedArray<GDPair> GDDictionaryNode::get_elements() const {
	TypedArray<GDPair> elements;
	for (int i=0; i<node->elements.size(); i++) {
		elements.append(GDPair::build_from(&node->elements[i]));
	}
	return elements;
}

GDDictionaryNode::Style GDDictionaryNode::get_style() const {
	return static_cast<GDDictionaryNode::Style>(node->style);
}

GDDictionaryNode::GDDictionaryNode() = default;
GDDictionaryNode::~GDDictionaryNode() {
}

void GDEnumNode::_bind_methods() {
}

GDEnumNode::GDEnumNode() = default;
GDEnumNode::~GDEnumNode() {
}

void GDExpressionNode::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_reduced_value"), &GDExpressionNode::get_reduced_value);
}

Variant GDExpressionNode::get_reduced_value() const {
	return node->reduced_value;
}

GDExpressionNode::GDExpressionNode() = default;
GDExpressionNode::~GDExpressionNode() {
}

void GDForNode::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_variable"), &GDForNode::get_variable);
	ClassDB::bind_method(D_METHOD("get_datatype_specifier"), &GDForNode::get_datatype_specifier);
	ClassDB::bind_method(D_METHOD("use_conversion_assign"), &GDForNode::use_conversion_assign);
	ClassDB::bind_method(D_METHOD("get_list"), &GDForNode::get_list);
	ClassDB::bind_method(D_METHOD("get_loop"), &GDForNode::get_loop);
}

Ref<GDIdentifierNode> GDForNode::get_variable() const {
	return build_from<GDIdentifierNode>(node->variable);
}

Ref<GDTypeNode> GDForNode::get_datatype_specifier() const {
	return build_from<GDTypeNode>(node->datatype_specifier);
}

bool GDForNode::use_conversion_assign() const {
	return node->use_conversion_assign;
}

Ref<GDExpressionNode> GDForNode::get_list() const {
	return build_from<GDExpressionNode>(node->list);
}

Ref<GDSuiteNode> GDForNode::get_loop() const {
	return build_from<GDSuiteNode>(node->loop);
}

GDForNode::GDForNode() = default;
GDForNode::~GDForNode() {
}

void GDFunctionNode::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_identifier"), &GDFunctionNode::get_identifier);
	ClassDB::bind_method(D_METHOD("get_parameters"), &GDFunctionNode::get_parameters);
	ClassDB::bind_method(D_METHOD("get_parameter_indices"), &GDFunctionNode::get_parameter_indices);
	ClassDB::bind_method(D_METHOD("get_rest_parameter"), &GDFunctionNode::get_rest_parameter);
	ClassDB::bind_method(D_METHOD("get_return_type"), &GDFunctionNode::get_return_type);
	ClassDB::bind_method(D_METHOD("get_body"), &GDFunctionNode::get_body);
	ClassDB::bind_method(D_METHOD("is_abstract"), &GDFunctionNode::is_abstract);
	ClassDB::bind_method(D_METHOD("is_static"), &GDFunctionNode::is_static);
	ClassDB::bind_method(D_METHOD("is_coroutine"), &GDFunctionNode::is_coroutine);
	ClassDB::bind_method(D_METHOD("get_rpc_config"), &GDFunctionNode::get_rpc_config);
	ClassDB::bind_method(D_METHOD("get_source_lambda"), &GDFunctionNode::get_source_lambda);
	ClassDB::bind_method(D_METHOD("get_default_arg_values"), &GDFunctionNode::get_default_arg_values);
	ClassDB::bind_method(D_METHOD("resolved_signature"), &GDFunctionNode::resolved_signature);
	ClassDB::bind_method(D_METHOD("resolved_body"), &GDFunctionNode::resolved_body);
	ClassDB::bind_method(D_METHOD("is_vararg"), &GDFunctionNode::is_vararg);
}

Ref<GDIdentifierNode> GDFunctionNode::get_identifier() const {
	return build_from<GDIdentifierNode>(node->identifier);
}

TypedArray<GDParameterNode> GDFunctionNode::get_parameters() const {
	TypedArray<GDParameterNode> parameters;
	for (int i=0; i<node->parameters.size(); i++) {
		parameters.append(build_from<GDParameterNode>(node->parameters[i]));
	}
	return parameters;
}

Dictionary GDFunctionNode::get_parameter_indices() const {
	Dictionary indices;
	for (int i=0; i<node->parameters.size(); i++) {
		indices[node->parameters[i]->identifier->name] = i;
	}
	return indices;
}

Ref<GDParameterNode> GDFunctionNode::get_rest_parameter() const {
	return build_from<GDParameterNode>(node->rest_parameter);
}

Ref<GDTypeNode> GDFunctionNode::get_return_type() const {
	return build_from<GDTypeNode>(node->return_type);
}

Ref<GDSuiteNode> GDFunctionNode::get_body() const {
	return build_from<GDSuiteNode>(node->body);
}

bool GDFunctionNode::is_abstract() const {
	return node->is_abstract;
}

bool GDFunctionNode::is_static() const {
	return node->is_static;
}

bool GDFunctionNode::is_coroutine() const {
	return node->is_coroutine;
}

Variant GDFunctionNode::get_rpc_config() const {
	return node->rpc_config;
}

Ref<GDLambdaNode> GDFunctionNode::get_source_lambda() const {
	return build_from<GDLambdaNode>(node->source_lambda);
}

Array GDFunctionNode::get_default_arg_values() const {
	Array arg_values;
	for (int i=0; i<node->default_arg_values.size(); i++) {
		arg_values.push_back(node->default_arg_values[i]);
	}
	return arg_values;
}

bool GDFunctionNode::resolved_signature() const {
	return node->resolved_signature;
}

bool GDFunctionNode::resolved_body() const {
	return node->resolved_body;
}

bool GDFunctionNode::is_vararg() const {
	return node->is_vararg();
}

GDFunctionNode::GDFunctionNode() = default;
GDFunctionNode::~GDFunctionNode() {
}

void GDGetNodeNode::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_full_path"), &GDGetNodeNode::get_full_path);
	ClassDB::bind_method(D_METHOD("use_dollar"), &GDGetNodeNode::use_dollar);
}

String GDGetNodeNode::get_full_path() const {
	return node->full_path;
}

bool GDGetNodeNode::use_dollar() const {
	return node->use_dollar;
}

GDGetNodeNode::GDGetNodeNode() = default;
GDGetNodeNode::~GDGetNodeNode() {
}

void GDIdentifierNode::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_name"), &GDIdentifierNode::get_name);
	ClassDB::bind_method(D_METHOD("get_suite"), &GDIdentifierNode::get_suite);
	ClassDB::bind_method(D_METHOD("get_source"), &GDIdentifierNode::get_source);
	ClassDB::bind_method(D_METHOD("get_source_as_parameter"), &GDIdentifierNode::get_source_as_parameter);
	ClassDB::bind_method(D_METHOD("get_source_as_bind"), &GDIdentifierNode::get_source_as_bind);
	ClassDB::bind_method(D_METHOD("get_source_as_variable"), &GDIdentifierNode::get_source_as_variable);
	ClassDB::bind_method(D_METHOD("get_source_as_constant"), &GDIdentifierNode::get_source_as_constant);
	ClassDB::bind_method(D_METHOD("get_source_as_signal"), &GDIdentifierNode::get_source_as_signal);
	ClassDB::bind_method(D_METHOD("function_source_is_static"), &GDIdentifierNode::function_source_is_static);
	ClassDB::bind_method(D_METHOD("get_source_function"), &GDIdentifierNode::get_source_function);
	ClassDB::bind_method(D_METHOD("get_usages"), &GDIdentifierNode::get_usages);

	BIND_ENUM_CONSTANT(UNDEFINED_SOURCE);
	BIND_ENUM_CONSTANT(FUNCTION_PARAMETER);
	BIND_ENUM_CONSTANT(LOCAL_VARIABLE);
	BIND_ENUM_CONSTANT(LOCAL_CONSTANT);
	BIND_ENUM_CONSTANT(LOCAL_ITERATOR);
	BIND_ENUM_CONSTANT(LOCAL_BIND);
	BIND_ENUM_CONSTANT(MEMBER_VARIABLE);
	BIND_ENUM_CONSTANT(MEMBER_CONSTANT);
	BIND_ENUM_CONSTANT(MEMBER_FUNCTION);
	BIND_ENUM_CONSTANT(MEMBER_SIGNAL);
	BIND_ENUM_CONSTANT(MEMBER_CLASS);
	BIND_ENUM_CONSTANT(INHERITED_VARIABLE);
	BIND_ENUM_CONSTANT(STATIC_VARIABLE);
	BIND_ENUM_CONSTANT(NATIVE_CLASS);
}

StringName GDIdentifierNode::get_name() const {
	return node->name;
}

Ref<GDSuiteNode> GDIdentifierNode::get_suite() const {
	return build_from<GDSuiteNode>(node->suite);
}

GDIdentifierNode::Source GDIdentifierNode::get_source() const {
	return static_cast<GDIdentifierNode::Source>(node->source);
}

Ref<GDParameterNode> GDIdentifierNode::get_source_as_parameter() const {
	if (node->source != GDScriptParser::IdentifierNode::Source::FUNCTION_PARAMETER) {
		return nullptr;
	}
	return build_from<GDParameterNode>(node->parameter_source);
}

Ref<GDIdentifierNode> GDIdentifierNode::get_source_as_bind() const {
	if (node->source != GDScriptParser::IdentifierNode::Source::LOCAL_BIND) {
		return nullptr;
	}

	return build_from<GDIdentifierNode>(node->bind_source);
}

Ref<GDVariableNode> GDIdentifierNode::get_source_as_variable() const {
	if (
		node->source != GDScriptParser::IdentifierNode::Source::LOCAL_VARIABLE &&
		node->source != GDScriptParser::IdentifierNode::Source::MEMBER_VARIABLE &&
		node->source != GDScriptParser::IdentifierNode::Source::INHERITED_VARIABLE &&
		node->source != GDScriptParser::IdentifierNode::Source::STATIC_VARIABLE &&
		node->source != GDScriptParser::IdentifierNode::Source::LOCAL_CONSTANT) {
		return nullptr;
	}
	return build_from<GDVariableNode>(node->variable_source);
}

Ref<GDConstantNode> GDIdentifierNode::get_source_as_constant() const {
	if (
		node->source != GDScriptParser::IdentifierNode::Source::LOCAL_CONSTANT &&
		node->source != GDScriptParser::IdentifierNode::Source::MEMBER_CONSTANT) {
		return nullptr;
	}
	return build_from<GDConstantNode>(node->constant_source);
}

Ref<GDSignalNode> GDIdentifierNode::get_source_as_signal() const {
	if (node->source != GDScriptParser::IdentifierNode::Source::MEMBER_SIGNAL) {
		return nullptr;
	}
	return build_from<GDSignalNode>(node->signal_source);
}

Ref<GDFunctionNode> GDIdentifierNode::get_source_as_function() const {
	if (node->source != GDScriptParser::IdentifierNode::Source::MEMBER_FUNCTION) {
		return nullptr;
	}
	return build_from<GDFunctionNode>(node->function_source);
}

bool GDIdentifierNode::function_source_is_static() const {
	return node->function_source_is_static;
}

Ref<GDFunctionNode> GDIdentifierNode::get_source_function() const {
	return build_from<GDFunctionNode>(node->source_function);
}

int GDIdentifierNode::get_usages() const {
	return node->usages;
}

GDIdentifierNode::GDIdentifierNode() = default;
GDIdentifierNode::~GDIdentifierNode() {
}

void GDIfNode::_bind_methods() {
}

Ref<GDExpressionNode> GDIfNode::get_condition() const {
	return build_from<GDExpressionNode>(node->condition);
}

GDIfNode::GDIfNode() = default;
GDIfNode::~GDIfNode() {
}

void GDLambdaNode::_bind_methods() {
}

GDLambdaNode::GDLambdaNode() = default;
GDLambdaNode::~GDLambdaNode() {
}

void GDLiteralNode::_bind_methods() {
}

GDLiteralNode::GDLiteralNode() = default;
GDLiteralNode::~GDLiteralNode() {
}

void GDMatchNode::_bind_methods() {
}

GDMatchNode::GDMatchNode() = default;
GDMatchNode::~GDMatchNode() {
}

void GDMatchBranchNode::_bind_methods() {
}

GDMatchBranchNode::GDMatchBranchNode() = default;
GDMatchBranchNode::~GDMatchBranchNode() {
}

void GDParameterNode::_bind_methods() {
}

GDParameterNode::GDParameterNode() = default;
GDParameterNode::~GDParameterNode() {
}

void GDPassNode::_bind_methods() {
}

GDPassNode::GDPassNode() = default;
GDPassNode::~GDPassNode() {
}

void GDPatternNode::_bind_methods() {
}

GDPatternNode::GDPatternNode() = default;
GDPatternNode::~GDPatternNode() {
}

void GDPreloadNode::_bind_methods() {
}

GDPreloadNode::GDPreloadNode() = default;
GDPreloadNode::~GDPreloadNode() {
}

void GDReturnNode::_bind_methods() {
}

GDReturnNode::GDReturnNode() = default;
GDReturnNode::~GDReturnNode() {
}

void GDSelfNode::_bind_methods() {
}

GDSelfNode::GDSelfNode() = default;
GDSelfNode::~GDSelfNode() {
}

void GDSignalNode::_bind_methods() {
}

GDSignalNode::GDSignalNode() = default;
GDSignalNode::~GDSignalNode() {
}

void GDSubscriptNode::_bind_methods() {
}

GDSubscriptNode::GDSubscriptNode() = default;
GDSubscriptNode::~GDSubscriptNode() {
}

void GDSuiteNode::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_statements"), &GDSuiteNode::get_statements);
}

TypedArray<GDNode> GDSuiteNode::get_statements() const {
	TypedArray<GDNode> statements;
	for (int i = 0; i < node->statements.size(); ++i) {
		statements.push_back(build_from(node->statements[i]));
	}
	return statements;
}

GDSuiteNode::GDSuiteNode() = default;
GDSuiteNode::~GDSuiteNode() {
}

void GDTernaryOpNode::_bind_methods() {
}

GDTernaryOpNode::GDTernaryOpNode() = default;
GDTernaryOpNode::~GDTernaryOpNode() {
}

void GDTypeNode::_bind_methods() {
}

GDTypeNode::GDTypeNode() = default;
GDTypeNode::~GDTypeNode() {
}

void GDTypeTestNode::_bind_methods() {
}

GDTypeTestNode::GDTypeTestNode() = default;
GDTypeTestNode::~GDTypeTestNode() {
}

void GDUnaryOpNode::_bind_methods() {
}

GDUnaryOpNode::GDUnaryOpNode() = default;
GDUnaryOpNode::~GDUnaryOpNode() {
}

void GDVariableNode::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_export_info"), &GDVariableNode::get_export_info);
}

GDVariableNode::GDVariableNode() = default;
GDVariableNode::~GDVariableNode() {
}

Dictionary GDVariableNode::get_export_info() const {
	return node->export_info;
}

void GDWhileNode::_bind_methods() {
}

GDWhileNode::GDWhileNode() = default;
GDWhileNode::~GDWhileNode() {
}

