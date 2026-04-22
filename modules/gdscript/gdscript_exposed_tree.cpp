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

#include <csignal>

void GDDataType::_bind_method() {
	ClassDB::bind_method(D_METHOD("get_container_element_types"), &GDDataType::get_container_element_types);
	ClassDB::bind_method(D_METHOD("get_kind"), &GDDataType::get_kind);
	ClassDB::bind_method(D_METHOD("get_type_source"), &GDDataType::get_type_source);
	ClassDB::bind_method(D_METHOD("is_constant"), &GDDataType::is_constant);
	ClassDB::bind_method(D_METHOD("is_read_only"), &GDDataType::is_read_only);
	ClassDB::bind_method(D_METHOD("is_meta_type"), &GDDataType::is_meta_type);
	ClassDB::bind_method(D_METHOD("is_pseudo_type"), &GDDataType::is_pseudo_type);
	ClassDB::bind_method(D_METHOD("is_coroutine"), &GDDataType::is_coroutine);
	ClassDB::bind_method(D_METHOD("get_builtin_type"), &GDDataType::get_builtin_type);
	ClassDB::bind_method(D_METHOD("get_native_type"), &GDDataType::get_native_type);
	ClassDB::bind_method(D_METHOD("get_enum_type"), &GDDataType::get_enum_type);
	ClassDB::bind_method(D_METHOD("get_script_type"), &GDDataType::get_script_type);
	ClassDB::bind_method(D_METHOD("get_script_path"), &GDDataType::get_script_path);
	ClassDB::bind_method(D_METHOD("get_class_type"), &GDDataType::get_class_type);
	ClassDB::bind_method(D_METHOD("get_method_info"), &GDDataType::get_method_info);
	ClassDB::bind_method(D_METHOD("get_enum_values"), &GDDataType::get_enum_values);
	ClassDB::bind_method(D_METHOD("is_set"), &GDDataType::is_set);
	ClassDB::bind_method(D_METHOD("is_resolving"), &GDDataType::is_resolving);
	ClassDB::bind_method(D_METHOD("has_no_type"), &GDDataType::has_no_type);
	ClassDB::bind_method(D_METHOD("is_variant"), &GDDataType::is_variant);
	ClassDB::bind_method(D_METHOD("is_hard_type"), &GDDataType::is_hard_type);
	ClassDB::bind_method(D_METHOD("to_string"), &GDDataType::to_string);
	ClassDB::bind_method(D_METHOD("to_string_strict"), &GDDataType::to_string_strict);
	ClassDB::bind_method(D_METHOD("to_property_info", "name"), &GDDataType::to_property_info);
	ClassDB::bind_method(D_METHOD("get_container_element_type_count"), &GDDataType::get_container_element_type_count);
	ClassDB::bind_method(D_METHOD("has_container_element_type", "index"), &GDDataType::has_container_element_type);
	ClassDB::bind_method(D_METHOD("has_container_element_types"), &GDDataType::has_container_element_types);
	ClassDB::bind_method(D_METHOD("is_typed_container_type"), &GDDataType::is_typed_container_type);
	ClassDB::bind_method(D_METHOD("can_reference", "other"), &GDDataType::can_reference);

	BIND_ENUM_CONSTANT(BUILTIN);
	BIND_ENUM_CONSTANT(NATIVE);
	BIND_ENUM_CONSTANT(SCRIPT);
	BIND_ENUM_CONSTANT(CLASS);
	BIND_ENUM_CONSTANT(ENUM);
	BIND_ENUM_CONSTANT(VARIANT);
	BIND_ENUM_CONSTANT(RESOLVING);
	BIND_ENUM_CONSTANT(UNRESOLVED);

	BIND_ENUM_CONSTANT(UNDETECTED);
	BIND_ENUM_CONSTANT(INFERRED);
	BIND_ENUM_CONSTANT(ANNOTATED_EXPLICIT);
	BIND_ENUM_CONSTANT(ANNOTATED_INFERRED);
}

GDDataType::GDDataType() {
}

GDDataType::~GDDataType() {
}

TypedArray<GDDataType> GDDataType::get_container_element_types() const {
	TypedArray<GDDataType> types;
	for (int i = 0; i < node->container_element_types.size(); ++i) {
		Ref<GDDataType> type = memnew(GDDataType);
		type->set_node(&node->container_element_types[i]);
		types.push_back(type);
	}
	return types;
}

GDDataType::Kind GDDataType::get_kind() const {
	return static_cast<Kind>(node->kind);
}

GDDataType::TypeSource GDDataType::get_type_source() const {
	return static_cast<TypeSource>(node->type_source);
}

bool GDDataType::is_constant() const {
	return node->is_constant;
}

bool GDDataType::is_read_only() const {
	return node->is_read_only;
}

bool GDDataType::is_meta_type() const {
	return node->is_meta_type;
}

bool GDDataType::is_pseudo_type() const {
	return node->is_pseudo_type;
}

bool GDDataType::is_coroutine() const {
	return node->is_coroutine;
}

Variant::Type GDDataType::get_builtin_type() const {
	return node->builtin_type;
}

StringName GDDataType::get_native_type() const {
	return node->native_type;
}

StringName GDDataType::get_enum_type() const {
	return node->enum_type;
}

Ref<Script> GDDataType::get_script_type() const {
	return node->script_type;
}

String GDDataType::get_script_path() const {
	return node->script_path;
}

Ref<GDClassNode> GDDataType::get_class_type() const {
	return GDNode::build_from(node->class_type);
}

Dictionary GDDataType::get_method_info() const {
	return node->method_info;
}

Dictionary GDDataType::get_enum_values() const {
	Dictionary values;
	for (const KeyValue<StringName, int64_t> &E: node->enum_values) {
		values[E.key] = E.value;
	}
	return values;
}

bool GDDataType::is_set() const {
	return node->is_set();
}

bool GDDataType::is_resolving() const {
	return node->is_resolving();
}

bool GDDataType::has_no_type() const {
	return node->has_no_type();
}

bool GDDataType::is_variant() const {
	return node->is_variant();
}

bool GDDataType::is_hard_type() const {
	return node->is_hard_type();
}

String GDDataType::to_string() const {
	return node->to_string();
}

String GDDataType::to_string_strict() const {
	return node->to_string_strict();;
}

Dictionary GDDataType::to_property_info(const String &p_name) const {
	return node->to_property_info(p_name);
}

int GDDataType::get_container_element_type_count() const {
	return node->get_container_element_type_count();
}

bool GDDataType::has_container_element_type(int p_index) const {
	return node->has_container_element_type(p_index);
}

bool GDDataType::has_container_element_types() const {
	return node->has_container_element_types();
}

bool GDDataType::is_typed_container_type() const {
	return node->is_typed_container_type();
}

bool GDDataType::can_reference(const Ref<GDDataType> &p_other) const {
	const GDScriptParser::DataType* other = p_other->node;
	return node->can_reference(*other);
}

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
	ClassDB::bind_method(D_METHOD("get_datatype"), &GDMember::get_datatype);

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
	return GDClassNode::build_from(node->m_class);
}

