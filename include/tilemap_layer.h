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

#ifndef _TILEMAP_LAYER_H_
#define _TILEMAP_LAYER_H_

// Headers
#include <vector>
#include <boost/container/flat_map.hpp>
#include "memory_management.h"
#include "drawable.h"

/**
 * TilemapLayer class.
 */
class TilemapLayer : public Drawable {
public:
	TilemapLayer(int ilayer);
	~TilemapLayer();

	void DrawTile(BitmapScreen& screen, int x, int y, int row, int col, bool autotile);
	void Draw(int z_order);

	void Update();

	BitmapRef const& GetChipset() const;
	void SetChipset(BitmapRef const& nchipset);
	std::vector<int16_t> const& GetMapData() const;
	void SetMapData(std::vector<int16_t> const& nmap_data);
	std::vector<uint8_t> const& GetPassable() const;
	void SetPassable(std::vector<uint8_t> const& npassable);
	int GetOx() const;
	void SetOx(int nox);
	int GetOy() const;
	void SetOy(int noy);
	int GetWidth() const;
	void SetWidth(int nwidth);
	int GetHeight() const;
	void SetHeight(int nheight);
	int GetAnimationSpeed() const;
	void SetAnimationSpeed(int speed);
	int GetAnimationType() const;
	void SetAnimationType(int type);

	int GetZ() const;
	void Substitute(int old_id, int new_id);

private:
	BitmapRef chipset;
	BitmapScreenRef chipset_screen;
	std::vector<int16_t> map_data;
	std::vector<uint8_t> passable;
	std::vector<uint8_t> substitutions;
	int ox;
	int oy;
	int width;
	int height;
	char animation_frame;
	char animation_step_ab;
	char animation_step_c;
	int animation_speed;
	int animation_type;

	int layer;

	void GenerateAutotileAB(short ID, short animID);
	void GenerateAutotileD(short ID);

	static const int TILES_PER_ROW = 64;

	struct TileXY {
		uint8_t x;
		uint8_t y;
		bool valid;
		TileXY() : valid(false) {}
		TileXY(uint8_t x, uint8_t y) : x(x), y(y), valid(true) {}
	};

	typedef boost::container::flat_map<uint32_t, TileXY> autotiles_map_type;

	BitmapScreenRef GenerateAutotiles(int count, autotiles_map_type const& map);

	TileXY GetCachedAutotileAB(short ID, short animID);
	TileXY GetCachedAutotileD(short ID);

	BitmapScreenRef autotiles_ab_screen;
	BitmapScreenRef autotiles_d_screen;

	int autotiles_ab_next;
	int autotiles_d_next;

	TileXY autotiles_ab[3][3][16][47];
	TileXY autotiles_d[12][50];

	autotiles_map_type autotiles_ab_map;
	autotiles_map_type autotiles_d_map;

	struct TileData {
		short ID;
		int z;
	};
	std::vector<std::vector<TileData> > data_cache;
};

#endif
