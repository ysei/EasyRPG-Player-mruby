/*
 * This file is part of EasyRPG Player.
 *
 * EasyRPG Player is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * EasyRPG Player is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with EasyRPG Player. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _MEMORY_MANAGEMENT_H_
#define _MEMORY_MANAGEMENT_H_

// Headers
#include <cstdint>

#ifdef BOOST_NO_CWCHAR
typedef uint32_t wchar_t;
#endif

#include <memory>

class Bitmap;
class BitmapScreen;
class Font;

typedef std::shared_ptr<Bitmap> BitmapRef;
typedef std::shared_ptr<BitmapScreen> BitmapScreenRef;
typedef std::shared_ptr<Font> FontRef;

#endif // _MEMORY_MANAGEMENT_H_
