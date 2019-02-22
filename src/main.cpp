/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 15:13:41 by vomelchu          #+#    #+#             */
/*   Updated: 2019/02/05 15:13:43 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "AvmException.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"

int main(int argc, char **argv)
{
	try
	{
		Lexer *lexer = new Lexer(argc, argv);
		Parser *parser = new Parser(lexer->get_lexer());
	}
	catch (AvmException& e)
	{
		remove("tmp.txt");
		std::cout << e.what() << std::endl;
	}
	//printf("\n\n\n\n\n");
	//system("leaks -q avm");
	return (0);
}