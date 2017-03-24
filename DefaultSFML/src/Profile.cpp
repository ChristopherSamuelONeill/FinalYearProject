#include "Profile.h"

bool Profile::bInstanceFlag = false;
Profile* Profile::profile = nullptr;


Profile * Profile::getInstance()
{
	if (!bInstanceFlag) // return the singleton window class
	{
		profile = new Profile();
		bInstanceFlag = true;
		return profile;
	}
	else
	{
		
		return profile;
	}
}


Profile::Profile(string location)
{
	fstream file;
	string lineData;
	string temp;

	file.open("Assets/profiles/" +location);
	if (file.is_open())
	{
		while (getline(file, lineData))
		{
			istringstream settings(lineData);
			settings.str(lineData);
			settings >> temp;
			if (temp == "c")
			{
				//ingore
			}
			else if (temp == "s")
			{
				settings >> m_sfResolution.x >> m_sfResolution.y >> m_bFullscreen >> m_bTextures >> m_iGameAudioVolume >> m_iInterfaceAudioVolume >> m_iMusicAudioVolume;
			}
			else if (temp == "d")
			{
				settings >> m_sProfileName >> m_uilevel >> m_fXP >> m_uiPedestriansTotal >> m_uiCarsTotal >> m_uiCrashesTotal >> m_uiFatalitiesTotal >> m_fFlowRate;
			}
		}
		m_sProfile = m_sProfileName;
	}
	else
	{
		cout << "Couldnt Open file ... Assets/profiles/"<< location << endl;
	}

	file.close();
}

Profile::Profile(string nameOfPlayer, bool create)
{
	//create not used

	//load profile list
	vector<string> profileNames;
	fstream file;
	ofstream ofile;
	
	ofstream onewFile;

	string tempProfile;
	string lineData;

	file.open("Assets/profiles/profileList.txt");
	

	if (file.is_open())
	{
		while (getline(file, lineData))
		{
			istringstream iss(lineData);
			iss.str(lineData);
			iss >> tempProfile;
			profileNames.push_back(tempProfile);
		}
	
	}
	
	file.close();

	ofile.open("Assets/profiles/profileList.txt");
	// add new player to list
	profileNames.push_back(nameOfPlayer + ".txt");

	for (int i = 0; i < profileNames.size(); i++)
	{
		ofile << profileNames[i] << endl;
	}
	
	//create name .txt file

	onewFile.open("Assets/profiles/" + nameOfPlayer + ".txt");
	if (onewFile.is_open())
	{
		
		onewFile << "c " << "x res " << "y res " << "full " << "texures " << "gme vl " << "ivl " << "mvl " << endl;
		onewFile << "s " << "1280 " << "720 " << "0 " << "1 " << "10 " << "5 " << "5 " << endl;
		onewFile << "c " << "name " << "level " << "xp " << "tPed " << "tCar " << "cTot " << "fTot " << "fRat " << endl;
		onewFile << "d " << nameOfPlayer << " " << 0 << " " << 0 << " " << 0 << " " << 0 << " " << 0 << " " << 0 << " " << 0 << " " << endl;
	}
	onewFile.close();

}

Profile::~Profile()
{
}

void Profile::saveProfile()
{
	ofstream ofile;
	ofile.open("Assets/profiles/" +m_sProfileName +".txt");
	if (ofile.is_open())
	{

		ofile << "c " << "x res " << "y res " << "full " << "texures " << "gme vl " << "ivl " << "mvl " << endl;
		ofile << "s " << m_sfResolution.x << " " << m_sfResolution.y << " " << m_bFullscreen << " " << m_bTextures << " " << m_iGameAudioVolume << " " << m_iMusicAudioVolume << " " << m_iInterfaceAudioVolume << endl;
		ofile << "c " << "name " << "level " << "xp " << "tPed " << "tCar " << "cTot " << "fTot " << "fRat " << endl;
		ofile << "d " << m_sProfileName << " " << m_uilevel << " " << m_fXP << " " << m_uiPedestriansTotal << " " << m_uiCarsTotal<< " " << m_uiCrashesTotal << " " << m_uiFatalitiesTotal << " " << m_fFlowRate<< " " << endl;
	}
	ofile.close();
}

bool Profile::loadProfile(string name)
{
	fstream file;
	string lineData;
	string temp;

	file.open("Assets/profiles/" + name +".txt");
	if (file.is_open())
	{
		while (getline(file, lineData))
		{
			istringstream settings(lineData);
			settings.str(lineData);
			settings >> temp;
			if (temp == "c")
			{
				//ingore
			}
			else if (temp == "s")
			{
				settings >> m_sfResolution.x >> m_sfResolution.y >> m_bFullscreen >> m_bTextures >> m_iGameAudioVolume >> m_iInterfaceAudioVolume >> m_iMusicAudioVolume;
			}
			else if (temp == "d")
			{
				settings >> m_sProfileName >> m_uilevel >> m_fXP >> m_uiPedestriansTotal >> m_uiCarsTotal >> m_uiCrashesTotal >> m_uiFatalitiesTotal >> m_fFlowRate;
			}
		}
	}
	else
	{
		cout << "Couldnt Open file ... Assets/profiles/" << name + ".txt" << endl;
		return false;
	}

	return true;

	file.close();
}
