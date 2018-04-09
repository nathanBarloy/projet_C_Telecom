#include <JSONAll.hpp>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;
class Film : public JSONPOCO
{
private:
	void init()
	{
		set("Id", 0);
		set("Title", "");
		set("Description", "");
		set("Actors", new JSONArray());
		set("Genres", new JSONArray());
		set("Duration", 0);
		set("Year", 0);
		set("Director", "");
		set("Type", "Film");
	}
public:
	Film()
	{
		init();
	}
	Film(int id, string title, string description, int duration)
	{
		init();
		setId(id);
		setTitle(title);
		setDescription(description);
		setDuration(duration);
	}
	void setTitle(string str)
	{
		set("Title", str);
	}
	string getTitle()
	{
		return stringValue("Title");
	}
	void setDescription(string str)
	{
		set("Description", str);
	}
	string getDescription()
	{
		return stringValue("Description");
	}
	void setDuration(int duration)
	{
		set("Duration", duration);
	}
	int getDuration()
	{
		return intValue("Duration");
	}
	JSONArray* actors()
	{
		return dynamic_cast<JSONArray*>(get("Actors"));
	}
	JSONArray* genres()
	{
		return dynamic_cast<JSONArray*>(get("Genres"));
	}
	void setId(int id)
	{
		set("Id", id);
	}
	int getId()
	{
		return intValue("Id");
	}
	void setYear(int y)
	{
		set("Year", y);
	}
	int getYear()
	{
		return intValue("Year");
	}
	void setDirector(string d)
	{
		set("Director", d);
	}
	string getDirector()
	{
		return stringValue("Director");
	}
	void setType(string t)
	{
		set("Type", t);
	}
	string getType()
	{
		return stringValue("Type");
	}
};
int main()
{
	JSONArray *arr = new JSONArray();
	ifstream i("BDCSD.txt", ifstream::in);
	if(i.is_open())
	{
		Film *f = 0;
		string line;
		int mode = 0;
		while(getline(i, line))
		{
			if(line != "")
			{
				if(mode == 0)
				{
					if(f == 0)
					{
						f = new Film();
					}
					string sid;
					int c = 0;
					while(c < line.size() && line[c] != '.')
					{
						sid += line[c];
						++c;
					}
					f->setId(atoi(sid.c_str()));
					c += 2;
					string title;
					while(c < line.size())
					{
						if(line[c] == ' ' && c < line.size() - 1 && line[c + 1] != '(')
						{
							title += ' ';
						}
						else if(line[c] != '(')
						{
							title += line[c];
						}
						else
						{
							if(line[c] == ' ')
							{
								c += 2;
							}
							else
							{
								++c;
							}
							break;
						}
						++c;
					}
					f->setTitle(title);
					if(c < line.size())
					{
						string year;
						while(c < line.size() && line[c] != ' ')
						{
							year += line[c];
							++c;
						}
						f->setYear(atoi(year.c_str()));
						++c;
						string type;
						while(c < line.size() && line[c] != ')')
						{
							type += line[c];
							++c;
						}
						f->setType(type);
					}
					mode = 1;
				}
				else if(mode == 2)
				{
					f->setDescription(line);
					mode = 3;
				}
				else if(mode == 3)
				{
					int c = 0;
					string delimiter;
					while(c < line.size() && line[c] != ' ' && line[c] != ':')
					{
						delimiter += line[c];
						++c;
					}
					if(delimiter == "Director")
					{
						++c;
						string director;
						while(c < line.size())
						{
							director += line[c];
							++c;
						}
						f->setDirector(director);
					}
					else if(delimiter == "With")
					{
						c += 3;
						string actor;
						while(c < line.size())
						{
							if(line[c] == ',')
							{
								f->actors()->add(actor);
								actor.clear();
								++c;
							}
							else
							{
								actor += line[c];
							}
							++c;
						}
						if(actor != "")
						{
							f->actors()->add(actor);
						}
						mode = 4;
					}
					else
					{
						mode = 4;
					}
				}
				else if(mode == 4)
				{
					string genre;
					int c = 0;
					while(c < line.size())
					{
						if(line[c] >= '0' && line[c] <= '9')
						{
							break;
						}
						if(line[c] == ' ')
						{
							f->genres()->add(genre);
							genre.clear();
							if(c < line.size() - 1 && line[c + 1] != '|')
							{
								++c;
							}
							else
							{
								c += 3;
							}
						}
						else if(line[c] == '|')
						{
							f->genres()->add(genre);
							genre.clear();
							c += 2;
						}
						++c;
					}
					if(genre != "")
					{
						f->genres()->add(genre);
					}
					string mins;
					while(c < line.size() && line[c] >= '0' && line[c] <= '9')
					{
						mins += line[c];
						++c;
					}
					f->setDuration(atoi(mins.c_str()));
				}
				else
				{
					mode = 0;
				}


			}
			else
			{
				if(mode == 1)
				{
					mode = 2;
				}
				else
				{
					mode = 0;
				}
			}
			if(mode == 0)
			{
				arr->add(f);
				f = 0;
			}
		}
		if(f != 0)
		{
			arr->add(f);
			f = 0;
		}
		i.close();
		JSONParser::saveFile(arr, "bd.json");
		cout << arr->asString() << endl;
	}
	else
	{
		cout << "Unable to open BDCSD.txt" << endl;
	}
	delete arr;
}
