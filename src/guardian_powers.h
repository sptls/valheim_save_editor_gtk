#ifndef GUARDIAN_POWERS_H
#define GUARDIAN_POWERS_H
#include <string>

struct gp
{
	std::string gp_name;
	std::string gp_var_name;
	std::string image_file;
	std::string description;
};

class GuardianPowersGui
{
	public:
		gp g[6];
		GuardianPowersGui();
		~GuardianPowersGui();
};

#endif
