#include "wx_password_list.h"

LoggerPtr password_list_log(Logger::getLogger("wx_password_list"));

//(*InternalHeaders(wx_password_list)
#include <wx/string.h>
#include <wx/intl.h>
//*)

//(*IdInit(wx_password_list)
const long wx_password_list::ID_LST_PASSWORD_LIST = wxNewId();
const long wx_password_list::ID_BTN_REFRESH_PWD_LIST = wxNewId();
const long wx_password_list::ID_BTN_ADD_PWD_ENTRY = wxNewId();
const long wx_password_list::ID_BTN_EDIT_PWD_ENTRY = wxNewId();
const long wx_password_list::ID_BTN_PWD_ENTRY_DELETE = wxNewId();
//*)

BEGIN_EVENT_TABLE(wx_password_list,wxDialog)
	//(*EventTable(wx_password_list)
	//*)
END_EVENT_TABLE()

wx_password_list::wx_password_list(wxWindow* parent,wxWindowID id)
{
	//(*Initialize(wx_password_list)
	Create(parent, wxID_ANY, _("Password list"), wxDefaultPosition, wxDefaultSize, wxSTAY_ON_TOP|wxDEFAULT_DIALOG_STYLE|wxSYSTEM_MENU, _T("wxID_ANY"));
	SetClientSize(wxSize(460,292));
	SetMinSize(wxSize(400,400));
	pwlMainBoxSizer = new wxBoxSizer(wxVERTICAL);
	lstPasswordList = new wxListBox(this, ID_LST_PASSWORD_LIST, wxDefaultPosition, wxSize(450,199), 0, 0, 0, wxDefaultValidator, _T("ID_LST_PASSWORD_LIST"));
	lstPasswordList->Append(_("1 password_1 username:x password:y target:whatever"));
	lstPasswordList->Append(_("2 password_2 username:y password:x target:other_whatever"));
	pwlMainBoxSizer->Add(lstPasswordList, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	pwlListButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	btnRefreshPasswordList = new wxButton(this, ID_BTN_REFRESH_PWD_LIST, _("Refresh"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BTN_REFRESH_PWD_LIST"));
	pwlListButtonSizer->Add(btnRefreshPasswordList, 1, wxALL|wxALIGN_LEFT|wxALIGN_BOTTOM, 5);
	btnAddPasswordEntry = new wxButton(this, ID_BTN_ADD_PWD_ENTRY, _("Add"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BTN_ADD_PWD_ENTRY"));
	pwlListButtonSizer->Add(btnAddPasswordEntry, 1, wxALL|wxALIGN_LEFT|wxALIGN_BOTTOM, 5);
	btnEditPasswordEntry = new wxButton(this, ID_BTN_EDIT_PWD_ENTRY, _("Edit"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BTN_EDIT_PWD_ENTRY"));
	pwlListButtonSizer->Add(btnEditPasswordEntry, 1, wxALL|wxALIGN_LEFT|wxALIGN_BOTTOM, 5);
	btnDeletePasswordEntry = new wxButton(this, ID_BTN_PWD_ENTRY_DELETE, _("Delete"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BTN_PWD_ENTRY_DELETE"));
	pwlListButtonSizer->Add(btnDeletePasswordEntry, 1, wxALL|wxALIGN_LEFT|wxALIGN_BOTTOM, 5);
	pwlMainBoxSizer->Add(pwlListButtonSizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_BOTTOM, 5);
	SetSizer(pwlMainBoxSizer);
	SetSizer(pwlMainBoxSizer);
	Layout();
	Center();

	Connect(ID_BTN_REFRESH_PWD_LIST,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wx_password_list::OnbtnRefreshPasswordListClick);
	Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&wx_password_list::OnClose);
	//*)
    utils = new utility();
    string configuration_path = utils->get_config_path();

    // Load XML configuration file using DOMConfigurator
    DOMConfigurator::configure(configuration_path + "Log4cxxConfig.xml");

    LOG4CXX_INFO(password_list_log, "-- program start --");
    LOG4CXX_INFO(password_list_log, "password storage project - fat client component");
    LOG4CXX_INFO(password_list_log, "-------------------------------------------");
    LOG4CXX_INFO(password_list_log, "wxWidgets fat client where target server is deployed at VPS which is online all the time");
    LOG4CXX_INFO(password_list_log, "client needs to show stored passwords and enable CRUD of password information");
    LOG4CXX_INFO(password_list_log, "");

    LOG4CXX_INFO(password_list_log, "log4cxx configuration successfully parsed");

    comm = new wx_password_communicator();
    comm->set_server_ipv4_address(utils->get_server_ip());
}

wx_password_list::~wx_password_list()
{
	//(*Destroy(wx_password_list)
	//*)
}


void wx_password_list::OnClose(wxCloseEvent& event)
{
    this->EndModal(wxOK);
}

void wx_password_list::OnbtnRefreshPasswordListClick(wxCommandEvent& event)
{
    comm->init_comm();
}