Ref<GDConstantNode> GDMember::get_as_constant_node() const {
	if (get_type() != GDMember::Type::CONSTANT) {
		return nullptr;
	}
	return GDConstantNode::build_from(node->constant);
}

Ref<GDFunctionNode> GDMember::get_as_function_node() const {
	if (get_type() != GDMember::Type::FUNCTION) {
		return nullptr;
	}
	return GDFunctionNode::build_from(node->function);
}

Ref<GDSignalNode> GDMember::get_as_signal_node() const {
	if (get_type() != GDMember::Type::SIGNAL) {
		return nullptr;
	}
	return GDSignalNode::build_from(node->signal);
}

Ref<GDVariableNode> GDMember::get_as_signal_variable_node() const {
	if (get_type() != GDMember::Type::VARIABLE) {
		return nullptr;
	}
	return GDVariableNode::build_from(node->variable);
}

Ref<GDEnumNode> GDMember::get_as_enum_node() const {
	if (get_type() != GDMember::Type::ENUM) {
		return nullptr;
	}
	return GDEnumNode::build_from(node->m_enum);
}

Ref<GDAnnotationNode> GDMember::get_as_annotation_node() const {
	if (get_type() != GDMember::Type::GROUP) {
		return nullptr;
	}
	return GDAnnotationNode::build_from(node->annotation);
}

Ref<GDEnumValue> GDMember::get_enum_value() const {
	Ref<GDEnumValue> value = memnew(GDEnumValue);
	value->set_node(&node->enum_value);
	return value;
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

Ref<GDDataType> GDMember::get_datatype() const {
	Ref<GDDataType> value = memnew(GDDataType);
	switch (node->type) {
		case CLASS:
			value->set_node(&node->m_class->datatype);
			break;
		case CONSTANT:
			value->set_node(&node->constant->datatype);
			break;
		case FUNCTION:
			value->set_node(&node->function->datatype);
			break;
		case VARIABLE:
			value->set_node(&node->variable->datatype);
			break;
		case ENUM:
			value->set_node(&node->m_enum->datatype);
			break;
		case ENUM_VALUE:
			value->set_node(&node->enum_value.identifier->datatype);
			break;
		case SIGNAL:
			value->set_node(&node->signal->datatype);
			break;
		default:
			break;
	}
	return value;
}

Ref<GDNode> GDMember::get_source_node() const {
	switch (get_type()) {
		case GDMember::Type::CLASS:
			return GDNode::build_from(node->m_class);
		case GDMember::Type::CONSTANT:
			return GDNode::build_from(node->constant);
		case GDMember::Type::FUNCTION:
			return GDNode::build_from(node->function);
		case GDMember::Type::VARIABLE:
			return GDNode::build_from(node->variable);
		case GDMember::Type::ENUM:
			return GDNode::build_from(node->m_enum);
		case GDMember::Type::ENUM_VALUE:
			return GDNode::build_from(node->enum_value.identifier);
		case GDMember::Type::SIGNAL:
			return GDNode::build_from(node->signal);
		case GDMember::Type::GROUP:
			return GDNode::build_from(node->annotation);
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
	ClassDB::bind_method(D_METHOD("get_annotations"), &GDNode::get_annotations);
	ClassDB::bind_method(D_METHOD("get_datatype"), &GDNode::get_datatype);

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

TypedArray<GDAnnotationNode> GDNode::get_annotations() const {
	TypedArray<GDAnnotationNode> annotations;
	for (GDScriptParser::AnnotationNode *&annotation : base_node->annotations) {
		Ref<GDAnnotationNode> node = build_from(annotation);
		annotations.push_back(node);
	}
	return annotations;
}

Ref<GDDataType> GDNode::get_datatype() const {
	Ref<GDDataType> data = memnew(GDDataType);
	data->set_node(&base_node->datatype);
	return data;
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
	ClassDB::bind_method(D_METHOD("get_name"), &GDAnnotationNode::get_name);
	ClassDB::bind_method(D_METHOD("get_arguments"), &GDAnnotationNode::get_arguments);
	ClassDB::bind_method(D_METHOD("get_resolved_arguments"), &GDAnnotationNode::get_resolved_arguments);

	ClassDB::bind_method(D_METHOD("get_export_info"), &GDAnnotationNode::get_export_info);
	ClassDB::bind_method(D_METHOD("is_resolved"), &GDAnnotationNode::is_resolved);
	ClassDB::bind_method(D_METHOD("is_applied"), &GDAnnotationNode::is_applied);
	ClassDB::bind_method(D_METHOD("applies_to", "target_kinds"), &GDAnnotationNode::applies_to);
}

GDAnnotationNode::GDAnnotationNode() = default;
GDAnnotationNode::~GDAnnotationNode() {
}

StringName GDAnnotationNode::get_name() const {
	return node->name;
}

TypedArray<GDExpressionNode> GDAnnotationNode::get_arguments() const {
	TypedArray<GDExpressionNode> arguments;
	for (int i = 0; i < node->arguments.size(); ++i) {
		arguments.push_back(build_from(node->arguments[i]));
	}
	return arguments;
}

Array GDAnnotationNode::get_resolved_arguments() const {
	Array arguments;
	for (int i = 0; i < node->resolved_arguments.size(); ++i) {
		arguments.push_back(node->resolved_arguments[i]);
	}
	return arguments;
}

Dictionary GDAnnotationNode::get_export_info() const {
	return node->export_info;
}

bool GDAnnotationNode::is_resolved() const {
	return node->is_resolved;
}

bool GDAnnotationNode::is_applied() const {
	return node->is_applied;
}

bool GDAnnotationNode::applies_to(uint32_t p_target_kinds) const {
	return node->applies_to(p_target_kinds);
}

void GDArrayNode::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_elements"), &GDArrayNode::get_elements);
}

GDArrayNode::GDArrayNode() = default;
GDArrayNode::~GDArrayNode() {
}

TypedArray<GDExpressionNode> GDArrayNode::get_elements() const {
	TypedArray<GDExpressionNode> elements;
	for (int i = 0; i < node->elements.size(); ++i) {
		elements.push_back(build_from(node->elements[i]));
	}
	return elements;
}

void GDAssertNode::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_condition"), &GDAssertNode::get_condition);
	ClassDB::bind_method(D_METHOD("get_message"), &GDAssertNode::get_message);
}

GDAssertNode::GDAssertNode() = default;
GDAssertNode::~GDAssertNode() {
}

Ref<GDExpressionNode> GDAssertNode::get_condition() const {
	return build_from(node->condition);
}

Ref<GDExpressionNode> GDAssertNode::get_message() const {
	return build_from(node->message);
}

void GDAssignableNode::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_initializer"), &GDAssignableNode::get_initializer);
	ClassDB::bind_method(D_METHOD("get_identifier"), &GDAssignableNode::get_identifier);
	ClassDB::bind_method(D_METHOD("get_datatype_specifier"), &GDAssignableNode::get_datatype_specifier);
	ClassDB::bind_method(D_METHOD("infer_datatype"), &GDAssignableNode::infer_datatype);
	ClassDB::bind_method(D_METHOD("use_conversion_assign"), &GDAssignableNode::use_conversion_assign);
	ClassDB::bind_method(D_METHOD("get_usages"), &GDAssignableNode::get_usages);
}

