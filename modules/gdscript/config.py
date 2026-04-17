def can_build(env, platform):
    env.module_add_dependencies("gdscript", ["jsonrpc", "websocket"], True)
    return True


def configure(env):
    pass


def get_doc_classes():
    return [
        "@GDScript",
        "GDScript",
        "GDScriptSyntaxHighlighter",
        "GDScriptErrorChecker",
        "GDMember",
        "GDNode",
        "GDAnnotationNode",
        "GDArrayNode",
        "GDAssertNode",
        "GDAssignableNode",
        "GDAssignmentNode",
        "GDAwaitNode",
        "GDBinaryOpNode",
        "GDBreakNode",
        "GDBreakpointNode",
        "GDCallNode",
        "GDCastNode",
        "GDClassNode",
        "GDConstantNode",
        "GDContinueNode",
        "GDDictionaryNode",
        "GDEnumNode",
        "GDExpressionNode",
        "GDForNode",
        "GDFunctionNode",
        "GDGetNodeNode",
        "GDIdentifierNode",
        "GDIfNode",
        "GDLambdaNode",
        "GDLiteralNode",
        "GDMatchNode",
        "GDMatchBranchNode",
        "GDParameterNode",
        "GDPassNode",
        "GDPatternNode",
        "GDPreloadNode",
        "GDReturnNode",
        "GDSelfNode",
        "GDSignalNode",
        "GDSubscriptNode",
        "GDSuiteNode",
        "GDTernaryOpNode",
        "GDTypeNode",
        "GDTypeTestNode",
        "GDUnaryOpNode",
        "GDVariableNode",
        "GDWhileNode",
    ]


def get_doc_path():
    return "doc_classes"
