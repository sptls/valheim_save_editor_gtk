#include "gui_crap.h"


IHateGTK::IHateGTK()
{
	builder = Gtk::Builder::create_from_resource("/gui/vse_gui.glade");

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
	builder->get_widget("grid_inventory", grid_inventory);



	button_change_gp_ok->signal_clicked().connect(sigc::mem_fun(*this, &IHateGTK::SetGP));
	button_change_gp->signal_clicked().connect(sigc::mem_fun(*this, &IHateGTK::ChangeGPOpenDialog));
	button_change_gp_close->signal_clicked().connect(sigc::mem_fun(*this, &IHateGTK::ChangeGPClose));
	load_button->signal_clicked().connect(sigc::mem_fun(*this, &IHateGTK::OpenClicked));
	save_file->signal_clicked().connect(sigc::mem_fun(*this, &IHateGTK::Save));
	button_saved_ok->signal_clicked().connect(sigc::mem_fun(*this, &IHateGTK::CloseSavedWindow));
	button_reset_gp_cooldown->signal_clicked().connect(sigc::mem_fun(*this, &IHateGTK::ResetGPCD));
	entry_name->signal_changed().connect(sigc::bind(sigc::mem_fun(*this, &IHateGTK::OnEntryChange), entry_name, &player.data.Name));
	radiobutton_male->signal_toggled().connect(sigc::mem_fun(*this, &IHateGTK::ChangeGender));
	radiobutton_female->signal_toggled().connect(sigc::mem_fun(*this, &IHateGTK::ChangeGender));
	comboboxtext_hair->signal_changed().connect(sigc::mem_fun(*this, &IHateGTK::HairChange));
	comboboxtext_beard->signal_changed().connect(sigc::mem_fun(*this, &IHateGTK::BeardChanege));
	checkbutton_female_beard->signal_clicked().connect(sigc::mem_fun(*this, &IHateGTK::FemaleBeardActive));
	comboboxtext_gp->signal_changed().connect(sigc::mem_fun(*this, &IHateGTK::GPComboChange));



	for(int i = 0, row = 0; row < 4; row++)
	{
		for(int column = 0; column < 8; column++)
		{
			image_slot_background[i].set_visible();
			image_inventory_slot[i].set_visible();
			image_slot_background[i].set_from_resource("/gui/item_slot.png");
			grid_inventory->attach(image_slot_background[i], column, row);
			grid_inventory->attach(image_inventory_slot[i], column, row);
			i++;
		}
	}
};

IHateGTK::~IHateGTK()
{
	
};
