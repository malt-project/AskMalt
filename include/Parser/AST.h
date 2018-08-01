#pragma once

//#include <string>
#include <vector>
#include <memory>
#include "Objects.h"

namespace amalt {
	class Token {
	public:
		enum Type {
			LP = '(',
			RP = ')',
			LMP = '[',
			RMP = ']',
			QUO = '\'',

			NUM = 'N',
			STR = 'S',
			SYM = 's',
		};
		int tp;
		std::wstring exvalue;
		size_t line, pos;

		Token(int t, std::wstring v, size_t line, size_t pos);

		bool operator==(const Token &);
		bool operator!=(const Token &);

		std::wstring toString() const;
	};

	class AST {
	public:
		enum Type {
			OBJ,
			IF_,
			COND,
			MATCH,
			QUOTE,
			FCALL,
			DEFUN,
		} type;

		const ui64 line, pos;

		AST(Type t, const ui64 l, const ui64 p) : type(t), line(l), pos(p) {}
		AST(AST &) = default;
		AST(AST &&) = default;
		//virtual Value eval() = 0;
	};

	class FCallAST : public AST {
	public:
		std::vector<AST> args;

		FCallAST(const ui64 l, const ui64 p, std::vector<AST> a):
			AST(FCALL, l, p), args(std::move(a)) {}
	};

	class DefunAST : public AST {
	public:
		String fname;
		std::vector<String> args;

	};
}