Ref<GDIdentifierNode> GDAssignableNode::get_identifier() const {
	return build_from(node->identifier);
}

Ref<GDTypeNode> GDAssignableNode::get_datatype_specifier() const {
	return build_from(node->datatype_specifier);
}

bool GDAssignableNode::infer_datatype() const {
	return node->infer_datatype;
}

bool GDAssignableNode::use_conversion_assign() const {
	return node->use_conversion_assign;
}

int GDAssignableNode::get_usages() const {
	return node->usages;
}

Ref<GDExpressionNode> GDAssignableNode::get_initializer() const {
	return build_from(node->initializer);
}

GDAssignableNode::GDAssignableNode() = default;
GDAssignableNode::~GDAssignableNode() {
}

void GDAssignmentNode::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_operation"), &GDAssignmentNode::get_operation);
	ClassDB::bind_method(D_METHOD("get_variant_op"), &GDAssignmentNode::get_variant_op);
	ClassDB::bind_method(D_METHOD("get_assignee"), &GDAssignmentNode::get_assignee);
	ClassDB::bind_method(D_METHOD("get_assigned_value"), &GDAssignmentNode::get_assigned_value);
	ClassDB::bind_method(D_METHOD("use_conversion_assign"), &GDAssignmentNode::use_conversion_assign);

	BIND_ENUM_CONSTANT(OP_NONE);
	BIND_ENUM_CONSTANT(OP_ADDITION);
	BIND_ENUM_CONSTANT(OP_SUBTRACTION);
	BIND_ENUM_CONSTANT(OP_MULTIPLICATION);
	BIND_ENUM_CONSTANT(OP_DIVISION);
	BIND_ENUM_CONSTANT(OP_MODULO);
	BIND_ENUM_CONSTANT(OP_POWER);
	BIND_ENUM_CONSTANT(OP_BIT_SHIFT_LEFT);
	BIND_ENUM_CONSTANT(OP_BIT_SHIFT_RIGHT);
	BIND_ENUM_CONSTANT(OP_BIT_AND);
	BIND_ENUM_CONSTANT(OP_BIT_OR);
	BIND_ENUM_CONSTANT(OP_BIT_XOR);
}

GDAssignmentNode::Operation GDAssignmentNode::get_operation() const {
	return static_cast<GDAssignmentNode::Operation>(node->operation);
}

Variant::Operator GDAssignmentNode::get_variant_op() const {
	return node->variant_op;
}

Ref<GDExpressionNode> GDAssignmentNode::get_assignee() const {
	return build_from(node->assignee);
}

bool GDAssignmentNode::use_conversion_assign() const {
	return node->use_conversion_assign;
}

GDAssignmentNode::GDAssignmentNode() = default;
GDAssignmentNode::~GDAssignmentNode() {
}

Ref<GDExpressionNode> GDAssignmentNode::get_assigned_value() const {
	return build_from(node->assigned_value);
}

void GDAwaitNode::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_to_await"), &GDAwaitNode::get_to_await);
}

Ref<GDExpressionNode> GDAwaitNode::get_to_await() const {
	return build_from(node->to_await);
}

GDAwaitNode::GDAwaitNode() = default;
GDAwaitNode::~GDAwaitNode() {
}

void GDBinaryOpNode::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_operation"), &GDBinaryOpNode::get_operation);
	ClassDB::bind_method(D_METHOD("get_variant_op"), &GDBinaryOpNode::get_variant_op);
	ClassDB::bind_method(D_METHOD("get_left_operand"), &GDBinaryOpNode::get_left_operand);
	ClassDB::bind_method(D_METHOD("get_right_operand"), &GDBinaryOpNode::get_right_operand);

	BIND_ENUM_CONSTANT(OP_ADDITION);
	BIND_ENUM_CONSTANT(OP_SUBTRACTION);
	BIND_ENUM_CONSTANT(OP_MULTIPLICATION);
	BIND_ENUM_CONSTANT(OP_DIVISION);
	BIND_ENUM_CONSTANT(OP_MODULO);
	BIND_ENUM_CONSTANT(OP_POWER);
	BIND_ENUM_CONSTANT(OP_BIT_LEFT_SHIFT);
	BIND_ENUM_CONSTANT(OP_BIT_RIGHT_SHIFT);
	BIND_ENUM_CONSTANT(OP_BIT_AND);
	BIND_ENUM_CONSTANT(OP_BIT_OR);
	BIND_ENUM_CONSTANT(OP_BIT_XOR);
	BIND_ENUM_CONSTANT(OP_LOGIC_AND);
	BIND_ENUM_CONSTANT(OP_LOGIC_OR);
	BIND_ENUM_CONSTANT(OP_CONTENT_TEST);
	BIND_ENUM_CONSTANT(OP_COMP_EQUAL);
	BIND_ENUM_CONSTANT(OP_COMP_NOT_EQUAL);
	BIND_ENUM_CONSTANT(OP_COMP_LESS);
	BIND_ENUM_CONSTANT(OP_COMP_LESS_EQUAL);
	BIND_ENUM_CONSTANT(OP_COMP_GREATER);
	BIND_ENUM_CONSTANT(OP_COMP_GREATER_EQUAL);
}

GDBinaryOpNode::OpType GDBinaryOpNode::get_operation() const {
	return static_cast<GDBinaryOpNode::OpType>(node->operation);
}

Variant::Operator GDBinaryOpNode::get_variant_op() const {
	return node->variant_op;
}

Ref<GDExpressionNode> GDBinaryOpNode::get_left_operand() const {
	return build_from(node->left_operand);
}

Ref<GDExpressionNode> GDBinaryOpNode::get_right_operand() const {
	return build_from(node->right_operand);
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
	ClassDB::bind_method(D_METHOD("get_callee"), &GDCallNode::get_callee);
	ClassDB::bind_method(D_METHOD("get_arguments"), &GDCallNode::get_arguments);
	ClassDB::bind_method(D_METHOD("get_function_name"), &GDCallNode::get_function_name);
	ClassDB::bind_method(D_METHOD("is_super"), &GDCallNode::is_super);
	ClassDB::bind_method(D_METHOD("is_static"), &GDCallNode::is_static);
	ClassDB::bind_method(D_METHOD("get_callee_type"), &GDCallNode::get_callee_type);
}

Ref<GDExpressionNode> GDCallNode::get_callee() const {
	return build_from(node->callee);
}

TypedArray<GDExpressionNode> GDCallNode::get_arguments() const {
	TypedArray<GDExpressionNode> arguments;
	for (int i = 0; i < node->arguments.size(); ++i) {
		arguments.push_back(build_from(node->arguments[i]));
	}
	return arguments;
}

