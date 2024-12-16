#include <Trackable.h>
#include <string>

class Singleton:public Trackable
{
private:
	static Singleton* mpsInstance;
	Singleton(){ mAString = "Hi"; mAnInt = 12; };
	~Singleton() {};

	int mAnInt;
	std::string mAString;

public:
	static Singleton* getInstance();
	//static void createInstance();
	//static void destroyInstance();

	int getInt(){ return mAnInt; };
	const std::string& getString(){ return mAString; };
};