#pragma once

#include <vector>

namespace Sprocket {

struct RivetTypeProfile
{
	uint32_t model;
	float    spacing;
	float    diameter;
	float    height;
	float    padding;
};

// https://discord.com/channels/788349365466038283/788349366091513888/1433856885429370900
enum RivetFlags
{
	RivetFlags_None     = 0,
	RivetFlags_Manual   = 1 << 0,
	RivetFlags_Auto     = 1 << 1,
	RivetFlags_Selected = 1 << 2,
	RivetFlags_Hovered  = 1 << 3,
	RivetFlags_Delete   = 1 << 4

};

struct RivetNode
{
	uint32_t next; // looping linked list
	uint32_t prev;
	uint32_t face; // face index

	// 1,0,0 is a valid default
	float u = 1.0f;
	float v = 0.0f;
	float w = 0.0f;

	uint32_t faceOffset;
	uint32_t profile = 0; // index into profile array
	RivetFlags flags = RivetFlags_Auto;
};

struct Rivets
{
	std::vector<RivetTypeProfile> profiles = {
		RivetTypeProfile{ 0, 0.1, 0.05, 0.025, 0.4 } // one default profile. Required?
	};

	std::vector<RivetNode> nodes;
};


}