/**************************************************************************/
/*  gdscript_error_checker.cpp                                            */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#include "gdscript_error_checker.h"

#include "gdscript_analyzer.h"
#include "gdscript_compiler.h"
#include "gdscript_parser.h"

void GDScriptErrorChecker::_bind_methods() {
	ClassDB::bind_method("has_errors", &GDScriptErrorChecker::has_errors);
	ClassDB::bind_method("get_error_count", &GDScriptErrorChecker::get_error_count);
	ClassDB::bind_method(D_METHOD("set_source", "source_code"), &GDScriptErrorChecker::set_source);
	ClassDB::bind_method(D_METHOD("get_error", "idx"), &GDScriptErrorChecker::get_error);
	ClassDB::bind_method(D_METHOD("get_error_line", "idx"), &GDScriptErrorChecker::get_error_line);
	ClassDB::bind_method(D_METHOD("get_error_column", "idx"), &GDScriptErrorChecker::get_error_column);
}

bool GDScriptErrorChecker::has_errors() const {
	ERR_FAIL_COND_V_MSG(parser == nullptr || compiler == nullptr, false, "No source code provided.");
	return !parser->get_errors().is_empty() || !compiler->get_error().is_empty();
}

int GDScriptErrorChecker::get_error_count() const {
	ERR_FAIL_COND_V_MSG(parser == nullptr || compiler == nullptr, -1, "No source code provided.");
	if (!parser->get_errors().is_empty()) {
		return parser->get_errors().size();
	}
	if (!compiler->get_error().is_empty()) {
		return 1;
	}
	return 0;
}

String GDScriptErrorChecker::get_error(const int p_idx) const {
	ERR_FAIL_COND_V_MSG(parser == nullptr || compiler == nullptr, String(), "No source code provided.");
	if (!parser->get_errors().is_empty()) {
		ERR_FAIL_INDEX_V(p_idx, parser->get_errors().size(), String());
		return parser->get_errors().get(p_idx).message;
	}
	if (!compiler->get_error().is_empty()) {
		ERR_FAIL_INDEX_V(p_idx, 1, String());
		return compiler->get_error();
	}
	return String();
}

int GDScriptErrorChecker::get_error_line(const int p_idx) const {
	ERR_FAIL_COND_V_MSG(parser == nullptr || compiler == nullptr, -1, "No source code provided.");
	if (!parser->get_errors().is_empty()) {
		ERR_FAIL_INDEX_V(p_idx, parser->get_errors().size(), -1);
		return parser->get_errors().get(p_idx).line;
	}
	if (!compiler->get_error().is_empty()) {
		ERR_FAIL_INDEX_V(p_idx, 1, -1);
		return compiler->get_error_line();
	}
	return -1;
}

int GDScriptErrorChecker::get_error_column(const int p_idx) const {
	ERR_FAIL_COND_V_MSG(parser == nullptr || compiler == nullptr, -1, "No source code provided.");
	if (!parser->get_errors().is_empty()) {
		ERR_FAIL_INDEX_V(p_idx, parser->get_errors().size(), -1);
		return parser->get_errors().get(p_idx).column;
	}
	if (!compiler->get_error().is_empty()) {
		ERR_FAIL_INDEX_V(p_idx, 1, -1);
		return 0;
	}
	return -1;
}

Error GDScriptErrorChecker::set_source(const String &p_source) {
	if (parser != nullptr) {
		memdelete(parser);
		parser = memnew(GDScriptParser);
	}
	if (compiler != nullptr) {
		memdelete(compiler);
		compiler = memnew(GDScriptCompiler);
	}

	Error err = parser->parse(p_source, "", false);
	if (err) {
		return err;
	}
	GDScriptAnalyzer analyzer(parser);
	err = analyzer.analyze();
	if (err) {
		return err;
	}

	Ref<GDScript> main_script = memnew(GDScript);
	main_script->set_source_code(p_source);

	err = compiler->compile(parser, *main_script, false);
	return err;
}

GDScriptErrorChecker::GDScriptErrorChecker() = default;

GDScriptErrorChecker::~GDScriptErrorChecker() {
	if (parser != nullptr) {
		memdelete(parser);
		parser = nullptr;
	}
	if (compiler != nullptr) {
		memdelete(compiler);
		compiler = nullptr;
	}
}
