#include <cmath>
#include "lweparams.h"

using namespace std;

LweParams::LweParams(int32_t n, double alpha_min, double alpha_max, double alpha_lvl21):
		n(n),
		alpha_min(alpha_min),
		alpha_max(alpha_max),
		alpha_lvl21(alpha_lvl21) {}

LweParams::~LweParams() {}