StringName GDCallNode::get_function_name() const {
	return node->function_name;
}

bool GDCallNode::is_super() const {
	return node->is_super;
}

bool GDCallNode::is_static() const {
	return node->is_static;
}

GDNode::Type GDCallNode::get_callee_type() const {
	return static_cast<GDNode::Type>(node->get_callee_type());
}

GDCallNode::GDCallNode() = default;
GDCallNode::~GDCallNode() {
}

void GDCastNode::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_operand"), &GDCastNode::get_operand);
	ClassDB::bind_method(D_METHOD("get_cast_type"), &GDCastNode::get_cast_type);
}

Ref<GDExpressionNode> GDCastNode::get_operand() const {
	return build_from(node->operand);
}

Ref<GDTypeNode> GDCastNode::get_cast_type() const {
	return build_from(node->operand);
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
	ClassDB::bind_method(D_METHOD("get_outer"), &GDClassNode::get_outer);
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
	ClassDB::bind_method(D_METHOD("get_base_type"), &GDClassNode::get_base_type);
}

Ref<GDIdentifierNode> GDClassNode::get_identifier() const {
	return build_from(node->identifier);
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

Ref<GDClassNode> GDClassNode::get_outer() const {
	return build_from(node->outer);
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
		extends.append(build_from(node->extends[i]));
	}
	return extends;
}

Ref<GDDataType> GDClassNode::get_base_type() const {
	Ref<GDDataType> datatype = memnew(GDDataType);
	datatype->set_node(&node->base_type);
	return datatype;
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
	return GDNode::build_from(node->key);
}

Ref<GDExpressionNode> GDPair::get_value() const {
	return GDNode::build_from(node->value);
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

void GDEnumValue::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_identifier"), &GDEnumValue::get_identifier);
	ClassDB::bind_method(D_METHOD("get_custom_value"), &GDEnumValue::get_custom_value);
	ClassDB::bind_method(D_METHOD("get_parent_enum"), &GDEnumValue::get_parent_enum);
	ClassDB::bind_method(D_METHOD("get_index"), &GDEnumValue::get_index);
	ClassDB::bind_method(D_METHOD("resolved"), &GDEnumValue::resolved);
	ClassDB::bind_method(D_METHOD("get_value"), &GDEnumValue::get_value);
	ClassDB::bind_method(D_METHOD("get_line"), &GDEnumValue::get_line);
	ClassDB::bind_method(D_METHOD("get_start_column"), &GDEnumValue::get_start_column);
	ClassDB::bind_method(D_METHOD("get_end_column"), &GDEnumValue::get_end_column);
}

Ref<GDIdentifierNode> GDEnumValue::get_identifier() const {
	return GDNode::build_from(node->identifier);
}

Ref<GDExpressionNode> GDEnumValue::get_custom_value() const {
	return GDNode::build_from(node->custom_value);
}

Ref<GDEnumNode> GDEnumValue::get_parent_enum() const {
	return GDNode::build_from(node->parent_enum);
}

int GDEnumValue::get_index() const {
	return node->index;
}

bool GDEnumValue::resolved() const {
	return node->resolved;
}

int64_t GDEnumValue::get_value() const {
	return node->value;
}

int GDEnumValue::get_line() const {
	return node->line;
}

int GDEnumValue::get_start_column() const {
	return node->start_column;
}

int GDEnumValue::get_end_column() const {
	return node->end_column;
}

void GDEnumNode::_bind_methods() {
}

GDEnumNode::GDEnumNode() = default;
GDEnumNode::~GDEnumNode() {
}

Ref<GDIdentifierNode> GDEnumNode::get_identifier() const {
	return GDNode::build_from(node->identifier);
}

TypedArray<GDEnumValue> GDEnumNode::get_values() const {
	TypedArray<GDEnumValue> values;
	for (int i=0; i<node->values.size(); i++) {
		Ref<GDEnumValue> value = memnew(GDEnumValue);
		value->set_node(&node->values[i]);
		values.append(value);
	}
	return values;
}

Variant GDEnumNode::get_dictionary() const {
	return node->dictionary;
}

void GDExpressionNode::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_reduced_value"), &GDExpressionNode::get_reduced_value);
	ClassDB::bind_method(D_METHOD("reduced"), &GDExpressionNode::reduced);
	ClassDB::bind_method(D_METHOD("get_reduced_value"), &GDExpressionNode::get_reduced_value);
}

bool GDExpressionNode::reduced() const {
	return node->reduced;
}

bool GDExpressionNode::is_constant() const {
	return node->is_constant;
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
	return build_from(node->variable);
}

Ref<GDTypeNode> GDForNode::get_datatype_specifier() const {
	return build_from(node->datatype_specifier);
}

bool GDForNode::use_conversion_assign() const {
	return node->use_conversion_assign;
}

Ref<GDExpressionNode> GDForNode::get_list() const {
	return build_from(node->list);
}

Ref<GDSuiteNode> GDForNode::get_loop() const {
	return build_from(node->loop);
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
	ClassDB::bind_method(D_METHOD("get_info"), &GDFunctionNode::get_info);
}

Ref<GDIdentifierNode> GDFunctionNode::get_identifier() const {
	return build_from(node->identifier);
}

