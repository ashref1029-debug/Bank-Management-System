#include<iostream>
#include<iomanip>
#include<fstream>
#include<vector>
#include<string>


using namespace std;
enum class enOpeType {
	ShowClients = 1
	, FindClient = 2
	, AddClient = 3
	, UpdateClient = 4
	, DeleteClient = 5
	, Exist = 6
};
struct stClient
{
	string AccountNumber;
	string PinCode;
	string name;
	string phone;
	float AccountBalance;
	bool MarkeForDelete = false;
};

enOpeType ReadUserChoice()
{

	short choice; cout << "\n\t\t\tWhat do you want ? 1>>>6 ?"; cin >> choice;

	while (choice < 1 || choice >6)
	{
		cout << "\t\t\t-***! This choice not exist ?  "; cin >> choice;
	}

	return (enOpeType)choice;
}
void FillFileWithDummyData(string FileName)
{
	fstream MyFile;

	MyFile.open(FileName, ios::out);
	vector<stClient> vClients; string Line;


	if (MyFile.is_open())
	{
		MyFile << "A101|#|1234|#|Ahmed Ali|#|777123456|#|2500.75\n";
		MyFile << "A102|#|4321|#|Mona Saleh|#|778654321|#|1830.50\n";
		MyFile << "A103|#|5678|#|Khaled Omar|#|733987654|#|920.00\n";
		MyFile << "A104|#|8765|#|Sara Nasser|#|735112233|#|10450.25\n";
		MyFile << "A105|#|9999|#|Yousef Hassan|#|711445566|#|570.10\n";
		MyFile << "A106|#|1111|#|Laila Ahmed|#|734778899|#|2100.00\n";
		MyFile << "A107|#|2222|#|Omar Saeed|#|736990011|#|4899.99\n";
		MyFile << "A108|#|3333|#|Hana Fares|#|739002244|#|120.75\n";
		MyFile << "A109|#|4444|#|Nour Al-Harbi|#|737665544|#|845.00\n";
		MyFile << "A110|#|5555|#|Tariq Zaid|#|738776655|#|30000.00\n";
	}
	MyFile.close();

}
vector<string> SplitString(string st, string delim = " ")
{

	short pos = 0;
	string word = "";
	vector<string> v_st;

	while ((pos = st.find(delim)) != string::npos)
	{

		word = st.substr(0, pos);

		if (word != "")
			v_st.push_back(word);
		st.erase(0, pos + delim.length());

	}

	if (st != "")
		v_st.push_back(st);

	return v_st;
}
stClient ConvertLineToRecord(string Line)
{
	vector<string> vLine = SplitString(Line, "|#|");
	stClient client;

	client.AccountNumber = vLine[0];
	client.PinCode = vLine[1];
	client.name = vLine[2];
	client.phone = vLine[3];
	client.AccountBalance = stof(vLine[4]);

	return client;
}
vector<stClient> LoadClientsFromFile(string FileName)
{
	fstream MyFile;


	MyFile.open(FileName, ios::in);
	vector<stClient> vClients; string Line;


	if (MyFile.is_open())
	{
		while (getline(MyFile, Line))
			vClients.push_back(ConvertLineToRecord(Line));
	}
	MyFile.close();

	return vClients;
}
string ConvertRecordToLine(stClient Client, string sep = "|#|")
{
	string Record = "";

	Record += Client.AccountNumber + sep;
	Record += Client.PinCode + sep;
	Record += Client.name + sep;
	Record += Client.phone + sep;
	Record += to_string(Client.AccountBalance);

	return Record;

}
stClient ReadClientData()
{
	stClient Client;
	cout << "Please enter Client Data: \n\n";
	cout << "Acc. Number  :"; getline(cin >> ws, Client.AccountNumber);

	cout << "PinCode      :"; getline(cin, Client.PinCode);
	cout << "Name         :"; getline(cin, Client.name);
	cout << "Phone        :"; getline(cin, Client.phone);
	cout << "Acc.Balance :"; cin >> Client.AccountBalance;

	return Client;
}

void ShowMainMenueScreen();
void MainMenue()
{
	cout << "\n\n" << endl;
	system("pause");
	ShowMainMenueScreen();
}




