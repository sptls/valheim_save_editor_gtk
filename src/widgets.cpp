#include "gui_crap.h"
#include <iostream>


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
	builder->get_widget("window_item_edit", window_item_edit);
	builder->get_widget("comboboxtext_wie_item_type", comboboxtext_wie_item_type);
	builder->get_widget("comboboxtext_wie_item", comboboxtext_wie_item);
	builder->get_widget("scale_wie_stack", scale_wie_stack);
	builder->get_widget("label_wie_current_stack", label_wie_current_stack);
	builder->get_widget("label_wie_max_stack", label_wie_max_stack);
	builder->get_widget("scale_wie_durability", scale_wie_durability);
	builder->get_widget("label_wie_current_durability", label_wie_current_durability);
	builder->get_widget("label_wie_max_durability", label_wie_max_durability);
	builder->get_widget("spinbutton_wie_quality", spinbutton_wie_quality);
	builder->get_widget("entry_wie_crafter", entry_wie_crafter);
	builder->get_widget("button_wie_ok", button_wie_ok);
	builder->get_widget("button_wie_cancel", button_wie_cancel);
	builder->get_widget("grid_skills", grid_skills);
	builder->get_widget("window_change_skill", window_change_skill);
	builder->get_widget("label_skill_change", label_skill_change);
	builder->get_widget("spinbutton_skill_change", spinbutton_skill_change);
	builder->get_widget("button_skill_change_ok", button_skill_change_ok);
	builder->get_widget("button_skill_change_cancel", button_skill_change_cancel);


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
	button_wie_ok->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &IHateGTK::ItemEditWindowButtons), 1));
	button_wie_cancel->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &IHateGTK::ItemEditWindowButtons), 0));


	for(int i = 0, row = 0; row < 4; row++)
	{
		for(int column = 0; column < 8; column++)
		{
			event_box_inventory[i].signal_button_press_event().connect(sigc::bind(sigc::mem_fun(*this, &IHateGTK::ContextMenu), &event_box_inventory[i]));
			event_box_inventory[i].set_events(Gdk::BUTTON_PRESS_MASK);
			image_slot_background[i].set_visible();
			image_inventory_slot[i].set_visible();
			image_slot_background[i].set_from_resource("/gui/item_slot.png");
			event_box_inventory[i].add(image_inventory_slot[i]);
			event_box_inventory[i].set_visible_window(false);
			event_box_inventory[i].set_above_child();
			event_box_inventory[i].show();
			label_inventory_slot[i].set_size_request(90,20);
			label_inventory_slot[i].set_margin_top(70);
			label_inventory_slot[i].set_text("");
			label_inventory_slot[i].show();
			grid_inventory->attach(image_slot_background[i], column, row);
			grid_inventory->attach(event_box_inventory[i], column, row);
			grid_inventory->attach(label_inventory_slot[i], column, row);
			i++;
		}
	}
//popup menu for inventory
	popup_menu.append(menu_item_edit);
	popup_menu.append(menu_item_delete);
	popup_menu.append(menu_item_add);
	menu_item_edit.set_label("Edit");
	menu_item_delete.set_label("Delete");
	menu_item_add.set_label("Add");
	popup_menu.show_all();
	menu_item_edit.signal_activate().connect(sigc::bind(sigc::mem_fun(*this, &IHateGTK::OnMenuClick), &inventory_slot_pos, 0));
	menu_item_delete.signal_activate().connect(sigc::bind(sigc::mem_fun(*this, &IHateGTK::OnMenuClick), &inventory_slot_pos, 1));


	spinbutton_skill_change->set_range(0.0, 100.0);
	//setup for skills grid
	for(int i = 0, column = 0; column < 3; column++)
	{
		for(int row = 0; row < 5; row++)
		{
			eventbox_skill[i].add(label_skill_name[i]);
			//eventbox_skill[i].set_above_child();
			eventbox_skill[i].show();
			eventbox_skill[i].signal_button_press_event().connect(sigc::bind(sigc::mem_fun(*this, &IHateGTK::ChangeSkillLevel), i));
			grid_skills->attach(eventbox_skill[i],column, row);
			grid_skills->attach(levelbar_skill[i],column, row);
			//label_skill_name[i].set_justify(Gtk::Justification::CENTER);
			label_skill_name[i].show();
			levelbar_skill[i].show();
			levelbar_skill[i].set_max_value(100.0);
			levelbar_skill[i].set_min_value(0.0);
			i++;
		}
	}

	button_skill_change_ok->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &IHateGTK::ChangeSkillButtons), 1));
	button_skill_change_cancel->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &IHateGTK::ChangeSkillButtons), 0));
	spinbutton_skill_change->set_increments(1.0, -1.0);

};


