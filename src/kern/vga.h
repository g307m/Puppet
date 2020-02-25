#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

namespace VGA
{
	static const size_t WIDTH  = 80;
	static const size_t HEIGHT = 25;

	class Terminal
	{
		public:
			size_t    row    = 0;
			size_t    column = 0;
			uint8_t   color  = 7 | 0 << 4;
			uint16_t* buffer = (uint16_t*) 0xB8000;
	}
}
