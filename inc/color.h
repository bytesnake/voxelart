#ifndef COLOR_H
#define COLOR_H

#include "byteorder.h"

/*
 * Definiert Alle Farben, die im Spiel vorkommen
 */
namespace cubiverse {
	struct color {
		static uint8_t get(int id, int channel) {
			uint8_t colors[2][3] = {{100,100,100}, {200,200,200}};
			return colors[id][channel];
		}
	};
}
	
#endif
