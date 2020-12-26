#include <string>
using namespace std;

class card{
	public:
	card(string Type, string Name);
	string returntype();
	string gettype();
	void movegraveyard();
	bool checkgraveyard();
	string getname();
	private:
	bool graveyard;
	string type;
	string name;
};
