#include "gui_crap.h"
#include <gtkmm.h>
#include <iostream>

IHateGTK::IHateGTK()
{
	builder = Gtk::Builder::create_from_file("gui/vse_gui.glade");
};

IHateGTK::~IHateGTK()
{
	
};

void IHateGTK::GetWidgets()
{
	builder->get_widget("fixed", fixed);
	builder->get_widget("notebook", notebook);
	builder->get_widget("window", window);
	builder->get_widget("load_button", load_button);
	builder->get_widget("save_file", save_file);
	builder->get_widget("label_top", label_top);
	builder->get_widget("entry_name", entry_name);
	builder->get_widget("label_kills", label_kills);
	builder->get_widget("label_deaths", label_deaths);
	builder->get_widget("label_crafts", label_crafts);
	builder->get_widget("label_builds", label_builds);
	builder->get_widget("label_start_seed", label_start_seed);
	builder->get_widget("label_max_hp", label_max_hp);
	builder->get_widget("label_current_hp", label_current_hp);
	builder->get_widget("label_stamina", label_stamina);
	builder->get_widget("label_guardian_power", label_guardian_power);
	builder->get_widget("label_gp_desc", label_gp_desc);
	builder->get_widget("image_gp", image_gp);
	builder->get_widget("button_change_gp", button_change_gp);
	builder->get_widget("dialog_change_gp", dialog_change_gp);
	builder->get_widget("button_change_gp_ok", button_change_gp_ok);
	builder->get_widget("button_change_gp_close", button_change_gp_close);
	builder->get_widget("comboboxtext_gp", comboboxtext_gp);
	builder->get_widget("window_saved_popup", window_saved_popup);
	builder->get_widget("button_saved_ok", button_saved_ok);
	builder->get_widget("label_saved_to", label_saved_to);
	builder->get_widget("label_gp_cooldown", label_gp_cooldown);
	builder->get_widget("button_reset_gp_cooldown", button_reset_gp_cooldown);
	builder->get_widget("comboboxtext_hair", comboboxtext_hair);
	builder->get_widget("radiobutton_male", radiobutton_male);
	builder->get_widget("radiobutton_female", radiobutton_female);
	builder->get_widget("comboboxtext_beard", comboboxtext_beard);
	builder->get_widget("checkbutton_female_beard", checkbutton_female_beard);
	builder->get_widget("label_gp_change_desc", label_gp_change_desc);



	button_change_gp_ok->signal_clicked().connect(sigc::mem_fun(*this, &IHateGTK::SetGP));
	button_change_gp->signal_clicked().connect(sigc::mem_fun(*this, &IHateGTK::ChangeGPOpenDialog));
	button_change_gp_close->signal_clicked().connect(sigc::mem_fun(*this, &IHateGTK::ChangeGPClose));
	load_button->signal_clicked().connect(sigc::mem_fun(*this, &IHateGTK::OpenClicked));
	save_file->signal_clicked().connect(sigc::mem_fun(*this, &IHateGTK::Save));
	button_saved_ok->signal_clicked().connect(sigc::mem_fun(*this, &IHateGTK::CloseSavedWindow));
	button_reset_gp_cooldown->signal_clicked().connect(sigc::mem_fun(*this, &IHateGTK::ResetGPCD));
};

void IHateGTK::Fill()
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
			image_gp->set(GPG.g[i].image_file);
			label_guardian_power->set_text(GPG.g[i].gp_name);
			label_gp_desc->set_text(GPG.g[i].description);
			break;
		}
	}

	entry_name->signal_changed().connect(sigc::bind(sigc::mem_fun(*this, &IHateGTK::OnEntryChange), entry_name, &player.data.Name));
	radiobutton_male->signal_toggled().connect(sigc::mem_fun(*this, &IHateGTK::ChangeGender));
	radiobutton_female->signal_toggled().connect(sigc::mem_fun(*this, &IHateGTK::ChangeGender));
	comboboxtext_hair->signal_changed().connect(sigc::mem_fun(*this, &IHateGTK::HairChange));
	comboboxtext_beard->signal_changed().connect(sigc::mem_fun(*this, &IHateGTK::BeardChanege));
	checkbutton_female_beard->signal_clicked().connect(sigc::mem_fun(*this, &IHateGTK::FemaleBeardActive));
	comboboxtext_gp->signal_changed().connect(sigc::mem_fun(*this, &IHateGTK::GPComboChange));

};

void IHateGTK::SetGP()
{
	player.data.GuardianPower = comboboxtext_gp->get_active_id();
	Fill();
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
		Fill();
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
	Fill();
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