TypedArray<GDParameterNode> GDFunctionNode::get_parameters() const {
	TypedArray<GDParameterNode> parameters;
	for (int i=0; i<node->parameters.size(); i++) {
		parameters.append(build_from(node->parameters[i]));
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
	return build_from(node->rest_parameter);
}

Ref<GDTypeNode> GDFunctionNode::get_return_type() const {
	return build_from(node->return_type);
}

Ref<GDSuiteNode> GDFunctionNode::get_body() const {
	return build_from(node->body);
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

Dictionary GDFunctionNode::get_info() const {
	return node->info;
}

Ref<GDLambdaNode> GDFunctionNode::get_source_lambda() const {
	return build_from(node->source_lambda);
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
	return build_from(node->suite);
}

GDIdentifierNode::Source GDIdentifierNode::get_source() const {
	return static_cast<GDIdentifierNode::Source>(node->source);
}

Ref<GDParameterNode> GDIdentifierNode::get_source_as_parameter() const {
	if (node->source != GDScriptParser::IdentifierNode::Source::FUNCTION_PARAMETER) {
		return nullptr;
	}
	return build_from(node->parameter_source);
}

Ref<GDIdentifierNode> GDIdentifierNode::get_source_as_bind() const {
	if (node->source != GDScriptParser::IdentifierNode::Source::LOCAL_BIND) {
		return nullptr;
	}

	return build_from(node->bind_source);
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
	return build_from(node->variable_source);
}

Ref<GDConstantNode> GDIdentifierNode::get_source_as_constant() const {
	if (
		node->source != GDScriptParser::IdentifierNode::Source::LOCAL_CONSTANT &&
		node->source != GDScriptParser::IdentifierNode::Source::MEMBER_CONSTANT) {
		return nullptr;
	}
	return build_from(node->constant_source);
}

Ref<GDSignalNode> GDIdentifierNode::get_source_as_signal() const {
	if (node->source != GDScriptParser::IdentifierNode::Source::MEMBER_SIGNAL) {
		return nullptr;
	}
	return build_from(node->signal_source);
}

Ref<GDFunctionNode> GDIdentifierNode::get_source_as_function() const {
	if (node->source != GDScriptParser::IdentifierNode::Source::MEMBER_FUNCTION) {
		return nullptr;
	}
	return build_from(node->function_source);
}

bool GDIdentifierNode::function_source_is_static() const {
	return node->function_source_is_static;
}

Ref<GDFunctionNode> GDIdentifierNode::get_source_function() const {
	return build_from(node->source_function);
}

int GDIdentifierNode::get_usages() const {
	return node->usages;
}

GDIdentifierNode::GDIdentifierNode() = default;
GDIdentifierNode::~GDIdentifierNode() {
}

void GDIfNode::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_condition"), &GDIfNode::get_condition);
	ClassDB::bind_method(D_METHOD("get_true_block"), &GDIfNode::get_true_block);
	ClassDB::bind_method(D_METHOD("get_false_block"), &GDIfNode::get_false_block);
}

Ref<GDExpressionNode> GDIfNode::get_condition() const {
	return build_from(node->condition);
}

Ref<GDSuiteNode> GDIfNode::get_true_block() const {
	return build_from(node->true_block);
}

Ref<GDSuiteNode> GDIfNode::get_false_block() const {
	return build_from(node->false_block);
}

GDIfNode::GDIfNode() = default;
GDIfNode::~GDIfNode() {
}

void GDLambdaNode::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_function"), &GDLambdaNode::get_function);
	ClassDB::bind_method(D_METHOD("get_parent_function"), &GDLambdaNode::get_parent_function);
	ClassDB::bind_method(D_METHOD("get_parent_lambda"), &GDLambdaNode::get_parent_lambda);
	ClassDB::bind_method(D_METHOD("get_captures"), &GDLambdaNode::get_captures);
	ClassDB::bind_method(D_METHOD("get_capture_indices"), &GDLambdaNode::get_capture_indices);
	ClassDB::bind_method(D_METHOD("use_self"), &GDLambdaNode::use_self);
	ClassDB::bind_method(D_METHOD("has_name"), &GDLambdaNode::has_name);
}

Ref<GDFunctionNode> GDLambdaNode::get_function() const {
	return build_from(node->function);
}

Ref<GDFunctionNode> GDLambdaNode::get_parent_function() const {
	return build_from(node->parent_function);
}

Ref<GDLambdaNode> GDLambdaNode::get_parent_lambda() const {
	return build_from(node->parent_lambda);
}

TypedArray<GDIdentifierNode> GDLambdaNode::get_captures() const {
	TypedArray<GDIdentifierNode> captures;
	for (int i = 0; i < node->captures.size(); ++i) {
		captures.push_back(build_from(node->captures[i]));
	}
	return captures;
}

Dictionary GDLambdaNode::get_capture_indices() const {
	Dictionary indices;
	for (const KeyValue<StringName, int> &E: node->captures_indices) {
		indices[E.key] = E.value;
	}
	return indices;
}

bool GDLambdaNode::use_self() const {
	return node->use_self;
}

bool GDLambdaNode::has_name() const {
	return node->has_name();
}

GDLambdaNode::GDLambdaNode() = default;
GDLambdaNode::~GDLambdaNode() {
}

void GDLiteralNode::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_value"), &GDLiteralNode::get_value);
}

Variant GDLiteralNode::get_value() const {
	return node->value;
}

GDLiteralNode::GDLiteralNode() = default;
GDLiteralNode::~GDLiteralNode() {
}

void GDMatchNode::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_test"), &GDMatchNode::get_test);
	ClassDB::bind_method(D_METHOD("get_branches"), &GDMatchNode::get_branches);
}

Ref<GDExpressionNode> GDMatchNode::get_test() const {
	return build_from(node->test);
}

TypedArray<GDMatchBranchNode> GDMatchNode::get_branches() const {
	TypedArray<GDMatchBranchNode> branches;
	for (int i = 0; i < node->branches.size(); ++i) {
		branches.push_back(build_from(node->branches[i]));
	}
	return branches;
}

GDMatchNode::GDMatchNode() = default;
GDMatchNode::~GDMatchNode() {
}

void GDMatchBranchNode::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_patterns"), &GDMatchBranchNode::get_patterns);
	ClassDB::bind_method(D_METHOD("get_block"), &GDMatchBranchNode::get_block);
	ClassDB::bind_method(D_METHOD("has_wildcard"), &GDMatchBranchNode::has_wildcard);
	ClassDB::bind_method(D_METHOD("get_guard_body"), &GDMatchBranchNode::get_guard_body);
}

TypedArray<GDPatternNode> GDMatchBranchNode::get_patterns() const {
	TypedArray<GDPatternNode> patterns;
	for (int i = 0; i < node->patterns.size(); ++i) {
		patterns.push_back(build_from(node->patterns[i]));
	}
	return patterns;
}

Ref<GDSuiteNode> GDMatchBranchNode::get_block() const {
	return build_from(node->block);
}

bool GDMatchBranchNode::has_wildcard() const {
	return node->has_wildcard;
}

Ref<GDSuiteNode> GDMatchBranchNode::get_guard_body() const {
	return build_from(node->guard_body);
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
	ClassDB::bind_method(D_METHOD("get_pattern_type"), &GDPatternNode::get_pattern_type);
	ClassDB::bind_method(D_METHOD("get_as_literal"), &GDPatternNode::get_as_literal);
	ClassDB::bind_method(D_METHOD("get_as_identifier"), &GDPatternNode::get_as_identifier);
	ClassDB::bind_method(D_METHOD("get_as_expression"), &GDPatternNode::get_as_expression);
	ClassDB::bind_method(D_METHOD("get_array"), &GDPatternNode::get_array);
	ClassDB::bind_method(D_METHOD("rest_used"), &GDPatternNode::rest_used);
	ClassDB::bind_method(D_METHOD("get_dictionary"), &GDPatternNode::get_dictionary);
	ClassDB::bind_method(D_METHOD("get_binds"), &GDPatternNode::get_binds);
	ClassDB::bind_method(D_METHOD("has_bind", "name"), &GDPatternNode::has_bind);
	ClassDB::bind_method(D_METHOD("get_bind", "name"), &GDPatternNode::get_bind);

	BIND_ENUM_CONSTANT(PT_LITERAL);
	BIND_ENUM_CONSTANT(PT_EXPRESSION);
	BIND_ENUM_CONSTANT(PT_BIND);
	BIND_ENUM_CONSTANT(PT_ARRAY);
	BIND_ENUM_CONSTANT(PT_DICTIONARY);
	BIND_ENUM_CONSTANT(PT_REST);
	BIND_ENUM_CONSTANT(PT_WILDCARD);
}