void ShowClientsRecord(stClient Client)
{
	cout << "\t\t\t" <<
		"| " << setw(13) << left << Client.AccountNumber <<
		"| " << setw(9) << left << Client.PinCode <<
		"| " << setw(15) << left << Client.name <<
		"| " << setw(9) << left << Client.phone <<
		"| " << setw(9) << left << Client.AccountBalance << endl;
}
void ShowAllClints()
{
	vector<stClient> Clients = LoadClientsFromFile("File.text");

	cout << "\n \t\t\t           Clients List  (" << Clients.size() << ")  Client(s).";

	cout << "\n\t\t\t____________________________________________________________________________\n" << endl;
	cout << "\t\t\t"
		"| " << setw(13) << left << "Acc.Number" <<
		"| " << setw(9) << left << "PinCode" <<
		"| " << setw(15) << left << "FullName" <<
		"| " << setw(9) << left << "Phone" <<
		"| " << setw(9) << left << "Acc.Balance" << endl;
	cout << "\t\t\t____________________________________________________________________________" << endl;


	if (Clients.size() != 0)
	{
		for (stClient& C : Clients)
		{
			ShowClientsRecord(C);
		}
		cout << "\t\t\t____________________________________________________________________________" << endl;
	}
	else
	{
		cout << "\n\t\t\tThers is not any Client in File :-( " << endl;
	}

}
void ClientsListScreen()
{
	system("cls");
	ShowAllClints();
}


void ShowClientData(stClient Client)
{
	cout << "\nClients Data: \n";
	cout << "Acc. Number  :" << Client.AccountNumber << endl;

	cout << "PinCode      :" << Client.PinCode << endl;
	cout << "Name         :" << Client.name << endl;
	cout << "Phone        :" << Client.phone << endl;
	cout << "Acc.Balance :" << Client.AccountBalance << endl;
}
bool FindClientByAccNumber(string AccNumber, vector<stClient> vClients, stClient& Client)
{
	fstream MyFile;


	MyFile.open("File.text", ios::in);


	if (MyFile.is_open())
	{
		for (stClient& C : vClients)
		{
			if (C.AccountNumber == AccNumber)
			{
				Client = C;
				return true;
			}
		}

	}
	MyFile.close();

	return false;
}
void FindClient()
{
	cout << "Enter Account Number :"; string AccNumber; cin >> AccNumber;

	vector<stClient> vClients = LoadClientsFromFile("File.text"); stClient Client;


	if (FindClientByAccNumber(AccNumber, vClients, Client))
	{
		ShowClientData(Client);
	}
	else
		cout << "Client with Account Number [" << AccNumber << "] is not found !" << endl;
}
void FindClientScreen()
{
	system("cls");
	cout << "------------------------------------------" << endl;
	cout << "\t    Find Client Screen\n";
	cout << "------------------------------------------\n" << endl;
	FindClient();
}

bool AddLineToFile(string FileName, string Line)
{
	fstream MyFile;

	MyFile.open(FileName, ios::app);

	if (MyFile.is_open())
	{
		MyFile << Line << endl;

		MyFile.close();
		return true;
	}

}
void AddNewClient()
{
	stClient client = ReadClientData();

	if (AddLineToFile("File.text", ConvertRecordToLine(client)))
		cout << "\nClient Added Successfuly :-)";
}
void AddClientScreen()
{
	system("cls");
	cout << "------------------------------------------" << endl;
	cout << "\t    Add New Client Screen\n";
	cout << "------------------------------------------\n" << endl;

	AddNewClient();
}


