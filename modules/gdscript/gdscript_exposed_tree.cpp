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

void GDAnnotationNode::_bind_methods() {
}

void GDAnnotationNode::set_node(GDScriptParser::AnnotationNode *p_node) {
	node = p_node;
}

GDAnnotationNode::GDAnnotationNode() = default;
GDAnnotationNode::~GDAnnotationNode() {
}

void GDArrayNode::_bind_methods() {
}

void GDArrayNode::set_node(GDScriptParser::ArrayNode *p_node) {
	node = p_node;
}

GDArrayNode::GDArrayNode() = default;
GDArrayNode::~GDArrayNode() {
}

void GDAssertNode::_bind_methods() {
}

void GDAssertNode::set_node(GDScriptParser::AssertNode *p_node) {
	node = p_node;
}

GDAssertNode::GDAssertNode() = default;
GDAssertNode::~GDAssertNode() {
}

void GDAssignableNode::_bind_methods() {
}

void GDAssignableNode::set_node(GDScriptParser::AssignableNode *p_node) {
	node = p_node;
}

GDAssignableNode::GDAssignableNode() = default;
GDAssignableNode::~GDAssignableNode() {
}

void GDAssignmentNode::_bind_methods() {
}

void GDAssignmentNode::set_node(GDScriptParser::AssignmentNode *p_node) {
	node = p_node;
}

GDAssignmentNode::GDAssignmentNode() = default;
GDAssignmentNode::~GDAssignmentNode() {
}

void GDAwaitNode::_bind_methods() {
}

void GDAwaitNode::set_node(GDScriptParser::AwaitNode *p_node) {
	node = p_node;
}

GDAwaitNode::GDAwaitNode() = default;
GDAwaitNode::~GDAwaitNode() {
}

void GDBinaryOpNode::_bind_methods() {
}

void GDBinaryOpNode::set_node(GDScriptParser::BinaryOpNode *p_node) {
	node = p_node;
}

GDBinaryOpNode::GDBinaryOpNode() = default;
GDBinaryOpNode::~GDBinaryOpNode() {
}

void GDBreakNode::_bind_methods() {
}

void GDBreakNode::set_node(GDScriptParser::BreakNode *p_node) {
	node = p_node;
}

GDBreakNode::GDBreakNode() = default;
GDBreakNode::~GDBreakNode() {
}

void GDBreakpointNode::_bind_methods() {
}

void GDBreakpointNode::set_node(GDScriptParser::BreakpointNode *p_node) {
	node = p_node;
}

GDBreakpointNode::GDBreakpointNode() = default;
GDBreakpointNode::~GDBreakpointNode() {
}

void GDCallNode::_bind_methods() {
}

void GDCallNode::set_node(GDScriptParser::CallNode *p_node) {
	node = p_node;
}

GDCallNode::GDCallNode() = default;
GDCallNode::~GDCallNode() {
}

void GDCastNode::_bind_methods() {
}

void GDCastNode::set_node(GDScriptParser::CastNode *p_node) {
	node = p_node;
}

GDCastNode::GDCastNode() = default;
GDCastNode::~GDCastNode() {
}

void GDClassNode::_bind_methods() {
}

void GDClassNode::set_node(GDScriptParser::ClassNode *p_node) {
	node = p_node;
}

GDClassNode::GDClassNode() = default;
GDClassNode::~GDClassNode() {
}

void GDConstantNode::_bind_methods() {
}

void GDConstantNode::set_node(GDScriptParser::ConstantNode *p_node) {
	node = p_node;
}

GDConstantNode::GDConstantNode() = default;
GDConstantNode::~GDConstantNode() {
}

void GDContinueNode::_bind_methods() {
}

void GDContinueNode::set_node(GDScriptParser::ContinueNode *p_node) {
	node = p_node;
}

GDContinueNode::GDContinueNode() = default;
GDContinueNode::~GDContinueNode() {
}

void GDDictionaryNode::_bind_methods() {
}

void GDDictionaryNode::set_node(GDScriptParser::DictionaryNode *p_node) {
	node = p_node;
}

GDDictionaryNode::GDDictionaryNode() = default;
GDDictionaryNode::~GDDictionaryNode() {
}

void GDEnumNode::_bind_methods() {
}

void GDEnumNode::set_node(GDScriptParser::EnumNode *p_node) {
	node = p_node;
}

GDEnumNode::GDEnumNode() = default;
GDEnumNode::~GDEnumNode() {
}

void GDExpressionNode::_bind_methods() {
}

void GDExpressionNode::set_node(GDScriptParser::ExpressionNode *p_node) {
	node = p_node;
}

GDExpressionNode::GDExpressionNode() = default;
GDExpressionNode::~GDExpressionNode() {
}

void GDForNode::_bind_methods() {
}

void GDForNode::set_node(GDScriptParser::ForNode *p_node) {
	node = p_node;
}

GDForNode::GDForNode() = default;
GDForNode::~GDForNode() {
}

void GDFunctionNode::_bind_methods() {
}

void GDFunctionNode::set_node(GDScriptParser::FunctionNode *p_node) {
	node = p_node;
}

GDFunctionNode::GDFunctionNode() = default;
GDFunctionNode::~GDFunctionNode() {
}

void GDGetNodeNode::_bind_methods() {
}

void GDGetNodeNode::set_node(GDScriptParser::GetNodeNode *p_node) {
	node = p_node;
}

GDGetNodeNode::GDGetNodeNode() = default;
GDGetNodeNode::~GDGetNodeNode() {
}

void GDIdentifierNode::_bind_methods() {
}

void GDIdentifierNode::set_node(GDScriptParser::IdentifierNode *p_node) {
	node = p_node;
}