GDPatternNode::Type GDPatternNode::get_pattern_type() const {
	return static_cast<Type>(node->pattern_type);
}

Ref<GDLiteralNode> GDPatternNode::get_as_literal() const {
	if (get_pattern_type() != PT_LITERAL) {
		return nullptr;
	}
	return build_from(node->literal);
}

Ref<GDIdentifierNode> GDPatternNode::get_as_identifier() const {
	if (get_pattern_type() != PT_BIND) {
		return nullptr;
	}
	return build_from(node);
}

Ref<GDExpressionNode> GDPatternNode::get_as_expression() const {
	if (get_pattern_type() == PT_LITERAL || get_pattern_type() == PT_BIND) {
		return nullptr;
	}
	return build_from(node->expression);
}

TypedArray<GDPatternNode> GDPatternNode::get_array() const {
	TypedArray<GDPatternNode> array;
	for (int i = 0; i < node->array.size(); ++i) {
		array.push_back(build_from(node->array[i]));
	}
	return array;
}

bool GDPatternNode::rest_used() const {
	return node->rest_used;
}

TypedArray<GDPatternPair> GDPatternNode::get_dictionary() const {
	TypedArray<GDPatternPair> dictionary;
	for (int i = 0; i < node->dictionary.size(); ++i) {
		Ref<GDPatternPair> pair = memnew(GDPatternPair);
		pair->set_node(&node->dictionary[i]);
		dictionary.push_back(pair);
	}
	return dictionary;
}

Dictionary GDPatternNode::get_binds() const {
	Dictionary binds;
	for (const KeyValue<StringName, GDScriptParser::IdentifierNode*> &E: node->binds) {
		binds[E.key] = build_from(E.value);
	}
	return binds;
}

bool GDPatternNode::has_bind(const StringName &p_name) const {
	return node->has_bind(p_name);
}

Ref<GDIdentifierNode> GDPatternNode::get_bind(const StringName &p_name) const {
	Ref<GDIdentifierNode> bind = build_from(node->get_bind(p_name));
	return bind;
}

GDPatternNode::GDPatternNode() = default;
GDPatternNode::~GDPatternNode() {
}

void GDPatternPair::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_key"), &GDPatternPair::get_key);
	ClassDB::bind_method(D_METHOD("get_value_pattern"), &GDPatternPair::get_value_pattern);
}

Ref<GDExpressionNode> GDPatternPair::get_key() const {
	return GDNode::build_from(node->key);
}

Ref<GDPatternNode> GDPatternPair::get_value_pattern() const {
	return GDNode::build_from(node->value_pattern);
}

void GDPreloadNode::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_path"), &GDPreloadNode::get_path);
	ClassDB::bind_method(D_METHOD("get_resolved_path"), &GDPreloadNode::get_resolved_path);
	ClassDB::bind_method(D_METHOD("get_resource"), &GDPreloadNode::get_resource);
}

Ref<GDExpressionNode> GDPreloadNode::get_path() const {
	return build_from(node->path);
}

String GDPreloadNode::get_resolved_path() const {
	return node->resolved_path;
}

Ref<Resource> GDPreloadNode::get_resource() const {
	return node->resource;
}

GDPreloadNode::GDPreloadNode() = default;
GDPreloadNode::~GDPreloadNode() {
}

void GDReturnNode::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_return_value"), &GDReturnNode::get_return_value);
	ClassDB::bind_method(D_METHOD("void_return"), &GDReturnNode::void_return);
}

Ref<GDExpressionNode> GDReturnNode::get_return_value() const {
	return build_from(node->return_value);
}

bool GDReturnNode::void_return() const {
	return node->void_return;
}

GDReturnNode::GDReturnNode() = default;
GDReturnNode::~GDReturnNode() {
}

void GDSelfNode::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_current_class"), &GDSelfNode::get_current_class);
}

Ref<GDClassNode> GDSelfNode::get_current_class() const {
	return build_from(node->current_class);
}

GDSelfNode::GDSelfNode() = default;
GDSelfNode::~GDSelfNode() {
}

void GDSignalNode::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_identifier"), &GDSignalNode::get_identifier);
	ClassDB::bind_method(D_METHOD("get_parameters"), &GDSignalNode::get_parameters);
	ClassDB::bind_method(D_METHOD("get_parameter_indices"), &GDSignalNode::get_parameter_indices);
	ClassDB::bind_method(D_METHOD("get_method_info"), &GDSignalNode::get_method_info);
	ClassDB::bind_method(D_METHOD("get_usages"), &GDSignalNode::get_usages);
}

Ref<GDIdentifierNode> GDSignalNode::get_identifier() const {
	return build_from(node->identifier);
}

TypedArray<GDParameterNode> GDSignalNode::get_parameters() const {
	TypedArray<GDParameterNode> parameters;
	for (int i = 0; i < node->parameters.size(); ++i) {
		parameters.push_back(build_from(node->parameters[i]));
	}
	return parameters;
}

Dictionary GDSignalNode::get_parameter_indices() const {
	Dictionary indices;
	for (KeyValue<StringName, int> &E: node->parameters_indices) {
		indices[E.key] = E.value;
	}
	return indices;
}

Dictionary GDSignalNode::get_method_info() const {
	return node->method_info;
}

int GDSignalNode::get_usages() const {
	return node->usages;
}

GDSignalNode::GDSignalNode() = default;
GDSignalNode::~GDSignalNode() {
}

void GDSubscriptNode::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_base"), &GDSubscriptNode::get_base);
	ClassDB::bind_method(D_METHOD("get_as_index"), &GDSubscriptNode::get_as_index);
	ClassDB::bind_method(D_METHOD("get_as_attribute"), &GDSubscriptNode::get_as_attribute);
	ClassDB::bind_method(D_METHOD("is_attribute"), &GDSubscriptNode::is_attribute);
}

Ref<GDExpressionNode> GDSubscriptNode::get_base() const {
	return build_from(node->base);
}

Ref<GDExpressionNode> GDSubscriptNode::get_as_index() const {
	if (node->is_attribute) {
		return nullptr;
	}
	return build_from(node->index);
}

Ref<GDIdentifierNode> GDSubscriptNode::get_as_attribute() const {
	if (!node->is_attribute) {
		return nullptr;
	}
	return build_from(node->attribute);
}

bool GDSubscriptNode::is_attribute() const {
	return node->is_attribute;
}

GDSubscriptNode::GDSubscriptNode() = default;
GDSubscriptNode::~GDSubscriptNode() {
}

