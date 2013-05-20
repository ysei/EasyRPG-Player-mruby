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

// Headers
#include <string>
#include <iomanip>
#include <sstream>
#include "window_savefile.h"
#include "game_system.h"
#include "input.h"
#include "font.h"
#include "bitmap.h"

Window_SaveFile::Window_SaveFile(int ix, int iy, int iwidth, int iheight) :
	Window_Base(ix, iy, iwidth, iheight),
	index(0), hero_hp(0), hero_level(0), corrupted(false) {

	SetContents(Bitmap::Create(width - 8, height - 16));
	SetZ(9999);

	Refresh();
	UpdateCursorRect();
}

void Window_SaveFile::UpdateCursorRect() {
	SetCursorRect(GetActive() ? Rect(0, 0, 48, 16) : Rect());
}

void Window_SaveFile::SetIndex(int id) {
	index = id;
}

void Window_SaveFile::SetParty(const std::vector<std::pair<int, std::string> >& actors,
	std::string name, int hp, int level) {
	party = actors;
	hero_name = name;
	hero_hp = hp;
	hero_level = level;
}

void Window_SaveFile::SetCorrupted(bool corrupted) {
	this->corrupted = corrupted;
}

void Window_SaveFile::Refresh() {
	contents->clear();

	std::ostringstream out;
	out << Data::terms.file << std::setw(2) << std::setfill(' ') << index + 1;
	contents->draw_text(4, 2, out.str(), Font::ColorDefault);

	if (corrupted) {
		contents->draw_text(4, 16 + 2, "Savegame corrupted", Font::ColorKnockout);
		return;
	}

	if (party.empty())
		return;

	contents->draw_text(8, 16 + 2, hero_name, Font::ColorDefault);

	contents->draw_text(8, 32 + 2, Data::terms.lvl_short, 1);

	int lx = Font::Default()->GetSize(Data::terms.lvl_short).width;
	out.str("");
	out << std::setw(2) << std::setfill(' ') << hero_level;
	contents->draw_text(8 + lx, 32 + 2, out.str(), Font::ColorDefault);

	contents->draw_text(42, 32 + 2, Data::terms.hp_short, 1);

	int hx = Font::Default()->GetSize(Data::terms.hp_short).width;
	out.str("");
	out << hero_hp;
	contents->draw_text(42 + hx, 32 + 2, out.str(), Font::ColorDefault);

	for (int i = 0; i < 4 && (size_t) i < party.size(); i++) {
		DrawFace(party[i].second, party[i].first, 88 + i * 56, 0);
	}
}

void Window_SaveFile::Update() {
	Window_Base::Update();
	UpdateCursorRect();
}
