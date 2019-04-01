#pragma once

#include "../api.hh"
#include "image.hh"

struct UMBRA_API Filter
{
	virtual ~Filter() = default;
	virtual void run(SP<Image> image) = 0;
};