void GDSuiteNode::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_statements"), &GDSuiteNode::get_statements);
	ClassDB::bind_method(D_METHOD("get_empty"), &GDSuiteNode::get_empty);
	ClassDB::bind_method(D_METHOD("get_locals"), &GDSuiteNode::get_locals);
	ClassDB::bind_method(D_METHOD("get_locals_indices"), &GDSuiteNode::get_locals_indices);
	ClassDB::bind_method(D_METHOD("get_parent_function"), &GDSuiteNode::get_parent_function);
	ClassDB::bind_method(D_METHOD("get_parent_if"), &GDSuiteNode::get_parent_if);
	ClassDB::bind_method(D_METHOD("has_return"), &GDSuiteNode::has_return);
	ClassDB::bind_method(D_METHOD("has_continue"), &GDSuiteNode::has_continue);
	ClassDB::bind_method(D_METHOD("has_unreachable_code"), &GDSuiteNode::has_unreachable_code);
	ClassDB::bind_method(D_METHOD("is_in_loop"), &GDSuiteNode::is_in_loop);
	ClassDB::bind_method(D_METHOD("has_local", "name"), &GDSuiteNode::has_local);
	ClassDB::bind_method(D_METHOD("get_local", "name"), &GDSuiteNode::get_local);
}

Ref<GDSuiteLocal> GDSuiteNode::get_empty() const {
	Ref<GDSuiteLocal> local = memnew(GDSuiteLocal);
	local->set_node(&node->empty);
	return local;
}

TypedArray<GDSuiteLocal> GDSuiteNode::get_locals() const {
	TypedArray<GDSuiteLocal> locals;
	for (int i = 0; i < node->locals.size(); ++i) {
		Ref<GDSuiteLocal> local = memnew(GDSuiteLocal);
		local->set_node(&node->locals[i]);
		locals.push_back(local);
	}
	return locals;
}

Dictionary GDSuiteNode::get_locals_indices() const {
	Dictionary indices;
	for (KeyValue<StringName, int> &E: node->locals_indices) {
		indices[E.key] = E.value;
	}
	return indices;
}

Ref<GDFunctionNode> GDSuiteNode::get_parent_function() const {
	return GDNode::build_from(node->parent_function);
}

Ref<GDIfNode> GDSuiteNode::get_parent_if() const {
	return GDNode::build_from(node->parent_if);
}

bool GDSuiteNode::has_return() const {
	return node->has_return;
}

bool GDSuiteNode::has_continue() const {
	return node->has_continue;
}

bool GDSuiteNode::has_unreachable_code() const {
	return node->has_unreachable_code;
}

bool GDSuiteNode::is_in_loop() const {
	return node->is_in_loop;
}

bool GDSuiteNode::has_local(const StringName &p_name) {
	return node->has_local(p_name);
}

Ref<GDSuiteLocal> GDSuiteNode::get_local(const StringName &p_name) {
	Ref<GDSuiteLocal> local = memnew(GDSuiteLocal);
	local->set_node(&node->get_local(p_name));
	return local;
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

void GDSuiteLocal::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_type"), &GDSuiteLocal::get_type);
	ClassDB::bind_method(D_METHOD("get_as_constant"), &GDSuiteLocal::get_as_constant);
	ClassDB::bind_method(D_METHOD("get_as_variable"), &GDSuiteLocal::get_as_variable);
	ClassDB::bind_method(D_METHOD("get_as_parameter"), &GDSuiteLocal::get_as_parameter);
	ClassDB::bind_method(D_METHOD("get_as_bind"), &GDSuiteLocal::get_as_bind);
	ClassDB::bind_method(D_METHOD("get_local_name"), &GDSuiteLocal::get_local_name);
	ClassDB::bind_method(D_METHOD("get_name"), &GDSuiteLocal::get_name);
	ClassDB::bind_method(D_METHOD("get_source_function"), &GDSuiteLocal::get_source_function);
	ClassDB::bind_method(D_METHOD("get_start_line"), &GDSuiteLocal::get_start_line);
	ClassDB::bind_method(D_METHOD("get_start_column"), &GDSuiteLocal::get_start_column);
	ClassDB::bind_method(D_METHOD("get_end_line"), &GDSuiteLocal::get_end_line);
	ClassDB::bind_method(D_METHOD("get_end_column"), &GDSuiteLocal::get_end_column);
	ClassDB::bind_method(D_METHOD("get_datatype"), &GDSuiteLocal::get_datatype);

	BIND_ENUM_CONSTANT(UNDEFINED);
	BIND_ENUM_CONSTANT(CONSTANT);
	BIND_ENUM_CONSTANT(VARIABLE);
	BIND_ENUM_CONSTANT(PARAMETER);
	BIND_ENUM_CONSTANT(FOR_VARIABLE);
	BIND_ENUM_CONSTANT(PATTERN_BIND);
}

GDSuiteLocal::Type GDSuiteLocal::get_type() const {
	return static_cast<GDSuiteLocal::Type>(node->type);
}

Ref<GDConstantNode> GDSuiteLocal::get_as_constant() const {
	if (get_type() != CONSTANT) {
		return nullptr;
	}
	return GDNode::build_from(node->constant);
}

Ref<GDVariableNode> GDSuiteLocal::get_as_variable() const {
	if (get_type() != VARIABLE) {
		return nullptr;
	}
	return GDNode::build_from(node->variable);
}

Ref<GDParameterNode> GDSuiteLocal::get_as_parameter() const {
	if (get_type() != PARAMETER) {
		return nullptr;
	}
	return GDNode::build_from(node->parameter);
}

Ref<GDIdentifierNode> GDSuiteLocal::get_as_bind() const {
	if (get_type() != PATTERN_BIND && get_type() != FOR_VARIABLE) {
		return nullptr;
	}
	return GDNode::build_from(node->bind);
}

StringName GDSuiteLocal::get_local_name() const {
	return node->name;
}

String GDSuiteLocal::get_name() const {
	return node->get_name();
}

Ref<GDFunctionNode> GDSuiteLocal::get_source_function() const {
	return GDNode::build_from(node->source_function);
}

int GDSuiteLocal::get_start_line() const {
	return node->start_line;
}

int GDSuiteLocal::get_start_column() const {
	return node->start_column;
}

int GDSuiteLocal::get_end_line() const {
	return node->end_line;
}

int GDSuiteLocal::get_end_column() const {
	return node->end_column;
}

Ref<GDDataType> GDSuiteLocal::get_datatype() const {
	Ref<GDDataType> type = memnew(GDDataType);
	switch (node->type) {
		case CONSTANT:
			type->set_node(&node->constant->datatype);
		case VARIABLE:
			type->set_node(&node->variable->datatype);
		case PARAMETER:
			type->set_node(&node->parameter->datatype);
		case FOR_VARIABLE:
		case PATTERN_BIND:
			 type->set_node(&node->bind->datatype);
		default:
			return nullptr;
	}
}

GDSuiteLocal::GDSuiteLocal() {
}

GDSuiteLocal::~GDSuiteLocal() {
}

void GDTernaryOpNode::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_condition"), &GDTernaryOpNode::get_condition);
	ClassDB::bind_method(D_METHOD("get_true_expr"), &GDTernaryOpNode::get_true_expr);
	ClassDB::bind_method(D_METHOD("get_false_expr"), &GDTernaryOpNode::get_false_expr);
}

Ref<GDExpressionNode> GDTernaryOpNode::get_condition() const {
	return build_from(node->condition);
}

Ref<GDExpressionNode> GDTernaryOpNode::get_true_expr() const {
	return build_from(node->true_expr);
}

