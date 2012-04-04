#ifndef GUI_H
#define GUI_H

#include "bsb_engine/bsb_game.h"
#include <boost/signal.hpp> 
#include <boost/bind.hpp>
#include <vector>

namespace cubiverse {
	class GUI {
		public:
			typedef boost::shared_ptr<cubiverse::GUI> pointer_t;

			boost::signal<void ()> draw;
			GUI(int width, int height);
			void changeMenu(string menu);
			string checkButton(int p_x, int p_y);

		private:
			string menu;

			void drawMenu();
			void drawMap();
			void drawBottom();

			std::vector<int> buttonPosition;
			std::vector<string> buttonName;
			void drawButton();
			//void checkButton(int x, int y);
			void addButton(string name, int x, int y, int width, int height);
				
			int width, height;
			
			Bsb_Font* std_font;
		public:	
			string getMenu() { return menu; };
			void drawFPS(int fps);
	};
};
 
#endif