bool IHateGTK::ContextMenu(GdkEventButton* event, Gtk::EventBox* event_box)
{
  if( (event->type == GDK_BUTTON_PRESS) && (event->button == 3) )
  {
  	for(int i = 0; i < 32; i++)
  		if(event_box == &event_box_inventory[i])	
  			inventory_slot_pos = i;

	int x, y;
	y = inventory_slot_pos/8;
	x = inventory_slot_pos%8;

	bool slot_has_item = false;

	for(int i = 0; i < player.data.NumberOfItems; i++)
	{
		if(x == player.data.Inventory[i].posX && y == player.data.Inventory[i].posY)
		{
			menu_item_add.hide();
			menu_item_edit.show();
			menu_item_delete.show();
  			popup_menu.popup_at_widget(event_box, Gdk::GRAVITY_CENTER, Gdk::GRAVITY_CENTER, nullptr);
  			slot_has_item = true;
  			break;
  		}
	}
	if(!slot_has_item)
	{
		menu_item_add.show();
		menu_item_edit.hide();
		menu_item_delete.hide();
  		popup_menu.popup_at_widget(event_box, Gdk::GRAVITY_CENTER, Gdk::GRAVITY_CENTER, nullptr);
	}
  }
  return true;
};

void IHateGTK::OnMenuClick(int* pos, int action_type)
{
	int x, y;
	y = *pos/8;
	x = *pos%8;

	switch(action_type)
	{
		case 0:
			for(int i = 0; i < player.data.NumberOfItems; i++)
			{
				if(x == player.data.Inventory[i].posX && y == player.data.Inventory[i].posY)
				{
					UpdateItemEditWindow(x, y);
					window_item_edit->show();
				}
			}
			break;
		case 1:
			Item* tmp = new Item[player.data.NumberOfItems-1];
			for(int i = 0, j = 0; i < player.data.NumberOfItems; i++)
			{
				if(x == player.data.Inventory[i].posX && y == player.data.Inventory[i].posY)
					continue;
			
				tmp[j++] = player.data.Inventory[i];
			}
			delete[] player.data.Inventory;
			player.data.NumberOfItems--;
			player.data.Inventory = tmp;
			Refresh();
			break;
	}
};

void IHateGTK::UpdateItemEditWindow(int x, int y)
{
	for(int i = 0; i < player.data.NumberOfItems; i++)
	{
		if(x == player.data.Inventory[i].posX && y == player.data.Inventory[i].posY)
		{
			scale_wie_stack->set_range(1, player.data.Inventory[i].MaxStack);
			scale_wie_stack->set_value(player.data.Inventory[i].Stack);
			scale_wie_durability->set_range(1, 1000);
			scale_wie_durability->set_value(player.data.Inventory[i].Durability);
			entry_wie_crafter->set_text(player.data.Inventory[i].Crafter);
			spinbutton_wie_quality->set_range(1, 4);
			spinbutton_wie_quality->set_value(player.data.Inventory[i].Quality);
			spinbutton_wie_quality->set_increments(1, -1);
		}
	}
};

void IHateGTK::ItemEditWindowButtons(int action)
{
	switch(action)
	{
		case 0:
			window_item_edit->hide();
			break;
		case 1:
			window_item_edit->hide();
			break;
	}
};

bool IHateGTK::ChangeSkillLevel(GdkEventButton *event, int slot_id)
{
		spinbutton_skill_change->set_value(player.data.Skills[slot_id].Level);
		std::string tmp = "Set skill level for ";
		tmp += player.data.Skills[slot_id].Name;
		label_skill_change->set_text(tmp);
		skill_slot_nr = slot_id;
		window_change_skill->show();
		return true;
};

void IHateGTK::ChangeSkillButtons(int action)
{
	if(action)
	{
		player.data.Skills[skill_slot_nr].Level = spinbutton_skill_change->get_value();	
		Refresh();
	}
	window_change_skill->hide();
};


IHateGTK::~IHateGTK()
{
	
};
