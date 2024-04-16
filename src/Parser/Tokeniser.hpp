#pragma once

namespace Match
{
	enum class Token : uint64_t
	{
		// Keywords
		Pattern,
		Template,
		Abstract,
		Statement,
		Group,
		Namespace,
		Rule,
		For,
		While,
		Loop,
		If,
		Else,
		ElseIf,
		Switch,
		Case,
		Default,
		// Primitives
		Char,
		U32,
		I32,
		F32,
		String,
		U64,
		I64,
		Bool,
		// Operators
		BitwiseOr,
		Or,
		BitwiseAnd,
		And,
		BitwiseXor,
		Not,
		ShiftLeft,
		ShiftRight,
		Add,
		Subtract,
		Multiply,
		Divide,
		Modulo,
		Equal,
		NotEqual,
		LessThan,
		GreaterThan,
		LessThanOrEqual,
		GreaterThanOrEqual,
		Assign,
		AddAssign,
		SubtractAssign,
		MultiplyAssign,
		DivideAssign,
		ModuloAssign,
		ShiftLeftAssign,
		ShiftRightAssign,
		BitwiseAndAssign,
		BitwiseOrAssign,
		Access,
		Type,
		Namespace,
		Optional,
		Return,
		// Brackets
		OpenCurlyBracket,
		CloseCurlyBracket,
		OpenSquareBracket,
		CloseSquareBracket,
		OpenRoundBracket,
		CloseRoundBracket,
		// Punctuation
		Comma,
		Colon,
		SemiColon,
		// Literals
		CharLiteral,
		U32Literal,
		I32Literal,
		F32Literal,
		StringLiteral,
		U64Literal,
		I64Literal,
		BoolLiteral,
		// Identifiers
		Identifier,
		// End of file
		Eof
	};

	class Tokeniser
	{
	public:
		Tokeniser();
		~Tokeniser();

	private:
	};

}