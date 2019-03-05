/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 17:18:31 by vomelchu          #+#    #+#             */
/*   Updated: 2019/02/11 17:18:35 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"
# define OUTPUT(x) 			std::cout << (x) << std::endl;

Parser::Parser(){}
Parser::~Parser(){}

Parser::Parser(Parser const &rhs){
	*this = rhs;
}

Parser &Parser::operator=(Parser const &rhs){
	if (this != &rhs)
	{
		this->iter = rhs.iter;
		this->end = rhs.end;
		this->data = rhs.data;
		this->operand = rhs.operand;
	}
	return *this;
}

eOperandType	Parser::return_type(int type)
{
	if (type == 1)
		return (Int8);
	else if (type == 2)
		return (Int16);
	else if (type == 3)
		return (Int32);
	else if (type == 4)
		return (Float);
	else if (type == 5)
		return (Double);
	else throw ParserException("Something bad");
}

void			Parser::add()
{
	int size = operand.size();
	if (size < 2)
		throw ParserException("add imposible");
	IOperand const * tmp = *operand.at(size - 2) + *operand.at(size - 1);
	if (!tmp) throw ParserException("overflow after add");
	delete operand.at(operand.size() - 1);
	delete operand.at(operand.size() - 2);
	operand.pop_back();
	operand.pop_back();
	operand.push_back(tmp);
}

void			Parser::pop()
{
	if (operand.size() < 1) throw ParserException("stack is empty:(");
	else {
		delete operand.at(operand.size() - 1);
		operand.pop_back();
	}
}

void			Parser::sub()
{
	int size = operand.size();
	if (size < 2)
		throw ParserException("sub imposible");
	IOperand const * tmp = *operand.at(size - 2) - *operand.at(size - 1);
	if (!tmp) throw ParserException("overflow after sub");
	delete operand.at(operand.size() - 1);
	delete operand.at(operand.size() - 2);
	operand.pop_back();
	operand.pop_back();
	operand.push_back(tmp);
}

void			Parser::mul()
{
	int size = operand.size();
	if (size < 2) throw ParserException("mul imposible");
	IOperand const * tmp = *operand.at(size - 1) * *operand.at(size - 2);
	if (!tmp) throw ParserException("overflow after mul");
	delete operand.at(operand.size() - 1);
	delete operand.at(operand.size() - 2);
	operand.pop_back();
	operand.pop_back();
	operand.push_back(tmp);
}

void			Parser::div()
{
	int size = operand.size();
	if (size < 2) throw ParserException("mul imposible");
	IOperand const * first = operand.at(size - 1);
	IOperand const * second = operand.at(size - 2);
	if (std::atof(first->toString().c_str()) == 0) throw ParserException("div to 0 imposible");
	IOperand const * tmp = *second / *first;
	if (!tmp) throw ParserException("overflow after div");
	delete operand.at(operand.size() - 1);
	delete operand.at(operand.size() - 2);
	operand.pop_back();
	operand.pop_back();
	operand.push_back(tmp);
}

void			Parser::mod()
{
	int size = operand.size();
	if (size < 2) throw ParserException("mod imposible");
	IOperand const * first = operand.at(size - 1);
	IOperand const * second = operand.at(size - 2);
	// printf("%s\n", first->toString().c_str());
	if (std::atof(first->toString().c_str()) == 0 ||
		std::atof(second->toString().c_str()) == 0) throw ParserException("div to 0 imposible");
	IOperand const * tmp = *first % *second;
	if (!tmp) throw ParserException("overflow after mod");
	delete operand.at(operand.size() - 1);
	delete operand.at(operand.size() - 2);
	operand.pop_back();
	operand.pop_back();
	operand.push_back(tmp);
}

void			Parser::dump()
{
	IOperand const * a;
	int size = operand.size();
	if (size < 1) throw ParserException("dump:( stack is empty");
	for (int i = size - 1; i >= 0; i--)
	{
		a = operand.at(i);
		std::cout << a->toString() << std::endl;
	}
}

void			Parser::push(std::vector<Data>::iterator	iter)
{
	IOperand const *a;
	a = _factory.createOperand(return_type(iter->type),iter->value);
	if (a) operand.push_back(a);
}

void			Parser::assert(std::vector<Data>::iterator	iter)
{
	if (operand.size() == 0) ParserException("stack is empty:(");
	// printf("first - : %f\n", std::atof(iter->value.c_str()));
	// printf("second - : %f\n", std::atof(operand.at(operand.size() - 1)->toString().c_str()));
	if (std::atof(iter->value.c_str()) != std::atof(operand.at(operand.size() - 1)->toString().c_str()))
		throw ParserException("dont assert. Something bad in type or value");
}

void			Parser::print()
{
	if (operand.size() < 1) throw ParserException("print dont work. Stack empty:(");
	IOperand const *a = operand.at(operand.size() - 1);
	if (a->getType() != Int8) throw ParserException("print dont work. not Int8");
	char b = (char)stoi(a->toString());
	std::cout << b << std::endl;
}

bool			Parser::check_exit()
{
	std::vector<Data>::iterator start_check = data.begin();
	std::vector<Data>::iterator end_check = data.end();
	try{
		while(start_check < end_check)
		{
			if (start_check->command == EXIT)
				return (true);
			++start_check;
		}
		throw ParserException("No exit in instruction");
	}
	catch (AvmException& e)
	{
		std::cout << e.what() <<std::endl;
	}
	return (false);
}

void			Parser::more()
{
	int size = operand.size();
	if (size < 2)
		throw ParserException("more imposible");
	IOperand const * first = operand.at(size - 2);
	IOperand const * second = operand.at(size - 1);
	IOperand const * tmp;
	if (std::atof(first->toString().c_str()) >= std::atof(second->toString().c_str()))
		tmp = _factory.createOperand(first->getType(), first->toString());
	else
		tmp = _factory.createOperand(second->getType(), second->toString());
	delete operand.at(operand.size() - 1);
	delete operand.at(operand.size() - 2);
	operand.pop_back();
	operand.pop_back();
	operand.push_back(tmp);
}

void			Parser::less()
{
	int size = operand.size();
	if (size < 2)
		throw ParserException("less imposible");
	IOperand const * first = operand.at(size - 2);
	IOperand const * second = operand.at(size - 1);
	IOperand const * tmp;
	if (std::atof(first->toString().c_str()) <= std::atof(second->toString().c_str()))
		tmp = _factory.createOperand(first->getType(), first->toString());
	else
		tmp = _factory.createOperand(second->getType(), second->toString());
	delete operand.at(operand.size() - 1);
	delete operand.at(operand.size() - 2);
	operand.pop_back();
	operand.pop_back();
	operand.push_back(tmp);
}

void			Parser::lastprint()
{
	if (operand.size() < 1) throw ParserException("stack empty for print");
	std::cout << operand.at(operand.size() - 1)->toString() << std::endl;
}

Parser::Parser(std::vector<Data> d) : data(d)
{
	iter = data.begin();
	end = data.end();
	int error_line = 1;
	if(check_exit())
		while (iter < end)
		{
			try
			{
				switch(iter->command)
				{
					case (PUSH):
						push(iter);
						break;
					case (ADD):
						add();
						break;
					case (POP):
						pop();
						break;
					case (SUB):
						sub();
						break;
					case (MUL):
						mul();
						break;
					case (DIV):
						div();
						break;
					case (MOD):
						mod();
						break;
					case (DUMP):
						dump();
						break;
					case (ASSERT):
						assert(iter);
						break;
					case (PRINT):
						print();
						break;
					case (MORE):
						more();
						break;
					case (LESS):
						less();
						break;
					case (LASTPRINT):
						lastprint();
						break;
					case (EXIT):
						iter = end;
						break;
				}
			}
			catch (AvmException& e)
			{
				std::cout << "\033[1;31merror in line [" << error_line<<"]\033[0m ";
				std::cout << e.what() << std::endl;
			}
			error_line++;
			++iter;
		}
}