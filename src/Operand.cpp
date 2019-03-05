/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 17:18:22 by vomelchu          #+#    #+#             */
/*   Updated: 2019/02/11 17:18:23 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Operand.hpp"
#include "FactoryMethod.hpp"
#include <iomanip>

Factory			_factory;

template <class T> Operand<T>::Operand(){}
template <class T> Operand<T>::~Operand(void){}

template <class T> Operand<T>::Operand(Operand const &rhs)
{
	*this = rhs;
}

template <class T> IOperand & Operand<T>::operator = (Operand const &rhs)
{ 
	if (this != &rhs)
	{
		this->_value = rhs._value;
		this->_type = rhs._type;
		this->_str = rhs._str;
	}
	return *this;
}

template <class T> Operand<T>::Operand(T value, eOperandType type)
{
	_value = value;
	_type = type;
	if (typeid(T) == typeid(float))
	{
		std::stringstream set(std::stringstream::out);
		set << std::setprecision(7) << value;
		_str = set.str();
	}
	else if (typeid(T) == typeid(double))
	{
		std::stringstream set(std::stringstream::out);
		set << std::setprecision(14) << value;
		_str = set.str();	
	}
	else
		_str = std::to_string(value);

}

template <class T> int Operand<T>::getPrecision( void ) const
{
	
	if ( typeid(T) == typeid(int8_t) )       	{ return(Int8); }
	else if ( typeid(T) == typeid(int16_t) ) 	{ return(Int16); }
	else if ( typeid(T) == typeid(int32_t) ) 	{ return(Int32); }
	else if ( typeid(T) == typeid(float) )   	{ return(Float); }
	else if ( typeid(T) == typeid(double) )  	{ return(Double); }
	else { return (0); }
}

template <class T> IOperand const *Operand<T>::operator+(IOperand const &rhs) const
{
	// if (_type == Double || rhs.getType() == Double)
	// 	return (new Operand<double>(_value + std::stod(rhs.toString()), Double));
	// else if (_type == Float || rhs.getType() == Float)
	// 	return (new Operand<float>(_value + std::stof(rhs.toString()), Float));
	// else if (_type == Int32 || rhs.getType() == Int32)
	// 	return (new Operand<int32_t>(_value + std::stoi(rhs.toString()), Int32));
	// else if (_type == Int16 || rhs.getType() == Int16)
	// 	return (new Operand<int16_t>(_value + std::stoi(rhs.toString()), Int16));
	// else return (new Operand<int8_t>(_value + std::stoi(rhs.toString()), Int8));
	IOperand const * oper;
	std::string str = std::to_string(std::stof(this->toString()) + std::stof(rhs.toString()));
	if (this->getPrecision() > rhs.getPrecision())
		oper = _factory.createOperand(this->getType(), str);
	else
		oper = _factory.createOperand(rhs.getType(), str);
	if (oper)
		return(oper);
	return (0);
}

template <class T> IOperand const *Operand<T>::operator-(IOperand const &rhs) const
{
	// if (_type == Double || rhs.getType() == Double)
	// 	return (new Operand<double>(_value - std::stod(rhs.toString()), Double));
	// else if (_type == Float || rhs.getType() == Float)
	// 	return (new Operand<float>(_value - std::stof(rhs.toString()), Float));
	// else if (_type == Int32 || rhs.getType() == Int32)
	// 	return (new Operand<int32_t>(_value - std::stoi(rhs.toString()), Int32));
	// else if (_type == Int16 || rhs.getType() == Int16)
	// 	return (new Operand<int16_t>(_value - std::stoi(rhs.toString()), Int16));
	// else return (new Operand<int8_t>(_value - std::stoi(rhs.toString()), Int8));
	IOperand const * oper;
	std::string str = std::to_string(std::stof(this->toString()) - std::stof(rhs.toString()));
	if (this->getPrecision() > rhs.getPrecision())
		oper = _factory.createOperand(this->getType(), str);
	else
		oper = _factory.createOperand(rhs.getType(), str);
	if (oper)
		return(oper);
	return (0);
}

template <class T> IOperand const *Operand<T>::operator*(IOperand const &rhs) const
{
	// if (_type == Double || rhs.getType() == Double)
	// 	return (new Operand<double>(_value * std::stod(rhs.toString()), Double));
	// else if (_type == Float || rhs.getType() == Float)
	// 	return (new Operand<float>(_value * std::stof(rhs.toString()), Float));
	// else if (_type == Int32 || rhs.getType() == Int32)
	// 	return (new Operand<int32_t>(_value * std::stoi(rhs.toString()), Int32));
	// else if (_type == Int16 || rhs.getType() == Int16)
	// 	return (new Operand<int16_t>(_value * std::stoi(rhs.toString()), Int16));
	// else return (new Operand<int8_t>(_value * std::stoi(rhs.toString()), Int8));
	IOperand const * oper;
	std::string str = std::to_string(std::stod(this->toString()) * std::stod(rhs.toString()));
	if (this->getPrecision() > rhs.getPrecision())
		oper = _factory.createOperand(this->getType(), str);
	else
		oper = _factory.createOperand(rhs.getType(), str);
	if (oper)
		return(oper);
	return (0);
}

template <class T> IOperand const *Operand<T>::operator/(IOperand const &rhs) const
{
	// if (_type == Double || rhs.getType() == Double)
	// 	return (new Operand<double>(_value / std::stod(rhs.toString()), Double));
	// else if (_type == Float || rhs.getType() == Float)
	// 	return (new Operand<float>(_value / std::stof(rhs.toString()), Float));
	// else if (_type == Int32 || rhs.getType() == Int32)
	// 	return (new Operand<int32_t>(_value / std::stoi(rhs.toString()), Int32));
	// else if (_type == Int16 || rhs.getType() == Int16)
	// 	return (new Operand<int16_t>(_value / std::stoi(rhs.toString()), Int16));
	// else return (new Operand<int8_t>(_value / std::stoi(rhs.toString()), Int8));
	IOperand const * oper;
	std::string str = std::to_string(std::stof(this->toString()) / std::stof(rhs.toString()));
	if (this->getPrecision() > rhs.getPrecision())
		oper = _factory.createOperand(this->getType(), str);
	else
		oper = _factory.createOperand(rhs.getType(), str);
	if (oper)
		return(oper);
	return (0);
}

template <class T> IOperand const *Operand<T>::operator%(IOperand const &rhs) const
{
	IOperand const * oper;
	std::string str = std::to_string(std::stoi(this->toString()) % std::stoi(rhs.toString()));
	if (this->getPrecision() > rhs.getPrecision())
		oper = _factory.createOperand(this->getType(), str);
	else
		oper = _factory.createOperand(rhs.getType(), str);
	if (oper)
		return(oper);
	return (0);
}

template <class T> std::string	const & Operand<T>::toString( void ) const
{
	return (this->_str);
}

template <class T> eOperandType Operand<T>::getType( void ) const
{
	return (_type);
}

template class Operand<int32_t>;
template class Operand<int8_t>;
template class Operand<int16_t>;
template class Operand<float>;
template class Operand<double>;