Ref<GDExpressionNode> GDTernaryOpNode::get_false_expr() const {
	return build_from(node->false_expr);
}

GDTernaryOpNode::GDTernaryOpNode() = default;
GDTernaryOpNode::~GDTernaryOpNode() {
}

void GDTypeNode::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_type_chain"), &GDTypeNode::get_type_chain);
	ClassDB::bind_method(D_METHOD("get_container_types"), &GDTypeNode::get_container_types);
	ClassDB::bind_method(D_METHOD("get_container_type_or_null", "index"), &GDTypeNode::get_container_type_or_null);
}

TypedArray<GDIdentifierNode> GDTypeNode::get_type_chain() const {
	TypedArray<GDIdentifierNode> types;
	for (int i = 0; i < node->type_chain.size(); ++i) {
		types.push_back(build_from(node->type_chain[i]));
	}
	return types;
}

TypedArray<GDTypeNode> GDTypeNode::get_container_types() const {
	TypedArray<GDTypeNode> types;
	for (int i = 0; i < node->container_types.size(); ++i) {
		types.push_back(build_from(node->container_types[i]));
	}
	return types;
}

Ref<GDTypeNode> GDTypeNode::get_container_type_or_null(int p_index) const {
	GDScriptParser::TypeNode *container_type = node->get_container_type_or_null(p_index);
	if (container_type != nullptr) {
		return build_from(container_type);
	}
	return nullptr;
}

GDTypeNode::GDTypeNode() = default;
GDTypeNode::~GDTypeNode() {
}

void GDTypeTestNode::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_operand"), &GDTypeTestNode::get_operand);
	ClassDB::bind_method(D_METHOD("get_test_type"), &GDTypeTestNode::get_test_type);
	ClassDB::bind_method(D_METHOD("get_test_datatype"), &GDTypeTestNode::get_test_datatype);
}

Ref<GDExpressionNode> GDTypeTestNode::get_operand() const {
	return build_from(node->operand);
}

Ref<GDTypeNode> GDTypeTestNode::get_test_type() const {
	return build_from(node->test_type);
}

Ref<GDDataType> GDTypeTestNode::get_test_datatype() const {
	Ref<GDDataType> type = memnew(GDDataType);
	type->set_node(&node->datatype);
	return type;
}

GDTypeTestNode::GDTypeTestNode() = default;
GDTypeTestNode::~GDTypeTestNode() {
}

void GDUnaryOpNode::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_operation"), &GDUnaryOpNode::get_operation);
	ClassDB::bind_method(D_METHOD("get_variant_op"), &GDUnaryOpNode::get_variant_op);
	ClassDB::bind_method(D_METHOD("get_operand"), &GDUnaryOpNode::get_operand);

	BIND_ENUM_CONSTANT(OP_POSITIVE);
	BIND_ENUM_CONSTANT(OP_NEGATIVE);
	BIND_ENUM_CONSTANT(OP_COMPLEMENT);
	BIND_ENUM_CONSTANT(OP_LOGIC_NOT);
}

GDUnaryOpNode::OpType GDUnaryOpNode::get_operation() const {
	return static_cast<OpType>(node->operation);
}

Variant::Operator GDUnaryOpNode::get_variant_op() const {
	return node->variant_op;
}

Ref<GDExpressionNode> GDUnaryOpNode::get_operand() const {
	return build_from(node->operand);
}

GDUnaryOpNode::GDUnaryOpNode() = default;
GDUnaryOpNode::~GDUnaryOpNode() {
}

void GDVariableNode::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_property"), &GDVariableNode::get_property);
	ClassDB::bind_method(D_METHOD("get_setter_as_function"), &GDVariableNode::get_setter_as_function);
	ClassDB::bind_method(D_METHOD("get_setter_as_pointer"), &GDVariableNode::get_setter_as_pointer);
	ClassDB::bind_method(D_METHOD("get_setter_parameter"), &GDVariableNode::get_setter_parameter);
	ClassDB::bind_method(D_METHOD("get_getter_as_function"), &GDVariableNode::get_getter_as_function);
	ClassDB::bind_method(D_METHOD("get_getter_as_pointer"), &GDVariableNode::get_getter_as_pointer);
	ClassDB::bind_method(D_METHOD("exported"), &GDVariableNode::exported);
	ClassDB::bind_method(D_METHOD("onready"), &GDVariableNode::onready);
	ClassDB::bind_method(D_METHOD("get_export_info"), &GDVariableNode::get_export_info);
	ClassDB::bind_method(D_METHOD("get_assignments"), &GDVariableNode::get_assignments);
	ClassDB::bind_method(D_METHOD("is_static"), &GDVariableNode::is_static);

	BIND_ENUM_CONSTANT(PROP_NONE);
	BIND_ENUM_CONSTANT(PROP_INLINE);
	BIND_ENUM_CONSTANT(PROP_SETGET);
}

GDVariableNode::PropertyStyle GDVariableNode::get_property() const {
	return static_cast<PropertyStyle>(node->property);
}

Ref<GDFunctionNode> GDVariableNode::get_setter_as_function() const {
	if (get_property() != PROP_INLINE || node->setter == nullptr) {
		return nullptr;
	}
	return build_from(node->setter);
}

Ref<GDIdentifierNode> GDVariableNode::get_setter_as_pointer() const {
	if (get_property() != PROP_SETGET || node->setter_pointer == nullptr) {
		return nullptr;
	}
	return build_from(node->setter_pointer);
}

Ref<GDIdentifierNode> GDVariableNode::get_setter_parameter() const {
	if (get_property() != PROP_INLINE || node->setter == nullptr) {
		return nullptr;
	}
	return build_from(node->setter_parameter);
}

Ref<GDFunctionNode> GDVariableNode::get_getter_as_function() const {
	if (get_property() != PROP_INLINE || node->getter == nullptr) {
		return nullptr;
	}
	return build_from(node->getter);
}

Ref<GDIdentifierNode> GDVariableNode::get_getter_as_pointer() const {
	if (get_property() != PROP_SETGET || node->getter_pointer == nullptr) {
		return nullptr;
	}
	return build_from(node->getter_pointer);
}

bool GDVariableNode::exported() const {
	return node->exported;
}

bool GDVariableNode::onready() const {
	return node->onready;
}

int GDVariableNode::get_assignments() const {
	return node->assignments;
}

bool GDVariableNode::is_static() const {
	return node->is_static;
}

GDVariableNode::GDVariableNode() = default;
GDVariableNode::~GDVariableNode() {
}

Dictionary GDVariableNode::get_export_info() const {
	return node->export_info;
}

void GDWhileNode::_bind_methods() {
}

Ref<GDExpressionNode> GDWhileNode::get_condition() const {
	return build_from(node->condition);
}

Ref<GDSuiteNode> GDWhileNode::get_loop() const {
	return build_from(node->loop);
}

GDWhileNode::GDWhileNode() = default;
GDWhileNode::~GDWhileNode() {
}

