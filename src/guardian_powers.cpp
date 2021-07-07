#include "guardian_powers.h"

GuardianPowersGui::GuardianPowersGui()
{
	g[0].gp_name = "None";
	g[0].gp_var_name = "";
	g[0].image_file = "/gui/none.png";
	g[0].description = "";

	g[1].gp_name = "Eikthyr";
	g[1].gp_var_name = "GP_Eikthyr";
	g[1].image_file = "/gui/eikthyr.png";
	g[1].description = "Your ability to run and jump is improved.\nJump stamina usage: -60%\nRun stamina usage: -60%\n";

	g[2].gp_name = "The Elder";
	g[2].gp_var_name = "GP_The_Elder";
	g[2].image_file = "/gui/the_elder.png";
	g[2].description = "Faster wood cutting.";

	g[3].gp_name = "Bonemass";
	g[3].gp_var_name = "GP_Bonemass";
	g[3].image_file = "/gui/bonemass.png";
	g[3].description = "Resistance VS physical damage.\nDamage modifier: Resistant VS Blunt\nDamage modifier: Resistant VS Slash\nDamage modifier: Resistant VS Pierce";
	
	g[4].gp_name = "Moder";
	g[4].gp_var_name = "GP_Moder";
	g[4].image_file = "/gui/moder.png";
	g[4].description = "Always tailwind when sailing.";
	
	g[5].gp_name = "Yagluth";
	g[5].gp_var_name = "GP_Yagluth";
	g[5].image_file = "/gui/yagluth.png";
	g[5].description = "Resistance VS magic damage and lightning damage.\nDamage modifier: Resistant VS Fire\nDamage modifier: Resistant VS Frost\nDamage modifier: Resistant VS Lightning";
};

GuardianPowersGui::~GuardianPowersGui()
{
	
};
