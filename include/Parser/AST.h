#pragma once

#include <variant>
#include <memory>
#include "Objects.h"

namespace amalt {

	class TupleAst;
	class QuoteAst;
	class LetAst;
	class CondAst;
	class MatchAst;

	class AST {
	public:
		enum Type {
			NIL_,

			INT,
			UINT,
			FLOAT,
			STRING,
			SYMBOL,

			TUPLE,

			QUOTE,

			LET,
			COND,
			MATCH,
			FCALL,
			DEFUN,
			//LAMBDA_,
		};
		const Type type;

		using ae = std::variant <
			//base data
			i64,
			ui64,
			f64,
			RString,
			// ast struct
			std::shared_ptr<QuoteAst>,
			std::shared_ptr<TupleAst>,
			std::shared_ptr<LetAst>,
			std::shared_ptr<CondAst>,
			std::shared_ptr<MatchAst>
		>;
		ae expr;
		const ui64 line, pos;

		AST(const Type t,ae e, const ui64 l, const ui64 p);
		//AST();
		AST(const AST &o) = default;
		AST(AST &&) = default;
		//AST operator=(const AST&);
		String toString();
	};

	class TupleAst : public std::vector<AST> {
	public:
		String toString();
	};
	class QuoteAst{
	public:
		AST expr;
		String toString();
		QuoteAst(AST e);
	};

	class DefaultAst {
	public:
		DefaultAst() = default;
		DefaultAst(const DefaultAst &) = default;
		DefaultAst(DefaultAst &&) = default;
	};

	class LetAst : DefaultAst {
	public:
		AST nexpr;
		AST vexpr;
		LetAst(AST n, AST e);
		String toString();
	};

	class CondAst : DefaultAst {
	public:
		std::vector<std::shared_ptr<TupleAst>> exprlist;
		CondAst() = default;
		CondAst(std::vector<std::shared_ptr<TupleAst>> &el);
		String toString();
	};

	class MatchAst : DefaultAst {
	public:
		AST expr;
		std::vector<std::shared_ptr<TupleAst>> exprlist;

		MatchAst(AST e);
		MatchAst(AST e, std::vector<std::shared_ptr<TupleAst>> &el);
		String toString();
	};

	class FCallAst : DefaultAst {
	public:
		TupleAst exprlist;

		FCallAst(TupleAst el);
		String toString();
	};

	class DefunAst : DefaultAst {
		const RString name;
		const std::vector<RString> argsnames;
		// expend
		std::vector<AST> exprlist;

		DefunAst(const RString n, const std::vector<RString> &an, std::vector<AST> &el);
		String toString();
	};
}