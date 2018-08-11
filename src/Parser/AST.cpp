#include "Parser/AST.h"

namespace amalt {
	AST::AST(const Type t, ae e, const ui64 l, const ui64 p) : type(t), expr(std::move(e)), line(l), pos(p) {}
	//AST::AST() : type(INT), expr(), line(0), pos(0) {}
	LetAst::LetAst(AST n, AST e) : nexpr(std::move(n)), vexpr(std::move(e)) {}
	//CondAst::CondAst() {}
	CondAst::CondAst(std::vector<std::shared_ptr<TupleAst>> &el) : exprlist(std::move(el)) {}
	MatchAst::MatchAst(AST e, std::vector<std::shared_ptr<TupleAst>>& el) : expr(std::move(e)), exprlist(std::move(el)) {}
	FCallAst::FCallAst(TupleAst el) : exprlist(std::move(el)) {}
	DefunAst::DefunAst(const RString n, const std::vector<RString>& an, std::vector<AST>& el) : name(std::move(n)), argsnames(std::move(an)), exprlist(std::move(el)) {}
	QuoteAst::QuoteAst(AST e) : expr(e) {}
	/*AST AST::operator=(const AST & o)
	{
		return AST(o);
	}*/
	String AST::toString()
	{
		String s;
		switch (type)
		{
		case NIL_:
			s = L"nil";
			break;
		case INT:
			s = std::to_wstring(std::get<i64>(expr));
			break;
		case UINT:
			s = std::to_wstring(std::get<ui64>(expr));
			break;
		case FLOAT:
			s = std::to_wstring(std::get<f64>(expr));
			break;
		case SYMBOL:
			s = *std::get<RString>(expr);
			break;
		case STRING:
			s = String(L"\"") + *std::get<RString>(expr) + String(L"\"");
			break;
		case TUPLE:
			s = std::get<std::shared_ptr<TupleAst>>(expr).get()->toString();
			break;
		case QUOTE:
			s = std::get<std::shared_ptr<QuoteAst>>(expr).get()->toString();
			break;
		case LET:
			s = std::get<std::shared_ptr<LetAst>>(expr).get()->toString();
			break;
		case COND:
			s = std::get<std::shared_ptr<CondAst>>(expr).get()->toString();
			break;
		default:
			s = L"��ûд�꣬��ʲô����";
			break;
		}
		return s;
	}
	String LetAst::toString()
	{
		return String(L"(let ") + nexpr.toString() + String(L" ") + vexpr.toString() + String(L")");
	}
	String CondAst::toString()
	{
		String s;
		if (exprlist.size() != 0) {
			for (size_t i = 0;; i++) {
				s += exprlist[i].get()->toString();
				if (i == exprlist.size()-1) {
					break;
				}
				s += L' ';
			}
		}
		return String(L"(cond ") + s + String(L")");
	}
	String MatchAst::toString()
	{
		String s;
		if (exprlist.size() != 0) {
			for (size_t i = 0;; i++) {
				s += exprlist[i].get()->toString();
				if (i == exprlist.size()-1) {
					break;
				}
				s += L' ';
			}
		}
		return String(L"(match ") + expr.toString() + String(L")");
	}
	String FCallAst::toString()
	{
		String s;
		if (exprlist.size() != 0) {
			for (size_t i = 0;; i++) {
				s += exprlist[i].toString();
				if (i == exprlist.size()-1) {
					break;
				}
				s += L' ';
			}
		}
		return String(L"(") + s + String(L")");
	}
	String DefunAst::toString()
	{
		String ns;
		if (exprlist.size() != 0) {
			for (size_t i = 0;; i++) {
				ns += *argsnames[i];
				if (i == exprlist.size()-1) {
					break;
				}
				ns += L' ';
			}
		}
		String s;
		if (exprlist.size() != 0) {
			for (size_t i = 0;; i++) {
				s += exprlist[i].toString();
				if (i == exprlist.size()-1) {
					break;
				}
				s += L' ';
			}
		}
		return String(L"(fun ") + *name + String(L"(")  + ns + String(L")") +
			s + String(L")");
	}
	String TupleAst::toString()
	{
		String s;
		if (this->size() != 0) {
			for (size_t i = 0;; i++) {
				s += this->operator[](i).toString();
				if (i == this->size() -1) {
					break;
				}
				s += L' ';
			}
		}
		return String(L"(tuple ") + s + String(L")");
	}
	String QuoteAst::toString()
	{
		return String(L"(quote ") + expr.toString() +String(L")");
	}
}
