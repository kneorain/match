#include "Tokenizer.hpp"
#include <cstdint>
#include "../../Types/SlideView.hpp"
namespace Match::Parser
{
	Tokenizer::Tokenizer()
	{
	}
	Tokenizer::~Tokenizer()
	{
	}

	const u8 INSTANCE_ACCESS = '.';

	std::vector<Token> Tokenizer::Tokenize(SlideViewChar source)
	{
		std::vector<Token> tokens = {};
		this->m_subTokens = source;
		this->m_window = SlideViewChar(source.GetHead(), source.GetHead());
		this->lastRowIndex = 0;

		while (this->m_subTokens.IsWindowExausted(m_window))
			tokens.push_back(this->NextToken());
		return tokens;
	}

	Token Tokenizer::NextToken()
	{
		u8 peek;
		u8 quote;
		constexpr u8 Or = getFirstByte((u16)Operator2::Or);
		constexpr u8 And = getFirstByte((u16)Operator2::And);
		constexpr u8 ShiftLeft = getFirstByte((u16)Operator2::ShiftLeft);
		constexpr u8 ShiftRight = getFirstByte((u16)Operator2::ShiftRight);
		constexpr u8 AddAssign = getFirstByte((u16)Operator2::AddAssign);
		constexpr u8 SubtractAssign = getFirstByte((u16)Operator2::SubtractAssign);
		constexpr u8 MultiplyAssign = getFirstByte((u16)Operator2::MultiplyAssign);
		constexpr u8 DivideAssign = getFirstByte((u16)Operator2::DivideAssign);
		constexpr u8 ModuloAssign = getFirstByte((u16)Operator2::ModuloAssign);
		constexpr u8 BitwiseAndAssign = getFirstByte((u16)Operator2::BitwiseAndAssign);
		constexpr u8 BitwiseOrAssign = getFirstByte((u16)Operator2::BitwiseOrAssign);
		constexpr u8 BitwiseXorAssign = getFirstByte((u16)Operator2::BitwiseXorAssign);
		constexpr u8 Return = getFirstByte((u16)Operator2::Return);
		constexpr u8 Equal = getFirstByte((u16)Operator2::Equal);
		constexpr u8 NotEqual = getFirstByte((u16)Operator2::NotEqual);
		constexpr u8 LessThanOrEqual = getFirstByte((u16)Operator2::LessThanOrEqual);
		constexpr u8 GreaterThanOrEqual = getFirstByte((u16)Operator2::GreaterThanOrEqual);

	next_sub_token:
		peek = this->m_window.Back<u8>();
		// Back the tail of the window
		switch (peek)
		{
		case (u8)Whitespace::CarriageReturn:
		case (u8)Whitespace::FormFeed:
		case (u8)Whitespace::Newline:
		case (u8)Whitespace::Space:
		case (u8)Whitespace::Tab:
		{
			this->m_window.Skip();

			if (peek == (u8)Whitespace::Newline)
				this->IncrementRow();

			goto next_sub_token;
		};
		}
		
		switch (peek)
		{

		// 2 char operators
		case getFirstByte((u16)Operator2::Or):
		case getFirstByte((u16)Operator2::And):
		case getFirstByte((u16)Operator2::ShiftLeft):
		case getFirstByte((u16)Operator2::ShiftRight):
		case getFirstByte((u16)Operator2::AddAssign):
		case getFirstByte((u16)Operator2::SubtractAssign):
		case getFirstByte((u16)Operator2::MultiplyAssign):
		case getFirstByte((u16)Operator2::DivideAssign):
		case getFirstByte((u16)Operator2::ModuloAssign):
			// case getFirstByte((u16)Operator2::BitwiseAndAssign):
			// case getFirstByte((u16)Operator2::BitwiseOrAssign):
		case getFirstByte((u16)Operator2::BitwiseXorAssign):
			// case getFirstByte((u16)Operator2::Return):
		case getFirstByte((u16)Operator2::Equal):
		case getFirstByte((u16)Operator2::NotEqual):
			// case getFirstByte((u16)Operator2::LessThanOrEqual):
			// case getFirstByte((u16)Operator2::GreaterThanOrEqual):
			{
				this->SetTokenType(TokenType::Operator);

				switch (this->m_window.Back<u16>())
				{
				case (u16)Operator2::Or:
				case (u16)Operator2::And:
				case (u16)Operator2::ShiftLeft:
				case (u16)Operator2::ShiftRight:
				case (u16)Operator2::AddAssign:
				case (u16)Operator2::SubtractAssign:
				case (u16)Operator2::MultiplyAssign:
				case (u16)Operator2::DivideAssign:
				case (u16)Operator2::ModuloAssign:
				case (u16)Operator2::BitwiseAndAssign:
				case (u16)Operator2::BitwiseOrAssign:
				case (u16)Operator2::BitwiseXorAssign:
				case (u16)Operator2::Return:
				case (u16)Operator2::Equal:
				case (u16)Operator2::NotEqual:
				case (u16)Operator2::LessThanOrEqual:
				case (u16)Operator2::GreaterThanOrEqual:
				{
					this->SetTokenType(TokenType::Operator);
					this->m_window.IncTail(1);
					goto increment;
				}
				}
			}
		}

		// 1 char operators -----------------------
		switch (peek)
		{
		case (u8)Operator1::Not:
		case (u8)Operator1::BitwiseOr:
		case (u8)Operator1::BitwiseAnd:
		case (u8)Operator1::BitwiseXor:
		case (u8)Operator1::Add:
		case (u8)Operator1::Subtract:
		case (u8)Operator1::Multiply:
		case (u8)Operator1::Divide:
		case (u8)Operator1::Modulo:
		case (u8)Operator1::Equal:
		// case (u8)Operator1::NotEqual:
		case (u8)Operator1::LessThan:
		case (u8)Operator1::GreaterThan:
		// case (u8)Operator1::Assign:
		case (u8)Operator1::Access:
		case (u8)Operator1::Type:
		case (u8)Operator1::Optional:
		{
			this->SetTokenType(TokenType::Operator);
			goto increment;
		}
		}

		// Delimiters -----------------------
		switch (peek)
		{

		case (u8)Delimiter::OpenBrace:
		case (u8)Delimiter::CloseBrace:
		case (u8)Delimiter::OpenParenthesis:
		case (u8)Delimiter::CloseParenthesis:
		case (u8)Delimiter::OpenSquareBracket:
		case (u8)Delimiter::CloseSquareBracket:
		case listSeparator:
		case scopeResolution:
		case typeSeparator:
		case INSTANCE_ACCESS:
		{
			this->SetTokenType(TokenType::Delimiter);
			// breaks nested switch in loop
			if (this->m_window.IsPopulated())
				this->m_window.IncTail();
			goto increment;
		};
		}

		// Quotes -----------------------
		quote = peek;
		switch (quote)
		{
		case (u8)Quotes::Single:
			this->SetTokenType(TokenType::CharLiteral);
			goto parse_quote;

		case (u8)Quotes::Double:
			this->SetTokenType(TokenType::StringLiteral);
		parse_quote:
			this->m_window.IncTail();

			switch (peek = this->m_window.Back<u8>())
			{
			case (u8)Whitespace::Newline:
			{
				this->IncrementRow();
				// Temp fix for newlines in strings
				// as this fixes the column calculation
				this->lastRowIndex -= 2;
				break;
			}

			// Backslash
			case '\\':
			{
				if (this->m_window.Back(1) == quote)
					this->m_window.IncTail();
				goto increment;
			}
			// Closing quote
			default:
			{
				if (peek == quote)
				{
					this->m_window.IncTail();
					goto return_token;
				}
			}
			};
			

			if (this->m_window.IsPopulated())
				goto parse_quote;

			// TODO: Throw compiler error if incomplete
			goto return_token;
		}

		// Identifiers -----------------------
		switch (peek)
		{
		case Or:
		case And:
		case ShiftLeft:
		case ShiftRight:
		case AddAssign:
		case SubtractAssign:
		case MultiplyAssign:
		case DivideAssign:
		case ModuloAssign:
		case BitwiseXorAssign:
			// case BitwiseAndAssign:
			// case BitwiseOrAssign:
			// case Return:
			// case LessThanOrEqual:
			// case GreaterThanOrEqual:
		case Equal:
		case NotEqual:
		// case (u8)Operator1::Not:
		// case (u8)Operator1::BitwiseOr:
		// case (u8)Operator1::BitwiseAnd:
		// case (u8)Operator1::BitwiseXor:
		// case (u8)Operator1::Add:
		// case (u8)Operator1::Subtract:
		// case (u8)Operator1::Multiply:
		// case (u8)Operator1::Divide:
		// case (u8)Operator1::Modulo:
		// case (u8)Operator1::Equal:
		// case (u8)Operator1::NotEqual:
		// case (u8)Operator1::LessThan:
		// case (u8)Operator1::GreaterThan:
		//  case (u8)Operator1::Assign:
		case (u8)Operator1::Access:
		case (u8)Operator1::Type:
		case (u8)Operator1::Optional:
			// case INSTANCE_ACCESS:
			// case typeSeparator:
		case scopeResolution:
		case listSeparator:
		{
			this->SetTokenType(TokenType::Identifier);
			goto increment;
		}

		increment:
			this->m_window.IncTail();

			if (this->m_window.IsPopulated())
				goto next_sub_token;

		return_token:

			return this->CreateToken();
		}
	}

	enum class Quote : u8
	{
		Single = '\'',
		Double = '"',
	};
}