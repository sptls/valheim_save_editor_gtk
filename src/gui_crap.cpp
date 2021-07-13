#include "gui_crap.h"
#include <gtkmm.h>
#include <iostream>

void IHateGTK::Refresh()
{
	entry_name->set_sensitive();
	button_change_gp->set_sensitive();
	save_file->set_sensitive();
	radiobutton_male->set_sensitive();
	radiobutton_female->set_sensitive();
	comboboxtext_hair->set_sensitive();
	button_reset_gp_cooldown->set_sensitive();
	checkbutton_female_beard->set_sensitive();
	

	entry_name->set_text(player.data.Name);	
	label_top->set_text(player.data.Name);
	label_kills->set_text(std::to_string(player.data.Kills));
	label_deaths->set_text(std::to_string(player.data.Deaths));
	label_crafts->set_text(std::to_string(player.data.Crafts));
	label_builds->set_text(std::to_string(player.data.Builds));
	label_start_seed->set_text(player.data.StartSeed);
	label_max_hp->set_text(std::to_string(player.data.MaxHP));
	label_current_hp->set_text(std::to_string(player.data.CurrentHP));
	label_stamina->set_text(std::to_string(player.data.Stamina));
	label_gp_cooldown->set_text(std::to_string(player.data.GuardianCooldown));

	if(player.data.Hair == "")
		player.data.Hair = "HairNone";
	
	comboboxtext_hair->set_active_id(player.data.Hair);
	comboboxtext_beard->set_active_id(player.data.Beard);

	if(player.data.Gender)
		radiobutton_female->set_active();
	else
		radiobutton_male->set_active();

	if(checkbutton_female_beard->get_active() || !(player.data.Gender))
	{
		comboboxtext_beard->set_sensitive();
	}

	for(int i = 0; i < 6; i++)
	{
		if(GPG.g[i].gp_var_name ==  player.data.GuardianPower)
		{
			image_gp->set_from_resource(GPG.g[i].image_file);
			label_guardian_power->set_text(GPG.g[i].gp_name);
			label_gp_desc->set_text(GPG.g[i].description);
			break;
		}
	}

	//fill image source map
	GetItemImages();
	//clear inventory slots
	for(int i = 0; i < 32; i++)
	{
		image_inventory_slot[i].clear();
		image_slot_background[i].set_from_resource("/gui/item_slot.png");
		label_inventory_slot[i].set_text("");
	}
	
	//refresh inventory page
	for(int i = 0; i < player.data.NumberOfItems; i++)
	{
		if(item_images.contains(player.data.Inventory[i].Name))
		{
			player.data.Inventory[i].ItemImage = item_images[player.data.Inventory[i].Name];
			int pos = 0;
			pos += player.data.Inventory[i].posY * 8;
			pos += player.data.Inventory[i].posX;
			image_inventory_slot[pos].set_from_resource(player.data.Inventory[i].ItemImage);
			if(player.data.Inventory[i].BoolEquipped)
				image_slot_background[pos].set_from_resource("/gui/item_slot_equipped.png");
			if(player.data.Inventory[i].MaxStack != 1)
				label_inventory_slot[pos].set_text(std::to_string(player.data.Inventory[i].Stack) + "/" + std::to_string(player.data.Inventory[i].MaxStack));
		}
	}



	//skills tab
	for(int i = 0; i < 15; i++)
	{
		if(i <= player.data.NoSkills)
		{
			std::string tmp = player.data.Skills[i].Name;
			tmp += "\n";
			tmp += std::to_string((int)player.data.Skills[i].Level);
			tmp += "/100";

			label_skill_name[i].set_text(tmp);
			label_skill_name[i].show();
			levelbar_skill[i].set_value(player.data.Skills[i].Level);
			levelbar_skill[i].show();
		}
	}
	

};

void IHateGTK::SetGP()
{
	player.data.GuardianPower = comboboxtext_gp->get_active_id();
	Refresh();
	dialog_change_gp->hide();
	save_file->set_sensitive();
};

void IHateGTK::OnEntryChange(Gtk::Entry* entry, std::string* data)
{
	*data = entry->get_text();
	save_file->set_sensitive();
}

void IHateGTK::ChangeGPClose()
{
	dialog_change_gp->hide();	
};

void IHateGTK::ChangeGPOpenDialog()
{
	dialog_change_gp->show();	
	comboboxtext_gp->set_active_id(player.data.GuardianPower);
	for(int i = 0; i < 6; i++)
	{
		if(player.data.GuardianPower == GPG.g[i].gp_var_name)
		{
			label_gp_change_desc->set_text(GPG.g[i].description);
		}
	}
};

void IHateGTK::OpenClicked()
{
	auto dialog = new Gtk::FileChooserDialog("Please choose a file");
	auto file_filter = Gtk::FileFilter::create();
	file_filter->add_pattern("*.fch");
	file_filter->set_name("Valheim save file");
	dialog->add_filter(file_filter);
	dialog->set_modal(true);
	dialog->signal_response().connect(sigc::bind(sigc::mem_fun(*this, &IHateGTK::HandleResponse), dialog));
	dialog->add_button("_Open", 1);
	dialog->add_button("_Close", 2);
	dialog->show();
};

void IHateGTK::Save()
{
	player.UpdateDataLength();
	player.SaveFile(path.c_str());	
	save_file->set_sensitive(false);
	label_saved_to->set_text(path);
	window_saved_popup->show();
}

void IHateGTK::HandleResponse(int id, Gtk::FileChooserDialog* dialog)
{
	if(id == 1)
	{
		path = dialog->get_file()->get_path();
		std::cout << "File: " << path << std::endl;
		player.LoadSaveFile(path.c_str());
		Refresh();
	}
	dialog->hide();
};

void IHateGTK::CloseSavedWindow()
{
	window_saved_popup->hide();	
};

void IHateGTK::ResetGPCD()
{
	label_gp_cooldown->set_text("0.0");
	player.data.GuardianCooldown = atof(label_gp_cooldown->get_text().c_str());
	Refresh();
};

void IHateGTK::ChangeGender()
{
	if(radiobutton_female->get_active())
	{
		player.data.Gender = FEMALE;
		if(checkbutton_female_beard->get_active())
			comboboxtext_beard->set_sensitive();
		else
			comboboxtext_beard->set_sensitive(false);
	}
	else
	{
		player.data.Gender = MALE;
		comboboxtext_beard->set_sensitive();
	}
};

void IHateGTK::HairChange()
{
	player.data.Hair = comboboxtext_hair->get_active_id();
	save_file->set_sensitive();
};

void IHateGTK::BeardChanege()
{
	player.data.Beard = comboboxtext_beard->get_active_id();	
	save_file->set_sensitive();
};

void IHateGTK::FemaleBeardActive()
{
	if(player.data.Gender == FEMALE)
	{
		if(checkbutton_female_beard->get_active())	
			comboboxtext_beard->set_sensitive();
		else
		{
			player.data.Beard = "BeardNone";	
			comboboxtext_beard->set_sensitive(false);
		}
	}
	else
		comboboxtext_beard->set_sensitive();
	save_file->set_sensitive();
};

void IHateGTK::GPComboChange()
{
	for(int i = 0; i < 6; i++)
	{
		if(comboboxtext_gp->get_active_id() == GPG.g[i].gp_var_name)
		{
			label_gp_change_desc->set_text(GPG.g[i].description);
		}
	}
};
