#include <JSONAll.hpp>
#include <iostream>
#include <fstream>
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
		return get("Title");
	}
	void setDescription(string str)
	{
		set("Description", str);
	}
	string getDescription()
	{
		return get("Description");
	}
	void setDuration(int duration)
	{
		set("Duration", duration);
	}
	string getDuration()
	{
		return get("Duration");
	}
	JSONArray* actors()
	{
		return get("Actors");
	}
	JSONArray* genres()
	{
		return get("Genres");
	}
	void setId(int id)
	{
		set("Id", id);
	}
	int getId()
	{
		get("Id");
	}
};
int main()
{
	JSONObject *l = new JSONObject();
	ifstream i("BDCSD.txt", ifstream::in);
	if(i.is_open())
	{
		Film *f = 0;
		string line;
		while(getline(i, line))
		{
			
		}
		i.close();
	}
	else
	{
		cout << "Unable to open BDCSD.txt" << endl;
	}
	delete l;
}