stClient ReadUpdatedClientData(string AccNumber)
{
	stClient Client;
	Client.AccountNumber = AccNumber;

	cout << "\nPlease enter Client Data: \n\n";
	cout << "PinCode      :"; getline(cin >> ws, Client.PinCode);
	cout << "Name         :"; getline(cin, Client.name);
	cout << "Phone        :"; getline(cin, Client.phone);
	cout << "Acc.Balance :"; cin >> Client.AccountBalance;

	return Client;
}
void SaveClientsInFile(vector<stClient> vClients)
{
	fstream MyFile;


	MyFile.open("File.text", ios::out);

	if (MyFile.is_open())
	{
		for (stClient& C : vClients)
		{
			if (C.MarkeForDelete != true)
				MyFile << ConvertRecordToLine(C) << endl;
		}

	}
	MyFile.close();

}
void UpdateClientByAccountanumber(vector<stClient>& vClients, string AccNumber)
{
	stClient Client;

	if (FindClientByAccNumber(AccNumber, vClients, Client))
	{

		ShowClientData(Client);

		cout << "\nAre you sure you want to update this client ? "; char Answer = 'Y'; cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			Client = ReadUpdatedClientData(AccNumber);

			for (stClient& C : vClients)
			{
				if (C.AccountNumber == Client.AccountNumber)
				{
					C = Client;
				}

			}
			SaveClientsInFile(vClients);
			cout << "\nClient Updated Sucessfully :-) " << endl;

		}
		else
		{
			return;
		}



	}
	else
	{
		cout << "\nClient with this Account Number not Exist" << endl;
	}


}
void UpdateCliet()
{
	cout << "Enter Account Number :"; string AccNumber; cin >> AccNumber;

	vector<stClient> vClients = LoadClientsFromFile("File.text"); stClient Client;


	UpdateClientByAccountanumber(vClients, AccNumber);
}
void UpdateClietScreen()
{
	system("cls");
	cout << "------------------------------------------" << endl;
	cout << "\t    Update Client Screen\n";
	cout << "------------------------------------------\n" << endl;
	UpdateCliet();

}


void MarkForDelete(vector<stClient>& vClients, string AccNumber)
{
	for (stClient& C : vClients)
	{
		if (C.AccountNumber == AccNumber)
		{
			C.MarkeForDelete = true;
		}
	}
}
void DeletClientFromFile(vector<stClient>& vClients)
{
	cout << "Enter Account Number :"; string AccNumber; cin >> AccNumber;
	stClient Client;

	if (FindClientByAccNumber(AccNumber, vClients, Client))
	{
		ShowClientData(Client);
		cout << "Are you sure you want delete this Accont ? "; char Answer = 'Y'; cin >> Answer;

		if (Answer == 'Y' || Answer == 'y')
		{
			MarkForDelete(vClients, AccNumber);
			SaveClientsInFile(vClients);

			vector<stClient> vClients = LoadClientsFromFile("File.text");
			cout << "\nClient Deleted Sucessfully :-) " << endl;
		}
		else
		{
			cout << "\nOperation Failed  " << endl;
		}




	}
	else
	{
		cout << "\nClient with this Account Number not Exist" << endl;

	}


}
void DeletClient()
{
	vector<stClient> vClients = LoadClientsFromFile("File.text"); stClient Client;

	DeletClientFromFile(vClients);
}
void DeletClientScreen()
{
	system("cls");
	cout << "------------------------------------------" << endl;
	cout << "\t    Delete Client Screen\n";
	cout << "------------------------------------------\n" << endl;
	DeletClient();
}

void PerformOperation(enOpeType ope)
{
	switch (ope)
	{
	case enOpeType::ShowClients:ClientsListScreen(); MainMenue(); break;
	case enOpeType::FindClient: FindClientScreen(); MainMenue(); break;
	case enOpeType::AddClient: AddClientScreen(); MainMenue(); break;
	case enOpeType::UpdateClient:UpdateClietScreen(); MainMenue(); break;
	case enOpeType::DeleteClient:DeletClientScreen(); MainMenue(); break;
	default: break;
	}
}
void ShowMainMenueScreen()
{
	system("cls");
	cout << "\t\t\t " << "==========================================" << endl;
	cout << "\t\t\t " << "\t    Main Menue Screen\n";
	cout << "\t\t\t " << "==========================================" << endl;
	cout << "\t\t\t " << " [1] Show Client List" << endl;
	cout << "\t\t\t " << " [2] Fine Client" << endl;
	cout << "\t\t\t " << " [3] Add New Client " << endl;
	cout << "\t\t\t " << " [4] Update Client ifo" << endl;
	cout << "\t\t\t " << " [5] Delete Client" << endl;
	cout << "\t\t\t " << " [6] Exist" << endl;

	PerformOperation(ReadUserChoice());
}

int main()
{
	ShowMainMenueScreen();
}
