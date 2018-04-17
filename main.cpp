#include <iostream>
#include <vector>
#include <string>

#ifndef _COLORS_
#define _COLORS_
// https://stackoverflow.com/questions/20608058/c-colour-console-text
/* FOREGROUND */
#define RST  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#define BG_RST  "\x1B[40m"
#define BG_KRED  "\x1B[41m"
#define BG_KGRN  "\x1B[42m"
#define BG_KYEL  "\x1B[43m"
#define BG_KBLU  "\x1B[44m"
#define BG_KMAG  "\x1B[45m"
#define BG_KCYN  "\x1B[46m"
#define BG_KWHT  "\x1B[47m"

#define FRED(x) KRED x RST
#define FGRN(x) KGRN x RST
#define FYEL(x) KYEL x RST
#define FBLU(x) KBLU x RST
#define FMAG(x) KMAG x RST
#define FCYN(x) KCYN x RST
#define FWHT(x) KWHT x RST

#define BOLD(x) "\x1B[1m" x RST
#define UNDL(x) "\x1B[4m" x RST
#endif  /* _COLORS_ */

int mColumns = 10;

void clearLine()
{
    std::string cleanLine(mColumns, ' ');
    std::cout << "\r" << cleanLine;
}

void clear() {
	// https://stackoverflow.com/a/6487534
    // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
    std::cout << "\x1B[2J\x1B[H";
}

class Menu
{
	bool is_selected;
	unsigned selected_row;
	std::vector<std::string> rows;

public:
	Menu() = default;
	Menu(bool _is_selected, unsigned _selected_row, std::vector<std::string> _rows): //тут всё копируеться, не дело
		is_selected(_is_selected),
		selected_row(_selected_row),
		rows(_rows)
	{};

	~Menu() = default;
	
	void print() //печатает ВСЁ - оч медленно //пусть это будет инициализирующая печать
	{
		clear();
		int i =0;
		for (auto row = rows.begin(); row != rows.end(); ++row)
		{
			if (is_selected and selected_row == i++ )
			{
				// Save cursor position: \033[s
				// https://en.wikipedia.org/wiki/ANSI_escape_code
				// std::cout << "\033[s";
				std::cout << BG_KRED << *row << RST << std::endl;
			}
			else
				std::cout << *row << std::endl;
		}
		// std::cout << "\033[u"; // а если if (is_selected and selected_row == i++ ) не сработал??????
	};

	void select(int to_row) 
	{
	//печатает ВСЁ - оч медленно 

		//предпологаеться что в начале выбранной
		//std::cout << "\033[K"; //Erase to end of line: \033[K
		// std::cout << rows[selected_row] << "\r";
		
		// std::cout << "\033[\\"<< to_row-selected_row << "A"; //down
		
		selected_row = to_row;
		print();

	};

	void select_upper() { select(selected_row-1); };
	void select_downer() { select(selected_row+1); };

private:

};

int main(int argc, char const *argv[])
{
	// std::string dsdfs = std::string("23d3");
	// std::vector<int> v = {1,2,3};
	// std::vector<std::string> v = {std::string("23"), std::string("dfsdfs"), std::string("Привет!))")};
	std::vector<std::string> v = {"23", "dfsdfs", "drfois!))"};
	Menu menu1(true, 0, v);
	menu1.print();

	menu1.select(2);
	menu1.select(1);
	menu1.select_upper();
	
	return 0;
}