GDIdentifierNode::GDIdentifierNode() = default;
GDIdentifierNode::~GDIdentifierNode() {
}

void GDIfNode::_bind_methods() {
}

void GDIfNode::set_node(GDScriptParser::IfNode *p_node) {
	node = p_node;
}

GDIfNode::GDIfNode() = default;
GDIfNode::~GDIfNode() {
}

void GDLambdaNode::_bind_methods() {
}

void GDLambdaNode::set_node(GDScriptParser::LambdaNode *p_node) {
	node = p_node;
}

GDLambdaNode::GDLambdaNode() = default;
GDLambdaNode::~GDLambdaNode() {
}

void GDLiteralNode::_bind_methods() {
}

void GDLiteralNode::set_node(GDScriptParser::LiteralNode *p_node) {
	node = p_node;
}

GDLiteralNode::GDLiteralNode() = default;
GDLiteralNode::~GDLiteralNode() {
}

void GDMatchNode::_bind_methods() {
}

void GDMatchNode::set_node(GDScriptParser::MatchNode *p_node) {
	node = p_node;
}

GDMatchNode::GDMatchNode() = default;
GDMatchNode::~GDMatchNode() {
}

void GDMatchBranchNode::_bind_methods() {
}

void GDMatchBranchNode::set_node(GDScriptParser::MatchBranchNode *p_node) {
	node = p_node;
}

GDMatchBranchNode::GDMatchBranchNode() = default;
GDMatchBranchNode::~GDMatchBranchNode() {
}

void GDParameterNode::_bind_methods() {
}

void GDParameterNode::set_node(GDScriptParser::ParameterNode *p_node) {
	node = p_node;
}

GDParameterNode::GDParameterNode() = default;
GDParameterNode::~GDParameterNode() {
}

void GDPassNode::_bind_methods() {
}

void GDPassNode::set_node(GDScriptParser::PassNode *p_node) {
	node = p_node;
}

GDPassNode::GDPassNode() = default;
GDPassNode::~GDPassNode() {
}

void GDPatternNode::_bind_methods() {
}

void GDPatternNode::set_node(GDScriptParser::PatternNode *p_node) {
	node = p_node;
}

GDPatternNode::GDPatternNode() = default;
GDPatternNode::~GDPatternNode() {
}

void GDPreloadNode::_bind_methods() {
}

void GDPreloadNode::set_node(GDScriptParser::PreloadNode *p_node) {
	node = p_node;
}

GDPreloadNode::GDPreloadNode() = default;
GDPreloadNode::~GDPreloadNode() {
}

void GDReturnNode::_bind_methods() {
}

void GDReturnNode::set_node(GDScriptParser::ReturnNode *p_node) {
	node = p_node;
}

GDReturnNode::GDReturnNode() = default;
GDReturnNode::~GDReturnNode() {
}

void GDSelfNode::_bind_methods() {
}

void GDSelfNode::set_node(GDScriptParser::SelfNode *p_node) {
	node = p_node;
}

GDSelfNode::GDSelfNode() = default;
GDSelfNode::~GDSelfNode() {
}

void GDSignalNode::_bind_methods() {
}

void GDSignalNode::set_node(GDScriptParser::SignalNode *p_node) {
	node = p_node;
}

GDSignalNode::GDSignalNode() = default;
GDSignalNode::~GDSignalNode() {
}

void GDSubscriptNode::_bind_methods() {
}

void GDSubscriptNode::set_node(GDScriptParser::SubscriptNode *p_node) {
	node = p_node;
}

GDSubscriptNode::GDSubscriptNode() = default;
GDSubscriptNode::~GDSubscriptNode() {
}

void GDSuiteNode::_bind_methods() {
}

void GDSuiteNode::set_node(GDScriptParser::SuiteNode *p_node) {
	node = p_node;
}

GDSuiteNode::GDSuiteNode() = default;
GDSuiteNode::~GDSuiteNode() {
}

void GDTernaryOpNode::_bind_methods() {
}

void GDTernaryOpNode::set_node(GDScriptParser::TernaryOpNode *p_node) {
	node = p_node;
}

GDTernaryOpNode::GDTernaryOpNode() = default;
GDTernaryOpNode::~GDTernaryOpNode() {
}

void GDTypeNode::_bind_methods() {
}

void GDTypeNode::set_node(GDScriptParser::TypeNode *p_node) {
	node = p_node;
}

GDTypeNode::GDTypeNode() = default;
GDTypeNode::~GDTypeNode() {
}

void GDTypeTestNode::_bind_methods() {
}

void GDTypeTestNode::set_node(GDScriptParser::TypeTestNode *p_node) {
	node = p_node;
}

GDTypeTestNode::GDTypeTestNode() = default;
GDTypeTestNode::~GDTypeTestNode() {
}

void GDUnaryOpNode::_bind_methods() {
}

void GDUnaryOpNode::set_node(GDScriptParser::UnaryOpNode *p_node) {
	node = p_node;
}

GDUnaryOpNode::GDUnaryOpNode() = default;
GDUnaryOpNode::~GDUnaryOpNode() {
}

void GDVariableNode::_bind_methods() {
}

void GDVariableNode::set_node(GDScriptParser::VariableNode *p_node) {
	node = p_node;
}

GDVariableNode::GDVariableNode() = default;
GDVariableNode::~GDVariableNode() {
}

void GDWhileNode::_bind_methods() {
}

void GDWhileNode::set_node(GDScriptParser::WhileNode *p_node) {
	node = p_node;
}

GDWhileNode::GDWhileNode() = default;
GDWhileNode::~GDWhileNode() {
}

