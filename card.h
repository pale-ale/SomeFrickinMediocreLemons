#include <string>
using namespace std;

class card{
	public:
	card(string Type, string Name);
	string returnType();
	string getType();
	void moveGraveyard();
	bool checkGraveyard();
	string getName();
	private:
	bool graveyard;
	string type;
	string name;
};
