/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 17:44:12 by vomelchu          #+#    #+#             */
/*   Updated: 2019/02/18 17:46:55 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lexer.hpp"
#include <cstring>
#include <regex>

Lexer::Lexer(){}
Lexer::~Lexer(){}

int					Lexer::ret_command(char *str)
{
	if (str == NULL) return (0);
	else if (!strcmp(";;", str)) {return (15);}
	else if (!strcmp(";", str)) return (0);
	else if (str[0] == ';') return (0);
	else if (!strcmp("push", str)) return (1);
	else if (!strcmp("assert", str)) return (2);
	else if (!strcmp("add", str)) return (3);
	else if (!strcmp("pop", str)) return (4);
	else if (!strcmp("dump", str)) return (5);
	else if (!strcmp("sub", str)) return (6);
	else if (!strcmp("mul", str)) return (7);
	else if (!strcmp("div", str)) return (8);
	else if (!strcmp("mod", str)) return (9);
	else if (!strcmp("print", str)) return (10);
	else if (!strcmp("exit", str)) return (11);
	else if (!strcmp("more", str)) return (12);
	else if (!strcmp("less", str)) return (13);
	else if (!strcmp("lastprint", str)) return (14);
	else return (16);
}

int		Lexer::make_token(char *str)
{
	if (!strcmp("int8", str)) return (1);
	else if (!strcmp("int16", str)) return (2);
	else if (!strcmp("int32", str)) return (3);
	else if (!strcmp("float", str)) return (4);
	else if (!strcmp("double", str)) return (5);
	else return (0);
}

Data				Lexer::make_data(int com, int val1, char *val2)
{
	Data data;
	data.command = com;
	data.type = val1;
	data.value = (std::string)val2;
	return data;
}

std::vector<Data>	Lexer::get_lexer() const
{
	return (this->_lexer);
}

bool				Lexer::check_with_regex(const char *arg)
{
	std::string line;
	std::ifstream in(arg);

	std::cmatch result;
	std::regex instruct("^(pop|dump|add|sub|mul|div|mod|less|more|lastprint|print|exit|;;|;.*) *?(;.*)?$");
	std::regex command_int("^(push|assert) (int8|int16|int32)\\(([\\-]?[0-9]+)\\) *?(;.*)?$");
	std::regex command_point("^(push|assert) (float|double)\\(([\\-]?[0-9]+\\.[0-9]+)\\) *?(;.*)?$");
	std::regex space_line("^(\\s*)$");
	//int i = 0;
	while (getline(in, line))
	{
	//	printf("%d\n", i);
	//	i++;
		if (std::regex_match(line.c_str(), result, instruct)) ;
		else if (std::regex_match(line.c_str(), result, command_int)) ;
		else if (std::regex_match(line.c_str(), result, command_point)) ;
		else if (std::regex_match(line.c_str(), result, space_line)) ;
		else return (false);
	}
	return (true);
}

void				Lexer::do_lexer(const char *arg)
{
	std::string line;
	std::ifstream in(arg);
	if (!check_with_regex(arg)) throw LexerException("\033[1;31mBad instuction regex\033[0m ");
	if (in.is_open())
	{
		char *s;
		while (getline(in, line))
		{
			char *s = new char[line.size() + 1];
			strcpy(s, line.c_str());
			char *p = strtok(s, " ");
			delete [] s;
			int a = ret_command(p);
			if (a == 0) continue;
			else if (a == 16) throw LexerException("\033[1;31mBad instuction\033[0m ");
			else if (a > 2 && a < 15) {_lexer.push_back(make_data(a, 0, p));}
			else if (a == 1 || a == 2)
			{
				char *command = p;
				p = strtok(NULL, "(");
				char *tmp = p;
				int toke = make_token(p);
				if (toke == 0) throw LexerException("\033[1;31mBad instuction\033[0m ");
				p = strtok(NULL, ")");
				_lexer.push_back(make_data(a, toke, p));
			}
		}
		in.close();
		remove("tmp.txt");
	}
	else throw LexerException ("\033[1;31mFile not opened\033[0m ");
}

void				Lexer::without_argv()
{
	std::ofstream out;
	out.open("tmp.txt");
	std::string str;
	int q = -1;
	while (str != ";;")
	{
		++q;
		std::cout << q <<" : ";
		if(!(std::getline(std::cin, str)))
			exit(0);
		out << str << std::endl;
	}
	std::cout << "<----result---->\n" << std::endl;
	do_lexer("tmp.txt");
}

Lexer::Lexer(int argc, char **argv)
{
	if (argc == 1)
		without_argv();
	else if (argc == 2)
		do_lexer(argv[1]);
	else throw LexerException("\033[1;31mBad Argument\033[0m ");
}
