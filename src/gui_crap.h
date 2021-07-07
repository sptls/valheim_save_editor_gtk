#ifndef GUI_CRAP_H
#define GUI_CRAP_H

#include <gtkmm.h>
#include "parser.h"
#include "guardian_powers.h"

enum
{
	MALE = 0,
	FEMALE = 1,
};

class IHateGTK
{
	public:
		std::string path;
		std::map<std::string, std::string> item_images;
		Player player;
		GuardianPowersGui GPG;
		IHateGTK();
		~IHateGTK();
		Glib::RefPtr<Gtk::Builder> builder;
		Gtk::Window* window;
		Gtk::Container* fixed;
		Gtk::Notebook* notebook;
		Gtk::Button* load_button;
		Gtk::Button* save_file;
		Gtk::Entry* entry_name;
		Gtk::Label* label_top;
		Gtk::Label* label_kills;
		Gtk::Label* label_deaths;
		Gtk::Label* label_crafts;
		Gtk::Label* label_builds;
		Gtk::Label* label_start_seed;
		Gtk::Label* label_max_hp;
		Gtk::Label* label_current_hp;
		Gtk::Label* label_stamina;
		Gtk::Label* label_guardian_power;
		Gtk::Label* label_gp_desc;
		Gtk::Image* image_gp;
		Gtk::Button* button_change_gp;
		Gtk::Dialog* dialog_change_gp;
		Gtk::Button* button_change_gp_ok;
		Gtk::Button* button_change_gp_close;
		Gtk::ComboBoxText* comboboxtext_gp;
		Gtk::Window* window_saved_popup;
		Gtk::Button* button_saved_ok;
		Gtk::Label* label_saved_to;
		Gtk::Label* label_gp_cooldown;
		Gtk::Button* button_reset_gp_cooldown;
		Gtk::ComboBoxText* comboboxtext_hair;
		Gtk::RadioButton* radiobutton_male;
		Gtk::RadioButton* radiobutton_female;
		Gtk::ComboBoxText* comboboxtext_beard;
		Gtk::CheckButton* checkbutton_female_beard;
		Gtk::Label* label_gp_change_desc;
		Gtk::Grid* grid_inventory;
		Gtk::Image image_slot_background[32];
		Gtk::Image image_inventory_slot[32];

		void GetItemImages();
		void OpenClicked();
		void Refresh();
		void Save();
		void HandleResponse(int id, Gtk::FileChooserDialog* dialog);
		void ChangeGPClose();
		void ChangeGPOpenDialog();
		void SetGP();
		void OnEntryChange(Gtk::Entry* entry, std::string* data);
		void CloseSavedWindow();
		void ResetGPCD();
		void ChangeGender();
		void HairChange();
		void BeardChanege();
		void FemaleBeardActive();
		void GPComboChange();
};

#endif
